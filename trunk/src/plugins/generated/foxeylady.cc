// generated from file '../src/plugins/foxeylady.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "gx_faust_support.h"
#include "gx_plugin.h"
#include "trany.h"

namespace pluginlib {
namespace foxeylady {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	FAUSTFLOAT 	fslider0;
	double 	fRec6[2];
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	FAUSTFLOAT 	fslider1;
	double 	fRec7[2];
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	double 	fConst22;
	double 	fConst23;
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fConst27;
	double 	fConst28;
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fConst33;
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fConst38;
	double 	fConst39;
	double 	fConst40;
	double 	fRec8[7];
	double 	fConst41;
	double 	fConst42;
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	double 	fConst46;
	double 	fConst47;
	double 	fConst48;
	double 	fConst49;
	double 	fConst50;
	double 	fConst51;
	double 	fConst52;
	double 	fConst53;
	double 	fConst54;
	double 	fConst55;
	double 	fConst56;
	double 	fConst57;
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
	double 	fConst68;
	double 	fConst69;
	double 	fConst70;
	double 	fConst71;
	double 	fConst72;
	double 	fConst73;
	double 	fConst74;
	double 	fConst75;
	double 	fConst76;
	double 	fRec9[2];
	double 	fRec5[3];
	double 	fConst77;
	double 	fConst78;
	double 	fConst79;
	double 	fConst80;
	double 	fConst81;
	double 	fRec4[2];
	double 	fRec10[2];
	double 	fRec3[3];
	double 	fRec2[2];
	double 	fRec11[2];
	double 	fRec1[3];
	double 	fRec0[2];
	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int samplingFreq, PluginDef*);
	static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef*);
	static int register_params_static(const ParamReg& reg);
	static void del_instance(PluginDef *p);
public:
	Dsp();
	~Dsp();
};



