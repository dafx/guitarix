declare id "amp";
declare name "Amplifier";

import("music.lib");
import("guitarix.lib");

gain = vslider(".amp.out_amp[name:Level]", 0, -20, 4, 0.1) : db2linear : smoothi(0.999);
process = *(gain);
