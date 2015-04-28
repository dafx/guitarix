// generated automatically
// DO NOT MODIFY!
declare id "fumaster";
declare name "Fuzz Master";
declare category "Distortion";
declare shortname "Fuzz Master";
declare description "Vintage Fuzz Master";

import("filter.lib");

process = pre : _<:*(dry),(*(wet) : iir((b0/a0,b1/a0,b2/a0,b3/a0,b4/a0,b5/a0,b6/a0),(a1/a0,a2/a0,a3/a0,a4/a0,a5/a0,a6/a0))):>_ with {
    LogPot(a, x) = if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = if(b, 1 - x, x);
    s = 0.993;
    fs = float(SR);
    pre = _;
    wet = vslider("wet_dry[name:wet/dry][tooltip:percentage of processed signal in output signal]",  100, 0, 100, 1) : /(100);
    dry = 1 - wet;

    
        Tone = vslider("Tone[name:Tone]", 0.5, 0, 1, 0.01) : Inverted(0) : LogPot(0) : smooth(s);
    
        Volume = vslider("Volume[name:Volume]", 0.1, 0, 1, 0.01) : Inverted(0) : LogPot(0) : smooth(s);
    
    b0 = Tone*(Volume*pow(fs,5)*(-1.41775270516311e-27*fs + 4.71779589725812e-22) + pow(fs,5)*(-1.41775270516311e-29*fs + 4.71779589725812e-24)) + Volume*pow(fs,4)*(fs*(1.41775270516311e-27*fs - 4.70999825737972e-22) - 2.59478774349197e-19) + pow(fs,4)*(fs*(1.41775270516311e-29*fs - 4.70999825737972e-24) - 2.59478774349197e-21);

    b1 = Tone*(Volume*pow(fs,5)*(8.50651623097868e-27*fs - 1.88711835890325e-21) + pow(fs,5)*(8.50651623097868e-29*fs - 1.88711835890325e-23)) + Volume*pow(fs,4)*(fs*(-8.50651623097868e-27*fs + 1.88399930295189e-21) + 5.18957548698393e-19) + pow(fs,4)*(fs*(-8.50651623097868e-29*fs + 1.88399930295189e-23) + 5.18957548698393e-21);

    b2 = Tone*(Volume*pow(fs,5)*(-2.12662905774467e-26*fs + 2.35889794862906e-21) + pow(fs,5)*(-2.12662905774467e-28*fs + 2.35889794862906e-23)) + Volume*pow(fs,4)*(fs*(2.12662905774467e-26*fs - 2.35499912868986e-21) + 2.59478774349197e-19) + pow(fs,4)*(fs*(2.12662905774467e-28*fs - 2.35499912868986e-23) + 2.59478774349197e-21);

    b3 = Tone*(2.83550541032623e-26*Volume*pow(fs,6) + 2.83550541032623e-28*pow(fs,6)) + Volume*pow(fs,4)*(-2.83550541032623e-26*pow(fs,2) - 1.03791509739679e-18) + pow(fs,4)*(-2.83550541032623e-28*pow(fs,2) - 1.03791509739679e-20);

    b4 = Tone*(Volume*pow(fs,5)*(-2.12662905774467e-26*fs - 2.35889794862906e-21) + pow(fs,5)*(-2.12662905774467e-28*fs - 2.35889794862906e-23)) + Volume*pow(fs,4)*(fs*(2.12662905774467e-26*fs + 2.35499912868986e-21) + 2.59478774349197e-19) + pow(fs,4)*(fs*(2.12662905774467e-28*fs + 2.35499912868986e-23) + 2.59478774349197e-21);

    b5 = Tone*(Volume*pow(fs,5)*(8.50651623097868e-27*fs + 1.88711835890325e-21) + pow(fs,5)*(8.50651623097868e-29*fs + 1.88711835890325e-23)) + Volume*pow(fs,4)*(fs*(-8.50651623097868e-27*fs - 1.88399930295189e-21) + 5.18957548698393e-19) + pow(fs,4)*(fs*(-8.50651623097868e-29*fs - 1.88399930295189e-23) + 5.18957548698393e-21);

    b6 = Tone*(Volume*pow(fs,5)*(-1.41775270516311e-27*fs - 4.71779589725812e-22) + pow(fs,5)*(-1.41775270516311e-29*fs - 4.71779589725812e-24)) + Volume*pow(fs,4)*(fs*(1.41775270516311e-27*fs + 4.70999825737972e-22) - 2.59478774349197e-19) + pow(fs,4)*(fs*(1.41775270516311e-29*fs + 4.70999825737972e-24) - 2.59478774349197e-21);

    a0 = Tone*(Tone*pow(fs,2)*(fs*(fs*(fs*(-1.00799506674223e-28*fs - 2.59175366383786e-25) - 4.35259230096405e-22) - 1.02583553103419e-19) - 2.16974948431515e-18) + fs*(fs*(fs*(fs*(fs*(-1.5016846937505e-31*fs + 4.96235474586462e-26) + 1.27917670111645e-22) + 2.16655787499057e-19) + 5.11414335446406e-17) + 1.08487474215758e-15)) + fs*(fs*(fs*(fs*(fs*(1.00949675143598e-28*fs + 3.20513868924941e-25) + 5.95381363906935e-22) + 3.72110810064138e-19) + 7.52873102578757e-17) + 3.94912717206244e-15) + 5.42437371078787e-14;

    a1 = Tone*(Tone*pow(fs,2)*(pow(fs,2)*(fs*(6.0479704004534e-28*fs + 1.03670146553514e-24) + 8.70518460192809e-22) - 4.3394989686303e-18) + fs*(fs*(pow(fs,2)*(fs*(9.01010816250298e-31*fs - 1.98494189834585e-25) - 2.5583534022329e-22) + 1.02282867089281e-16) + 4.3394989686303e-15)) + fs*(fs*(pow(fs,2)*(fs*(-6.0569805086159e-28*fs - 1.28205547569977e-24) - 1.19076272781387e-21) + 1.50574620515751e-16) + 1.57965086882498e-14) + 3.25462422647273e-13;

    a2 = Tone*(Tone*pow(fs,2)*(fs*(fs*(fs*(-1.51199260011335e-27*fs - 1.29587683191893e-24) + 4.35259230096405e-22) + 3.07750659310257e-19) + 2.16974948431515e-18) + fs*(fs*(fs*(fs*(fs*(-2.25252704062574e-30*fs + 2.48117737293231e-25) - 1.27917670111645e-22) - 6.4996736249717e-19) - 5.11414335446406e-17) + 5.42437371078788e-15)) + fs*(fs*(fs*(fs*(fs*(1.51424512715397e-27*fs + 1.60256934462471e-24) - 5.95381363906935e-22) - 1.11633243019242e-18) - 7.52873102578757e-17) + 1.97456358603122e-14) + 8.13656056618181e-13;

    a3 = Tone*(Tone*pow(fs,2)*(pow(fs,2)*(2.01599013348447e-27*pow(fs,2) - 1.74103692038562e-21) + 8.6789979372606e-18) + pow(fs,2)*(pow(fs,2)*(3.00336938750099e-30*pow(fs,2) + 5.11670680446579e-22) - 2.04565734178562e-16)) + pow(fs,2)*(pow(fs,2)*(-2.01899350287197e-27*pow(fs,2) + 2.38152545562774e-21) - 3.01149241031503e-16) + 1.08487474215758e-12;

    a4 = Tone*(Tone*pow(fs,2)*(fs*(fs*(fs*(-1.51199260011335e-27*fs + 1.29587683191893e-24) + 4.35259230096405e-22) - 3.07750659310257e-19) + 2.16974948431515e-18) + fs*(fs*(fs*(fs*(fs*(-2.25252704062574e-30*fs - 2.48117737293231e-25) - 1.27917670111645e-22) + 6.4996736249717e-19) - 5.11414335446406e-17) - 5.42437371078788e-15)) + fs*(fs*(fs*(fs*(fs*(1.51424512715397e-27*fs - 1.60256934462471e-24) - 5.95381363906935e-22) + 1.11633243019242e-18) - 7.52873102578757e-17) - 1.97456358603122e-14) + 8.13656056618181e-13;

    a5 = Tone*(Tone*pow(fs,2)*(pow(fs,2)*(fs*(6.0479704004534e-28*fs - 1.03670146553514e-24) + 8.70518460192809e-22) - 4.3394989686303e-18) + fs*(fs*(pow(fs,2)*(fs*(9.01010816250298e-31*fs + 1.98494189834585e-25) - 2.5583534022329e-22) + 1.02282867089281e-16) - 4.3394989686303e-15)) + fs*(fs*(pow(fs,2)*(fs*(-6.0569805086159e-28*fs + 1.28205547569977e-24) - 1.19076272781387e-21) + 1.50574620515751e-16) - 1.57965086882498e-14) + 3.25462422647273e-13;

    a6 = Tone*(Tone*pow(fs,2)*(fs*(fs*(fs*(-1.00799506674223e-28*fs + 2.59175366383786e-25) - 4.35259230096405e-22) + 1.02583553103419e-19) - 2.16974948431515e-18) + fs*(fs*(fs*(fs*(fs*(-1.5016846937505e-31*fs - 4.96235474586462e-26) + 1.27917670111645e-22) - 2.16655787499057e-19) + 5.11414335446406e-17) - 1.08487474215758e-15)) + fs*(fs*(fs*(fs*(fs*(1.00949675143598e-28*fs - 3.20513868924941e-25) + 5.95381363906935e-22) - 3.72110810064138e-19) + 7.52873102578757e-17) - 3.94912717206244e-15) + 5.42437371078787e-14;
};
