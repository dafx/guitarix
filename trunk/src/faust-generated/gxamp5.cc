// generated from file '../src/faust/gxamp5.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)

#include "valve.h"

namespace gxamp5 {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fRec2[2];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec3[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec5[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fRec13[2];
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fRec14[2];
	double 	fRec12[3];
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fRec11[2];
	double 	fConst14;
	double 	fRec10[2];
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	double 	fRec15[2];
	double 	fRec9[3];
	double 	fRec8[2];
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	double 	fConst22;
	double 	fRec16[2];
	double 	fRec7[3];
	double 	fRec6[2];
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
	double 	fConst41;
	double 	fConst42;
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	double 	fConst46;
	double 	fConst47;
	double 	fConst48;
	double 	fRec25[3];
	double 	fVec0[2];
	double 	fConst49;
	double 	fRec24[2];
	double 	fConst50;
	double 	fConst51;
	double 	fConst52;
	double 	fRec23[2];
	double 	fRec22[3];
	double 	fVec1[2];
	double 	fConst53;
	double 	fConst54;
	double 	fConst55;
	double 	fRec21[2];
	double 	fRec20[3];
	double 	fVec2[2];
	double 	fConst56;
	double 	fConst57;
	double 	fConst58;
	double 	fRec19[2];
	double 	fRec18[3];
	double 	fConst59;
	double 	fConst60;
	double 	fConst61;
	double 	fRec28[2];
	double 	fRec27[3];
	double 	fConst62;
	double 	fRec26[3];
	double 	fConst63;
	double 	fConst64;
	double 	fConst65;
	double 	fRec32[2];
	double 	fRec31[3];
	double 	fConst66;
	double 	fRec30[3];
	double 	fRec29[3];
	double 	fConst67;
	double 	fRec34[2];
	double 	fRec33[3];
	double 	fConst68;
	double 	fVec3[2];
	double 	fRec17[2];
	double 	fVec4[2];
	double 	fRec4[2];
	double 	fRec1[3];
	double 	fRec0[2];
	double 	fRec37[2];
	double 	fRec36[3];
	double 	fRec35[2];
	void clear_state_f();
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
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
	id = "pre 12ax7/ master 6V6";
	name = N_("pre 12ax7/ master 6V6");
	groups = 0;
	description = ""; // description (tooltip)
	category = "";       // category
	shortname = "";     // shortname
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = 0;
	register_params = register_params_static;
	load_ui = 0;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<3; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<3; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec23[i] = 0;
	for (int i=0; i<3; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec20[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<3; i++) fRec18[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec27[i] = 0;
	for (int i=0; i<3; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<3; i++) fRec31[i] = 0;
	for (int i=0; i<3; i++) fRec30[i] = 0;
	for (int i=0; i<3; i++) fRec29[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<3; i++) fRec33[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec37[i] = 0;
	for (int i=0; i<3; i++) fRec36[i] = 0;
	for (int i=0; i<2; i++) fRec35[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0 / tan((20517.741620594938 / double(iConst0))));
	fConst2 = (1 + fConst1);
	fConst3 = (0.0082 / fConst2);
	fConst4 = (0 - ((1 - fConst1) / fConst2));
	fConst5 = (1.0 / tan((270.1769682087222 / double(iConst0))));
	fConst6 = (1 + fConst5);
	fConst7 = (0.027 / fConst6);
	fConst8 = (0 - ((1 - fConst5) / fConst6));
	fConst9 = (1.0 / tan((97.38937226128358 / double(iConst0))));
	fConst10 = (0 - fConst9);
	fConst11 = (1 + fConst9);
	fConst12 = (0.025 / fConst11);
	fConst13 = (0 - ((1 - fConst9) / fConst11));
	fConst14 = (1.0 / fConst2);
	fConst15 = (1.0 / tan((414.6902302738527 / double(iConst0))));
	fConst16 = (1 + fConst15);
	fConst17 = (0.015 / fConst16);
	fConst18 = (0 - ((1 - fConst15) / fConst16));
	fConst19 = (1.0 / tan((609.4689747964198 / double(iConst0))));
	fConst20 = (1 + fConst19);
	fConst21 = (0.0082 / fConst20);
	fConst22 = (0 - ((1 - fConst19) / fConst20));
	fConst23 = tan((942.4777960769379 / double(iConst0)));
	fConst24 = (1.0 / faustpower<2>(fConst23));
	fConst25 = (2 * (1 - fConst24));
	fConst26 = (1.0 / fConst23);
	fConst27 = (1 + ((fConst26 - 1.0000000000000004) / fConst23));
	fConst28 = (1.0 / (1 + ((fConst26 + 1.0000000000000004) / fConst23)));
	fConst29 = tan((3769.9111843077517 / double(iConst0)));
	fConst30 = (1.0 / faustpower<2>(fConst29));
	fConst31 = (2 * (1 - fConst30));
	fConst32 = (1.0 / fConst29);
	fConst33 = (1 + ((fConst32 - 1.0000000000000004) / fConst29));
	fConst34 = (1 + ((fConst32 + 1.0000000000000004) / fConst29));
	fConst35 = (1.0 / fConst34);
	fConst36 = tan((10053.096491487338 / double(iConst0)));
	fConst37 = (1.0 / faustpower<2>(fConst36));
	fConst38 = (2 * (1 - fConst37));
	fConst39 = (1.0 / fConst36);
	fConst40 = (1 + ((fConst39 - 1.0000000000000004) / fConst36));
	fConst41 = (1 + ((1.0000000000000004 + fConst39) / fConst36));
	fConst42 = (1.0 / fConst41);
	fConst43 = tan((47123.8898038469 / double(iConst0)));
	fConst44 = (2 * (1 - (1.0 / faustpower<2>(fConst43))));
	fConst45 = (1.0 / fConst43);
	fConst46 = (1 + ((fConst45 - 1.414213562373095) / fConst43));
	fConst47 = (1 + ((1.414213562373095 + fConst45) / fConst43));
	fConst48 = (1.0 / fConst47);
	fConst49 = (1.0 / (fConst11 * fConst47));
	fConst50 = (1 + fConst39);
	fConst51 = (1.0 / fConst50);
	fConst52 = (0 - ((1 - fConst39) / fConst50));
	fConst53 = (1 + fConst32);
	fConst54 = (1.0 / (fConst53 * fConst41));
	fConst55 = (0 - ((1 - fConst32) / fConst53));
	fConst56 = (1 + fConst26);
	fConst57 = (1.0 / (fConst56 * fConst34));
	fConst58 = (0 - ((1 - fConst26) / fConst56));
	fConst59 = (1 + ((fConst26 - 1.0) / fConst23));
	fConst60 = (1.0 / (1 + ((1.0 + fConst26) / fConst23)));
	fConst61 = (0 - fConst32);
	fConst62 = (2 * (0 - fConst30));
	fConst63 = (1 + ((fConst32 - 1.0) / fConst29));
	fConst64 = (1.0 / (1 + ((1.0 + fConst32) / fConst29)));
	fConst65 = (0 - fConst39);
	fConst66 = (2 * (0 - fConst37));
	fConst67 = (0 - fConst26);
	fConst68 = (2 * (0 - fConst24));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
#define fslider3 (*fslider3_)
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider0))));
	double 	fSlow1 = (1.000000000000001e-05 * double(fslider1));
	double 	fSlow2 = double(fslider2);
	double 	fSlow3 = (2 * (fSlow2 - 0.5));
	double 	fSlow4 = (1 - max((double)0, fSlow3));
	double 	fSlow5 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider3))));
	double 	fSlow6 = (1.25 * fSlow2);
	double 	fSlow7 = (fConst28 * pow(1e+01,(0.9 * fSlow2)));
	double 	fSlow8 = pow(1e+01,(1.2 * fSlow2));
	double 	fSlow9 = pow(1e+01,(0.8 * fSlow2));
	double 	fSlow10 = (fConst28 * pow(1e+01,(2 * fSlow2)));
	double 	fSlow11 = (1 - max((double)0, (0 - fSlow3)));
	for (int i=0; i<count; i++) {
		fRec2[0] = ((fConst4 * fRec2[1]) + (fConst3 * (fRec1[1] + fRec1[2])));
		fRec3[0] = ((0.999 * fRec3[1]) + fSlow0);
		fRec5[0] = (fSlow1 + (0.999 * fRec5[1]));
		double fTemp0 = (1 - fRec5[0]);
		fRec13[0] = ((0.999 * fRec13[1]) + fSlow5);
		fRec14[0] = ((fConst8 * fRec14[1]) + (fConst7 * (fRec12[1] + fRec12[2])));
		fRec12[0] = (Ftube(TUBE_TABLE_12AX7_68k, ((fRec14[0] + ((double)input0[i] * fRec13[0])) - 1.581656)) - 191.42014814814814);
		fRec11[0] = ((fConst13 * fRec11[1]) + (fConst12 * ((fConst9 * fRec12[0]) + (fConst10 * fRec12[1]))));
		fRec10[0] = ((fConst4 * fRec10[1]) + (fConst14 * (fRec11[0] + fRec11[1])));
		fRec15[0] = ((fConst18 * fRec15[1]) + (fConst17 * (fRec9[1] + fRec9[2])));
		fRec9[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec15[0] + fRec10[0]) - 1.204285)) - 169.71433333333334);
		fRec8[0] = ((fConst13 * fRec8[1]) + (fConst12 * ((fConst9 * fRec9[0]) + (fConst10 * fRec9[1]))));
		fRec16[0] = ((fConst22 * fRec16[1]) + (fConst21 * (fRec7[1] + fRec7[2])));
		fRec7[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec16[0] + fRec8[0]) - 0.840703)) - 147.47524390243905);
		fRec6[0] = ((fConst13 * fRec6[1]) + (fConst12 * ((fConst9 * fRec7[0]) + (fConst10 * fRec7[1]))));
		fRec25[0] = ((fRec6[0] * fRec5[0]) - (fConst48 * ((fConst46 * fRec25[2]) + (fConst44 * fRec25[1]))));
		double fTemp1 = (fRec25[2] + (fRec25[0] + (2 * fRec25[1])));
		fVec0[0] = fTemp1;
		fRec24[0] = ((fConst13 * fRec24[1]) + (fConst49 * ((fConst9 * fVec0[0]) + (fConst10 * fVec0[1]))));
		fRec23[0] = ((fConst52 * fRec23[1]) + (fConst51 * (fRec24[0] + fRec24[1])));
		fRec22[0] = (fRec23[0] - (fConst42 * ((fConst40 * fRec22[2]) + (fConst38 * fRec22[1]))));
		double fTemp2 = (fRec22[2] + (fRec22[0] + (2 * fRec22[1])));
		fVec1[0] = fTemp2;
		fRec21[0] = ((fConst55 * fRec21[1]) + (fConst54 * (fVec1[0] + fVec1[1])));
		fRec20[0] = (fRec21[0] - (fConst35 * ((fConst33 * fRec20[2]) + (fConst31 * fRec20[1]))));
		double fTemp3 = (fRec20[2] + (fRec20[0] + (2 * fRec20[1])));
		fVec2[0] = fTemp3;
		fRec19[0] = ((fConst58 * fRec19[1]) + (fConst57 * (fVec2[0] + fVec2[1])));
		fRec18[0] = (fRec19[0] - (fConst28 * ((fConst27 * fRec18[2]) + (fConst25 * fRec18[1]))));
		double fTemp4 = max((double)-1, min((double)1, (fSlow7 * (fRec18[2] + (fRec18[0] + (2 * fRec18[1]))))));
		double fTemp5 = (fConst25 * fRec26[1]);
		fRec28[0] = ((fConst55 * fRec28[1]) + (fConst54 * ((fConst32 * fVec1[0]) + (fConst61 * fVec1[1]))));
		fRec27[0] = (fRec28[0] - (fConst35 * ((fConst33 * fRec27[2]) + (fConst31 * fRec27[1]))));
		fRec26[0] = ((fConst35 * (((fConst30 * fRec27[0]) + (fConst62 * fRec27[1])) + (fConst30 * fRec27[2]))) - (fConst60 * ((fConst59 * fRec26[2]) + fTemp5)));
		double fTemp6 = max((double)-1, min((double)1, (fSlow8 * (fRec26[2] + (fConst60 * (fTemp5 + (fConst59 * fRec26[0])))))));
		double fTemp7 = (fConst25 * fRec29[1]);
		double fTemp8 = (fConst31 * fRec30[1]);
		fRec32[0] = ((fConst52 * fRec32[1]) + (fConst51 * ((fConst39 * fRec24[0]) + (fConst65 * fRec24[1]))));
		fRec31[0] = (fRec32[0] - (fConst42 * ((fConst40 * fRec31[2]) + (fConst38 * fRec31[1]))));
		fRec30[0] = ((fConst42 * (((fConst37 * fRec31[0]) + (fConst66 * fRec31[1])) + (fConst37 * fRec31[2]))) - (fConst64 * ((fConst63 * fRec30[2]) + fTemp8)));
		fRec29[0] = ((fRec30[2] + (fConst64 * (fTemp8 + (fConst63 * fRec30[0])))) - (fConst60 * ((fConst59 * fRec29[2]) + fTemp7)));
		double fTemp9 = max((double)-1, min((double)1, (fSlow9 * (fRec29[2] + (fConst60 * (fTemp7 + (fConst59 * fRec29[0])))))));
		fRec34[0] = ((fConst58 * fRec34[1]) + (fConst57 * ((fConst26 * fVec2[0]) + (fConst67 * fVec2[1]))));
		fRec33[0] = (fRec34[0] - (fConst28 * ((fConst27 * fRec33[2]) + (fConst25 * fRec33[1]))));
		double fTemp10 = max((double)-1, min((double)1, (fSlow10 * (((fConst24 * fRec33[0]) + (fConst68 * fRec33[1])) + (fConst24 * fRec33[2])))));
		double fTemp11 = ((1.584893192 * ((fTemp10 * (1 - (0.3333333333333333 * faustpower<2>(fTemp10)))) + ((fTemp9 * (1 - (0.3333333333333333 * faustpower<2>(fTemp9)))) + (0.8413951417869425 * (fTemp6 * (1 - (0.3333333333333333 * faustpower<2>(fTemp6)))))))) + (1.2589412 * (fTemp4 * (1 - (0.3333333333333333 * faustpower<2>(fTemp4))))));
		fVec3[0] = fTemp11;
		fRec17[0] = ((fConst4 * fRec17[1]) + (fConst14 * (fVec3[0] + fVec3[1])));
		double fTemp12 = ((fSlow11 * fRec17[0]) + (fRec6[0] * ((fTemp0 * (1 + (fSlow6 * ((4 - (4 * fabs((fRec6[0] * fTemp0)))) - 1)))) + (fSlow4 * fRec5[0]))));
		fVec4[0] = fTemp12;
		fRec4[0] = ((fConst4 * fRec4[1]) + (fConst14 * (fVec4[0] + fVec4[1])));
		double fTemp13 = (fRec4[0] * fRec3[0]);
		fRec1[0] = (Ftube(TUBE_TABLE_6V6_68k, ((fTemp13 + fRec2[0]) - 1.13074)) - 112.10487804878048);
		fRec0[0] = ((fConst13 * fRec0[1]) + (fConst12 * ((fConst9 * fRec1[0]) + (fConst10 * fRec1[1]))));
		fRec37[0] = ((fConst4 * fRec37[1]) + (fConst3 * (fRec36[1] + fRec36[2])));
		fRec36[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec37[0] + fTemp13) - 1.130462)) - 112.13878048780487);
		fRec35[0] = ((fConst13 * fRec35[1]) + (fConst12 * ((fConst9 * fRec36[0]) + (fConst10 * fRec36[1]))));
		output0[i] = (FAUSTFLOAT)(fRec35[0] + fRec0[0]);
		// post processing
		fRec35[1] = fRec35[0];
		fRec36[2] = fRec36[1]; fRec36[1] = fRec36[0];
		fRec37[1] = fRec37[0];
		fRec0[1] = fRec0[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec4[1] = fRec4[0];
		fVec4[1] = fVec4[0];
		fRec17[1] = fRec17[0];
		fVec3[1] = fVec3[0];
		fRec33[2] = fRec33[1]; fRec33[1] = fRec33[0];
		fRec34[1] = fRec34[0];
		fRec29[2] = fRec29[1]; fRec29[1] = fRec29[0];
		fRec30[2] = fRec30[1]; fRec30[1] = fRec30[0];
		fRec31[2] = fRec31[1]; fRec31[1] = fRec31[0];
		fRec32[1] = fRec32[0];
		fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
		fRec27[2] = fRec27[1]; fRec27[1] = fRec27[0];
		fRec28[1] = fRec28[0];
		fRec18[2] = fRec18[1]; fRec18[1] = fRec18[0];
		fRec19[1] = fRec19[0];
		fVec2[1] = fVec2[0];
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fVec1[1] = fVec1[0];
		fRec22[2] = fRec22[1]; fRec22[1] = fRec22[0];
		fRec23[1] = fRec23[0];
		fRec24[1] = fRec24[0];
		fVec0[1] = fVec0[0];
		fRec25[2] = fRec25[1]; fRec25[1] = fRec25[0];
		fRec6[1] = fRec6[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec16[1] = fRec16[0];
		fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec15[1] = fRec15[0];
		fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fRec12[2] = fRec12[1]; fRec12[1] = fRec12[0];
		fRec14[1] = fRec14[0];
		fRec13[1] = fRec13[0];
		fRec5[1] = fRec5[0];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
	}
#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	fslider2_ = reg.registerVar("gxdistortion.drive","","SA","",&fslider2, 0.35, 0.0, 1.0, 0.01);
	fslider1_ = reg.registerVar("gxdistortion.wet_dry","","SA","",&fslider1, 1e+02, 0.0, 1e+02, 1.0);
	fslider3_ = reg.registerVar("amp2.stage1.Pregain","","SA","",&fslider3, -6.0, -2e+01, 2e+01, 0.1);
	fslider0_ = reg.registerVar("amp2.stage2.gain1","","SA","",&fslider0, -6.0, -2e+01, 2e+01, 0.1);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

PluginDef *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginDef *p)
{
	delete static_cast<Dsp*>(p);
}

} // end namespace gxamp5
