// generated from file '../src/LV2/faust/tonestack_ac15.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace tonestack_ac15 {

class Dsp: public PluginLV2 {
private:
	uint32_t fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fRec0[4];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fConst5;
	double 	fConst6;
	void connect(uint32_t port,void* data);
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);

	static void clear_state_f_static(PluginLV2*);
	static void init_static(uint32_t samplingFreq, PluginLV2*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2*);
	static void del_instance(PluginLV2 *p);
	static void connect_static(uint32_t port,void* data, PluginLV2 *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginLV2() {
	version = PLUGINLV2_VERSION;
	id = "AC-15";
	name = N_("AC-15");
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = 0;
	connect_ports = connect_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<4; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginLV2 *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = double(min(192000, max(1, fSamplingFreq)));
	fConst1 = (2 * fConst0);
	fConst2 = (1.0691560000000003e-08 * fConst1);
	fConst3 = faustpower<2>(fConst1);
	fConst4 = (3.2074680000000005e-08 * fConst1);
	fConst5 = (0.044206800000000004 * fConst0);
	fConst6 = (3 * fConst1);
	clear_state_f();
}

void Dsp::init_static(uint32_t samplingFreq, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
	double 	fSlow0 = exp((3.4 * (double(fslider0) - 1)));
	double 	fSlow1 = double(fslider1);
	double 	fSlow2 = (0.00022854915600000004 * fSlow1);
	double 	fSlow3 = (((fSlow1 * ((0.00012621831200000002 + (0.00022854915600000004 * fSlow0)) - fSlow2)) + (0.00010719478000000002 * fSlow0)) + 0.00010871476000000002);
	double 	fSlow4 = ((3.421299200000001e-08 * fSlow0) - (3.421299200000001e-08 * fSlow1));
	double 	fSlow5 = (1.0 + (fSlow0 + (93531720.34763868 * (fSlow1 * (2.3521432000000005e-08 + fSlow4)))));
	double 	fSlow6 = (fConst2 * fSlow5);
	double 	fSlow7 = (fConst1 * (0.036906800000000003 + ((0.01034 * fSlow1) + (0.022103400000000002 * fSlow0))));
	double 	fSlow8 = ((fSlow7 + (fConst3 * (fSlow6 - fSlow3))) - 1);
	double 	fSlow9 = (fConst4 * fSlow5);
	double 	fSlow10 = ((fSlow7 + (fConst3 * (fSlow3 - fSlow9))) - 3);
	double 	fSlow11 = ((fConst3 * (fSlow3 + fSlow9)) - (3 + fSlow7));
	double 	fSlow12 = (1.0 / ((fConst3 * (0 - (fSlow3 + fSlow6))) - (1 + fSlow7)));
	double 	fSlow13 = double(fslider2);
	double 	fSlow14 = (3.7947800000000004e-06 + (((1.5199800000000001e-06 * fSlow13) + (fSlow1 * (0.00022961831200000004 - fSlow2))) + (fSlow0 * (fSlow2 + 3.7947800000000004e-06))));
	double 	fSlow15 = ((fSlow1 * (3.421299200000001e-08 + fSlow4)) + (fSlow13 * ((1.0691560000000003e-08 * fSlow0) + (1.0691560000000003e-08 - (1.0691560000000003e-08 * fSlow1)))));
	double 	fSlow16 = (fConst1 * fSlow15);
	double 	fSlow17 = (1.0 + (fSlow0 + ((0.4678013337314621 * fSlow1) + (0.0046780133373146215 * fSlow13))));
	double 	fSlow18 = (fConst5 * fSlow17);
	double 	fSlow19 = (fSlow18 + (fConst3 * (fSlow16 - fSlow14)));
	double 	fSlow20 = (fConst6 * fSlow15);
	double 	fSlow21 = (fSlow18 + (fConst3 * (fSlow14 - fSlow20)));
	double 	fSlow22 = (fConst1 * (0 - (0.022103400000000002 * fSlow17)));
	double 	fSlow23 = (fSlow22 + (fConst3 * (fSlow14 + fSlow20)));
	double 	fSlow24 = (fSlow22 - (fConst3 * (fSlow14 + fSlow16)));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((double)input0[i] - (fSlow12 * (((fSlow11 * fRec0[1]) + (fSlow10 * fRec0[2])) + (fSlow8 * fRec0[3]))));
		output0[i] = (FAUSTFLOAT)(fSlow12 * ((((fSlow24 * fRec0[0]) + (fSlow23 * fRec0[1])) + (fSlow21 * fRec0[2])) + (fSlow19 * fRec0[3])));
		// post processing
		for (int i=3; i>0; i--) fRec0[i] = fRec0[i-1];
	}
#undef fslider0
#undef fslider1
#undef fslider2
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case BASS: 
		fslider0_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case MIDDLE: 
		fslider1_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	case TREBLE: 
		fslider2_ = (float*)data; // , 0.5, 0.0, 1.0, 0.01 
		break;
	default:
		break;
	}
}

void Dsp::connect_static(uint32_t port,void* data, PluginLV2 *p)
{
	static_cast<Dsp*>(p)->connect(port, data);
}


PluginLV2 *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginLV2 *p)
{
	delete static_cast<Dsp*>(p);
}

/*
typedef enum
{
   BASS, 
   MIDDLE, 
   TREBLE, 
} PortIndex;
*/

} // end namespace tonestack_ac15
