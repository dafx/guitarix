/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
 * Copyright (C) 2011 Pete Shorthose
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * --------------------------------------------------------------------------
 */

#pragma once

#include <errno.h>

namespace gx_engine {

/****************************************************************
 ** class ModuleSelector
 */

class ModuleSelector {
public:
    virtual ~ModuleSelector() {}
    virtual void set_module() = 0;
};


/****************************************************************
 ** class ProcessingChainBase
 ** members and methods accessed by the rt thread are marked RT
 */

class ProcessingChainBase {
public:
    enum RampMode { ramp_mode_down_dead, ramp_mode_down, ramp_mode_up_dead, ramp_mode_up, ramp_mode_off };
private:
    sem_t sync_sem; // RT
    list<Plugin*> to_release;
    int ramp_value; // RT
    RampMode ramp_mode; // RT
    bool stopped;
protected:
    int steps_up;		// RT; >= 1
    int steps_up_dead;		// RT; >= 0
    int steps_down;		// RT; >= 1
    volatile bool latch; // RT; set between commit and end of rt cycle
    list<Plugin*> modules;
    inline void set_ramp_value(int n) { g_atomic_int_set(&ramp_value, n); } // RT
    inline void set_ramp_mode(RampMode n) { g_atomic_int_set(&ramp_mode, n); } // RT
    void try_set_ramp_mode(RampMode oldmode, RampMode newmode, int oldrv, int newrv); // RT
public:
    bool next_commit_needs_ramp;
    ProcessingChainBase();
    inline RampMode get_ramp_mode() {
      return static_cast<RampMode>(g_atomic_int_get(&ramp_mode)); // RT
    }
    inline int get_ramp_value() { return g_atomic_int_get(&ramp_value); } // RT
    void set_samplerate(int samplerate);
    bool set_plugin_list(const list<Plugin*> &p);
    void clear_module_states();
    void post_rt_finished() { // RT
	int val;
	latch = false;
	if (sem_getvalue(&sync_sem, &val) == 0 && val == 0) {
	    sem_post(&sync_sem);
	}
    }
    void wait_rt_finished() {
	if (stopped) {
	    return;
	}
	while (sem_wait(&sync_sem) == EINTR);
    }
    inline void wait_latch() {
	if (latch) {
	    wait_rt_finished();
	}
    }
    inline bool check_release() {
	return !to_release.empty();
    }
    void release();
    void wait_ramp_down_finished() {
	if (stopped) {
	    return;
	}
	while (ramp_mode == ramp_mode_down) {
	    wait_rt_finished();
	}
    }
    inline void start_ramp_up() { set_ramp_value(0); set_ramp_mode(ramp_mode_up_dead); }
    inline void start_ramp_down() { set_ramp_value(steps_down); set_ramp_mode(ramp_mode_down); }
    inline void set_down_dead() { set_ramp_mode(ramp_mode_down_dead); }
    inline void set_stopped(bool v) { stopped = v; }
};


/****************************************************************
 ** template class ThreadSafeChainPointer
 ** members and methods accessed by the rt thread are marked RT
 */

template <class F>
class ThreadSafeChainPointer: public ProcessingChainBase {
private:
    F *rack_order_ptr[2]; // RT
    int size[2];
    int current_index;
    F *current_pointer;
    void setsize(int n);
    inline F get_audio(PluginDef *p);
protected:
    F *processing_pointer; // RT
    inline F* get_rt_chain() { return reinterpret_cast<F*>(g_atomic_pointer_get(&processing_pointer)); } // RT
public:
    ThreadSafeChainPointer();
    ~ThreadSafeChainPointer();
    inline void empty_chain() {
	list<Plugin*> p;
	if (set_plugin_list(p)) {
	    commit(true);
	}
    }
    void commit(bool clear);
};

typedef void (*monochainorder)(int count, float *output, float *output1,
			       PluginDef *plugin);
typedef void (*stereochainorder)(int count, float* input, float* input1,
				 float *output, float *output1, PluginDef *plugin);

struct monochain_data {
    monochainorder func;
    PluginDef      *plugin;
    monochain_data(monochainorder func_, PluginDef *plugin_): func(func_), plugin(plugin_) {}
    monochain_data() {}
    const monochain_data& operator=(const monochain_data& d) { func = d.func; plugin = d.plugin; return *this; }
};

struct stereochain_data {
    stereochainorder func;
    PluginDef       *plugin;
    stereochain_data(stereochainorder func_, PluginDef *plugin_): func(func_), plugin(plugin_) {}
    stereochain_data() {}
};

template <>
inline monochain_data ThreadSafeChainPointer<monochain_data>::get_audio(PluginDef *p)
{
    return monochain_data(p->mono_audio, p);
}

template <>
inline stereochain_data ThreadSafeChainPointer<stereochain_data>::get_audio(PluginDef *p)
{
    return stereochain_data(p->stereo_audio, p);
}

template <class F>
ThreadSafeChainPointer<F>::ThreadSafeChainPointer():
    rack_order_ptr(),
    size(),
    current_index(0),
    current_pointer(),
    processing_pointer() {
    setsize(1);
    current_pointer[0].func = 0;
    processing_pointer = current_pointer;
    current_index = 1;
    current_pointer = rack_order_ptr[1];
}

template <class F>
ThreadSafeChainPointer<F>::~ThreadSafeChainPointer() {
    delete rack_order_ptr[0];
    delete rack_order_ptr[1];
}

template <class F>
void ThreadSafeChainPointer<F>::setsize(int n)
{
    if (n <= size[current_index]) {
	return;
    }
    delete rack_order_ptr[current_index];
    rack_order_ptr[current_index] = new F[n];
    size[current_index] = n;
    current_pointer = rack_order_ptr[current_index];
}

template <class F>
void ThreadSafeChainPointer<F>::commit(bool clear) {
    setsize(modules.size()+1);  // leave one slot for 0 marker
    int active_counter = 0;
    for (list<Plugin*>::const_iterator p = modules.begin(); p != modules.end(); p++) {
	PluginDef* pd = (*p)->pdef;
	if (pd->activate_plugin) {
	    pd->activate_plugin(true, pd);
	} else if (pd->clear_state && clear) {
	    pd->clear_state(pd);
	}
	F f = get_audio(pd);
	assert(f.func);
	current_pointer[active_counter++] = f;
    }
    current_pointer[active_counter].func = 0;
    g_atomic_pointer_set(&processing_pointer, current_pointer);
    latch = true;
    current_index = (current_index+1) % 2;
    current_pointer = rack_order_ptr[current_index];
}

/****************************************************************
 ** class MonoModuleChain, class StereoModuleChain
 */

class MonoModuleChain: public ThreadSafeChainPointer<monochain_data> {
public:
    MonoModuleChain(): ThreadSafeChainPointer<monochain_data>() {}
    void process(int count, float *input, float *output);
    inline void print() { printlist("Mono", modules); }
};

class StereoModuleChain: public ThreadSafeChainPointer<stereochain_data> {
public:
    StereoModuleChain(): ThreadSafeChainPointer<stereochain_data>() {}
    void process(int count, float *input, float *output1, float *output2);
    inline void print() { printlist("Stereo", modules); }
};


/****************************************************************
 ** class ModuleSequencer
 */

class ModuleSequencer {
protected:
    list<ModuleSelector*> selectors;
    bool rack_changed;
    int audio_mode;
    int policy;
    int priority;
public:
    PluginList pluginlist;
    enum GxEngineState {
	kEngineOff    = 0,
	kEngineOn     = 1,
	kEngineBypass = 2
    };
    MonoModuleChain mono_chain;
    StereoModuleChain stereo_chain;
    enum StateFlag {
	SF_NO_CONNECTION = 0x01,
	SF_JACK_RECONFIG = 0x02,
	SF_INITIALIZING  = 0x04,
    };
    int stateflags;
    sigc::signal<void, unsigned int> buffersize_change;
    sigc::signal<void, unsigned int> samplerate_change;
public:
    ModuleSequencer();
    ~ModuleSequencer();
    void init(unsigned int samplerate, unsigned int buffersize,
	      int policy, int priority);
    void get_sched_priority(int &policy, int &priority, int prio_dim = 0);
    void set_samplerate(unsigned int samplerate);
    void set_buffersize(unsigned int buffersize);
    void clear_module_states() {
	mono_chain.clear_module_states();
	stereo_chain.clear_module_states();
    }
    void start_ramp_up() {
	mono_chain.start_ramp_up();
	stereo_chain.start_ramp_up();
    }
    void start_ramp_down() {
	mono_chain.start_ramp_down();
	stereo_chain.start_ramp_down();
    }
    void wait_ramp_down_finished() {
	mono_chain.wait_ramp_down_finished();
	stereo_chain.wait_ramp_down_finished();
    }
    void ramp_down() {
	start_ramp_down();
	wait_ramp_down_finished();
    }
    void set_down_dead() {
	mono_chain.set_down_dead();
	stereo_chain.set_down_dead();
    }
    void add_selector(ModuleSelector& sel);
    bool prepare_module_lists();
    void commit_module_lists();
    void set_rack_changed() { rack_changed = true; }
    void clear_rack_changed() { rack_changed = false; }
    bool update_module_lists() {
	if (prepare_module_lists()) {
	    commit_module_lists();
	    return true;
	}
	return false;
    }
    inline void check_module_lists() {
	if (mono_chain.check_release()) {
	    mono_chain.release();
	}
	if (stereo_chain.check_release()) {
	    stereo_chain.release();
	}
	if (rack_changed) {
	    update_module_lists();
	}
    }
    void set_stateflag(StateFlag flag);
    void clear_stateflag(StateFlag flag);
    void set_state(GxEngineState state);
    GxEngineState get_state();
    void registerParameter(gx_gui::ParameterGroups& groups);
};

} /* end of gx_engine namespace */