Dsp::Dsp()
	: PluginDef() {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "foxeylady";
	name = N_("Foxey Lady");
	groups = 0;
	description = N_("Foxey Lady fuzz pedal"); // description (tooltip)
	category = N_("Fuzz");       // category
	shortname = N_("Foxey Lady");     // shortname
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = 0;
	register_params = register_params_static;
	load_ui = load_ui_f_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<7; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = double(iConst0);
	fConst2 = (5.24588897595767e-29 * fConst1);
	fConst3 = (6.94956080958259e-12 + (fConst1 * (1.71281273151154e-13 + (fConst1 * (1.29693461432975e-15 + (fConst1 * (3.61888994332083e-18 + (fConst1 * (2.89396306244108e-21 + (fConst1 * (7.02844574269719e-25 + fConst2)))))))))));
	fConst4 = (4.59387215604116e-29 * fConst1);
	fConst5 = ((fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (0 - (4.36933720361044e-25 + fConst4))) - 8.96539812308464e-22)) - 3.5938048928126e-19)) - 4.96738293767392e-17)) - 2.0568206880379e-15);
	fConst6 = (4.57704216569471e-29 * fConst1);
	fConst7 = ((fConst1 * ((fConst1 * ((fConst1 * (2.55877854891379e-22 + (fConst1 * (4.12221097685163e-25 + fConst6)))) - 9.9587457844786e-19)) - 4.94708666311112e-16)) - 7.32065571555064e-14);
	fConst8 = (3.28344197367049e-30 * fConst1);
	fConst9 = ((fConst1 * (4.33524374895714e-19 + (fConst1 * ((fConst1 * (1.8701619702637e-25 - fConst8)) - 2.16157324062859e-21)))) - 5.90848481409701e-18);
	fConst10 = (3.28344197367049e-28 * fConst1);
	fConst11 = ((fConst1 * (4.33524374895714e-17 + (fConst1 * ((fConst1 * (1.8701619702637e-23 - fConst10)) - 2.16157324062859e-19)))) - 5.90848481409701e-16);
	fConst12 = (6.42669378638762e-27 * fConst1);
	fConst13 = (4.84302033942378e-16 + (fConst1 * ((fConst1 * (1.79551930386446e-19 + (fConst1 * (fConst12 - 2.86240593005591e-23)))) - 3.55668379874028e-17)));
	fConst14 = (6.42669378638762e-29 * fConst1);
	fConst15 = (4.84302033942378e-18 + (fConst1 * ((fConst1 * (1.79551930386446e-21 + (fConst1 * (fConst14 - 2.86240593005591e-25)))) - 3.55668379874028e-19)));
	fConst16 = (6.94956080958259e-12 + (fConst1 * ((fConst1 * (1.29693461432975e-15 + (fConst1 * ((fConst1 * (2.89396306244108e-21 + (fConst1 * (fConst2 - 7.02844574269719e-25)))) - 3.61888994332083e-18)))) - 1.71281273151154e-13)));
	fConst17 = (2.0568206880379e-15 + (fConst1 * ((fConst1 * (3.5938048928126e-19 + (fConst1 * ((fConst1 * (4.36933720361044e-25 - fConst4)) - 8.96539812308464e-22)))) - 4.96738293767392e-17)));
	fConst18 = (7.32065571555064e-14 + (fConst1 * ((fConst1 * (9.9587457844786e-19 + (fConst1 * (2.55877854891379e-22 + (fConst1 * (fConst6 - 4.12221097685163e-25)))))) - 4.94708666311112e-16)));
	fConst19 = (3.1475333855746e-28 * fConst1);
	fConst20 = faustpower<2>(fConst1);
	fConst21 = (4.16973648574956e-11 + (fConst1 * ((fConst1 * (2.5938692286595e-15 + (fConst20 * ((fConst1 * (2.81137829707888e-24 - fConst19)) - 5.78792612488216e-21)))) - 6.85125092604618e-13)));
	fConst22 = (2.7563232936247e-28 * fConst1);
	fConst23 = (8.22728275215159e-15 + (fConst1 * ((fConst20 * (1.79307962461693e-21 + (fConst1 * (fConst22 - 1.74773488144418e-24)))) - 9.93476587534785e-17)));
	fConst24 = (2.74622529941683e-28 * fConst1);
	fConst25 = (2.92826228622026e-13 + (fConst1 * ((fConst20 * ((fConst1 * (1.64888439074065e-24 - fConst24)) - 5.11755709782759e-22)) - 9.89417332622223e-16)));
	fConst26 = (7.8688334639365e-28 * fConst1);
	fConst27 = (1.04243412143739e-10 + (fConst1 * ((fConst1 * ((fConst1 * (1.08566698299625e-17 + (fConst1 * ((fConst1 * (fConst26 - 3.51422287134859e-24)) - 2.89396306244108e-21)))) - 1.29693461432975e-15)) - 8.56406365755772e-13)));
	fConst28 = (6.89080823406175e-28 * fConst1);
	fConst29 = (1.02841034401895e-14 + (fConst1 * (4.96738293767392e-17 + (fConst1 * ((fConst1 * (8.96539812308464e-22 + (fConst1 * (2.18466860180522e-24 - fConst28)))) - 1.07814146784378e-18)))));
	fConst30 = (6.86556324854206e-28 * fConst1);
	fConst31 = (3.66032785777532e-13 + (fConst1 * (4.94708666311112e-16 + (fConst1 * ((fConst1 * ((fConst1 * (fConst30 - 2.06110548842582e-24)) - 2.55877854891379e-22)) - 2.98762373534358e-18)))));
	fConst32 = (1.38991216191652e-10 + (fConst20 * ((fConst20 * (1.15758522497643e-20 - (1.04917779519153e-27 * fConst20))) - 5.18773845731899e-15)));
	fConst33 = (1.98695317506957e-16 + (fConst20 * ((9.18774431208233e-28 * fConst20) - 3.58615924923386e-21)));
	fConst34 = (1.97883466524445e-15 + (fConst20 * (1.02351141956552e-21 - (9.15408433138942e-28 * fConst20))));
	fConst35 = (1.04243412143739e-10 + (fConst1 * (8.56406365755772e-13 + (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (3.51422287134859e-24 + fConst26)) - 2.89396306244108e-21)) - 1.08566698299625e-17)) - 1.29693461432975e-15)))));
	fConst36 = ((fConst1 * (4.96738293767392e-17 + (fConst1 * (1.07814146784378e-18 + (fConst1 * (8.96539812308464e-22 + (fConst1 * (0 - (2.18466860180522e-24 + fConst28))))))))) - 1.02841034401895e-14);
	fConst37 = ((fConst1 * (4.94708666311112e-16 + (fConst1 * (2.98762373534358e-18 + (fConst1 * ((fConst1 * (2.06110548842582e-24 + fConst30)) - 2.55877854891379e-22)))))) - 3.66032785777532e-13);
	fConst38 = (4.16973648574956e-11 + (fConst1 * (6.85125092604618e-13 + (fConst1 * (2.5938692286595e-15 + (fConst20 * ((fConst1 * (0 - (2.81137829707888e-24 + fConst19))) - 5.78792612488216e-21)))))));
	fConst39 = ((fConst1 * ((fConst20 * (1.79307962461693e-21 + (fConst1 * (1.74773488144418e-24 + fConst22)))) - 9.93476587534785e-17)) - 8.22728275215159e-15);
	fConst40 = ((fConst1 * ((fConst20 * ((fConst1 * (0 - (1.64888439074065e-24 + fConst24))) - 5.11755709782759e-22)) - 9.89417332622223e-16)) - 2.92826228622026e-13);
	fConst41 = (1.97006518420229e-29 * fConst1);
	fConst42 = ((fConst20 * (4.32314648125718e-21 + (fConst1 * (fConst41 - 7.48064788105479e-25)))) - 1.1816969628194e-17);
	fConst43 = (1.97006518420229e-27 * fConst1);
	fConst44 = ((fConst20 * (4.32314648125718e-19 + (fConst1 * (fConst43 - 7.48064788105479e-23)))) - 1.1816969628194e-15);
	fConst45 = (3.85601627183257e-26 * fConst1);
	fConst46 = (9.68604067884756e-16 + (fConst20 * ((fConst1 * (1.14496237202237e-22 - fConst45)) - 3.59103860772892e-19)));
	fConst47 = (3.85601627183257e-28 * fConst1);
	fConst48 = (9.68604067884756e-18 + (fConst20 * ((fConst1 * (1.14496237202237e-24 - fConst47)) - 3.59103860772892e-21)));
	fConst49 = (4.92516296050573e-29 * fConst1);
	fConst50 = (5.90848481409701e-18 + (fConst1 * ((fConst1 * (2.16157324062859e-21 + (fConst1 * (9.35080985131849e-25 - fConst49)))) - 1.30057312468714e-18)));
	fConst51 = (4.92516296050573e-27 * fConst1);
	fConst52 = (5.90848481409701e-16 + (fConst1 * ((fConst1 * (2.16157324062859e-19 + (fConst1 * (9.35080985131849e-23 - fConst51)))) - 1.30057312468714e-16)));
	fConst53 = (9.64004067958143e-26 * fConst1);
	fConst54 = ((fConst1 * (1.06700513962208e-16 + (fConst1 * ((fConst1 * (fConst53 - 1.43120296502796e-22)) - 1.79551930386446e-19)))) - 4.84302033942378e-16);
	fConst55 = (9.64004067958143e-28 * fConst1);
	fConst56 = ((fConst1 * (1.06700513962208e-18 + (fConst1 * ((fConst1 * (fConst55 - 1.43120296502796e-24)) - 1.79551930386446e-21)))) - 4.84302033942378e-18);
	fConst57 = (2.3633939256388e-17 + (fConst20 * ((6.56688394734098e-29 * fConst20) - 8.64629296251435e-21)));
	fConst58 = (2.3633939256388e-15 + (fConst20 * ((6.56688394734098e-27 * fConst20) - 8.64629296251435e-19)));
	fConst59 = ((fConst20 * (7.18207721545784e-19 - (1.28533875727752e-25 * fConst20))) - 1.93720813576951e-15);
	fConst60 = ((fConst20 * (7.18207721545784e-21 - (1.28533875727752e-27 * fConst20))) - 1.93720813576951e-17);
	fConst61 = (5.90848481409701e-18 + (fConst1 * (1.30057312468714e-18 + (fConst1 * (2.16157324062859e-21 + (fConst1 * (0 - (9.35080985131849e-25 + fConst49))))))));
	fConst62 = (5.90848481409701e-16 + (fConst1 * (1.30057312468714e-16 + (fConst1 * (2.16157324062859e-19 + (fConst1 * (0 - (9.35080985131849e-23 + fConst51))))))));
	fConst63 = ((fConst1 * ((fConst1 * ((fConst1 * (1.43120296502796e-22 + fConst53)) - 1.79551930386446e-19)) - 1.06700513962208e-16)) - 4.84302033942378e-16);
	fConst64 = ((fConst1 * ((fConst1 * ((fConst1 * (1.43120296502796e-24 + fConst55)) - 1.79551930386446e-21)) - 1.06700513962208e-18)) - 4.84302033942378e-18);
	fConst65 = ((fConst20 * (4.32314648125718e-21 + (fConst1 * (7.48064788105479e-25 + fConst41)))) - 1.1816969628194e-17);
	fConst66 = ((fConst20 * (4.32314648125718e-19 + (fConst1 * (7.48064788105479e-23 + fConst43)))) - 1.1816969628194e-15);
	fConst67 = (9.68604067884756e-16 + (fConst20 * ((fConst1 * (0 - (1.14496237202237e-22 + fConst45))) - 3.59103860772892e-19)));
	fConst68 = (9.68604067884756e-18 + (fConst20 * ((fConst1 * (0 - (1.14496237202237e-24 + fConst47))) - 3.59103860772892e-21)));
	fConst69 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (1.8701619702637e-25 + fConst8))) - 2.16157324062859e-21)) - 4.33524374895714e-19)) - 5.90848481409701e-18);
	fConst70 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (1.8701619702637e-23 + fConst10))) - 2.16157324062859e-19)) - 4.33524374895714e-17)) - 5.90848481409701e-16);
	fConst71 = (4.84302033942378e-16 + (fConst1 * (3.55668379874028e-17 + (fConst1 * (1.79551930386446e-19 + (fConst1 * (2.86240593005591e-23 + fConst12)))))));
	fConst72 = (4.84302033942378e-18 + (fConst1 * (3.55668379874028e-19 + (fConst1 * (1.79551930386446e-21 + (fConst1 * (2.86240593005591e-25 + fConst14)))))));
	fConst73 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst74 = (1 + fConst73);
	fConst75 = (0.027 / fConst74);
	fConst76 = (0 - ((1 - fConst73) / fConst74));
	fConst77 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst78 = (0 - fConst77);
	fConst79 = (1 + fConst77);
	fConst80 = (0.025 / fConst79);
	fConst81 = (0 - ((1 - fConst77) / fConst79));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (0.007000000000000006 * (1 - double(fslider0)));
	double 	fSlow1 = (0.007000000000000006 * double(fslider1));
	for (int i=0; i<count; i++) {
		fRec6[0] = ((0.993 * fRec6[1]) + fSlow0);
		double fTemp0 = ((fRec6[0] * ((fConst1 * (fConst7 + (fConst5 * fRec6[0]))) - 3.1163949818756e-12)) + fConst3);
		fRec7[0] = ((0.993 * fRec7[1]) + fSlow1);
		fRec8[0] = ((double)input0[i] - (((((((fRec8[1] * ((fRec6[0] * ((fConst1 * (fConst40 + (fConst39 * fRec6[0]))) - 1.86983698912536e-11)) + fConst38)) + (fRec8[2] * ((fRec6[0] * ((fConst1 * (fConst37 + (fConst36 * fRec6[0]))) - 4.6745924728134e-11)) + fConst35))) + (fRec8[3] * ((fRec6[0] * ((fConst20 * (fConst34 + (fConst33 * fRec6[0]))) - 6.23278996375121e-11)) + fConst32))) + (fRec8[4] * ((fRec6[0] * ((fConst1 * (fConst31 + (fConst29 * fRec6[0]))) - 4.6745924728134e-11)) + fConst27))) + (fRec8[5] * ((fRec6[0] * ((fConst1 * (fConst25 + (fConst23 * fRec6[0]))) - 1.86983698912536e-11)) + fConst21))) + (fRec8[6] * ((fRec6[0] * ((fConst1 * (fConst18 + (fConst17 * fRec6[0]))) - 3.1163949818756e-12)) + fConst16))) / fTemp0));
		fRec9[0] = ((fConst76 * fRec9[1]) + (fConst75 * (fRec5[1] + fRec5[2])));
		fRec5[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec9[0] + (fConst20 * ((((((((fRec8[0] * (((fRec6[0] * (fConst72 + (fConst71 * fRec7[0]))) + (fConst70 * fRec7[0])) + fConst69)) + (fRec8[1] * (((fRec6[0] * (fConst68 + (fConst67 * fRec7[0]))) + (fConst66 * fRec7[0])) + fConst65))) + (fRec8[2] * (((fRec6[0] * (fConst64 + (fConst63 * fRec7[0]))) + (fConst62 * fRec7[0])) + fConst61))) + (fRec8[3] * (((fRec6[0] * (fConst60 + (fConst59 * fRec7[0]))) + (fConst58 * fRec7[0])) + fConst57))) + (fRec8[4] * (((fRec6[0] * (fConst56 + (fConst54 * fRec7[0]))) + (fConst52 * fRec7[0])) + fConst50))) + (fRec8[5] * (((fRec6[0] * (fConst48 + (fConst46 * fRec7[0]))) + (fConst44 * fRec7[0])) + fConst42))) + (fRec8[6] * (((fRec6[0] * (fConst15 + (fConst13 * fRec7[0]))) + (fConst11 * fRec7[0])) + fConst9))) / fTemp0))) - 3.571981)) - 117.70440740740739);
		fRec4[0] = ((fConst81 * fRec4[1]) + (fConst80 * ((fConst77 * fRec5[0]) + (fConst78 * fRec5[1]))));
		fRec10[0] = ((fConst76 * fRec10[1]) + (fConst75 * (fRec3[1] + fRec3[2])));
		fRec3[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec10[0] + fRec4[0]) - 3.571981)) - 117.70440740740739);
		fRec2[0] = ((fConst81 * fRec2[1]) + (fConst80 * ((fConst77 * fRec3[0]) + (fConst78 * fRec3[1]))));
		fRec11[0] = ((fConst76 * fRec11[1]) + (fConst75 * (fRec1[1] + fRec1[2])));
		fRec1[0] = (Ftrany(TRANY_TABLE_7199P_68k, ((fRec11[0] + fRec2[0]) - 3.571981)) - 117.70440740740739);
		fRec0[0] = ((fConst81 * fRec0[1]) + (fConst80 * ((fConst77 * fRec1[0]) + (fConst78 * fRec1[1]))));
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec11[1] = fRec11[0];
		fRec2[1] = fRec2[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec10[1] = fRec10[0];
		fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec9[1] = fRec9[0];
		for (int i=6; i>0; i--) fRec8[i] = fRec8[i-1];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("foxeylady.Fuzz",N_("Fuzz"),"S","",&fslider0, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("foxeylady.Level",N_("Level"),"S","",&fslider1, 0.5, 0.0, 1.0, 0.01);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("foxeylady" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("Fuzz"), "Fuzz");
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("Level"), "Level");

    b.create_small_rackknobr(PARAM("Fuzz"), "Fuzz");
b.closeBox();

#undef PARAM
        return 0;
    }
	return -1;
}

int Dsp::load_ui_f_static(const UiBuilder& b, int form)
{
	return static_cast<Dsp*>(b.plugin)->load_ui_f(b, form);
}
PluginDef *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginDef *p)
{
	delete static_cast<Dsp*>(p);
}

} // end namespace foxeylady
} // end namespace pluginlib
