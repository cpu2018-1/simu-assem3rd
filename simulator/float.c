#include <math.h>
#include <stdio.h>
#include "float.h"

//必要に応じて実装を変更してください

float fadd(float a, float b){
    unsigned int x1,x2,x1a,x2a,s1a,s2a,sy,e1a,e2a,ey,m1a,m2a,my;
    unsigned int sm,m1b,m2b,mya,se,eya,eyb,myb,y;
    int i,bit;
    float r;

    x1 = *((unsigned int *)&a);
    x2 = *((unsigned int *)&b);
    if((x1 & 0x7fffffff) < (x2 & 0x7fffffff)){
	x1a = x2;
	x2a = x1;
    } else {
	x1a = x1;
	x2a = x2;
    }
    s1a = x1a >> 31;
    e1a = (x1a >> 23) & 0xff;
    m1a = x1a & 0x7fffff;
    s2a = x2a >> 31;
    e2a = (x2a >> 23) & 0xff;
    m2a = x2a & 0x7fffff;
    sm = e1a - e2a;
    m1b = (1 << 24) | (m1a << 1);
    if(sm < 32) m2b = ((1 << 24) | (m2a << 1)) >> sm;
    else m2b = 0;
    if(s1a == s2a) mya = m1b + m2b;
    else mya = m1b - m2b;
    for(i = 0;i < 26;i++){
	bit = (mya >> (25 - i)) & 1;
	if(bit == 1) break;
    }
    if(i == 26) se = 255;
    else se = i;
    sy = s1a;
    eya = e1a + 1;
    if(eya > se) eyb = eya - se;
    else eyb = 0;
    if(e2a == 0) ey = e1a;
    else ey = eyb;
    if (se < 32) myb = mya << se;
    else myb = 0;
    if(e2a == 0) my = m1a;
    else my = (myb >> 2) & 0x7fffff;
    y = (sy << 31) | (ey << 23) | my;
    r = *((float *)&y);
    
    return r;
}

float fsub(float a, float b){

    return fadd(a,-b);
  
}

float fmul(float a, float b){
    unsigned int x1,x2,s1,s2,sy,e1,e2,ey,m1,m2,my;
    unsigned int flag,e1a,e2a,eya,y,mya2;
    unsigned long mya;
    float r;
    x1 = *((unsigned int *)&a);
    x2 = *((unsigned int *)&b);
    s1 = x1 >> 31;
    e1 = (x1 & 0x7f800000) >> 23;
    m1 = x1 & 0x7fffff;
    s2 = x2 >> 31;
    e2 = (x2 & 0x7f800000) >> 23;
    m2 = x2 & 0x7fffff;
    sy = s1 ^ s2;
    mya = (unsigned long)((1 << 23) | m1) * (unsigned long)((1 << 23) | m2);
    mya = mya >> 20;
    mya2 = (unsigned int)mya;
    flag = (mya2 >> 27) & 1;
    if(flag == 1) my = (mya2 & 0x7ffffff) >> 4;
    else my = (mya2 & 0x3ffffff) >> 3;
    if(e2 == 0) e1a = 0;
    else e1a = e1;
    if(e1 == 0) e2a = 0;
    else e2a = e2;
    eya = e1a + e2a + flag;
    if(eya > 127) ey = eya - 127;
    else ey = 0;
    y = (sy << 31) | (ey << 23) | my;
    r = *((float *)&y);

    return r;

}
 
float finv(float f){
    unsigned int x,sx,ex;
    unsigned int ml,pm,mr,my,ey,y;
    unsigned int a0_inv,a02_inv,notmr;
    unsigned long my_extend1,my_extend2,my_long;
    float r;
    x = *((unsigned int *)&f);
    sx = x >> 31;
    ex = (x >> 23) & 0xff;
    ml = (x >> 13) & 0x3ff;
    pm = (x >> 12) & 1;
    mr = x & 0xfff;
    // ml から a0_inv,a02_inv を決定
    switch(ml){
        case 0:
            a0_inv  = 8380423;
            a02_inv = 16368;
            break;
        case 1:
            a0_inv  = 8364071;
            a02_inv = 16336;
            break;
        case 2:
            a0_inv  = 8347751;
            a02_inv = 16304;
            break;
        case 3:
            a0_inv  = 8331462;
            a02_inv = 16272;
            break;
        case 4:
            a0_inv  = 8315206;
            a02_inv = 16240;
            break;
        case 5:
            a0_inv  = 8298980;
            a02_inv = 16208;
            break;
        case 6:
            a0_inv  = 8282787;
            a02_inv = 16177;
            break;
        case 7:
            a0_inv  = 8266624;
            a02_inv = 16145;
            break;
        case 8:
            a0_inv  = 8250493;
            a02_inv = 16116;
            break;
        case 9:
            a0_inv  = 8234394;
            a02_inv = 16084;
            break;
        case 10:
            a0_inv  = 8218325;
            a02_inv = 16052;
            break;
        case 11:
            a0_inv  = 8202288;
            a02_inv = 16023;
            break;
        case 12:
            a0_inv  = 8186281;
            a02_inv = 15991;
            break;
        case 13:
            a0_inv  = 8170305;
            a02_inv = 15960;
            break;
        case 14:
            a0_inv  = 8154360;
            a02_inv = 15929;
            break;
        case 15:
            a0_inv  = 8138446;
            a02_inv = 15899;
            break;
        case 16:
            a0_inv  = 8122562;
            a02_inv = 15868;
            break;
        case 17:
            a0_inv  = 8106709;
            a02_inv = 15837;
            break;
        case 18:
            a0_inv  = 8090886;
            a02_inv = 15808;
            break;
        case 19:
            a0_inv  = 8075093;
            a02_inv = 15776;
            break;
        case 20:
            a0_inv  = 8059331;
            a02_inv = 15747;
            break;
        case 21:
            a0_inv  = 8043599;
            a02_inv = 15716;
            break;
        case 22:
            a0_inv  = 8027897;
            a02_inv = 15687;
            break;
        case 23:
            a0_inv  = 8012225;
            a02_inv = 15656;
            break;
        case 24:
            a0_inv  = 7996583;
            a02_inv = 15627;
            break;
        case 25:
            a0_inv  = 7980970;
            a02_inv = 15596;
            break;
        case 26:
            a0_inv  = 7965388;
            a02_inv = 15568;
            break;
        case 27:
            a0_inv  = 7949835;
            a02_inv = 15539;
            break;
        case 28:
            a0_inv  = 7934311;
            a02_inv = 15508;
            break;
        case 29:
            a0_inv  = 7918817;
            a02_inv = 15479;
            break;
        case 30:
            a0_inv  = 7903353;
            a02_inv = 15449;
            break;
        case 31:
            a0_inv  = 7887917;
            a02_inv = 15420;
            break;
        case 32:
            a0_inv  = 7872511;
            a02_inv = 15391;
            break;
        case 33:
            a0_inv  = 7857134;
            a02_inv = 15361;
            break;
        case 34:
            a0_inv  = 7841786;
            a02_inv = 15332;
            break;
        case 35:
            a0_inv  = 7826467;
            a02_inv = 15304;
            break;
        case 36:
            a0_inv  = 7811177;
            a02_inv = 15276;
            break;
        case 37:
            a0_inv  = 7795916;
            a02_inv = 15247;
            break;
        case 38:
            a0_inv  = 7780684;
            a02_inv = 15217;
            break;
        case 39:
            a0_inv  = 7765480;
            a02_inv = 15188;
            break;
        case 40:
            a0_inv  = 7750305;
            a02_inv = 15160;
            break;
        case 41:
            a0_inv  = 7735158;
            a02_inv = 15132;
            break;
        case 42:
            a0_inv  = 7720039;
            a02_inv = 15104;
            break;
        case 43:
            a0_inv  = 7704949;
            a02_inv = 15076;
            break;
        case 44:
            a0_inv  = 7689887;
            a02_inv = 15048;
            break;
        case 45:
            a0_inv  = 7674854;
            a02_inv = 15019;
            break;
        case 46:
            a0_inv  = 7659848;
            a02_inv = 14991;
            break;
        case 47:
            a0_inv  = 7644871;
            a02_inv = 14964;
            break;
        case 48:
            a0_inv  = 7629921;
            a02_inv = 14936;
            break;
        case 49:
            a0_inv  = 7614999;
            a02_inv = 14908;
            break;
        case 50:
            a0_inv  = 7600105;
            a02_inv = 14880;
            break;
        case 51:
            a0_inv  = 7585239;
            a02_inv = 14852;
            break;
        case 52:
            a0_inv  = 7570400;
            a02_inv = 14824;
            break;
        case 53:
            a0_inv  = 7555589;
            a02_inv = 14797;
            break;
        case 54:
            a0_inv  = 7540805;
            a02_inv = 14769;
            break;
        case 55:
            a0_inv  = 7526049;
            a02_inv = 14743;
            break;
        case 56:
            a0_inv  = 7511320;
            a02_inv = 14715;
            break;
        case 57:
            a0_inv  = 7496618;
            a02_inv = 14688;
            break;
        case 58:
            a0_inv  = 7481944;
            a02_inv = 14660;
            break;
        case 59:
            a0_inv  = 7467296;
            a02_inv = 14633;
            break;
        case 60:
            a0_inv  = 7452676;
            a02_inv = 14607;
            break;
        case 61:
            a0_inv  = 7438082;
            a02_inv = 14580;
            break;
        case 62:
            a0_inv  = 7423516;
            a02_inv = 14553;
            break;
        case 63:
            a0_inv  = 7408976;
            a02_inv = 14525;
            break;
        case 64:
            a0_inv  = 7394463;
            a02_inv = 14500;
            break;
        case 65:
            a0_inv  = 7379976;
            a02_inv = 14473;
            break;
        case 66:
            a0_inv  = 7365516;
            a02_inv = 14445;
            break;
        case 67:
            a0_inv  = 7351083;
            a02_inv = 14420;
            break;
        case 68:
            a0_inv  = 7336676;
            a02_inv = 14393;
            break;
        case 69:
            a0_inv  = 7322295;
            a02_inv = 14368;
            break;
        case 70:
            a0_inv  = 7307941;
            a02_inv = 14340;
            break;
        case 71:
            a0_inv  = 7293612;
            a02_inv = 14315;
            break;
        case 72:
            a0_inv  = 7279310;
            a02_inv = 14288;
            break;
        case 73:
            a0_inv  = 7265034;
            a02_inv = 14263;
            break;
        case 74:
            a0_inv  = 7250784;
            a02_inv = 14236;
            break;
        case 75:
            a0_inv  = 7236560;
            a02_inv = 14211;
            break;
        case 76:
            a0_inv  = 7222362;
            a02_inv = 14185;
            break;
        case 77:
            a0_inv  = 7208190;
            a02_inv = 14160;
            break;
        case 78:
            a0_inv  = 7194043;
            a02_inv = 14133;
            break;
        case 79:
            a0_inv  = 7179922;
            a02_inv = 14108;
            break;
        case 80:
            a0_inv  = 7165826;
            a02_inv = 14083;
            break;
        case 81:
            a0_inv  = 7151756;
            a02_inv = 14057;
            break;
        case 82:
            a0_inv  = 7137711;
            a02_inv = 14032;
            break;
        case 83:
            a0_inv  = 7123692;
            a02_inv = 14007;
            break;
        case 84:
            a0_inv  = 7109698;
            a02_inv = 13981;
            break;
        case 85:
            a0_inv  = 7095730;
            a02_inv = 13956;
            break;
        case 86:
            a0_inv  = 7081786;
            a02_inv = 13931;
            break;
        case 87:
            a0_inv  = 7067868;
            a02_inv = 13905;
            break;
        case 88:
            a0_inv  = 7053974;
            a02_inv = 13880;
            break;
        case 89:
            a0_inv  = 7040106;
            a02_inv = 13856;
            break;
        case 90:
            a0_inv  = 7026262;
            a02_inv = 13832;
            break;
        case 91:
            a0_inv  = 7012443;
            a02_inv = 13807;
            break;
        case 92:
            a0_inv  = 6998649;
            a02_inv = 13781;
            break;
        case 93:
            a0_inv  = 6984880;
            a02_inv = 13756;
            break;
        case 94:
            a0_inv  = 6971135;
            a02_inv = 13732;
            break;
        case 95:
            a0_inv  = 6957415;
            a02_inv = 13708;
            break;
        case 96:
            a0_inv  = 6943719;
            a02_inv = 13683;
            break;
        case 97:
            a0_inv  = 6930048;
            a02_inv = 13659;
            break;
        case 98:
            a0_inv  = 6916401;
            a02_inv = 13635;
            break;
        case 99:
            a0_inv  = 6902778;
            a02_inv = 13609;
            break;
        case 100:
            a0_inv  = 6889180;
            a02_inv = 13585;
            break;
        case 101:
            a0_inv  = 6875606;
            a02_inv = 13561;
            break;
        case 102:
            a0_inv  = 6862056;
            a02_inv = 13537;
            break;
        case 103:
            a0_inv  = 6848530;
            a02_inv = 13515;
            break;
        case 104:
            a0_inv  = 6835027;
            a02_inv = 13489;
            break;
        case 105:
            a0_inv  = 6821549;
            a02_inv = 13465;
            break;
        case 106:
            a0_inv  = 6808095;
            a02_inv = 13443;
            break;
        case 107:
            a0_inv  = 6794664;
            a02_inv = 13417;
            break;
        case 108:
            a0_inv  = 6781257;
            a02_inv = 13395;
            break;
        case 109:
            a0_inv  = 6767874;
            a02_inv = 13371;
            break;
        case 110:
            a0_inv  = 6754515;
            a02_inv = 13348;
            break;
        case 111:
            a0_inv  = 6741179;
            a02_inv = 13324;
            break;
        case 112:
            a0_inv  = 6727866;
            a02_inv = 13300;
            break;
        case 113:
            a0_inv  = 6714577;
            a02_inv = 13277;
            break;
        case 114:
            a0_inv  = 6701311;
            a02_inv = 13253;
            break;
        case 115:
            a0_inv  = 6688068;
            a02_inv = 13231;
            break;
        case 116:
            a0_inv  = 6674849;
            a02_inv = 13208;
            break;
        case 117:
            a0_inv  = 6661653;
            a02_inv = 13184;
            break;
        case 118:
            a0_inv  = 6648480;
            a02_inv = 13161;
            break;
        case 119:
            a0_inv  = 6635330;
            a02_inv = 13137;
            break;
        case 120:
            a0_inv  = 6622203;
            a02_inv = 13115;
            break;
        case 121:
            a0_inv  = 6609098;
            a02_inv = 13092;
            break;
        case 122:
            a0_inv  = 6596017;
            a02_inv = 13069;
            break;
        case 123:
            a0_inv  = 6582959;
            a02_inv = 13047;
            break;
        case 124:
            a0_inv  = 6569923;
            a02_inv = 13024;
            break;
        case 125:
            a0_inv  = 6556910;
            a02_inv = 13001;
            break;
        case 126:
            a0_inv  = 6543919;
            a02_inv = 12980;
            break;
        case 127:
            a0_inv  = 6530951;
            a02_inv = 12956;
            break;
        case 128:
            a0_inv  = 6518006;
            a02_inv = 12933;
            break;
        case 129:
            a0_inv  = 6505083;
            a02_inv = 12912;
            break;
        case 130:
            a0_inv  = 6492183;
            a02_inv = 12889;
            break;
        case 131:
            a0_inv  = 6479304;
            a02_inv = 12867;
            break;
        case 132:
            a0_inv  = 6466448;
            a02_inv = 12844;
            break;
        case 133:
            a0_inv  = 6453615;
            a02_inv = 12823;
            break;
        case 134:
            a0_inv  = 6440803;
            a02_inv = 12800;
            break;
        case 135:
            a0_inv  = 6428014;
            a02_inv = 12777;
            break;
        case 136:
            a0_inv  = 6415246;
            a02_inv = 12756;
            break;
        case 137:
            a0_inv  = 6402501;
            a02_inv = 12733;
            break;
        case 138:
            a0_inv  = 6389777;
            a02_inv = 12712;
            break;
        case 139:
            a0_inv  = 6377075;
            a02_inv = 12691;
            break;
        case 140:
            a0_inv  = 6364396;
            a02_inv = 12668;
            break;
        case 141:
            a0_inv  = 6351738;
            a02_inv = 12647;
            break;
        case 142:
            a0_inv  = 6339101;
            a02_inv = 12625;
            break;
        case 143:
            a0_inv  = 6326486;
            a02_inv = 12604;
            break;
        case 144:
            a0_inv  = 6313893;
            a02_inv = 12581;
            break;
        case 145:
            a0_inv  = 6301322;
            a02_inv = 12560;
            break;
        case 146:
            a0_inv  = 6288771;
            a02_inv = 12539;
            break;
        case 147:
            a0_inv  = 6276243;
            a02_inv = 12517;
            break;
        case 148:
            a0_inv  = 6263735;
            a02_inv = 12496;
            break;
        case 149:
            a0_inv  = 6251249;
            a02_inv = 12475;
            break;
        case 150:
            a0_inv  = 6238785;
            a02_inv = 12455;
            break;
        case 151:
            a0_inv  = 6226341;
            a02_inv = 12432;
            break;
        case 152:
            a0_inv  = 6213919;
            a02_inv = 12412;
            break;
        case 153:
            a0_inv  = 6201517;
            a02_inv = 12391;
            break;
        case 154:
            a0_inv  = 6189137;
            a02_inv = 12369;
            break;
        case 155:
            a0_inv  = 6176778;
            a02_inv = 12348;
            break;
        case 156:
            a0_inv  = 6164440;
            a02_inv = 12328;
            break;
        case 157:
            a0_inv  = 6152122;
            a02_inv = 12307;
            break;
        case 158:
            a0_inv  = 6139826;
            a02_inv = 12285;
            break;
        case 159:
            a0_inv  = 6127550;
            a02_inv = 12264;
            break;
        case 160:
            a0_inv  = 6115295;
            a02_inv = 12244;
            break;
        case 161:
            a0_inv  = 6103060;
            a02_inv = 12224;
            break;
        case 162:
            a0_inv  = 6090846;
            a02_inv = 12204;
            break;
        case 163:
            a0_inv  = 6078653;
            a02_inv = 12183;
            break;
        case 164:
            a0_inv  = 6066481;
            a02_inv = 12161;
            break;
        case 165:
            a0_inv  = 6054328;
            a02_inv = 12141;
            break;
        case 166:
            a0_inv  = 6042196;
            a02_inv = 12121;
            break;
        case 167:
            a0_inv  = 6030085;
            a02_inv = 12100;
            break;
        case 168:
            a0_inv  = 6017994;
            a02_inv = 12080;
            break;
        case 169:
            a0_inv  = 6005923;
            a02_inv = 12060;
            break;
        case 170:
            a0_inv  = 5993872;
            a02_inv = 12040;
            break;
        case 171:
            a0_inv  = 5981842;
            a02_inv = 12020;
            break;
        case 172:
            a0_inv  = 5969831;
            a02_inv = 12000;
            break;
        case 173:
            a0_inv  = 5957841;
            a02_inv = 11980;
            break;
        case 174:
            a0_inv  = 5945871;
            a02_inv = 11960;
            break;
        case 175:
            a0_inv  = 5933920;
            a02_inv = 11940;
            break;
        case 176:
            a0_inv  = 5921990;
            a02_inv = 11920;
            break;
        case 177:
            a0_inv  = 5910079;
            a02_inv = 11900;
            break;
        case 178:
            a0_inv  = 5898189;
            a02_inv = 11880;
            break;
        case 179:
            a0_inv  = 5886317;
            a02_inv = 11860;
            break;
        case 180:
            a0_inv  = 5874466;
            a02_inv = 11841;
            break;
        case 181:
            a0_inv  = 5862634;
            a02_inv = 11821;
            break;
        case 182:
            a0_inv  = 5850822;
            a02_inv = 11801;
            break;
        case 183:
            a0_inv  = 5839030;
            a02_inv = 11783;
            break;
        case 184:
            a0_inv  = 5827257;
            a02_inv = 11763;
            break;
        case 185:
            a0_inv  = 5815503;
            a02_inv = 11744;
            break;
        case 186:
            a0_inv  = 5803769;
            a02_inv = 11724;
            break;
        case 187:
            a0_inv  = 5792055;
            a02_inv = 11704;
            break;
        case 188:
            a0_inv  = 5780359;
            a02_inv = 11685;
            break;
        case 189:
            a0_inv  = 5768683;
            a02_inv = 11665;
            break;
        case 190:
            a0_inv  = 5757026;
            a02_inv = 11648;
            break;
        case 191:
            a0_inv  = 5745389;
            a02_inv = 11628;
            break;
        case 192:
            a0_inv  = 5733770;
            a02_inv = 11608;
            break;
        case 193:
            a0_inv  = 5722171;
            a02_inv = 11589;
            break;
        case 194:
            a0_inv  = 5710590;
            a02_inv = 11571;
            break;
        case 195:
            a0_inv  = 5699029;
            a02_inv = 11552;
            break;
        case 196:
            a0_inv  = 5687486;
            a02_inv = 11532;
            break;
        case 197:
            a0_inv  = 5675962;
            a02_inv = 11513;
            break;
        case 198:
            a0_inv  = 5664458;
            a02_inv = 11496;
            break;
        case 199:
            a0_inv  = 5652972;
            a02_inv = 11476;
            break;
        case 200:
            a0_inv  = 5641505;
            a02_inv = 11457;
            break;
        case 201:
            a0_inv  = 5630056;
            a02_inv = 11439;
            break;
        case 202:
            a0_inv  = 5618626;
            a02_inv = 11420;
            break;
        case 203:
            a0_inv  = 5607215;
            a02_inv = 11401;
            break;
        case 204:
            a0_inv  = 5595823;
            a02_inv = 11384;
            break;
        case 205:
            a0_inv  = 5584448;
            a02_inv = 11364;
            break;
        case 206:
            a0_inv  = 5573093;
            a02_inv = 11345;
            break;
        case 207:
            a0_inv  = 5561756;
            a02_inv = 11328;
            break;
        case 208:
            a0_inv  = 5550437;
            a02_inv = 11308;
            break;
        case 209:
            a0_inv  = 5539137;
            a02_inv = 11291;
            break;
        case 210:
            a0_inv  = 5527854;
            a02_inv = 11272;
            break;
        case 211:
            a0_inv  = 5516591;
            a02_inv = 11255;
            break;
        case 212:
            a0_inv  = 5505345;
            a02_inv = 11236;
            break;
        case 213:
            a0_inv  = 5494118;
            a02_inv = 11217;
            break;
        case 214:
            a0_inv  = 5482908;
            a02_inv = 11200;
            break;
        case 215:
            a0_inv  = 5471717;
            a02_inv = 11181;
            break;
        case 216:
            a0_inv  = 5460544;
            a02_inv = 11164;
            break;
        case 217:
            a0_inv  = 5449389;
            a02_inv = 11145;
            break;
        case 218:
            a0_inv  = 5438251;
            a02_inv = 11128;
            break;
        case 219:
            a0_inv  = 5427132;
            a02_inv = 11109;
            break;
        case 220:
            a0_inv  = 5416031;
            a02_inv = 11092;
            break;
        case 221:
            a0_inv  = 5404947;
            a02_inv = 11075;
            break;
        case 222:
            a0_inv  = 5393881;
            a02_inv = 11056;
            break;
        case 223:
            a0_inv  = 5382833;
            a02_inv = 11039;
            break;
        case 224:
            a0_inv  = 5371803;
            a02_inv = 11020;
            break;
        case 225:
            a0_inv  = 5360790;
            a02_inv = 11004;
            break;
        case 226:
            a0_inv  = 5349795;
            a02_inv = 10985;
            break;
        case 227:
            a0_inv  = 5338817;
            a02_inv = 10968;
            break;
        case 228:
            a0_inv  = 5327857;
            a02_inv = 10951;
            break;
        case 229:
            a0_inv  = 5316915;
            a02_inv = 10933;
            break;
        case 230:
            a0_inv  = 5305990;
            a02_inv = 10916;
            break;
        case 231:
            a0_inv  = 5295082;
            a02_inv = 10899;
            break;
        case 232:
            a0_inv  = 5284192;
            a02_inv = 10881;
            break;
        case 233:
            a0_inv  = 5273319;
            a02_inv = 10864;
            break;
        case 234:
            a0_inv  = 5262463;
            a02_inv = 10847;
            break;
        case 235:
            a0_inv  = 5251625;
            a02_inv = 10829;
            break;
        case 236:
            a0_inv  = 5240803;
            a02_inv = 10812;
            break;
        case 237:
            a0_inv  = 5229999;
            a02_inv = 10795;
            break;
        case 238:
            a0_inv  = 5219212;
            a02_inv = 10777;
            break;
        case 239:
            a0_inv  = 5208442;
            a02_inv = 10760;
            break;
        case 240:
            a0_inv  = 5197689;
            a02_inv = 10744;
            break;
        case 241:
            a0_inv  = 5186953;
            a02_inv = 10727;
            break;
        case 242:
            a0_inv  = 5176234;
            a02_inv = 10709;
            break;
        case 243:
            a0_inv  = 5165532;
            a02_inv = 10692;
            break;
        case 244:
            a0_inv  = 5154847;
            a02_inv = 10676;
            break;
        case 245:
            a0_inv  = 5144179;
            a02_inv = 10660;
            break;
        case 246:
            a0_inv  = 5133527;
            a02_inv = 10643;
            break;
        case 247:
            a0_inv  = 5122893;
            a02_inv = 10625;
            break;
        case 248:
            a0_inv  = 5112275;
            a02_inv = 10609;
            break;
        case 249:
            a0_inv  = 5101673;
            a02_inv = 10592;
            break;
        case 250:
            a0_inv  = 5091088;
            a02_inv = 10576;
            break;
        case 251:
            a0_inv  = 5080520;
            a02_inv = 10560;
            break;
        case 252:
            a0_inv  = 5069969;
            a02_inv = 10544;
            break;
        case 253:
            a0_inv  = 5059434;
            a02_inv = 10527;
            break;
        case 254:
            a0_inv  = 5048915;
            a02_inv = 10511;
            break;
        case 255:
            a0_inv  = 5038413;
            a02_inv = 10493;
            break;
        case 256:
            a0_inv  = 5027927;
            a02_inv = 10477;
            break;
        case 257:
            a0_inv  = 5017458;
            a02_inv = 10460;
            break;
        case 258:
            a0_inv  = 5007005;
            a02_inv = 10444;
            break;
        case 259:
            a0_inv  = 4996568;
            a02_inv = 10428;
            break;
        case 260:
            a0_inv  = 4986147;
            a02_inv = 10412;
            break;
        case 261:
            a0_inv  = 4975743;
            a02_inv = 10396;
            break;
        case 262:
            a0_inv  = 4965355;
            a02_inv = 10380;
            break;
        case 263:
            a0_inv  = 4954983;
            a02_inv = 10364;
            break;
        case 264:
            a0_inv  = 4944627;
            a02_inv = 10348;
            break;
        case 265:
            a0_inv  = 4934287;
            a02_inv = 10332;
            break;
        case 266:
            a0_inv  = 4923963;
            a02_inv = 10316;
            break;
        case 267:
            a0_inv  = 4913655;
            a02_inv = 10300;
            break;
        case 268:
            a0_inv  = 4903363;
            a02_inv = 10284;
            break;
        case 269:
            a0_inv  = 4893087;
            a02_inv = 10268;
            break;
        case 270:
            a0_inv  = 4882827;
            a02_inv = 10252;
            break;
        case 271:
            a0_inv  = 4872583;
            a02_inv = 10236;
            break;
        case 272:
            a0_inv  = 4862355;
            a02_inv = 10220;
            break;
        case 273:
            a0_inv  = 4852142;
            a02_inv = 10204;
            break;
        case 274:
            a0_inv  = 4841945;
            a02_inv = 10188;
            break;
        case 275:
            a0_inv  = 4831764;
            a02_inv = 10173;
            break;
        case 276:
            a0_inv  = 4821598;
            a02_inv = 10157;
            break;
        case 277:
            a0_inv  = 4811448;
            a02_inv = 10141;
            break;
        case 278:
            a0_inv  = 4801314;
            a02_inv = 10127;
            break;
        case 279:
            a0_inv  = 4791195;
            a02_inv = 10111;
            break;
        case 280:
            a0_inv  = 4781092;
            a02_inv = 10096;
            break;
        case 281:
            a0_inv  = 4771004;
            a02_inv = 10080;
            break;
        case 282:
            a0_inv  = 4760931;
            a02_inv = 10064;
            break;
        case 283:
            a0_inv  = 4750874;
            a02_inv = 10049;
            break;
        case 284:
            a0_inv  = 4740833;
            a02_inv = 10033;
            break;
        case 285:
            a0_inv  = 4730806;
            a02_inv = 10017;
            break;
        case 286:
            a0_inv  = 4720795;
            a02_inv = 10004;
            break;
        case 287:
            a0_inv  = 4710800;
            a02_inv = 9988;
            break;
        case 288:
            a0_inv  = 4700819;
            a02_inv = 9972;
            break;
        case 289:
            a0_inv  = 4690854;
            a02_inv = 9957;
            break;
        case 290:
            a0_inv  = 4680904;
            a02_inv = 9943;
            break;
        case 291:
            a0_inv  = 4670969;
            a02_inv = 9927;
            break;
        case 292:
            a0_inv  = 4661049;
            a02_inv = 9912;
            break;
        case 293:
            a0_inv  = 4651144;
            a02_inv = 9897;
            break;
        case 294:
            a0_inv  = 4641254;
            a02_inv = 9881;
            break;
        case 295:
            a0_inv  = 4631379;
            a02_inv = 9867;
            break;
        case 296:
            a0_inv  = 4621519;
            a02_inv = 9852;
            break;
        case 297:
            a0_inv  = 4611674;
            a02_inv = 9837;
            break;
        case 298:
            a0_inv  = 4601844;
            a02_inv = 9821;
            break;
        case 299:
            a0_inv  = 4592029;
            a02_inv = 9808;
            break;
        case 300:
            a0_inv  = 4582229;
            a02_inv = 9792;
            break;
        case 301:
            a0_inv  = 4572443;
            a02_inv = 9777;
            break;
        case 302:
            a0_inv  = 4562672;
            a02_inv = 9764;
            break;
        case 303:
            a0_inv  = 4552916;
            a02_inv = 9748;
            break;
        case 304:
            a0_inv  = 4543175;
            a02_inv = 9733;
            break;
        case 305:
            a0_inv  = 4533448;
            a02_inv = 9720;
            break;
        case 306:
            a0_inv  = 4523736;
            a02_inv = 9704;
            break;
        case 307:
            a0_inv  = 4514038;
            a02_inv = 9689;
            break;
        case 308:
            a0_inv  = 4504355;
            a02_inv = 9676;
            break;
        case 309:
            a0_inv  = 4494686;
            a02_inv = 9660;
            break;
        case 310:
            a0_inv  = 4485032;
            a02_inv = 9647;
            break;
        case 311:
            a0_inv  = 4475393;
            a02_inv = 9632;
            break;
        case 312:
            a0_inv  = 4465768;
            a02_inv = 9617;
            break;
        case 313:
            a0_inv  = 4456157;
            a02_inv = 9604;
            break;
        case 314:
            a0_inv  = 4446561;
            a02_inv = 9588;
            break;
        case 315:
            a0_inv  = 4436979;
            a02_inv = 9575;
            break;
        case 316:
            a0_inv  = 4427411;
            a02_inv = 9560;
            break;
        case 317:
            a0_inv  = 4417857;
            a02_inv = 9545;
            break;
        case 318:
            a0_inv  = 4408318;
            a02_inv = 9532;
            break;
        case 319:
            a0_inv  = 4398793;
            a02_inv = 9517;
            break;
        case 320:
            a0_inv  = 4389282;
            a02_inv = 9504;
            break;
        case 321:
            a0_inv  = 4379785;
            a02_inv = 9489;
            break;
        case 322:
            a0_inv  = 4370303;
            a02_inv = 9476;
            break;
        case 323:
            a0_inv  = 4360834;
            a02_inv = 9461;
            break;
        case 324:
            a0_inv  = 4351380;
            a02_inv = 9447;
            break;
        case 325:
            a0_inv  = 4341939;
            a02_inv = 9433;
            break;
        case 326:
            a0_inv  = 4332513;
            a02_inv = 9419;
            break;
        case 327:
            a0_inv  = 4323100;
            a02_inv = 9405;
            break;
        case 328:
            a0_inv  = 4313701;
            a02_inv = 9392;
            break;
        case 329:
            a0_inv  = 4304316;
            a02_inv = 9377;
            break;
        case 330:
            a0_inv  = 4294946;
            a02_inv = 9364;
            break;
        case 331:
            a0_inv  = 4285588;
            a02_inv = 9349;
            break;
        case 332:
            a0_inv  = 4276245;
            a02_inv = 9336;
            break;
        case 333:
            a0_inv  = 4266916;
            a02_inv = 9323;
            break;
        case 334:
            a0_inv  = 4257600;
            a02_inv = 9308;
            break;
        case 335:
            a0_inv  = 4248298;
            a02_inv = 9295;
            break;
        case 336:
            a0_inv  = 4239009;
            a02_inv = 9281;
            break;
        case 337:
            a0_inv  = 4229734;
            a02_inv = 9268;
            break;
        case 338:
            a0_inv  = 4220473;
            a02_inv = 9255;
            break;
        case 339:
            a0_inv  = 4211226;
            a02_inv = 9240;
            break;
        case 340:
            a0_inv  = 4201992;
            a02_inv = 9228;
            break;
        case 341:
            a0_inv  = 4192771;
            a02_inv = 9213;
            break;
        case 342:
            a0_inv  = 4183564;
            a02_inv = 9200;
            break;
        case 343:
            a0_inv  = 4174371;
            a02_inv = 9187;
            break;
        case 344:
            a0_inv  = 4165191;
            a02_inv = 9173;
            break;
        case 345:
            a0_inv  = 4156024;
            a02_inv = 9160;
            break;
        case 346:
            a0_inv  = 4146871;
            a02_inv = 9147;
            break;
        case 347:
            a0_inv  = 4137731;
            a02_inv = 9132;
            break;
        case 348:
            a0_inv  = 4128604;
            a02_inv = 9120;
            break;
        case 349:
            a0_inv  = 4119491;
            a02_inv = 9107;
            break;
        case 350:
            a0_inv  = 4110390;
            a02_inv = 9093;
            break;
        case 351:
            a0_inv  = 4101304;
            a02_inv = 9080;
            break;
        case 352:
            a0_inv  = 4092230;
            a02_inv = 9067;
            break;
        case 353:
            a0_inv  = 4083169;
            a02_inv = 9053;
            break;
        case 354:
            a0_inv  = 4074122;
            a02_inv = 9040;
            break;
        case 355:
            a0_inv  = 4065088;
            a02_inv = 9028;
            break;
        case 356:
            a0_inv  = 4056067;
            a02_inv = 9015;
            break;
        case 357:
            a0_inv  = 4047059;
            a02_inv = 9001;
            break;
        case 358:
            a0_inv  = 4038063;
            a02_inv = 8988;
            break;
        case 359:
            a0_inv  = 4029081;
            a02_inv = 8976;
            break;
        case 360:
            a0_inv  = 4020112;
            a02_inv = 8963;
            break;
        case 361:
            a0_inv  = 4011156;
            a02_inv = 8949;
            break;
        case 362:
            a0_inv  = 4002213;
            a02_inv = 8936;
            break;
        case 363:
            a0_inv  = 3993283;
            a02_inv = 8924;
            break;
        case 364:
            a0_inv  = 3984365;
            a02_inv = 8911;
            break;
        case 365:
            a0_inv  = 3975461;
            a02_inv = 8897;
            break;
        case 366:
            a0_inv  = 3966569;
            a02_inv = 8885;
            break;
        case 367:
            a0_inv  = 3957690;
            a02_inv = 8872;
            break;
        case 368:
            a0_inv  = 3948823;
            a02_inv = 8860;
            break;
        case 369:
            a0_inv  = 3939970;
            a02_inv = 8848;
            break;
        case 370:
            a0_inv  = 3931129;
            a02_inv = 8833;
            break;
        case 371:
            a0_inv  = 3922301;
            a02_inv = 8821;
            break;
        case 372:
            a0_inv  = 3913485;
            a02_inv = 8808;
            break;
        case 373:
            a0_inv  = 3904682;
            a02_inv = 8796;
            break;
        case 374:
            a0_inv  = 3895892;
            a02_inv = 8784;
            break;
        case 375:
            a0_inv  = 3887114;
            a02_inv = 8772;
            break;
        case 376:
            a0_inv  = 3878349;
            a02_inv = 8759;
            break;
        case 377:
            a0_inv  = 3869596;
            a02_inv = 8745;
            break;
        case 378:
            a0_inv  = 3860856;
            a02_inv = 8733;
            break;
        case 379:
            a0_inv  = 3852128;
            a02_inv = 8721;
            break;
        case 380:
            a0_inv  = 3843413;
            a02_inv = 8708;
            break;
        case 381:
            a0_inv  = 3834710;
            a02_inv = 8696;
            break;
        case 382:
            a0_inv  = 3826019;
            a02_inv = 8684;
            break;
        case 383:
            a0_inv  = 3817341;
            a02_inv = 8672;
            break;
        case 384:
            a0_inv  = 3808675;
            a02_inv = 8660;
            break;
        case 385:
            a0_inv  = 3800022;
            a02_inv = 8647;
            break;
        case 386:
            a0_inv  = 3791380;
            a02_inv = 8636;
            break;
        case 387:
            a0_inv  = 3782751;
            a02_inv = 8623;
            break;
        case 388:
            a0_inv  = 3774134;
            a02_inv = 8611;
            break;
        case 389:
            a0_inv  = 3765530;
            a02_inv = 8599;
            break;
        case 390:
            a0_inv  = 3756937;
            a02_inv = 8585;
            break;
        case 391:
            a0_inv  = 3748357;
            a02_inv = 8575;
            break;
        case 392:
            a0_inv  = 3739788;
            a02_inv = 8563;
            break;
        case 393:
            a0_inv  = 3731232;
            a02_inv = 8549;
            break;
        case 394:
            a0_inv  = 3722688;
            a02_inv = 8537;
            break;
        case 395:
            a0_inv  = 3714156;
            a02_inv = 8525;
            break;
        case 396:
            a0_inv  = 3705636;
            a02_inv = 8513;
            break;
        case 397:
            a0_inv  = 3697128;
            a02_inv = 8501;
            break;
        case 398:
            a0_inv  = 3688632;
            a02_inv = 8489;
            break;
        case 399:
            a0_inv  = 3680148;
            a02_inv = 8477;
            break;
        case 400:
            a0_inv  = 3671675;
            a02_inv = 8467;
            break;
        case 401:
            a0_inv  = 3663215;
            a02_inv = 8453;
            break;
        case 402:
            a0_inv  = 3654766;
            a02_inv = 8443;
            break;
        case 403:
            a0_inv  = 3646330;
            a02_inv = 8431;
            break;
        case 404:
            a0_inv  = 3637905;
            a02_inv = 8419;
            break;
        case 405:
            a0_inv  = 3629492;
            a02_inv = 8407;
            break;
        case 406:
            a0_inv  = 3621090;
            a02_inv = 8396;
            break;
        case 407:
            a0_inv  = 3612701;
            a02_inv = 8384;
            break;
        case 408:
            a0_inv  = 3604323;
            a02_inv = 8372;
            break;
        case 409:
            a0_inv  = 3595957;
            a02_inv = 8360;
            break;
        case 410:
            a0_inv  = 3587602;
            a02_inv = 8348;
            break;
        case 411:
            a0_inv  = 3579259;
            a02_inv = 8336;
            break;
        case 412:
            a0_inv  = 3570928;
            a02_inv = 8325;
            break;
        case 413:
            a0_inv  = 3562608;
            a02_inv = 8313;
            break;
        case 414:
            a0_inv  = 3554300;
            a02_inv = 8301;
            break;
        case 415:
            a0_inv  = 3546004;
            a02_inv = 8291;
            break;
        case 416:
            a0_inv  = 3537719;
            a02_inv = 8279;
            break;
        case 417:
            a0_inv  = 3529445;
            a02_inv = 8268;
            break;
        case 418:
            a0_inv  = 3521183;
            a02_inv = 8256;
            break;
        case 419:
            a0_inv  = 3512932;
            a02_inv = 8244;
            break;
        case 420:
            a0_inv  = 3504693;
            a02_inv = 8233;
            break;
        case 421:
            a0_inv  = 3496465;
            a02_inv = 8223;
            break;
        case 422:
            a0_inv  = 3488249;
            a02_inv = 8211;
            break;
        case 423:
            a0_inv  = 3480044;
            a02_inv = 8199;
            break;
        case 424:
            a0_inv  = 3471850;
            a02_inv = 8188;
            break;
        case 425:
            a0_inv  = 3463668;
            a02_inv = 8176;
            break;
        case 426:
            a0_inv  = 3455496;
            a02_inv = 8165;
            break;
        case 427:
            a0_inv  = 3447337;
            a02_inv = 8155;
            break;
        case 428:
            a0_inv  = 3439188;
            a02_inv = 8143;
            break;
        case 429:
            a0_inv  = 3431050;
            a02_inv = 8132;
            break;
        case 430:
            a0_inv  = 3422924;
            a02_inv = 8120;
            break;
        case 431:
            a0_inv  = 3414809;
            a02_inv = 8109;
            break;
        case 432:
            a0_inv  = 3406705;
            a02_inv = 8097;
            break;
        case 433:
            a0_inv  = 3398612;
            a02_inv = 8087;
            break;
        case 434:
            a0_inv  = 3390531;
            a02_inv = 8076;
            break;
        case 435:
            a0_inv  = 3382460;
            a02_inv = 8064;
            break;
        case 436:
            a0_inv  = 3374400;
            a02_inv = 8053;
            break;
        case 437:
            a0_inv  = 3366352;
            a02_inv = 8043;
            break;
        case 438:
            a0_inv  = 3358314;
            a02_inv = 8032;
            break;
        case 439:
            a0_inv  = 3350288;
            a02_inv = 8020;
            break;
        case 440:
            a0_inv  = 3342272;
            a02_inv = 8009;
            break;
        case 441:
            a0_inv  = 3334267;
            a02_inv = 8000;
            break;
        case 442:
            a0_inv  = 3326273;
            a02_inv = 7988;
            break;
        case 443:
            a0_inv  = 3318291;
            a02_inv = 7977;
            break;
        case 444:
            a0_inv  = 3310319;
            a02_inv = 7967;
            break;
        case 445:
            a0_inv  = 3302357;
            a02_inv = 7956;
            break;
        case 446:
            a0_inv  = 3294407;
            a02_inv = 7944;
            break;
        case 447:
            a0_inv  = 3286468;
            a02_inv = 7933;
            break;
        case 448:
            a0_inv  = 3278539;
            a02_inv = 7924;
            break;
        case 449:
            a0_inv  = 3270621;
            a02_inv = 7912;
            break;
        case 450:
            a0_inv  = 3262714;
            a02_inv = 7901;
            break;
        case 451:
            a0_inv  = 3254817;
            a02_inv = 7892;
            break;
        case 452:
            a0_inv  = 3246931;
            a02_inv = 7880;
            break;
        case 453:
            a0_inv  = 3239056;
            a02_inv = 7869;
            break;
        case 454:
            a0_inv  = 3231192;
            a02_inv = 7859;
            break;
        case 455:
            a0_inv  = 3223338;
            a02_inv = 7848;
            break;
        case 456:
            a0_inv  = 3215494;
            a02_inv = 7837;
            break;
        case 457:
            a0_inv  = 3207662;
            a02_inv = 7827;
            break;
        case 458:
            a0_inv  = 3199840;
            a02_inv = 7816;
            break;
        case 459:
            a0_inv  = 3192028;
            a02_inv = 7805;
            break;
        case 460:
            a0_inv  = 3184227;
            a02_inv = 7796;
            break;
        case 461:
            a0_inv  = 3176437;
            a02_inv = 7784;
            break;
        case 462:
            a0_inv  = 3168656;
            a02_inv = 7775;
            break;
        case 463:
            a0_inv  = 3160887;
            a02_inv = 7764;
            break;
        case 464:
            a0_inv  = 3153128;
            a02_inv = 7753;
            break;
        case 465:
            a0_inv  = 3145379;
            a02_inv = 7744;
            break;
        case 466:
            a0_inv  = 3137641;
            a02_inv = 7733;
            break;
        case 467:
            a0_inv  = 3129913;
            a02_inv = 7723;
            break;
        case 468:
            a0_inv  = 3122195;
            a02_inv = 7712;
            break;
        case 469:
            a0_inv  = 3114488;
            a02_inv = 7701;
            break;
        case 470:
            a0_inv  = 3106791;
            a02_inv = 7692;
            break;
        case 471:
            a0_inv  = 3099104;
            a02_inv = 7680;
            break;
        case 472:
            a0_inv  = 3091428;
            a02_inv = 7671;
            break;
        case 473:
            a0_inv  = 3083762;
            a02_inv = 7660;
            break;
        case 474:
            a0_inv  = 3076106;
            a02_inv = 7651;
            break;
        case 475:
            a0_inv  = 3068460;
            a02_inv = 7640;
            break;
        case 476:
            a0_inv  = 3060825;
            a02_inv = 7631;
            break;
        case 477:
            a0_inv  = 3053199;
            a02_inv = 7620;
            break;
        case 478:
            a0_inv  = 3045584;
            a02_inv = 7609;
            break;
        case 479:
            a0_inv  = 3037979;
            a02_inv = 7600;
            break;
        case 480:
            a0_inv  = 3030384;
            a02_inv = 7589;
            break;
        case 481:
            a0_inv  = 3022799;
            a02_inv = 7580;
            break;
        case 482:
            a0_inv  = 3015225;
            a02_inv = 7569;
            break;
        case 483:
            a0_inv  = 3007660;
            a02_inv = 7560;
            break;
        case 484:
            a0_inv  = 3000105;
            a02_inv = 7549;
            break;
        case 485:
            a0_inv  = 2992560;
            a02_inv = 7540;
            break;
        case 486:
            a0_inv  = 2985026;
            a02_inv = 7529;
            break;
        case 487:
            a0_inv  = 2977501;
            a02_inv = 7520;
            break;
        case 488:
            a0_inv  = 2969986;
            a02_inv = 7509;
            break;
        case 489:
            a0_inv  = 2962481;
            a02_inv = 7500;
            break;
        case 490:
            a0_inv  = 2954986;
            a02_inv = 7489;
            break;
        case 491:
            a0_inv  = 2947501;
            a02_inv = 7480;
            break;
        case 492:
            a0_inv  = 2940026;
            a02_inv = 7471;
            break;
        case 493:
            a0_inv  = 2932561;
            a02_inv = 7460;
            break;
        case 494:
            a0_inv  = 2925105;
            a02_inv = 7451;
            break;
        case 495:
            a0_inv  = 2917660;
            a02_inv = 7440;
            break;
        case 496:
            a0_inv  = 2910224;
            a02_inv = 7431;
            break;
        case 497:
            a0_inv  = 2902798;
            a02_inv = 7420;
            break;
        case 498:
            a0_inv  = 2895381;
            a02_inv = 7412;
            break;
        case 499:
            a0_inv  = 2887975;
            a02_inv = 7401;
            break;
        case 500:
            a0_inv  = 2880578;
            a02_inv = 7392;
            break;
        case 501:
            a0_inv  = 2873191;
            a02_inv = 7381;
            break;
        case 502:
            a0_inv  = 2865813;
            a02_inv = 7372;
            break;
        case 503:
            a0_inv  = 2858445;
            a02_inv = 7363;
            break;
        case 504:
            a0_inv  = 2851087;
            a02_inv = 7353;
            break;
        case 505:
            a0_inv  = 2843738;
            a02_inv = 7344;
            break;
        case 506:
            a0_inv  = 2836399;
            a02_inv = 7333;
            break;
        case 507:
            a0_inv  = 2829070;
            a02_inv = 7324;
            break;
        case 508:
            a0_inv  = 2821750;
            a02_inv = 7315;
            break;
        case 509:
            a0_inv  = 2814440;
            a02_inv = 7304;
            break;
        case 510:
            a0_inv  = 2807139;
            a02_inv = 7296;
            break;
        case 511:
            a0_inv  = 2799848;
            a02_inv = 7287;
            break;
        case 512:
            a0_inv  = 2792566;
            a02_inv = 7276;
            break;
        case 513:
            a0_inv  = 2785294;
            a02_inv = 7268;
            break;
        case 514:
            a0_inv  = 2778031;
            a02_inv = 7257;
            break;
        case 515:
            a0_inv  = 2770777;
            a02_inv = 7248;
            break;
        case 516:
            a0_inv  = 2763533;
            a02_inv = 7239;
            break;
        case 517:
            a0_inv  = 2756299;
            a02_inv = 7229;
            break;
        case 518:
            a0_inv  = 2749074;
            a02_inv = 7220;
            break;
        case 519:
            a0_inv  = 2741858;
            a02_inv = 7212;
            break;
        case 520:
            a0_inv  = 2734651;
            a02_inv = 7201;
            break;
        case 521:
            a0_inv  = 2727454;
            a02_inv = 7192;
            break;
        case 522:
            a0_inv  = 2720266;
            a02_inv = 7184;
            break;
        case 523:
            a0_inv  = 2713088;
            a02_inv = 7173;
            break;
        case 524:
            a0_inv  = 2705918;
            a02_inv = 7164;
            break;
        case 525:
            a0_inv  = 2698758;
            a02_inv = 7156;
            break;
        case 526:
            a0_inv  = 2691607;
            a02_inv = 7147;
            break;
        case 527:
            a0_inv  = 2684466;
            a02_inv = 7136;
            break;
        case 528:
            a0_inv  = 2677333;
            a02_inv = 7128;
            break;
        case 529:
            a0_inv  = 2670210;
            a02_inv = 7119;
            break;
        case 530:
            a0_inv  = 2663096;
            a02_inv = 7109;
            break;
        case 531:
            a0_inv  = 2655991;
            a02_inv = 7100;
            break;
        case 532:
            a0_inv  = 2648895;
            a02_inv = 7091;
            break;
        case 533:
            a0_inv  = 2641809;
            a02_inv = 7081;
            break;
        case 534:
            a0_inv  = 2634731;
            a02_inv = 7072;
            break;
        case 535:
            a0_inv  = 2627663;
            a02_inv = 7064;
            break;
        case 536:
            a0_inv  = 2620603;
            a02_inv = 7055;
            break;
        case 537:
            a0_inv  = 2613553;
            a02_inv = 7045;
            break;
        case 538:
            a0_inv  = 2606511;
            a02_inv = 7036;
            break;
        case 539:
            a0_inv  = 2599479;
            a02_inv = 7028;
            break;
        case 540:
            a0_inv  = 2592456;
            a02_inv = 7019;
            break;
        case 541:
            a0_inv  = 2585441;
            a02_inv = 7009;
            break;
        case 542:
            a0_inv  = 2578436;
            a02_inv = 7000;
            break;
        case 543:
            a0_inv  = 2571439;
            a02_inv = 6992;
            break;
        case 544:
            a0_inv  = 2564452;
            a02_inv = 6983;
            break;
        case 545:
            a0_inv  = 2557473;
            a02_inv = 6975;
            break;
        case 546:
            a0_inv  = 2550503;
            a02_inv = 6965;
            break;
        case 547:
            a0_inv  = 2543542;
            a02_inv = 6956;
            break;
        case 548:
            a0_inv  = 2536590;
            a02_inv = 6948;
            break;
        case 549:
            a0_inv  = 2529647;
            a02_inv = 6939;
            break;
        case 550:
            a0_inv  = 2522712;
            a02_inv = 6929;
            break;
        case 551:
            a0_inv  = 2515787;
            a02_inv = 6920;
            break;
        case 552:
            a0_inv  = 2508870;
            a02_inv = 6912;
            break;
        case 553:
            a0_inv  = 2501962;
            a02_inv = 6904;
            break;
        case 554:
            a0_inv  = 2495063;
            a02_inv = 6895;
            break;
        case 555:
            a0_inv  = 2488172;
            a02_inv = 6885;
            break;
        case 556:
            a0_inv  = 2481290;
            a02_inv = 6877;
            break;
        case 557:
            a0_inv  = 2474417;
            a02_inv = 6868;
            break;
        case 558:
            a0_inv  = 2467552;
            a02_inv = 6860;
            break;
        case 559:
            a0_inv  = 2460697;
            a02_inv = 6852;
            break;
        case 560:
            a0_inv  = 2453850;
            a02_inv = 6843;
            break;
        case 561:
            a0_inv  = 2447011;
            a02_inv = 6833;
            break;
        case 562:
            a0_inv  = 2440181;
            a02_inv = 6824;
            break;
        case 563:
            a0_inv  = 2433360;
            a02_inv = 6816;
            break;
        case 564:
            a0_inv  = 2426547;
            a02_inv = 6808;
            break;
        case 565:
            a0_inv  = 2419743;
            a02_inv = 6800;
            break;
        case 566:
            a0_inv  = 2412947;
            a02_inv = 6791;
            break;
        case 567:
            a0_inv  = 2406160;
            a02_inv = 6783;
            break;
        case 568:
            a0_inv  = 2399382;
            a02_inv = 6775;
            break;
        case 569:
            a0_inv  = 2392612;
            a02_inv = 6765;
            break;
        case 570:
            a0_inv  = 2385850;
            a02_inv = 6756;
            break;
        case 571:
            a0_inv  = 2379097;
            a02_inv = 6748;
            break;
        case 572:
            a0_inv  = 2372353;
            a02_inv = 6740;
            break;
        case 573:
            a0_inv  = 2365617;
            a02_inv = 6732;
            break;
        case 574:
            a0_inv  = 2358889;
            a02_inv = 6724;
            break;
        case 575:
            a0_inv  = 2352170;
            a02_inv = 6716;
            break;
        case 576:
            a0_inv  = 2345459;
            a02_inv = 6707;
            break;
        case 577:
            a0_inv  = 2338756;
            a02_inv = 6697;
            break;
        case 578:
            a0_inv  = 2332062;
            a02_inv = 6689;
            break;
        case 579:
            a0_inv  = 2325376;
            a02_inv = 6681;
            break;
        case 580:
            a0_inv  = 2318699;
            a02_inv = 6672;
            break;
        case 581:
            a0_inv  = 2312030;
            a02_inv = 6664;
            break;
        case 582:
            a0_inv  = 2305369;
            a02_inv = 6656;
            break;
        case 583:
            a0_inv  = 2298716;
            a02_inv = 6648;
            break;
        case 584:
            a0_inv  = 2292072;
            a02_inv = 6640;
            break;
        case 585:
            a0_inv  = 2285436;
            a02_inv = 6632;
            break;
        case 586:
            a0_inv  = 2278808;
            a02_inv = 6624;
            break;
        case 587:
            a0_inv  = 2272189;
            a02_inv = 6615;
            break;
        case 588:
            a0_inv  = 2265577;
            a02_inv = 6607;
            break;
        case 589:
            a0_inv  = 2258974;
            a02_inv = 6600;
            break;
        case 590:
            a0_inv  = 2252379;
            a02_inv = 6591;
            break;
        case 591:
            a0_inv  = 2245793;
            a02_inv = 6583;
            break;
        case 592:
            a0_inv  = 2239214;
            a02_inv = 6575;
            break;
        case 593:
            a0_inv  = 2232643;
            a02_inv = 6567;
            break;
        case 594:
            a0_inv  = 2226081;
            a02_inv = 6557;
            break;
        case 595:
            a0_inv  = 2219527;
            a02_inv = 6551;
            break;
        case 596:
            a0_inv  = 2212980;
            a02_inv = 6543;
            break;
        case 597:
            a0_inv  = 2206442;
            a02_inv = 6533;
            break;
        case 598:
            a0_inv  = 2199912;
            a02_inv = 6525;
            break;
        case 599:
            a0_inv  = 2193390;
            a02_inv = 6517;
            break;
        case 600:
            a0_inv  = 2186876;
            a02_inv = 6509;
            break;
        case 601:
            a0_inv  = 2180370;
            a02_inv = 6501;
            break;
        case 602:
            a0_inv  = 2173872;
            a02_inv = 6493;
            break;
        case 603:
            a0_inv  = 2167382;
            a02_inv = 6485;
            break;
        case 604:
            a0_inv  = 2160900;
            a02_inv = 6477;
            break;
        case 605:
            a0_inv  = 2154426;
            a02_inv = 6469;
            break;
        case 606:
            a0_inv  = 2147960;
            a02_inv = 6463;
            break;
        case 607:
            a0_inv  = 2141502;
            a02_inv = 6453;
            break;
        case 608:
            a0_inv  = 2135051;
            a02_inv = 6447;
            break;
        case 609:
            a0_inv  = 2128609;
            a02_inv = 6439;
            break;
        case 610:
            a0_inv  = 2122175;
            a02_inv = 6431;
            break;
        case 611:
            a0_inv  = 2115748;
            a02_inv = 6423;
            break;
        case 612:
            a0_inv  = 2109329;
            a02_inv = 6415;
            break;
        case 613:
            a0_inv  = 2102918;
            a02_inv = 6407;
            break;
        case 614:
            a0_inv  = 2096515;
            a02_inv = 6399;
            break;
        case 615:
            a0_inv  = 2090120;
            a02_inv = 6392;
            break;
        case 616:
            a0_inv  = 2083732;
            a02_inv = 6384;
            break;
        case 617:
            a0_inv  = 2077352;
            a02_inv = 6376;
            break;
        case 618:
            a0_inv  = 2070981;
            a02_inv = 6368;
            break;
        case 619:
            a0_inv  = 2064616;
            a02_inv = 6360;
            break;
        case 620:
            a0_inv  = 2058260;
            a02_inv = 6352;
            break;
        case 621:
            a0_inv  = 2051911;
            a02_inv = 6344;
            break;
        case 622:
            a0_inv  = 2045570;
            a02_inv = 6337;
            break;
        case 623:
            a0_inv  = 2039237;
            a02_inv = 6328;
            break;
        case 624:
            a0_inv  = 2032911;
            a02_inv = 6321;
            break;
        case 625:
            a0_inv  = 2026593;
            a02_inv = 6315;
            break;
        case 626:
            a0_inv  = 2020283;
            a02_inv = 6305;
            break;
        case 627:
            a0_inv  = 2013980;
            a02_inv = 6299;
            break;
        case 628:
            a0_inv  = 2007685;
            a02_inv = 6292;
            break;
        case 629:
            a0_inv  = 2001398;
            a02_inv = 6284;
            break;
        case 630:
            a0_inv  = 1995118;
            a02_inv = 6276;
            break;
        case 631:
            a0_inv  = 1988845;
            a02_inv = 6268;
            break;
        case 632:
            a0_inv  = 1982581;
            a02_inv = 6260;
            break;
        case 633:
            a0_inv  = 1976324;
            a02_inv = 6253;
            break;
        case 634:
            a0_inv  = 1970074;
            a02_inv = 6245;
            break;
        case 635:
            a0_inv  = 1963832;
            a02_inv = 6237;
            break;
        case 636:
            a0_inv  = 1957597;
            a02_inv = 6231;
            break;
        case 637:
            a0_inv  = 1951370;
            a02_inv = 6224;
            break;
        case 638:
            a0_inv  = 1945151;
            a02_inv = 6216;
            break;
        case 639:
            a0_inv  = 1938939;
            a02_inv = 6208;
            break;
        case 640:
            a0_inv  = 1932734;
            a02_inv = 6200;
            break;
        case 641:
            a0_inv  = 1926537;
            a02_inv = 6192;
            break;
        case 642:
            a0_inv  = 1920347;
            a02_inv = 6185;
            break;
        case 643:
            a0_inv  = 1914165;
            a02_inv = 6179;
            break;
        case 644:
            a0_inv  = 1907990;
            a02_inv = 6171;
            break;
        case 645:
            a0_inv  = 1901823;
            a02_inv = 6164;
            break;
        case 646:
            a0_inv  = 1895663;
            a02_inv = 6156;
            break;
        case 647:
            a0_inv  = 1889510;
            a02_inv = 6148;
            break;
        case 648:
            a0_inv  = 1883365;
            a02_inv = 6141;
            break;
        case 649:
            a0_inv  = 1877227;
            a02_inv = 6135;
            break;
        case 650:
            a0_inv  = 1871096;
            a02_inv = 6127;
            break;
        case 651:
            a0_inv  = 1864973;
            a02_inv = 6120;
            break;
        case 652:
            a0_inv  = 1858856;
            a02_inv = 6112;
            break;
        case 653:
            a0_inv  = 1852748;
            a02_inv = 6104;
            break;
        case 654:
            a0_inv  = 1846646;
            a02_inv = 6097;
            break;
        case 655:
            a0_inv  = 1840552;
            a02_inv = 6091;
            break;
        case 656:
            a0_inv  = 1834465;
            a02_inv = 6083;
            break;
        case 657:
            a0_inv  = 1828385;
            a02_inv = 6076;
            break;
        case 658:
            a0_inv  = 1822313;
            a02_inv = 6068;
            break;
        case 659:
            a0_inv  = 1816248;
            a02_inv = 6061;
            break;
        case 660:
            a0_inv  = 1810189;
            a02_inv = 6055;
            break;
        case 661:
            a0_inv  = 1804139;
            a02_inv = 6047;
            break;
        case 662:
            a0_inv  = 1798095;
            a02_inv = 6040;
            break;
        case 663:
            a0_inv  = 1792058;
            a02_inv = 6032;
            break;
        case 664:
            a0_inv  = 1786029;
            a02_inv = 6025;
            break;
        case 665:
            a0_inv  = 1780007;
            a02_inv = 6019;
            break;
        case 666:
            a0_inv  = 1773991;
            a02_inv = 6012;
            break;
        case 667:
            a0_inv  = 1767983;
            a02_inv = 6004;
            break;
        case 668:
            a0_inv  = 1761982;
            a02_inv = 5997;
            break;
        case 669:
            a0_inv  = 1755989;
            a02_inv = 5989;
            break;
        case 670:
            a0_inv  = 1750002;
            a02_inv = 5983;
            break;
        case 671:
            a0_inv  = 1744022;
            a02_inv = 5976;
            break;
        case 672:
            a0_inv  = 1738049;
            a02_inv = 5968;
            break;
        case 673:
            a0_inv  = 1732084;
            a02_inv = 5961;
            break;
        case 674:
            a0_inv  = 1726125;
            a02_inv = 5955;
            break;
        case 675:
            a0_inv  = 1720174;
            a02_inv = 5948;
            break;
        case 676:
            a0_inv  = 1714229;
            a02_inv = 5941;
            break;
        case 677:
            a0_inv  = 1708291;
            a02_inv = 5933;
            break;
        case 678:
            a0_inv  = 1702361;
            a02_inv = 5927;
            break;
        case 679:
            a0_inv  = 1696437;
            a02_inv = 5920;
            break;
        case 680:
            a0_inv  = 1690520;
            a02_inv = 5912;
            break;
        case 681:
            a0_inv  = 1684611;
            a02_inv = 5907;
            break;
        case 682:
            a0_inv  = 1678708;
            a02_inv = 5899;
            break;
        case 683:
            a0_inv  = 1672812;
            a02_inv = 5892;
            break;
        case 684:
            a0_inv  = 1666923;
            a02_inv = 5885;
            break;
        case 685:
            a0_inv  = 1661041;
            a02_inv = 5879;
            break;
        case 686:
            a0_inv  = 1655165;
            a02_inv = 5872;
            break;
        case 687:
            a0_inv  = 1649297;
            a02_inv = 5864;
            break;
        case 688:
            a0_inv  = 1643435;
            a02_inv = 5857;
            break;
        case 689:
            a0_inv  = 1637581;
            a02_inv = 5852;
            break;
        case 690:
            a0_inv  = 1631733;
            a02_inv = 5844;
            break;
        case 691:
            a0_inv  = 1625892;
            a02_inv = 5837;
            break;
        case 692:
            a0_inv  = 1620058;
            a02_inv = 5831;
            break;
        case 693:
            a0_inv  = 1614230;
            a02_inv = 5824;
            break;
        case 694:
            a0_inv  = 1608409;
            a02_inv = 5817;
            break;
        case 695:
            a0_inv  = 1602595;
            a02_inv = 5811;
            break;
        case 696:
            a0_inv  = 1596788;
            a02_inv = 5804;
            break;
        case 697:
            a0_inv  = 1590988;
            a02_inv = 5796;
            break;
        case 698:
            a0_inv  = 1585194;
            a02_inv = 5791;
            break;
        case 699:
            a0_inv  = 1579407;
            a02_inv = 5784;
            break;
        case 700:
            a0_inv  = 1573627;
            a02_inv = 5776;
            break;
        case 701:
            a0_inv  = 1567854;
            a02_inv = 5771;
            break;
        case 702:
            a0_inv  = 1562087;
            a02_inv = 5763;
            break;
        case 703:
            a0_inv  = 1556327;
            a02_inv = 5756;
            break;
        case 704:
            a0_inv  = 1550573;
            a02_inv = 5749;
            break;
        case 705:
            a0_inv  = 1544826;
            a02_inv = 5744;
            break;
        case 706:
            a0_inv  = 1539086;
            a02_inv = 5736;
            break;
        case 707:
            a0_inv  = 1533352;
            a02_inv = 5729;
            break;
        case 708:
            a0_inv  = 1527625;
            a02_inv = 5724;
            break;
        case 709:
            a0_inv  = 1521905;
            a02_inv = 5716;
            break;
        case 710:
            a0_inv  = 1516191;
            a02_inv = 5711;
            break;
        case 711:
            a0_inv  = 1510484;
            a02_inv = 5704;
            break;
        case 712:
            a0_inv  = 1504784;
            a02_inv = 5697;
            break;
        case 713:
            a0_inv  = 1499089;
            a02_inv = 5691;
            break;
        case 714:
            a0_inv  = 1493402;
            a02_inv = 5684;
            break;
        case 715:
            a0_inv  = 1487721;
            a02_inv = 5677;
            break;
        case 716:
            a0_inv  = 1482047;
            a02_inv = 5671;
            break;
        case 717:
            a0_inv  = 1476379;
            a02_inv = 5664;
            break;
        case 718:
            a0_inv  = 1470717;
            a02_inv = 5657;
            break;
        case 719:
            a0_inv  = 1465062;
            a02_inv = 5652;
            break;
        case 720:
            a0_inv  = 1459414;
            a02_inv = 5644;
            break;
        case 721:
            a0_inv  = 1453772;
            a02_inv = 5639;
            break;
        case 722:
            a0_inv  = 1448137;
            a02_inv = 5632;
            break;
        case 723:
            a0_inv  = 1442508;
            a02_inv = 5625;
            break;
        case 724:
            a0_inv  = 1436885;
            a02_inv = 5620;
            break;
        case 725:
            a0_inv  = 1431269;
            a02_inv = 5612;
            break;
        case 726:
            a0_inv  = 1425659;
            a02_inv = 5607;
            break;
        case 727:
            a0_inv  = 1420056;
            a02_inv = 5600;
            break;
        case 728:
            a0_inv  = 1414459;
            a02_inv = 5593;
            break;
        case 729:
            a0_inv  = 1408868;
            a02_inv = 5587;
            break;
        case 730:
            a0_inv  = 1403284;
            a02_inv = 5580;
            break;
        case 731:
            a0_inv  = 1397706;
            a02_inv = 5575;
            break;
        case 732:
            a0_inv  = 1392135;
            a02_inv = 5568;
            break;
        case 733:
            a0_inv  = 1386570;
            a02_inv = 5561;
            break;
        case 734:
            a0_inv  = 1381011;
            a02_inv = 5556;
            break;
        case 735:
            a0_inv  = 1375458;
            a02_inv = 5549;
            break;
        case 736:
            a0_inv  = 1369912;
            a02_inv = 5543;
            break;
        case 737:
            a0_inv  = 1364372;
            a02_inv = 5536;
            break;
        case 738:
            a0_inv  = 1358839;
            a02_inv = 5529;
            break;
        case 739:
            a0_inv  = 1353311;
            a02_inv = 5524;
            break;
        case 740:
            a0_inv  = 1347790;
            a02_inv = 5517;
            break;
        case 741:
            a0_inv  = 1342275;
            a02_inv = 5512;
            break;
        case 742:
            a0_inv  = 1336767;
            a02_inv = 5504;
            break;
        case 743:
            a0_inv  = 1331264;
            a02_inv = 5500;
            break;
        case 744:
            a0_inv  = 1325768;
            a02_inv = 5492;
            break;
        case 745:
            a0_inv  = 1320278;
            a02_inv = 5487;
            break;
        case 746:
            a0_inv  = 1314795;
            a02_inv = 5480;
            break;
        case 747:
            a0_inv  = 1309317;
            a02_inv = 5475;
            break;
        case 748:
            a0_inv  = 1303846;
            a02_inv = 5468;
            break;
        case 749:
            a0_inv  = 1298381;
            a02_inv = 5461;
            break;
        case 750:
            a0_inv  = 1292922;
            a02_inv = 5456;
            break;
        case 751:
            a0_inv  = 1287469;
            a02_inv = 5449;
            break;
        case 752:
            a0_inv  = 1282022;
            a02_inv = 5444;
            break;
        case 753:
            a0_inv  = 1276582;
            a02_inv = 5437;
            break;
        case 754:
            a0_inv  = 1271147;
            a02_inv = 5431;
            break;
        case 755:
            a0_inv  = 1265719;
            a02_inv = 5425;
            break;
        case 756:
            a0_inv  = 1260297;
            a02_inv = 5419;
            break;
        case 757:
            a0_inv  = 1254880;
            a02_inv = 5412;
            break;
        case 758:
            a0_inv  = 1249470;
            a02_inv = 5407;
            break;
        case 759:
            a0_inv  = 1244066;
            a02_inv = 5400;
            break;
        case 760:
            a0_inv  = 1238668;
            a02_inv = 5395;
            break;
        case 761:
            a0_inv  = 1233276;
            a02_inv = 5388;
            break;
        case 762:
            a0_inv  = 1227890;
            a02_inv = 5383;
            break;
        case 763:
            a0_inv  = 1222511;
            a02_inv = 5376;
            break;
        case 764:
            a0_inv  = 1217137;
            a02_inv = 5371;
            break;
        case 765:
            a0_inv  = 1211769;
            a02_inv = 5364;
            break;
        case 766:
            a0_inv  = 1206407;
            a02_inv = 5359;
            break;
        case 767:
            a0_inv  = 1201051;
            a02_inv = 5352;
            break;
        case 768:
            a0_inv  = 1195701;
            a02_inv = 5347;
            break;
        case 769:
            a0_inv  = 1190357;
            a02_inv = 5340;
            break;
        case 770:
            a0_inv  = 1185020;
            a02_inv = 5335;
            break;
        case 771:
            a0_inv  = 1179688;
            a02_inv = 5329;
            break;
        case 772:
            a0_inv  = 1174361;
            a02_inv = 5323;
            break;
        case 773:
            a0_inv  = 1169041;
            a02_inv = 5317;
            break;
        case 774:
            a0_inv  = 1163727;
            a02_inv = 5311;
            break;
        case 775:
            a0_inv  = 1158419;
            a02_inv = 5305;
            break;
        case 776:
            a0_inv  = 1153116;
            a02_inv = 5300;
            break;
        case 777:
            a0_inv  = 1147820;
            a02_inv = 5293;
            break;
        case 778:
            a0_inv  = 1142529;
            a02_inv = 5288;
            break;
        case 779:
            a0_inv  = 1137244;
            a02_inv = 5281;
            break;
        case 780:
            a0_inv  = 1131965;
            a02_inv = 5276;
            break;
        case 781:
            a0_inv  = 1126692;
            a02_inv = 5269;
            break;
        case 782:
            a0_inv  = 1121425;
            a02_inv = 5264;
            break;
        case 783:
            a0_inv  = 1116164;
            a02_inv = 5259;
            break;
        case 784:
            a0_inv  = 1110908;
            a02_inv = 5252;
            break;
        case 785:
            a0_inv  = 1105658;
            a02_inv = 5247;
            break;
        case 786:
            a0_inv  = 1100414;
            a02_inv = 5240;
            break;
        case 787:
            a0_inv  = 1095176;
            a02_inv = 5236;
            break;
        case 788:
            a0_inv  = 1089944;
            a02_inv = 5229;
            break;
        case 789:
            a0_inv  = 1084717;
            a02_inv = 5224;
            break;
        case 790:
            a0_inv  = 1079496;
            a02_inv = 5217;
            break;
        case 791:
            a0_inv  = 1074281;
            a02_inv = 5212;
            break;
        case 792:
            a0_inv  = 1069071;
            a02_inv = 5207;
            break;
        case 793:
            a0_inv  = 1063868;
            a02_inv = 5200;
            break;
        case 794:
            a0_inv  = 1058670;
            a02_inv = 5195;
            break;
        case 795:
            a0_inv  = 1053478;
            a02_inv = 5189;
            break;
        case 796:
            a0_inv  = 1048291;
            a02_inv = 5184;
            break;
        case 797:
            a0_inv  = 1043110;
            a02_inv = 5177;
            break;
        case 798:
            a0_inv  = 1037935;
            a02_inv = 5172;
            break;
        case 799:
            a0_inv  = 1032766;
            a02_inv = 5167;
            break;
        case 800:
            a0_inv  = 1027602;
            a02_inv = 5160;
            break;
        case 801:
            a0_inv  = 1022444;
            a02_inv = 5155;
            break;
        case 802:
            a0_inv  = 1017291;
            a02_inv = 5149;
            break;
        case 803:
            a0_inv  = 1012144;
            a02_inv = 5144;
            break;
        case 804:
            a0_inv  = 1007003;
            a02_inv = 5137;
            break;
        case 805:
            a0_inv  = 1001867;
            a02_inv = 5132;
            break;
        case 806:
            a0_inv  = 996737;
            a02_inv = 5127;
            break;
        case 807:
            a0_inv  = 991613;
            a02_inv = 5121;
            break;
        case 808:
            a0_inv  = 986494;
            a02_inv = 5116;
            break;
        case 809:
            a0_inv  = 981381;
            a02_inv = 5111;
            break;
        case 810:
            a0_inv  = 976273;
            a02_inv = 5104;
            break;
        case 811:
            a0_inv  = 971171;
            a02_inv = 5099;
            break;
        case 812:
            a0_inv  = 966075;
            a02_inv = 5093;
            break;
        case 813:
            a0_inv  = 960984;
            a02_inv = 5088;
            break;
        case 814:
            a0_inv  = 955898;
            a02_inv = 5083;
            break;
        case 815:
            a0_inv  = 950818;
            a02_inv = 5077;
            break;
        case 816:
            a0_inv  = 945744;
            a02_inv = 5072;
            break;
        case 817:
            a0_inv  = 940675;
            a02_inv = 5065;
            break;
        case 818:
            a0_inv  = 935612;
            a02_inv = 5060;
            break;
        case 819:
            a0_inv  = 930554;
            a02_inv = 5055;
            break;
        case 820:
            a0_inv  = 925501;
            a02_inv = 5049;
            break;
        case 821:
            a0_inv  = 920454;
            a02_inv = 5044;
            break;
        case 822:
            a0_inv  = 915413;
            a02_inv = 5039;
            break;
        case 823:
            a0_inv  = 910377;
            a02_inv = 5033;
            break;
        case 824:
            a0_inv  = 905346;
            a02_inv = 5028;
            break;
        case 825:
            a0_inv  = 900321;
            a02_inv = 5023;
            break;
        case 826:
            a0_inv  = 895302;
            a02_inv = 5016;
            break;
        case 827:
            a0_inv  = 890287;
            a02_inv = 5012;
            break;
        case 828:
            a0_inv  = 885279;
            a02_inv = 5007;
            break;
        case 829:
            a0_inv  = 880275;
            a02_inv = 5000;
            break;
        case 830:
            a0_inv  = 875277;
            a02_inv = 4996;
            break;
        case 831:
            a0_inv  = 870284;
            a02_inv = 4989;
            break;
        case 832:
            a0_inv  = 865297;
            a02_inv = 4984;
            break;
        case 833:
            a0_inv  = 860315;
            a02_inv = 4980;
            break;
        case 834:
            a0_inv  = 855339;
            a02_inv = 4973;
            break;
        case 835:
            a0_inv  = 850367;
            a02_inv = 4968;
            break;
        case 836:
            a0_inv  = 845402;
            a02_inv = 4964;
            break;
        case 837:
            a0_inv  = 840441;
            a02_inv = 4957;
            break;
        case 838:
            a0_inv  = 835486;
            a02_inv = 4952;
            break;
        case 839:
            a0_inv  = 830536;
            a02_inv = 4948;
            break;
        case 840:
            a0_inv  = 825591;
            a02_inv = 4941;
            break;
        case 841:
            a0_inv  = 820652;
            a02_inv = 4936;
            break;
        case 842:
            a0_inv  = 815718;
            a02_inv = 4932;
            break;
        case 843:
            a0_inv  = 810789;
            a02_inv = 4925;
            break;
        case 844:
            a0_inv  = 805866;
            a02_inv = 4920;
            break;
        case 845:
            a0_inv  = 800948;
            a02_inv = 4916;
            break;
        case 846:
            a0_inv  = 796035;
            a02_inv = 4909;
            break;
        case 847:
            a0_inv  = 791127;
            a02_inv = 4904;
            break;
        case 848:
            a0_inv  = 786225;
            a02_inv = 4900;
            break;
        case 849:
            a0_inv  = 781328;
            a02_inv = 4895;
            break;
        case 850:
            a0_inv  = 776436;
            a02_inv = 4889;
            break;
        case 851:
            a0_inv  = 771549;
            a02_inv = 4884;
            break;
        case 852:
            a0_inv  = 766668;
            a02_inv = 4879;
            break;
        case 853:
            a0_inv  = 761791;
            a02_inv = 4873;
            break;
        case 854:
            a0_inv  = 756920;
            a02_inv = 4868;
            break;
        case 855:
            a0_inv  = 752054;
            a02_inv = 4863;
            break;
        case 856:
            a0_inv  = 747194;
            a02_inv = 4857;
            break;
        case 857:
            a0_inv  = 742338;
            a02_inv = 4852;
            break;
        case 858:
            a0_inv  = 737488;
            a02_inv = 4848;
            break;
        case 859:
            a0_inv  = 732642;
            a02_inv = 4843;
            break;
        case 860:
            a0_inv  = 727802;
            a02_inv = 4837;
            break;
        case 861:
            a0_inv  = 722967;
            a02_inv = 4832;
            break;
        case 862:
            a0_inv  = 718137;
            a02_inv = 4827;
            break;
        case 863:
            a0_inv  = 713312;
            a02_inv = 4823;
            break;
        case 864:
            a0_inv  = 708493;
            a02_inv = 4816;
            break;
        case 865:
            a0_inv  = 703678;
            a02_inv = 4812;
            break;
        case 866:
            a0_inv  = 698869;
            a02_inv = 4807;
            break;
        case 867:
            a0_inv  = 694064;
            a02_inv = 4801;
            break;
        case 868:
            a0_inv  = 689265;
            a02_inv = 4796;
            break;
        case 869:
            a0_inv  = 684471;
            a02_inv = 4792;
            break;
        case 870:
            a0_inv  = 679682;
            a02_inv = 4787;
            break;
        case 871:
            a0_inv  = 674898;
            a02_inv = 4781;
            break;
        case 872:
            a0_inv  = 670119;
            a02_inv = 4776;
            break;
        case 873:
            a0_inv  = 665345;
            a02_inv = 4772;
            break;
        case 874:
            a0_inv  = 660576;
            a02_inv = 4767;
            break;
        case 875:
            a0_inv  = 655812;
            a02_inv = 4761;
            break;
        case 876:
            a0_inv  = 651053;
            a02_inv = 4756;
            break;
        case 877:
            a0_inv  = 646299;
            a02_inv = 4752;
            break;
        case 878:
            a0_inv  = 641550;
            a02_inv = 4747;
            break;
        case 879:
            a0_inv  = 636806;
            a02_inv = 4741;
            break;
        case 880:
            a0_inv  = 632067;
            a02_inv = 4736;
            break;
        case 881:
            a0_inv  = 627333;
            a02_inv = 4732;
            break;
        case 882:
            a0_inv  = 622604;
            a02_inv = 4727;
            break;
        case 883:
            a0_inv  = 617880;
            a02_inv = 4721;
            break;
        case 884:
            a0_inv  = 613160;
            a02_inv = 4716;
            break;
        case 885:
            a0_inv  = 608446;
            a02_inv = 4712;
            break;
        case 886:
            a0_inv  = 603737;
            a02_inv = 4707;
            break;
        case 887:
            a0_inv  = 599033;
            a02_inv = 4701;
            break;
        case 888:
            a0_inv  = 594333;
            a02_inv = 4696;
            break;
        case 889:
            a0_inv  = 589639;
            a02_inv = 4692;
            break;
        case 890:
            a0_inv  = 584949;
            a02_inv = 4687;
            break;
        case 891:
            a0_inv  = 580264;
            a02_inv = 4683;
            break;
        case 892:
            a0_inv  = 575585;
            a02_inv = 4677;
            break;
        case 893:
            a0_inv  = 570910;
            a02_inv = 4672;
            break;
        case 894:
            a0_inv  = 566240;
            a02_inv = 4668;
            break;
        case 895:
            a0_inv  = 561574;
            a02_inv = 4663;
            break;
        case 896:
            a0_inv  = 556914;
            a02_inv = 4657;
            break;
        case 897:
            a0_inv  = 552258;
            a02_inv = 4652;
            break;
        case 898:
            a0_inv  = 547608;
            a02_inv = 4648;
            break;
        case 899:
            a0_inv  = 542962;
            a02_inv = 4644;
            break;
        case 900:
            a0_inv  = 538321;
            a02_inv = 4639;
            break;
        case 901:
            a0_inv  = 533685;
            a02_inv = 4633;
            break;
        case 902:
            a0_inv  = 529054;
            a02_inv = 4628;
            break;
        case 903:
            a0_inv  = 524427;
            a02_inv = 4624;
            break;
        case 904:
            a0_inv  = 519805;
            a02_inv = 4620;
            break;
        case 905:
            a0_inv  = 515188;
            a02_inv = 4615;
            break;
        case 906:
            a0_inv  = 510576;
            a02_inv = 4609;
            break;
        case 907:
            a0_inv  = 505969;
            a02_inv = 4604;
            break;
        case 908:
            a0_inv  = 501366;
            a02_inv = 4600;
            break;
        case 909:
            a0_inv  = 496768;
            a02_inv = 4596;
            break;
        case 910:
            a0_inv  = 492175;
            a02_inv = 4591;
            break;
        case 911:
            a0_inv  = 487587;
            a02_inv = 4585;
            break;
        case 912:
            a0_inv  = 483003;
            a02_inv = 4581;
            break;
        case 913:
            a0_inv  = 478424;
            a02_inv = 4576;
            break;
        case 914:
            a0_inv  = 473850;
            a02_inv = 4572;
            break;
        case 915:
            a0_inv  = 469281;
            a02_inv = 4567;
            break;
        case 916:
            a0_inv  = 464716;
            a02_inv = 4563;
            break;
        case 917:
            a0_inv  = 460156;
            a02_inv = 4557;
            break;
        case 918:
            a0_inv  = 455601;
            a02_inv = 4552;
            break;
        case 919:
            a0_inv  = 451050;
            a02_inv = 4548;
            break;
        case 920:
            a0_inv  = 446504;
            a02_inv = 4544;
            break;
        case 921:
            a0_inv  = 441963;
            a02_inv = 4539;
            break;
        case 922:
            a0_inv  = 437426;
            a02_inv = 4535;
            break;
        case 923:
            a0_inv  = 432894;
            a02_inv = 4529;
            break;
        case 924:
            a0_inv  = 428367;
            a02_inv = 4524;
            break;
        case 925:
            a0_inv  = 423844;
            a02_inv = 4520;
            break;
        case 926:
            a0_inv  = 419326;
            a02_inv = 4516;
            break;
        case 927:
            a0_inv  = 414812;
            a02_inv = 4512;
            break;
        case 928:
            a0_inv  = 410304;
            a02_inv = 4507;
            break;
        case 929:
            a0_inv  = 405799;
            a02_inv = 4501;
            break;
        case 930:
            a0_inv  = 401300;
            a02_inv = 4496;
            break;
        case 931:
            a0_inv  = 396805;
            a02_inv = 4492;
            break;
        case 932:
            a0_inv  = 392315;
            a02_inv = 4488;
            break;
        case 933:
            a0_inv  = 387829;
            a02_inv = 4484;
            break;
        case 934:
            a0_inv  = 383348;
            a02_inv = 4479;
            break;
        case 935:
            a0_inv  = 378871;
            a02_inv = 4473;
            break;
        case 936:
            a0_inv  = 374399;
            a02_inv = 4469;
            break;
        case 937:
            a0_inv  = 369931;
            a02_inv = 4464;
            break;
        case 938:
            a0_inv  = 365468;
            a02_inv = 4460;
            break;
        case 939:
            a0_inv  = 361010;
            a02_inv = 4456;
            break;
        case 940:
            a0_inv  = 356556;
            a02_inv = 4452;
            break;
        case 941:
            a0_inv  = 352107;
            a02_inv = 4447;
            break;
        case 942:
            a0_inv  = 347662;
            a02_inv = 4443;
            break;
        case 943:
            a0_inv  = 343222;
            a02_inv = 4437;
            break;
        case 944:
            a0_inv  = 338786;
            a02_inv = 4433;
            break;
        case 945:
            a0_inv  = 334355;
            a02_inv = 4429;
            break;
        case 946:
            a0_inv  = 329928;
            a02_inv = 4424;
            break;
        case 947:
            a0_inv  = 325506;
            a02_inv = 4420;
            break;
        case 948:
            a0_inv  = 321088;
            a02_inv = 4416;
            break;
        case 949:
            a0_inv  = 316675;
            a02_inv = 4411;
            break;
        case 950:
            a0_inv  = 312266;
            a02_inv = 4407;
            break;
        case 951:
            a0_inv  = 307861;
            a02_inv = 4403;
            break;
        case 952:
            a0_inv  = 303461;
            a02_inv = 4397;
            break;
        case 953:
            a0_inv  = 299066;
            a02_inv = 4393;
            break;
        case 954:
            a0_inv  = 294675;
            a02_inv = 4388;
            break;
        case 955:
            a0_inv  = 290288;
            a02_inv = 4384;
            break;
        case 956:
            a0_inv  = 285906;
            a02_inv = 4380;
            break;
        case 957:
            a0_inv  = 281528;
            a02_inv = 4376;
            break;
        case 958:
            a0_inv  = 277155;
            a02_inv = 4371;
            break;
        case 959:
            a0_inv  = 272786;
            a02_inv = 4367;
            break;
        case 960:
            a0_inv  = 268422;
            a02_inv = 4363;
            break;
        case 961:
            a0_inv  = 264061;
            a02_inv = 4357;
            break;
        case 962:
            a0_inv  = 259706;
            a02_inv = 4353;
            break;
        case 963:
            a0_inv  = 255354;
            a02_inv = 4348;
            break;
        case 964:
            a0_inv  = 251007;
            a02_inv = 4344;
            break;
        case 965:
            a0_inv  = 246665;
            a02_inv = 4340;
            break;
        case 966:
            a0_inv  = 242327;
            a02_inv = 4336;
            break;
        case 967:
            a0_inv  = 237993;
            a02_inv = 4332;
            break;
        case 968:
            a0_inv  = 233663;
            a02_inv = 4328;
            break;
        case 969:
            a0_inv  = 229338;
            a02_inv = 4323;
            break;
        case 970:
            a0_inv  = 225017;
            a02_inv = 4319;
            break;
        case 971:
            a0_inv  = 220701;
            a02_inv = 4315;
            break;
        case 972:
            a0_inv  = 216388;
            a02_inv = 4309;
            break;
        case 973:
            a0_inv  = 212080;
            a02_inv = 4305;
            break;
        case 974:
            a0_inv  = 207777;
            a02_inv = 4301;
            break;
        case 975:
            a0_inv  = 203478;
            a02_inv = 4296;
            break;
        case 976:
            a0_inv  = 199183;
            a02_inv = 4292;
            break;
        case 977:
            a0_inv  = 194892;
            a02_inv = 4288;
            break;
        case 978:
            a0_inv  = 190606;
            a02_inv = 4284;
            break;
        case 979:
            a0_inv  = 186323;
            a02_inv = 4280;
            break;
        case 980:
            a0_inv  = 182046;
            a02_inv = 4276;
            break;
        case 981:
            a0_inv  = 177772;
            a02_inv = 4272;
            break;
        case 982:
            a0_inv  = 173503;
            a02_inv = 4267;
            break;
        case 983:
            a0_inv  = 169238;
            a02_inv = 4263;
            break;
        case 984:
            a0_inv  = 164977;
            a02_inv = 4259;
            break;
        case 985:
            a0_inv  = 160720;
            a02_inv = 4253;
            break;
        case 986:
            a0_inv  = 156468;
            a02_inv = 4249;
            break;
        case 987:
            a0_inv  = 152220;
            a02_inv = 4245;
            break;
        case 988:
            a0_inv  = 147976;
            a02_inv = 4241;
            break;
        case 989:
            a0_inv  = 143736;
            a02_inv = 4237;
            break;
        case 990:
            a0_inv  = 139501;
            a02_inv = 4233;
            break;
        case 991:
            a0_inv  = 135270;
            a02_inv = 4229;
            break;
        case 992:
            a0_inv  = 131043;
            a02_inv = 4224;
            break;
        case 993:
            a0_inv  = 126820;
            a02_inv = 4220;
            break;
        case 994:
            a0_inv  = 122601;
            a02_inv = 4216;
            break;
        case 995:
            a0_inv  = 118386;
            a02_inv = 4212;
            break;
        case 996:
            a0_inv  = 114176;
            a02_inv = 4208;
            break;
        case 997:
            a0_inv  = 109970;
            a02_inv = 4204;
            break;
        case 998:
            a0_inv  = 105768;
            a02_inv = 4200;
            break;
        case 999:
            a0_inv  = 101570;
            a02_inv = 4196;
            break;
        case 1000:
            a0_inv  = 97376;
            a02_inv = 4192;
            break;
        case 1001:
            a0_inv  = 93187;
            a02_inv = 4188;
            break;
        case 1002:
            a0_inv  = 89001;
            a02_inv = 4183;
            break;
        case 1003:
            a0_inv  = 84820;
            a02_inv = 4179;
            break;
        case 1004:
            a0_inv  = 80643;
            a02_inv = 4175;
            break;
        case 1005:
            a0_inv  = 76470;
            a02_inv = 4171;
            break;
        case 1006:
            a0_inv  = 72301;
            a02_inv = 4167;
            break;
        case 1007:
            a0_inv  = 68136;
            a02_inv = 4163;
            break;
        case 1008:
            a0_inv  = 63975;
            a02_inv = 4159;
            break;
        case 1009:
            a0_inv  = 59818;
            a02_inv = 4155;
            break;
        case 1010:
            a0_inv  = 55666;
            a02_inv = 4151;
            break;
        case 1011:
            a0_inv  = 51517;
            a02_inv = 4147;
            break;
        case 1012:
            a0_inv  = 47373;
            a02_inv = 4143;
            break;
        case 1013:
            a0_inv  = 43233;
            a02_inv = 4139;
            break;
        case 1014:
            a0_inv  = 39096;
            a02_inv = 4135;
            break;
        case 1015:
            a0_inv  = 34964;
            a02_inv = 4131;
            break;
        case 1016:
            a0_inv  = 30836;
            a02_inv = 4127;
            break;
        case 1017:
            a0_inv  = 26712;
            a02_inv = 4123;
            break;
        case 1018:
            a0_inv  = 22592;
            a02_inv = 4119;
            break;
        case 1019:
            a0_inv  = 18476;
            a02_inv = 4115;
            break;
        case 1020:
            a0_inv  = 14364;
            a02_inv = 4111;
            break;
        case 1021:
            a0_inv  = 10256;
            a02_inv = 4107;
            break;
        case 1022:
            a0_inv  = 6152;
            a02_inv = 4103;
            break;
        case 1023:
            a0_inv  = 2052;
            a02_inv = 4099;
            break;
    }
    notmr = mr ^ 0xfff;
    my_extend1 = ((unsigned long)a0_inv << 13) - (unsigned long)mr * (unsigned long)a02_inv;
    my_extend2 = ((unsigned long)a0_inv << 13) + (unsigned long)notmr * (unsigned long)a02_inv;
    if(pm) my_long = my_extend1 >> 13;
    else my_long = my_extend2 >> 13;
    my = (unsigned int)my_long;
    if(253 > ex) ey = 253 - ex;
    else ey = 0;
    y = (sx << 31) | (ey << 23) | my;
    r = *((float *)&y);
    return r;
}

float fsqrt(float f){
    unsigned int x,ex,key,h;
    unsigned int xr,corner_flag,ey,my,y;
    unsigned int rtx0,rtx0_inv;
    unsigned long my_extend,my_long;
    float r;
    x = *((unsigned int *)&f);
    ex = (x >> 23) & 0xff;
    key = (x >> 14) & 0x3ff;
    h = x & 0x3fff;
    switch(key){
        case 512:
            rtx0     = 0;
            rtx0_inv = 4096;
            break;
        case 513:
            rtx0     = 8188;
            rtx0_inv = 8184;
            break;
        case 514:
            rtx0     = 16368;
            rtx0_inv = 8176;
            break;
        case 515:
            rtx0     = 24540;
            rtx0_inv = 8168;
            break;
        case 516:
            rtx0     = 32704;
            rtx0_inv = 8160;
            break;
        case 517:
            rtx0     = 40860;
            rtx0_inv = 8152;
            break;
        case 518:
            rtx0     = 49009;
            rtx0_inv = 8144;
            break;
        case 519:
            rtx0     = 57149;
            rtx0_inv = 8137;
            break;
        case 520:
            rtx0     = 65282;
            rtx0_inv = 8129;
            break;
        case 521:
            rtx0     = 73407;
            rtx0_inv = 8121;
            break;
        case 522:
            rtx0     = 81524;
            rtx0_inv = 8113;
            break;
        case 523:
            rtx0     = 89633;
            rtx0_inv = 8105;
            break;
        case 524:
            rtx0     = 97735;
            rtx0_inv = 8098;
            break;
        case 525:
            rtx0     = 105828;
            rtx0_inv = 8090;
            break;
        case 526:
            rtx0     = 113915;
            rtx0_inv = 8082;
            break;
        case 527:
            rtx0     = 121993;
            rtx0_inv = 8075;
            break;
        case 528:
            rtx0     = 130064;
            rtx0_inv = 8067;
            break;
        case 529:
            rtx0     = 138127;
            rtx0_inv = 8059;
            break;
        case 530:
            rtx0     = 146182;
            rtx0_inv = 8052;
            break;
        case 531:
            rtx0     = 154230;
            rtx0_inv = 8044;
            break;
        case 532:
            rtx0     = 162271;
            rtx0_inv = 8037;
            break;
        case 533:
            rtx0     = 170303;
            rtx0_inv = 8029;
            break;
        case 534:
            rtx0     = 178329;
            rtx0_inv = 8021;
            break;
        case 535:
            rtx0     = 186346;
            rtx0_inv = 8014;
            break;
        case 536:
            rtx0     = 194356;
            rtx0_inv = 8006;
            break;
        case 537:
            rtx0     = 202359;
            rtx0_inv = 7999;
            break;
        case 538:
            rtx0     = 210355;
            rtx0_inv = 7992;
            break;
        case 539:
            rtx0     = 218342;
            rtx0_inv = 7984;
            break;
        case 540:
            rtx0     = 226323;
            rtx0_inv = 7977;
            break;
        case 541:
            rtx0     = 234296;
            rtx0_inv = 7969;
            break;
        case 542:
            rtx0     = 242262;
            rtx0_inv = 7962;
            break;
        case 543:
            rtx0     = 250220;
            rtx0_inv = 7955;
            break;
        case 544:
            rtx0     = 258171;
            rtx0_inv = 7947;
            break;
        case 545:
            rtx0     = 266115;
            rtx0_inv = 7940;
            break;
        case 546:
            rtx0     = 274051;
            rtx0_inv = 7933;
            break;
        case 547:
            rtx0     = 281981;
            rtx0_inv = 7926;
            break;
        case 548:
            rtx0     = 289903;
            rtx0_inv = 7918;
            break;
        case 549:
            rtx0     = 297817;
            rtx0_inv = 7911;
            break;
        case 550:
            rtx0     = 305725;
            rtx0_inv = 7904;
            break;
        case 551:
            rtx0     = 313625;
            rtx0_inv = 7897;
            break;
        case 552:
            rtx0     = 321518;
            rtx0_inv = 7890;
            break;
        case 553:
            rtx0     = 329404;
            rtx0_inv = 7882;
            break;
        case 554:
            rtx0     = 337283;
            rtx0_inv = 7875;
            break;
        case 555:
            rtx0     = 345155;
            rtx0_inv = 7868;
            break;
        case 556:
            rtx0     = 353020;
            rtx0_inv = 7861;
            break;
        case 557:
            rtx0     = 360878;
            rtx0_inv = 7854;
            break;
        case 558:
            rtx0     = 368728;
            rtx0_inv = 7847;
            break;
        case 559:
            rtx0     = 376572;
            rtx0_inv = 7840;
            break;
        case 560:
            rtx0     = 384408;
            rtx0_inv = 7833;
            break;
        case 561:
            rtx0     = 392238;
            rtx0_inv = 7826;
            break;
        case 562:
            rtx0     = 400060;
            rtx0_inv = 7819;
            break;
        case 563:
            rtx0     = 407876;
            rtx0_inv = 7812;
            break;
        case 564:
            rtx0     = 415685;
            rtx0_inv = 7805;
            break;
        case 565:
            rtx0     = 423486;
            rtx0_inv = 7798;
            break;
        case 566:
            rtx0     = 431281;
            rtx0_inv = 7791;
            break;
        case 567:
            rtx0     = 439069;
            rtx0_inv = 7785;
            break;
        case 568:
            rtx0     = 446850;
            rtx0_inv = 7778;
            break;
        case 569:
            rtx0     = 454625;
            rtx0_inv = 7771;
            break;
        case 570:
            rtx0     = 462392;
            rtx0_inv = 7764;
            break;
        case 571:
            rtx0     = 470153;
            rtx0_inv = 7757;
            break;
        case 572:
            rtx0     = 477907;
            rtx0_inv = 7750;
            break;
        case 573:
            rtx0     = 485654;
            rtx0_inv = 7744;
            break;
        case 574:
            rtx0     = 493394;
            rtx0_inv = 7737;
            break;
        case 575:
            rtx0     = 501128;
            rtx0_inv = 7730;
            break;
        case 576:
            rtx0     = 508854;
            rtx0_inv = 7723;
            break;
        case 577:
            rtx0     = 516575;
            rtx0_inv = 7717;
            break;
        case 578:
            rtx0     = 524288;
            rtx0_inv = 7710;
            break;
        case 579:
            rtx0     = 531995;
            rtx0_inv = 7703;
            break;
        case 580:
            rtx0     = 539695;
            rtx0_inv = 7697;
            break;
        case 581:
            rtx0     = 547388;
            rtx0_inv = 7690;
            break;
        case 582:
            rtx0     = 555075;
            rtx0_inv = 7684;
            break;
        case 583:
            rtx0     = 562756;
            rtx0_inv = 7677;
            break;
        case 584:
            rtx0     = 570429;
            rtx0_inv = 7670;
            break;
        case 585:
            rtx0     = 578096;
            rtx0_inv = 7664;
            break;
        case 586:
            rtx0     = 585757;
            rtx0_inv = 7657;
            break;
        case 587:
            rtx0     = 593411;
            rtx0_inv = 7651;
            break;
        case 588:
            rtx0     = 601059;
            rtx0_inv = 7644;
            break;
        case 589:
            rtx0     = 608700;
            rtx0_inv = 7638;
            break;
        case 590:
            rtx0     = 616334;
            rtx0_inv = 7631;
            break;
        case 591:
            rtx0     = 623962;
            rtx0_inv = 7625;
            break;
        case 592:
            rtx0     = 631584;
            rtx0_inv = 7618;
            break;
        case 593:
            rtx0     = 639199;
            rtx0_inv = 7612;
            break;
        case 594:
            rtx0     = 646808;
            rtx0_inv = 7606;
            break;
        case 595:
            rtx0     = 654410;
            rtx0_inv = 7599;
            break;
        case 596:
            rtx0     = 662006;
            rtx0_inv = 7593;
            break;
        case 597:
            rtx0     = 669596;
            rtx0_inv = 7586;
            break;
        case 598:
            rtx0     = 677179;
            rtx0_inv = 7580;
            break;
        case 599:
            rtx0     = 684756;
            rtx0_inv = 7574;
            break;
        case 600:
            rtx0     = 692327;
            rtx0_inv = 7567;
            break;
        case 601:
            rtx0     = 699891;
            rtx0_inv = 7561;
            break;
        case 602:
            rtx0     = 707449;
            rtx0_inv = 7555;
            break;
        case 603:
            rtx0     = 715001;
            rtx0_inv = 7549;
            break;
        case 604:
            rtx0     = 722546;
            rtx0_inv = 7542;
            break;
        case 605:
            rtx0     = 730085;
            rtx0_inv = 7536;
            break;
        case 606:
            rtx0     = 737618;
            rtx0_inv = 7530;
            break;
        case 607:
            rtx0     = 745145;
            rtx0_inv = 7524;
            break;
        case 608:
            rtx0     = 752666;
            rtx0_inv = 7517;
            break;
        case 609:
            rtx0     = 760180;
            rtx0_inv = 7511;
            break;
        case 610:
            rtx0     = 767688;
            rtx0_inv = 7505;
            break;
        case 611:
            rtx0     = 775190;
            rtx0_inv = 7499;
            break;
        case 612:
            rtx0     = 782686;
            rtx0_inv = 7493;
            break;
        case 613:
            rtx0     = 790176;
            rtx0_inv = 7487;
            break;
        case 614:
            rtx0     = 797660;
            rtx0_inv = 7481;
            break;
        case 615:
            rtx0     = 805138;
            rtx0_inv = 7475;
            break;
        case 616:
            rtx0     = 812609;
            rtx0_inv = 7469;
            break;
        case 617:
            rtx0     = 820075;
            rtx0_inv = 7462;
            break;
        case 618:
            rtx0     = 827534;
            rtx0_inv = 7456;
            break;
        case 619:
            rtx0     = 834987;
            rtx0_inv = 7450;
            break;
        case 620:
            rtx0     = 842435;
            rtx0_inv = 7444;
            break;
        case 621:
            rtx0     = 849876;
            rtx0_inv = 7438;
            break;
        case 622:
            rtx0     = 857312;
            rtx0_inv = 7432;
            break;
        case 623:
            rtx0     = 864741;
            rtx0_inv = 7426;
            break;
        case 624:
            rtx0     = 872164;
            rtx0_inv = 7420;
            break;
        case 625:
            rtx0     = 879582;
            rtx0_inv = 7415;
            break;
        case 626:
            rtx0     = 886994;
            rtx0_inv = 7409;
            break;
        case 627:
            rtx0     = 894399;
            rtx0_inv = 7403;
            break;
        case 628:
            rtx0     = 901799;
            rtx0_inv = 7397;
            break;
        case 629:
            rtx0     = 909193;
            rtx0_inv = 7391;
            break;
        case 630:
            rtx0     = 916581;
            rtx0_inv = 7385;
            break;
        case 631:
            rtx0     = 923963;
            rtx0_inv = 7379;
            break;
        case 632:
            rtx0     = 931339;
            rtx0_inv = 7373;
            break;
        case 633:
            rtx0     = 938710;
            rtx0_inv = 7368;
            break;
        case 634:
            rtx0     = 946074;
            rtx0_inv = 7362;
            break;
        case 635:
            rtx0     = 953433;
            rtx0_inv = 7356;
            break;
        case 636:
            rtx0     = 960786;
            rtx0_inv = 7350;
            break;
        case 637:
            rtx0     = 968134;
            rtx0_inv = 7344;
            break;
        case 638:
            rtx0     = 975475;
            rtx0_inv = 7339;
            break;
        case 639:
            rtx0     = 982811;
            rtx0_inv = 7333;
            break;
        case 640:
            rtx0     = 990141;
            rtx0_inv = 7327;
            break;
        case 641:
            rtx0     = 997465;
            rtx0_inv = 7321;
            break;
        case 642:
            rtx0     = 1004784;
            rtx0_inv = 7316;
            break;
        case 643:
            rtx0     = 1012097;
            rtx0_inv = 7310;
            break;
        case 644:
            rtx0     = 1019404;
            rtx0_inv = 7304;
            break;
        case 645:
            rtx0     = 1026705;
            rtx0_inv = 7299;
            break;
        case 646:
            rtx0     = 1034001;
            rtx0_inv = 7293;
            break;
        case 647:
            rtx0     = 1041291;
            rtx0_inv = 7287;
            break;
        case 648:
            rtx0     = 1048576;
            rtx0_inv = 7282;
            break;
        case 649:
            rtx0     = 1055855;
            rtx0_inv = 7276;
            break;
        case 650:
            rtx0     = 1063128;
            rtx0_inv = 7271;
            break;
        case 651:
            rtx0     = 1070396;
            rtx0_inv = 7265;
            break;
        case 652:
            rtx0     = 1077658;
            rtx0_inv = 7259;
            break;
        case 653:
            rtx0     = 1084915;
            rtx0_inv = 7254;
            break;
        case 654:
            rtx0     = 1092166;
            rtx0_inv = 7248;
            break;
        case 655:
            rtx0     = 1099412;
            rtx0_inv = 7243;
            break;
        case 656:
            rtx0     = 1106652;
            rtx0_inv = 7237;
            break;
        case 657:
            rtx0     = 1113886;
            rtx0_inv = 7232;
            break;
        case 658:
            rtx0     = 1121115;
            rtx0_inv = 7226;
            break;
        case 659:
            rtx0     = 1128338;
            rtx0_inv = 7221;
            break;
        case 660:
            rtx0     = 1135556;
            rtx0_inv = 7215;
            break;
        case 661:
            rtx0     = 1142769;
            rtx0_inv = 7210;
            break;
        case 662:
            rtx0     = 1149976;
            rtx0_inv = 7204;
            break;
        case 663:
            rtx0     = 1157178;
            rtx0_inv = 7199;
            break;
        case 664:
            rtx0     = 1164374;
            rtx0_inv = 7194;
            break;
        case 665:
            rtx0     = 1171565;
            rtx0_inv = 7188;
            break;
        case 666:
            rtx0     = 1178750;
            rtx0_inv = 7183;
            break;
        case 667:
            rtx0     = 1185930;
            rtx0_inv = 7177;
            break;
        case 668:
            rtx0     = 1193105;
            rtx0_inv = 7172;
            break;
        case 669:
            rtx0     = 1200274;
            rtx0_inv = 7167;
            break;
        case 670:
            rtx0     = 1207438;
            rtx0_inv = 7161;
            break;
        case 671:
            rtx0     = 1214597;
            rtx0_inv = 7156;
            break;
        case 672:
            rtx0     = 1221750;
            rtx0_inv = 7151;
            break;
        case 673:
            rtx0     = 1228898;
            rtx0_inv = 7145;
            break;
        case 674:
            rtx0     = 1236040;
            rtx0_inv = 7140;
            break;
        case 675:
            rtx0     = 1243178;
            rtx0_inv = 7135;
            break;
        case 676:
            rtx0     = 1250310;
            rtx0_inv = 7129;
            break;
        case 677:
            rtx0     = 1257436;
            rtx0_inv = 7124;
            break;
        case 678:
            rtx0     = 1264558;
            rtx0_inv = 7119;
            break;
        case 679:
            rtx0     = 1271674;
            rtx0_inv = 7114;
            break;
        case 680:
            rtx0     = 1278785;
            rtx0_inv = 7108;
            break;
        case 681:
            rtx0     = 1285891;
            rtx0_inv = 7103;
            break;
        case 682:
            rtx0     = 1292991;
            rtx0_inv = 7098;
            break;
        case 683:
            rtx0     = 1300087;
            rtx0_inv = 7093;
            break;
        case 684:
            rtx0     = 1307177;
            rtx0_inv = 7088;
            break;
        case 685:
            rtx0     = 1314262;
            rtx0_inv = 7082;
            break;
        case 686:
            rtx0     = 1321342;
            rtx0_inv = 7077;
            break;
        case 687:
            rtx0     = 1328416;
            rtx0_inv = 7072;
            break;
        case 688:
            rtx0     = 1335486;
            rtx0_inv = 7067;
            break;
        case 689:
            rtx0     = 1342550;
            rtx0_inv = 7062;
            break;
        case 690:
            rtx0     = 1349609;
            rtx0_inv = 7057;
            break;
        case 691:
            rtx0     = 1356664;
            rtx0_inv = 7052;
            break;
        case 692:
            rtx0     = 1363713;
            rtx0_inv = 7046;
            break;
        case 693:
            rtx0     = 1370756;
            rtx0_inv = 7041;
            break;
        case 694:
            rtx0     = 1377795;
            rtx0_inv = 7036;
            break;
        case 695:
            rtx0     = 1384829;
            rtx0_inv = 7031;
            break;
        case 696:
            rtx0     = 1391858;
            rtx0_inv = 7026;
            break;
        case 697:
            rtx0     = 1398881;
            rtx0_inv = 7021;
            break;
        case 698:
            rtx0     = 1405900;
            rtx0_inv = 7016;
            break;
        case 699:
            rtx0     = 1412914;
            rtx0_inv = 7011;
            break;
        case 700:
            rtx0     = 1419922;
            rtx0_inv = 7006;
            break;
        case 701:
            rtx0     = 1426926;
            rtx0_inv = 7001;
            break;
        case 702:
            rtx0     = 1433925;
            rtx0_inv = 6996;
            break;
        case 703:
            rtx0     = 1440918;
            rtx0_inv = 6991;
            break;
        case 704:
            rtx0     = 1447907;
            rtx0_inv = 6986;
            break;
        case 705:
            rtx0     = 1454890;
            rtx0_inv = 6981;
            break;
        case 706:
            rtx0     = 1461869;
            rtx0_inv = 6976;
            break;
        case 707:
            rtx0     = 1468843;
            rtx0_inv = 6971;
            break;
        case 708:
            rtx0     = 1475812;
            rtx0_inv = 6966;
            break;
        case 709:
            rtx0     = 1482776;
            rtx0_inv = 6961;
            break;
        case 710:
            rtx0     = 1489735;
            rtx0_inv = 6957;
            break;
        case 711:
            rtx0     = 1496689;
            rtx0_inv = 6952;
            break;
        case 712:
            rtx0     = 1503638;
            rtx0_inv = 6947;
            break;
        case 713:
            rtx0     = 1510583;
            rtx0_inv = 6942;
            break;
        case 714:
            rtx0     = 1517522;
            rtx0_inv = 6937;
            break;
        case 715:
            rtx0     = 1524457;
            rtx0_inv = 6932;
            break;
        case 716:
            rtx0     = 1531386;
            rtx0_inv = 6927;
            break;
        case 717:
            rtx0     = 1538311;
            rtx0_inv = 6923;
            break;
        case 718:
            rtx0     = 1545232;
            rtx0_inv = 6918;
            break;
        case 719:
            rtx0     = 1552147;
            rtx0_inv = 6913;
            break;
        case 720:
            rtx0     = 1559057;
            rtx0_inv = 6908;
            break;
        case 721:
            rtx0     = 1565963;
            rtx0_inv = 6903;
            break;
        case 722:
            rtx0     = 1572864;
            rtx0_inv = 6899;
            break;
        case 723:
            rtx0     = 1579760;
            rtx0_inv = 6894;
            break;
        case 724:
            rtx0     = 1586652;
            rtx0_inv = 6889;
            break;
        case 725:
            rtx0     = 1593538;
            rtx0_inv = 6884;
            break;
        case 726:
            rtx0     = 1600420;
            rtx0_inv = 6879;
            break;
        case 727:
            rtx0     = 1607297;
            rtx0_inv = 6875;
            break;
        case 728:
            rtx0     = 1614170;
            rtx0_inv = 6870;
            break;
        case 729:
            rtx0     = 1621037;
            rtx0_inv = 6865;
            break;
        case 730:
            rtx0     = 1627900;
            rtx0_inv = 6861;
            break;
        case 731:
            rtx0     = 1634758;
            rtx0_inv = 6856;
            break;
        case 732:
            rtx0     = 1641612;
            rtx0_inv = 6851;
            break;
        case 733:
            rtx0     = 1648461;
            rtx0_inv = 6847;
            break;
        case 734:
            rtx0     = 1655305;
            rtx0_inv = 6842;
            break;
        case 735:
            rtx0     = 1662145;
            rtx0_inv = 6837;
            break;
        case 736:
            rtx0     = 1668980;
            rtx0_inv = 6833;
            break;
        case 737:
            rtx0     = 1675810;
            rtx0_inv = 6828;
            break;
        case 738:
            rtx0     = 1682636;
            rtx0_inv = 6823;
            break;
        case 739:
            rtx0     = 1689457;
            rtx0_inv = 6819;
            break;
        case 740:
            rtx0     = 1696273;
            rtx0_inv = 6814;
            break;
        case 741:
            rtx0     = 1703085;
            rtx0_inv = 6810;
            break;
        case 742:
            rtx0     = 1709892;
            rtx0_inv = 6805;
            break;
        case 743:
            rtx0     = 1716695;
            rtx0_inv = 6800;
            break;
        case 744:
            rtx0     = 1723493;
            rtx0_inv = 6796;
            break;
        case 745:
            rtx0     = 1730286;
            rtx0_inv = 6791;
            break;
        case 746:
            rtx0     = 1737075;
            rtx0_inv = 6787;
            break;
        case 747:
            rtx0     = 1743860;
            rtx0_inv = 6782;
            break;
        case 748:
            rtx0     = 1750639;
            rtx0_inv = 6778;
            break;
        case 749:
            rtx0     = 1757415;
            rtx0_inv = 6773;
            break;
        case 750:
            rtx0     = 1764185;
            rtx0_inv = 6769;
            break;
        case 751:
            rtx0     = 1770952;
            rtx0_inv = 6764;
            break;
        case 752:
            rtx0     = 1777714;
            rtx0_inv = 6760;
            break;
        case 753:
            rtx0     = 1784471;
            rtx0_inv = 6755;
            break;
        case 754:
            rtx0     = 1791224;
            rtx0_inv = 6751;
            break;
        case 755:
            rtx0     = 1797972;
            rtx0_inv = 6746;
            break;
        case 756:
            rtx0     = 1804716;
            rtx0_inv = 6742;
            break;
        case 757:
            rtx0     = 1811455;
            rtx0_inv = 6737;
            break;
        case 758:
            rtx0     = 1818190;
            rtx0_inv = 6733;
            break;
        case 759:
            rtx0     = 1824921;
            rtx0_inv = 6728;
            break;
        case 760:
            rtx0     = 1831647;
            rtx0_inv = 6724;
            break;
        case 761:
            rtx0     = 1838368;
            rtx0_inv = 6719;
            break;
        case 762:
            rtx0     = 1845085;
            rtx0_inv = 6715;
            break;
        case 763:
            rtx0     = 1851798;
            rtx0_inv = 6711;
            break;
        case 764:
            rtx0     = 1858507;
            rtx0_inv = 6706;
            break;
        case 765:
            rtx0     = 1865211;
            rtx0_inv = 6702;
            break;
        case 766:
            rtx0     = 1871910;
            rtx0_inv = 6697;
            break;
        case 767:
            rtx0     = 1878606;
            rtx0_inv = 6693;
            break;
        case 768:
            rtx0     = 1885297;
            rtx0_inv = 6689;
            break;
        case 769:
            rtx0     = 1891983;
            rtx0_inv = 6684;
            break;
        case 770:
            rtx0     = 1898665;
            rtx0_inv = 6680;
            break;
        case 771:
            rtx0     = 1905343;
            rtx0_inv = 6676;
            break;
        case 772:
            rtx0     = 1912017;
            rtx0_inv = 6671;
            break;
        case 773:
            rtx0     = 1918686;
            rtx0_inv = 6667;
            break;
        case 774:
            rtx0     = 1925351;
            rtx0_inv = 6663;
            break;
        case 775:
            rtx0     = 1932012;
            rtx0_inv = 6658;
            break;
        case 776:
            rtx0     = 1938668;
            rtx0_inv = 6654;
            break;
        case 777:
            rtx0     = 1945320;
            rtx0_inv = 6650;
            break;
        case 778:
            rtx0     = 1951968;
            rtx0_inv = 6646;
            break;
        case 779:
            rtx0     = 1958611;
            rtx0_inv = 6641;
            break;
        case 780:
            rtx0     = 1965250;
            rtx0_inv = 6637;
            break;
        case 781:
            rtx0     = 1971885;
            rtx0_inv = 6633;
            break;
        case 782:
            rtx0     = 1978516;
            rtx0_inv = 6629;
            break;
        case 783:
            rtx0     = 1985143;
            rtx0_inv = 6624;
            break;
        case 784:
            rtx0     = 1991765;
            rtx0_inv = 6620;
            break;
        case 785:
            rtx0     = 1998383;
            rtx0_inv = 6616;
            break;
        case 786:
            rtx0     = 2004997;
            rtx0_inv = 6612;
            break;
        case 787:
            rtx0     = 2011606;
            rtx0_inv = 6608;
            break;
        case 788:
            rtx0     = 2018212;
            rtx0_inv = 6603;
            break;
        case 789:
            rtx0     = 2024813;
            rtx0_inv = 6599;
            break;
        case 790:
            rtx0     = 2031410;
            rtx0_inv = 6595;
            break;
        case 791:
            rtx0     = 2038003;
            rtx0_inv = 6591;
            break;
        case 792:
            rtx0     = 2044591;
            rtx0_inv = 6587;
            break;
        case 793:
            rtx0     = 2051176;
            rtx0_inv = 6582;
            break;
        case 794:
            rtx0     = 2057756;
            rtx0_inv = 6578;
            break;
        case 795:
            rtx0     = 2064333;
            rtx0_inv = 6574;
            break;
        case 796:
            rtx0     = 2070905;
            rtx0_inv = 6570;
            break;
        case 797:
            rtx0     = 2077473;
            rtx0_inv = 6566;
            break;
        case 798:
            rtx0     = 2084037;
            rtx0_inv = 6562;
            break;
        case 799:
            rtx0     = 2090596;
            rtx0_inv = 6558;
            break;
        case 800:
            rtx0     = 2097152;
            rtx0_inv = 6554;
            break;
        case 801:
            rtx0     = 2103704;
            rtx0_inv = 6550;
            break;
        case 802:
            rtx0     = 2110251;
            rtx0_inv = 6545;
            break;
        case 803:
            rtx0     = 2116794;
            rtx0_inv = 6541;
            break;
        case 804:
            rtx0     = 2123334;
            rtx0_inv = 6537;
            break;
        case 805:
            rtx0     = 2129869;
            rtx0_inv = 6533;
            break;
        case 806:
            rtx0     = 2136400;
            rtx0_inv = 6529;
            break;
        case 807:
            rtx0     = 2142927;
            rtx0_inv = 6525;
            break;
        case 808:
            rtx0     = 2149450;
            rtx0_inv = 6521;
            break;
        case 809:
            rtx0     = 2155969;
            rtx0_inv = 6517;
            break;
        case 810:
            rtx0     = 2162484;
            rtx0_inv = 6513;
            break;
        case 811:
            rtx0     = 2168995;
            rtx0_inv = 6509;
            break;
        case 812:
            rtx0     = 2175502;
            rtx0_inv = 6505;
            break;
        case 813:
            rtx0     = 2182005;
            rtx0_inv = 6501;
            break;
        case 814:
            rtx0     = 2188504;
            rtx0_inv = 6497;
            break;
        case 815:
            rtx0     = 2194999;
            rtx0_inv = 6493;
            break;
        case 816:
            rtx0     = 2201490;
            rtx0_inv = 6489;
            break;
        case 817:
            rtx0     = 2207978;
            rtx0_inv = 6485;
            break;
        case 818:
            rtx0     = 2214461;
            rtx0_inv = 6481;
            break;
        case 819:
            rtx0     = 2220940;
            rtx0_inv = 6477;
            break;
        case 820:
            rtx0     = 2227415;
            rtx0_inv = 6473;
            break;
        case 821:
            rtx0     = 2233886;
            rtx0_inv = 6469;
            break;
        case 822:
            rtx0     = 2240353;
            rtx0_inv = 6465;
            break;
        case 823:
            rtx0     = 2246817;
            rtx0_inv = 6461;
            break;
        case 824:
            rtx0     = 2253276;
            rtx0_inv = 6457;
            break;
        case 825:
            rtx0     = 2259732;
            rtx0_inv = 6454;
            break;
        case 826:
            rtx0     = 2266183;
            rtx0_inv = 6450;
            break;
        case 827:
            rtx0     = 2272631;
            rtx0_inv = 6446;
            break;
        case 828:
            rtx0     = 2279075;
            rtx0_inv = 6442;
            break;
        case 829:
            rtx0     = 2285515;
            rtx0_inv = 6438;
            break;
        case 830:
            rtx0     = 2291951;
            rtx0_inv = 6434;
            break;
        case 831:
            rtx0     = 2298383;
            rtx0_inv = 6430;
            break;
        case 832:
            rtx0     = 2304811;
            rtx0_inv = 6426;
            break;
        case 833:
            rtx0     = 2311235;
            rtx0_inv = 6422;
            break;
        case 834:
            rtx0     = 2317656;
            rtx0_inv = 6419;
            break;
        case 835:
            rtx0     = 2324073;
            rtx0_inv = 6415;
            break;
        case 836:
            rtx0     = 2330485;
            rtx0_inv = 6411;
            break;
        case 837:
            rtx0     = 2336895;
            rtx0_inv = 6407;
            break;
        case 838:
            rtx0     = 2343300;
            rtx0_inv = 6403;
            break;
        case 839:
            rtx0     = 2349701;
            rtx0_inv = 6399;
            break;
        case 840:
            rtx0     = 2356099;
            rtx0_inv = 6396;
            break;
        case 841:
            rtx0     = 2362492;
            rtx0_inv = 6392;
            break;
        case 842:
            rtx0     = 2368882;
            rtx0_inv = 6388;
            break;
        case 843:
            rtx0     = 2375269;
            rtx0_inv = 6384;
            break;
        case 844:
            rtx0     = 2381651;
            rtx0_inv = 6380;
            break;
        case 845:
            rtx0     = 2388029;
            rtx0_inv = 6377;
            break;
        case 846:
            rtx0     = 2394404;
            rtx0_inv = 6373;
            break;
        case 847:
            rtx0     = 2400775;
            rtx0_inv = 6369;
            break;
        case 848:
            rtx0     = 2407143;
            rtx0_inv = 6365;
            break;
        case 849:
            rtx0     = 2413506;
            rtx0_inv = 6362;
            break;
        case 850:
            rtx0     = 2419866;
            rtx0_inv = 6358;
            break;
        case 851:
            rtx0     = 2426222;
            rtx0_inv = 6354;
            break;
        case 852:
            rtx0     = 2432574;
            rtx0_inv = 6350;
            break;
        case 853:
            rtx0     = 2438923;
            rtx0_inv = 6347;
            break;
        case 854:
            rtx0     = 2445268;
            rtx0_inv = 6343;
            break;
        case 855:
            rtx0     = 2451609;
            rtx0_inv = 6339;
            break;
        case 856:
            rtx0     = 2457946;
            rtx0_inv = 6336;
            break;
        case 857:
            rtx0     = 2464280;
            rtx0_inv = 6332;
            break;
        case 858:
            rtx0     = 2470610;
            rtx0_inv = 6328;
            break;
        case 859:
            rtx0     = 2476937;
            rtx0_inv = 6325;
            break;
        case 860:
            rtx0     = 2483259;
            rtx0_inv = 6321;
            break;
        case 861:
            rtx0     = 2489578;
            rtx0_inv = 6317;
            break;
        case 862:
            rtx0     = 2495894;
            rtx0_inv = 6314;
            break;
        case 863:
            rtx0     = 2502205;
            rtx0_inv = 6310;
            break;
        case 864:
            rtx0     = 2508513;
            rtx0_inv = 6306;
            break;
        case 865:
            rtx0     = 2514818;
            rtx0_inv = 6303;
            break;
        case 866:
            rtx0     = 2521119;
            rtx0_inv = 6299;
            break;
        case 867:
            rtx0     = 2527416;
            rtx0_inv = 6295;
            break;
        case 868:
            rtx0     = 2533709;
            rtx0_inv = 6292;
            break;
        case 869:
            rtx0     = 2539999;
            rtx0_inv = 6288;
            break;
        case 870:
            rtx0     = 2546285;
            rtx0_inv = 6284;
            break;
        case 871:
            rtx0     = 2552568;
            rtx0_inv = 6281;
            break;
        case 872:
            rtx0     = 2558847;
            rtx0_inv = 6277;
            break;
        case 873:
            rtx0     = 2565122;
            rtx0_inv = 6274;
            break;
        case 874:
            rtx0     = 2571394;
            rtx0_inv = 6270;
            break;
        case 875:
            rtx0     = 2577662;
            rtx0_inv = 6266;
            break;
        case 876:
            rtx0     = 2583927;
            rtx0_inv = 6263;
            break;
        case 877:
            rtx0     = 2590188;
            rtx0_inv = 6259;
            break;
        case 878:
            rtx0     = 2596446;
            rtx0_inv = 6256;
            break;
        case 879:
            rtx0     = 2602699;
            rtx0_inv = 6252;
            break;
        case 880:
            rtx0     = 2608950;
            rtx0_inv = 6249;
            break;
        case 881:
            rtx0     = 2615197;
            rtx0_inv = 6245;
            break;
        case 882:
            rtx0     = 2621440;
            rtx0_inv = 6242;
            break;
        case 883:
            rtx0     = 2627680;
            rtx0_inv = 6238;
            break;
        case 884:
            rtx0     = 2633916;
            rtx0_inv = 6234;
            break;
        case 885:
            rtx0     = 2640149;
            rtx0_inv = 6231;
            break;
        case 886:
            rtx0     = 2646378;
            rtx0_inv = 6227;
            break;
        case 887:
            rtx0     = 2652604;
            rtx0_inv = 6224;
            break;
        case 888:
            rtx0     = 2658826;
            rtx0_inv = 6220;
            break;
        case 889:
            rtx0     = 2665044;
            rtx0_inv = 6217;
            break;
        case 890:
            rtx0     = 2671259;
            rtx0_inv = 6213;
            break;
        case 891:
            rtx0     = 2677471;
            rtx0_inv = 6210;
            break;
        case 892:
            rtx0     = 2683679;
            rtx0_inv = 6206;
            break;
        case 893:
            rtx0     = 2689884;
            rtx0_inv = 6203;
            break;
        case 894:
            rtx0     = 2696085;
            rtx0_inv = 6199;
            break;
        case 895:
            rtx0     = 2702283;
            rtx0_inv = 6196;
            break;
        case 896:
            rtx0     = 2708477;
            rtx0_inv = 6193;
            break;
        case 897:
            rtx0     = 2714668;
            rtx0_inv = 6189;
            break;
        case 898:
            rtx0     = 2720856;
            rtx0_inv = 6186;
            break;
        case 899:
            rtx0     = 2727039;
            rtx0_inv = 6182;
            break;
        case 900:
            rtx0     = 2733220;
            rtx0_inv = 6179;
            break;
        case 901:
            rtx0     = 2739397;
            rtx0_inv = 6175;
            break;
        case 902:
            rtx0     = 2745571;
            rtx0_inv = 6172;
            break;
        case 903:
            rtx0     = 2751741;
            rtx0_inv = 6169;
            break;
        case 904:
            rtx0     = 2757908;
            rtx0_inv = 6165;
            break;
        case 905:
            rtx0     = 2764071;
            rtx0_inv = 6162;
            break;
        case 906:
            rtx0     = 2770231;
            rtx0_inv = 6158;
            break;
        case 907:
            rtx0     = 2776388;
            rtx0_inv = 6155;
            break;
        case 908:
            rtx0     = 2782541;
            rtx0_inv = 6152;
            break;
        case 909:
            rtx0     = 2788691;
            rtx0_inv = 6148;
            break;
        case 910:
            rtx0     = 2794837;
            rtx0_inv = 6145;
            break;
        case 911:
            rtx0     = 2800980;
            rtx0_inv = 6141;
            break;
        case 912:
            rtx0     = 2807120;
            rtx0_inv = 6138;
            break;
        case 913:
            rtx0     = 2813256;
            rtx0_inv = 6135;
            break;
        case 914:
            rtx0     = 2819389;
            rtx0_inv = 6131;
            break;
        case 915:
            rtx0     = 2825519;
            rtx0_inv = 6128;
            break;
        case 916:
            rtx0     = 2831645;
            rtx0_inv = 6125;
            break;
        case 917:
            rtx0     = 2837768;
            rtx0_inv = 6121;
            break;
        case 918:
            rtx0     = 2843888;
            rtx0_inv = 6118;
            break;
        case 919:
            rtx0     = 2850004;
            rtx0_inv = 6115;
            break;
        case 920:
            rtx0     = 2856117;
            rtx0_inv = 6111;
            break;
        case 921:
            rtx0     = 2862226;
            rtx0_inv = 6108;
            break;
        case 922:
            rtx0     = 2868333;
            rtx0_inv = 6105;
            break;
        case 923:
            rtx0     = 2874436;
            rtx0_inv = 6101;
            break;
        case 924:
            rtx0     = 2880535;
            rtx0_inv = 6098;
            break;
        case 925:
            rtx0     = 2886632;
            rtx0_inv = 6095;
            break;
        case 926:
            rtx0     = 2892725;
            rtx0_inv = 6091;
            break;
        case 927:
            rtx0     = 2898815;
            rtx0_inv = 6088;
            break;
        case 928:
            rtx0     = 2904901;
            rtx0_inv = 6085;
            break;
        case 929:
            rtx0     = 2910984;
            rtx0_inv = 6082;
            break;
        case 930:
            rtx0     = 2917064;
            rtx0_inv = 6078;
            break;
        case 931:
            rtx0     = 2923141;
            rtx0_inv = 6075;
            break;
        case 932:
            rtx0     = 2929214;
            rtx0_inv = 6072;
            break;
        case 933:
            rtx0     = 2935285;
            rtx0_inv = 6069;
            break;
        case 934:
            rtx0     = 2941352;
            rtx0_inv = 6065;
            break;
        case 935:
            rtx0     = 2947415;
            rtx0_inv = 6062;
            break;
        case 936:
            rtx0     = 2953476;
            rtx0_inv = 6059;
            break;
        case 937:
            rtx0     = 2959533;
            rtx0_inv = 6056;
            break;
        case 938:
            rtx0     = 2965587;
            rtx0_inv = 6052;
            break;
        case 939:
            rtx0     = 2971637;
            rtx0_inv = 6049;
            break;
        case 940:
            rtx0     = 2977685;
            rtx0_inv = 6046;
            break;
        case 941:
            rtx0     = 2983729;
            rtx0_inv = 6043;
            break;
        case 942:
            rtx0     = 2989770;
            rtx0_inv = 6039;
            break;
        case 943:
            rtx0     = 2995808;
            rtx0_inv = 6036;
            break;
        case 944:
            rtx0     = 3001843;
            rtx0_inv = 6033;
            break;
        case 945:
            rtx0     = 3007874;
            rtx0_inv = 6030;
            break;
        case 946:
            rtx0     = 3013903;
            rtx0_inv = 6027;
            break;
        case 947:
            rtx0     = 3019928;
            rtx0_inv = 6024;
            break;
        case 948:
            rtx0     = 3025950;
            rtx0_inv = 6020;
            break;
        case 949:
            rtx0     = 3031968;
            rtx0_inv = 6017;
            break;
        case 950:
            rtx0     = 3037984;
            rtx0_inv = 6014;
            break;
        case 951:
            rtx0     = 3043996;
            rtx0_inv = 6011;
            break;
        case 952:
            rtx0     = 3050006;
            rtx0_inv = 6008;
            break;
        case 953:
            rtx0     = 3056012;
            rtx0_inv = 6005;
            break;
        case 954:
            rtx0     = 3062015;
            rtx0_inv = 6001;
            break;
        case 955:
            rtx0     = 3068015;
            rtx0_inv = 5998;
            break;
        case 956:
            rtx0     = 3074011;
            rtx0_inv = 5995;
            break;
        case 957:
            rtx0     = 3080005;
            rtx0_inv = 5992;
            break;
        case 958:
            rtx0     = 3085995;
            rtx0_inv = 5989;
            break;
        case 959:
            rtx0     = 3091982;
            rtx0_inv = 5986;
            break;
        case 960:
            rtx0     = 3097967;
            rtx0_inv = 5983;
            break;
        case 961:
            rtx0     = 3103948;
            rtx0_inv = 5979;
            break;
        case 962:
            rtx0     = 3109926;
            rtx0_inv = 5976;
            break;
        case 963:
            rtx0     = 3115900;
            rtx0_inv = 5973;
            break;
        case 964:
            rtx0     = 3121872;
            rtx0_inv = 5970;
            break;
        case 965:
            rtx0     = 3127841;
            rtx0_inv = 5967;
            break;
        case 966:
            rtx0     = 3133806;
            rtx0_inv = 5964;
            break;
        case 967:
            rtx0     = 3139769;
            rtx0_inv = 5961;
            break;
        case 968:
            rtx0     = 3145728;
            rtx0_inv = 5958;
            break;
        case 969:
            rtx0     = 3151684;
            rtx0_inv = 5955;
            break;
        case 970:
            rtx0     = 3157637;
            rtx0_inv = 5952;
            break;
        case 971:
            rtx0     = 3163588;
            rtx0_inv = 5949;
            break;
        case 972:
            rtx0     = 3169535;
            rtx0_inv = 5946;
            break;
        case 973:
            rtx0     = 3175479;
            rtx0_inv = 5942;
            break;
        case 974:
            rtx0     = 3181420;
            rtx0_inv = 5939;
            break;
        case 975:
            rtx0     = 3187358;
            rtx0_inv = 5936;
            break;
        case 976:
            rtx0     = 3193292;
            rtx0_inv = 5933;
            break;
        case 977:
            rtx0     = 3199224;
            rtx0_inv = 5930;
            break;
        case 978:
            rtx0     = 3205153;
            rtx0_inv = 5927;
            break;
        case 979:
            rtx0     = 3211079;
            rtx0_inv = 5924;
            break;
        case 980:
            rtx0     = 3217002;
            rtx0_inv = 5921;
            break;
        case 981:
            rtx0     = 3222921;
            rtx0_inv = 5918;
            break;
        case 982:
            rtx0     = 3228838;
            rtx0_inv = 5915;
            break;
        case 983:
            rtx0     = 3234752;
            rtx0_inv = 5912;
            break;
        case 984:
            rtx0     = 3240662;
            rtx0_inv = 5909;
            break;
        case 985:
            rtx0     = 3246570;
            rtx0_inv = 5906;
            break;
        case 986:
            rtx0     = 3252475;
            rtx0_inv = 5903;
            break;
        case 987:
            rtx0     = 3258376;
            rtx0_inv = 5900;
            break;
        case 988:
            rtx0     = 3264275;
            rtx0_inv = 5897;
            break;
        case 989:
            rtx0     = 3270171;
            rtx0_inv = 5894;
            break;
        case 990:
            rtx0     = 3276064;
            rtx0_inv = 5891;
            break;
        case 991:
            rtx0     = 3281953;
            rtx0_inv = 5888;
            break;
        case 992:
            rtx0     = 3287840;
            rtx0_inv = 5885;
            break;
        case 993:
            rtx0     = 3293724;
            rtx0_inv = 5882;
            break;
        case 994:
            rtx0     = 3299605;
            rtx0_inv = 5879;
            break;
        case 995:
            rtx0     = 3305483;
            rtx0_inv = 5876;
            break;
        case 996:
            rtx0     = 3311358;
            rtx0_inv = 5873;
            break;
        case 997:
            rtx0     = 3317230;
            rtx0_inv = 5871;
            break;
        case 998:
            rtx0     = 3323099;
            rtx0_inv = 5868;
            break;
        case 999:
            rtx0     = 3328965;
            rtx0_inv = 5865;
            break;
        case 1000:
            rtx0     = 3334828;
            rtx0_inv = 5862;
            break;
        case 1001:
            rtx0     = 3340688;
            rtx0_inv = 5859;
            break;
        case 1002:
            rtx0     = 3346546;
            rtx0_inv = 5856;
            break;
        case 1003:
            rtx0     = 3352400;
            rtx0_inv = 5853;
            break;
        case 1004:
            rtx0     = 3358252;
            rtx0_inv = 5850;
            break;
        case 1005:
            rtx0     = 3364100;
            rtx0_inv = 5847;
            break;
        case 1006:
            rtx0     = 3369946;
            rtx0_inv = 5844;
            break;
        case 1007:
            rtx0     = 3375789;
            rtx0_inv = 5841;
            break;
        case 1008:
            rtx0     = 3381628;
            rtx0_inv = 5838;
            break;
        case 1009:
            rtx0     = 3387465;
            rtx0_inv = 5836;
            break;
        case 1010:
            rtx0     = 3393299;
            rtx0_inv = 5833;
            break;
        case 1011:
            rtx0     = 3399131;
            rtx0_inv = 5830;
            break;
        case 1012:
            rtx0     = 3404959;
            rtx0_inv = 5827;
            break;
        case 1013:
            rtx0     = 3410784;
            rtx0_inv = 5824;
            break;
        case 1014:
            rtx0     = 3416607;
            rtx0_inv = 5821;
            break;
        case 1015:
            rtx0     = 3422427;
            rtx0_inv = 5818;
            break;
        case 1016:
            rtx0     = 3428243;
            rtx0_inv = 5815;
            break;
        case 1017:
            rtx0     = 3434057;
            rtx0_inv = 5813;
            break;
        case 1018:
            rtx0     = 3439868;
            rtx0_inv = 5810;
            break;
        case 1019:
            rtx0     = 3445677;
            rtx0_inv = 5807;
            break;
        case 1020:
            rtx0     = 3451482;
            rtx0_inv = 5804;
            break;
        case 1021:
            rtx0     = 3457285;
            rtx0_inv = 5801;
            break;
        case 1022:
            rtx0     = 3463084;
            rtx0_inv = 5798;
            break;
        case 1023:
            rtx0     = 3468881;
            rtx0_inv = 5795;
            break;
        case 0:
            rtx0     = 3474675;
            rtx0_inv = 11585;
            break;
        case 1:
            rtx0     = 3486255;
            rtx0_inv = 11574;
            break;
        case 2:
            rtx0     = 3497823;
            rtx0_inv = 11563;
            break;
        case 3:
            rtx0     = 3509380;
            rtx0_inv = 11551;
            break;
        case 4:
            rtx0     = 3520926;
            rtx0_inv = 11540;
            break;
        case 5:
            rtx0     = 3532461;
            rtx0_inv = 11529;
            break;
        case 6:
            rtx0     = 3543984;
            rtx0_inv = 11518;
            break;
        case 7:
            rtx0     = 3555497;
            rtx0_inv = 11507;
            break;
        case 8:
            rtx0     = 3566998;
            rtx0_inv = 11496;
            break;
        case 9:
            rtx0     = 3578488;
            rtx0_inv = 11485;
            break;
        case 10:
            rtx0     = 3589967;
            rtx0_inv = 11474;
            break;
        case 11:
            rtx0     = 3601436;
            rtx0_inv = 11463;
            break;
        case 12:
            rtx0     = 3612893;
            rtx0_inv = 11452;
            break;
        case 13:
            rtx0     = 3624339;
            rtx0_inv = 11441;
            break;
        case 14:
            rtx0     = 3635775;
            rtx0_inv = 11430;
            break;
        case 15:
            rtx0     = 3647199;
            rtx0_inv = 11419;
            break;
        case 16:
            rtx0     = 3658613;
            rtx0_inv = 11408;
            break;
        case 17:
            rtx0     = 3670016;
            rtx0_inv = 11398;
            break;
        case 18:
            rtx0     = 3681408;
            rtx0_inv = 11387;
            break;
        case 19:
            rtx0     = 3692790;
            rtx0_inv = 11376;
            break;
        case 20:
            rtx0     = 3704160;
            rtx0_inv = 11365;
            break;
        case 21:
            rtx0     = 3715520;
            rtx0_inv = 11355;
            break;
        case 22:
            rtx0     = 3726870;
            rtx0_inv = 11344;
            break;
        case 23:
            rtx0     = 3738209;
            rtx0_inv = 11333;
            break;
        case 24:
            rtx0     = 3749537;
            rtx0_inv = 11323;
            break;
        case 25:
            rtx0     = 3760854;
            rtx0_inv = 11312;
            break;
        case 26:
            rtx0     = 3772161;
            rtx0_inv = 11302;
            break;
        case 27:
            rtx0     = 3783458;
            rtx0_inv = 11291;
            break;
        case 28:
            rtx0     = 3794744;
            rtx0_inv = 11281;
            break;
        case 29:
            rtx0     = 3806020;
            rtx0_inv = 11270;
            break;
        case 30:
            rtx0     = 3817285;
            rtx0_inv = 11260;
            break;
        case 31:
            rtx0     = 3828540;
            rtx0_inv = 11250;
            break;
        case 32:
            rtx0     = 3839784;
            rtx0_inv = 11239;
            break;
        case 33:
            rtx0     = 3851019;
            rtx0_inv = 11229;
            break;
        case 34:
            rtx0     = 3862242;
            rtx0_inv = 11219;
            break;
        case 35:
            rtx0     = 3873456;
            rtx0_inv = 11208;
            break;
        case 36:
            rtx0     = 3884659;
            rtx0_inv = 11198;
            break;
        case 37:
            rtx0     = 3895853;
            rtx0_inv = 11188;
            break;
        case 38:
            rtx0     = 3907035;
            rtx0_inv = 11178;
            break;
        case 39:
            rtx0     = 3918208;
            rtx0_inv = 11168;
            break;
        case 40:
            rtx0     = 3929371;
            rtx0_inv = 11158;
            break;
        case 41:
            rtx0     = 3940523;
            rtx0_inv = 11147;
            break;
        case 42:
            rtx0     = 3951666;
            rtx0_inv = 11137;
            break;
        case 43:
            rtx0     = 3962798;
            rtx0_inv = 11127;
            break;
        case 44:
            rtx0     = 3973921;
            rtx0_inv = 11117;
            break;
        case 45:
            rtx0     = 3985033;
            rtx0_inv = 11107;
            break;
        case 46:
            rtx0     = 3996136;
            rtx0_inv = 11097;
            break;
        case 47:
            rtx0     = 4007228;
            rtx0_inv = 11088;
            break;
        case 48:
            rtx0     = 4018311;
            rtx0_inv = 11078;
            break;
        case 49:
            rtx0     = 4029383;
            rtx0_inv = 11068;
            break;
        case 50:
            rtx0     = 4040446;
            rtx0_inv = 11058;
            break;
        case 51:
            rtx0     = 4051499;
            rtx0_inv = 11048;
            break;
        case 52:
            rtx0     = 4062542;
            rtx0_inv = 11038;
            break;
        case 53:
            rtx0     = 4073575;
            rtx0_inv = 11028;
            break;
        case 54:
            rtx0     = 4084599;
            rtx0_inv = 11019;
            break;
        case 55:
            rtx0     = 4095613;
            rtx0_inv = 11009;
            break;
        case 56:
            rtx0     = 4106617;
            rtx0_inv = 10999;
            break;
        case 57:
            rtx0     = 4117612;
            rtx0_inv = 10990;
            break;
        case 58:
            rtx0     = 4128596;
            rtx0_inv = 10980;
            break;
        case 59:
            rtx0     = 4139572;
            rtx0_inv = 10970;
            break;
        case 60:
            rtx0     = 4150537;
            rtx0_inv = 10961;
            break;
        case 61:
            rtx0     = 4161493;
            rtx0_inv = 10951;
            break;
        case 62:
            rtx0     = 4172440;
            rtx0_inv = 10942;
            break;
        case 63:
            rtx0     = 4183377;
            rtx0_inv = 10932;
            break;
        case 64:
            rtx0     = 4194304;
            rtx0_inv = 10923;
            break;
        case 65:
            rtx0     = 4205222;
            rtx0_inv = 10913;
            break;
        case 66:
            rtx0     = 4216130;
            rtx0_inv = 10904;
            break;
        case 67:
            rtx0     = 4227029;
            rtx0_inv = 10894;
            break;
        case 68:
            rtx0     = 4237919;
            rtx0_inv = 10885;
            break;
        case 69:
            rtx0     = 4248799;
            rtx0_inv = 10876;
            break;
        case 70:
            rtx0     = 4259670;
            rtx0_inv = 10866;
            break;
        case 71:
            rtx0     = 4270532;
            rtx0_inv = 10857;
            break;
        case 72:
            rtx0     = 4281384;
            rtx0_inv = 10848;
            break;
        case 73:
            rtx0     = 4292227;
            rtx0_inv = 10838;
            break;
        case 74:
            rtx0     = 4303061;
            rtx0_inv = 10829;
            break;
        case 75:
            rtx0     = 4313885;
            rtx0_inv = 10820;
            break;
        case 76:
            rtx0     = 4324700;
            rtx0_inv = 10811;
            break;
        case 77:
            rtx0     = 4335506;
            rtx0_inv = 10801;
            break;
        case 78:
            rtx0     = 4346303;
            rtx0_inv = 10792;
            break;
        case 79:
            rtx0     = 4357091;
            rtx0_inv = 10783;
            break;
        case 80:
            rtx0     = 4367870;
            rtx0_inv = 10774;
            break;
        case 81:
            rtx0     = 4378639;
            rtx0_inv = 10765;
            break;
        case 82:
            rtx0     = 4389400;
            rtx0_inv = 10756;
            break;
        case 83:
            rtx0     = 4400151;
            rtx0_inv = 10747;
            break;
        case 84:
            rtx0     = 4410893;
            rtx0_inv = 10738;
            break;
        case 85:
            rtx0     = 4421627;
            rtx0_inv = 10729;
            break;
        case 86:
            rtx0     = 4432351;
            rtx0_inv = 10720;
            break;
        case 87:
            rtx0     = 4443066;
            rtx0_inv = 10711;
            break;
        case 88:
            rtx0     = 4453773;
            rtx0_inv = 10702;
            break;
        case 89:
            rtx0     = 4464470;
            rtx0_inv = 10693;
            break;
        case 90:
            rtx0     = 4475159;
            rtx0_inv = 10684;
            break;
        case 91:
            rtx0     = 4485839;
            rtx0_inv = 10675;
            break;
        case 92:
            rtx0     = 4496510;
            rtx0_inv = 10666;
            break;
        case 93:
            rtx0     = 4507172;
            rtx0_inv = 10658;
            break;
        case 94:
            rtx0     = 4517825;
            rtx0_inv = 10649;
            break;
        case 95:
            rtx0     = 4528469;
            rtx0_inv = 10640;
            break;
        case 96:
            rtx0     = 4539105;
            rtx0_inv = 10631;
            break;
        case 97:
            rtx0     = 4549732;
            rtx0_inv = 10623;
            break;
        case 98:
            rtx0     = 4560350;
            rtx0_inv = 10614;
            break;
        case 99:
            rtx0     = 4570960;
            rtx0_inv = 10605;
            break;
        case 100:
            rtx0     = 4581561;
            rtx0_inv = 10597;
            break;
        case 101:
            rtx0     = 4592153;
            rtx0_inv = 10588;
            break;
        case 102:
            rtx0     = 4602737;
            rtx0_inv = 10579;
            break;
        case 103:
            rtx0     = 4613312;
            rtx0_inv = 10571;
            break;
        case 104:
            rtx0     = 4623878;
            rtx0_inv = 10562;
            break;
        case 105:
            rtx0     = 4634436;
            rtx0_inv = 10554;
            break;
        case 106:
            rtx0     = 4644985;
            rtx0_inv = 10545;
            break;
        case 107:
            rtx0     = 4655526;
            rtx0_inv = 10536;
            break;
        case 108:
            rtx0     = 4666058;
            rtx0_inv = 10528;
            break;
        case 109:
            rtx0     = 4676582;
            rtx0_inv = 10519;
            break;
        case 110:
            rtx0     = 4687097;
            rtx0_inv = 10511;
            break;
        case 111:
            rtx0     = 4697604;
            rtx0_inv = 10503;
            break;
        case 112:
            rtx0     = 4708102;
            rtx0_inv = 10494;
            break;
        case 113:
            rtx0     = 4718592;
            rtx0_inv = 10486;
            break;
        case 114:
            rtx0     = 4729074;
            rtx0_inv = 10477;
            break;
        case 115:
            rtx0     = 4739547;
            rtx0_inv = 10469;
            break;
        case 116:
            rtx0     = 4750012;
            rtx0_inv = 10461;
            break;
        case 117:
            rtx0     = 4760468;
            rtx0_inv = 10452;
            break;
        case 118:
            rtx0     = 4770916;
            rtx0_inv = 10444;
            break;
        case 119:
            rtx0     = 4781356;
            rtx0_inv = 10436;
            break;
        case 120:
            rtx0     = 4791788;
            rtx0_inv = 10428;
            break;
        case 121:
            rtx0     = 4802211;
            rtx0_inv = 10419;
            break;
        case 122:
            rtx0     = 4812627;
            rtx0_inv = 10411;
            break;
        case 123:
            rtx0     = 4823033;
            rtx0_inv = 10403;
            break;
        case 124:
            rtx0     = 4833432;
            rtx0_inv = 10395;
            break;
        case 125:
            rtx0     = 4843823;
            rtx0_inv = 10387;
            break;
        case 126:
            rtx0     = 4854205;
            rtx0_inv = 10378;
            break;
        case 127:
            rtx0     = 4864580;
            rtx0_inv = 10370;
            break;
        case 128:
            rtx0     = 4874946;
            rtx0_inv = 10362;
            break;
        case 129:
            rtx0     = 4885304;
            rtx0_inv = 10354;
            break;
        case 130:
            rtx0     = 4895654;
            rtx0_inv = 10346;
            break;
        case 131:
            rtx0     = 4905996;
            rtx0_inv = 10338;
            break;
        case 132:
            rtx0     = 4916330;
            rtx0_inv = 10330;
            break;
        case 133:
            rtx0     = 4926656;
            rtx0_inv = 10322;
            break;
        case 134:
            rtx0     = 4936974;
            rtx0_inv = 10314;
            break;
        case 135:
            rtx0     = 4947284;
            rtx0_inv = 10306;
            break;
        case 136:
            rtx0     = 4957586;
            rtx0_inv = 10298;
            break;
        case 137:
            rtx0     = 4967880;
            rtx0_inv = 10290;
            break;
        case 138:
            rtx0     = 4978166;
            rtx0_inv = 10282;
            break;
        case 139:
            rtx0     = 4988444;
            rtx0_inv = 10274;
            break;
        case 140:
            rtx0     = 4998714;
            rtx0_inv = 10266;
            break;
        case 141:
            rtx0     = 5008977;
            rtx0_inv = 10258;
            break;
        case 142:
            rtx0     = 5019231;
            rtx0_inv = 10251;
            break;
        case 143:
            rtx0     = 5029478;
            rtx0_inv = 10243;
            break;
        case 144:
            rtx0     = 5039717;
            rtx0_inv = 10235;
            break;
        case 145:
            rtx0     = 5049948;
            rtx0_inv = 10227;
            break;
        case 146:
            rtx0     = 5060171;
            rtx0_inv = 10219;
            break;
        case 147:
            rtx0     = 5070387;
            rtx0_inv = 10212;
            break;
        case 148:
            rtx0     = 5080595;
            rtx0_inv = 10204;
            break;
        case 149:
            rtx0     = 5090795;
            rtx0_inv = 10196;
            break;
        case 150:
            rtx0     = 5100987;
            rtx0_inv = 10189;
            break;
        case 151:
            rtx0     = 5111172;
            rtx0_inv = 10181;
            break;
        case 152:
            rtx0     = 5121349;
            rtx0_inv = 10173;
            break;
        case 153:
            rtx0     = 5131518;
            rtx0_inv = 10166;
            break;
        case 154:
            rtx0     = 5141680;
            rtx0_inv = 10158;
            break;
        case 155:
            rtx0     = 5151834;
            rtx0_inv = 10150;
            break;
        case 156:
            rtx0     = 5161980;
            rtx0_inv = 10143;
            break;
        case 157:
            rtx0     = 5172119;
            rtx0_inv = 10135;
            break;
        case 158:
            rtx0     = 5182250;
            rtx0_inv = 10128;
            break;
        case 159:
            rtx0     = 5192374;
            rtx0_inv = 10120;
            break;
        case 160:
            rtx0     = 5202490;
            rtx0_inv = 10112;
            break;
        case 161:
            rtx0     = 5212599;
            rtx0_inv = 10105;
            break;
        case 162:
            rtx0     = 5222700;
            rtx0_inv = 10097;
            break;
        case 163:
            rtx0     = 5232794;
            rtx0_inv = 10090;
            break;
        case 164:
            rtx0     = 5242880;
            rtx0_inv = 10082;
            break;
        case 165:
            rtx0     = 5252959;
            rtx0_inv = 10075;
            break;
        case 166:
            rtx0     = 5263030;
            rtx0_inv = 10068;
            break;
        case 167:
            rtx0     = 5273094;
            rtx0_inv = 10060;
            break;
        case 168:
            rtx0     = 5283150;
            rtx0_inv = 10053;
            break;
        case 169:
            rtx0     = 5293199;
            rtx0_inv = 10045;
            break;
        case 170:
            rtx0     = 5303241;
            rtx0_inv = 10038;
            break;
        case 171:
            rtx0     = 5313275;
            rtx0_inv = 10031;
            break;
        case 172:
            rtx0     = 5323302;
            rtx0_inv = 10023;
            break;
        case 173:
            rtx0     = 5333322;
            rtx0_inv = 10016;
            break;
        case 174:
            rtx0     = 5343334;
            rtx0_inv = 10009;
            break;
        case 175:
            rtx0     = 5353340;
            rtx0_inv = 10001;
            break;
        case 176:
            rtx0     = 5363337;
            rtx0_inv = 9994;
            break;
        case 177:
            rtx0     = 5373328;
            rtx0_inv = 9987;
            break;
        case 178:
            rtx0     = 5383311;
            rtx0_inv = 9980;
            break;
        case 179:
            rtx0     = 5393287;
            rtx0_inv = 9972;
            break;
        case 180:
            rtx0     = 5403256;
            rtx0_inv = 9965;
            break;
        case 181:
            rtx0     = 5413218;
            rtx0_inv = 9958;
            break;
        case 182:
            rtx0     = 5423172;
            rtx0_inv = 9951;
            break;
        case 183:
            rtx0     = 5433119;
            rtx0_inv = 9944;
            break;
        case 184:
            rtx0     = 5443059;
            rtx0_inv = 9937;
            break;
        case 185:
            rtx0     = 5452992;
            rtx0_inv = 9929;
            break;
        case 186:
            rtx0     = 5462918;
            rtx0_inv = 9922;
            break;
        case 187:
            rtx0     = 5472837;
            rtx0_inv = 9915;
            break;
        case 188:
            rtx0     = 5482749;
            rtx0_inv = 9908;
            break;
        case 189:
            rtx0     = 5492653;
            rtx0_inv = 9901;
            break;
        case 190:
            rtx0     = 5502551;
            rtx0_inv = 9894;
            break;
        case 191:
            rtx0     = 5512441;
            rtx0_inv = 9887;
            break;
        case 192:
            rtx0     = 5522325;
            rtx0_inv = 9880;
            break;
        case 193:
            rtx0     = 5532201;
            rtx0_inv = 9873;
            break;
        case 194:
            rtx0     = 5542070;
            rtx0_inv = 9866;
            break;
        case 195:
            rtx0     = 5551933;
            rtx0_inv = 9859;
            break;
        case 196:
            rtx0     = 5561788;
            rtx0_inv = 9852;
            break;
        case 197:
            rtx0     = 5571637;
            rtx0_inv = 9845;
            break;
        case 198:
            rtx0     = 5581478;
            rtx0_inv = 9838;
            break;
        case 199:
            rtx0     = 5591313;
            rtx0_inv = 9831;
            break;
        case 200:
            rtx0     = 5601141;
            rtx0_inv = 9824;
            break;
        case 201:
            rtx0     = 5610962;
            rtx0_inv = 9817;
            break;
        case 202:
            rtx0     = 5620775;
            rtx0_inv = 9810;
            break;
        case 203:
            rtx0     = 5630583;
            rtx0_inv = 9804;
            break;
        case 204:
            rtx0     = 5640383;
            rtx0_inv = 9797;
            break;
        case 205:
            rtx0     = 5650176;
            rtx0_inv = 9790;
            break;
        case 206:
            rtx0     = 5659963;
            rtx0_inv = 9783;
            break;
        case 207:
            rtx0     = 5669742;
            rtx0_inv = 9776;
            break;
        case 208:
            rtx0     = 5679515;
            rtx0_inv = 9770;
            break;
        case 209:
            rtx0     = 5689281;
            rtx0_inv = 9763;
            break;
        case 210:
            rtx0     = 5699041;
            rtx0_inv = 9756;
            break;
        case 211:
            rtx0     = 5708793;
            rtx0_inv = 9749;
            break;
        case 212:
            rtx0     = 5718539;
            rtx0_inv = 9743;
            break;
        case 213:
            rtx0     = 5728278;
            rtx0_inv = 9736;
            break;
        case 214:
            rtx0     = 5738011;
            rtx0_inv = 9729;
            break;
        case 215:
            rtx0     = 5747737;
            rtx0_inv = 9722;
            break;
        case 216:
            rtx0     = 5757456;
            rtx0_inv = 9716;
            break;
        case 217:
            rtx0     = 5767168;
            rtx0_inv = 9709;
            break;
        case 218:
            rtx0     = 5776874;
            rtx0_inv = 9702;
            break;
        case 219:
            rtx0     = 5786573;
            rtx0_inv = 9696;
            break;
        case 220:
            rtx0     = 5796265;
            rtx0_inv = 9689;
            break;
        case 221:
            rtx0     = 5805951;
            rtx0_inv = 9683;
            break;
        case 222:
            rtx0     = 5815630;
            rtx0_inv = 9676;
            break;
        case 223:
            rtx0     = 5825303;
            rtx0_inv = 9669;
            break;
        case 224:
            rtx0     = 5834969;
            rtx0_inv = 9663;
            break;
        case 225:
            rtx0     = 5844628;
            rtx0_inv = 9656;
            break;
        case 226:
            rtx0     = 5854281;
            rtx0_inv = 9650;
            break;
        case 227:
            rtx0     = 5863928;
            rtx0_inv = 9643;
            break;
        case 228:
            rtx0     = 5873568;
            rtx0_inv = 9637;
            break;
        case 229:
            rtx0     = 5883201;
            rtx0_inv = 9630;
            break;
        case 230:
            rtx0     = 5892828;
            rtx0_inv = 9624;
            break;
        case 231:
            rtx0     = 5902448;
            rtx0_inv = 9617;
            break;
        case 232:
            rtx0     = 5912062;
            rtx0_inv = 9611;
            break;
        case 233:
            rtx0     = 5921669;
            rtx0_inv = 9604;
            break;
        case 234:
            rtx0     = 5931270;
            rtx0_inv = 9598;
            break;
        case 235:
            rtx0     = 5940865;
            rtx0_inv = 9591;
            break;
        case 236:
            rtx0     = 5950453;
            rtx0_inv = 9585;
            break;
        case 237:
            rtx0     = 5960035;
            rtx0_inv = 9579;
            break;
        case 238:
            rtx0     = 5969610;
            rtx0_inv = 9572;
            break;
        case 239:
            rtx0     = 5979179;
            rtx0_inv = 9566;
            break;
        case 240:
            rtx0     = 5988742;
            rtx0_inv = 9559;
            break;
        case 241:
            rtx0     = 5998298;
            rtx0_inv = 9553;
            break;
        case 242:
            rtx0     = 6007848;
            rtx0_inv = 9547;
            break;
        case 243:
            rtx0     = 6017391;
            rtx0_inv = 9540;
            break;
        case 244:
            rtx0     = 6026929;
            rtx0_inv = 9534;
            break;
        case 245:
            rtx0     = 6036460;
            rtx0_inv = 9528;
            break;
        case 246:
            rtx0     = 6045984;
            rtx0_inv = 9521;
            break;
        case 247:
            rtx0     = 6055503;
            rtx0_inv = 9515;
            break;
        case 248:
            rtx0     = 6065015;
            rtx0_inv = 9509;
            break;
        case 249:
            rtx0     = 6074521;
            rtx0_inv = 9503;
            break;
        case 250:
            rtx0     = 6084020;
            rtx0_inv = 9496;
            break;
        case 251:
            rtx0     = 6093513;
            rtx0_inv = 9490;
            break;
        case 252:
            rtx0     = 6103001;
            rtx0_inv = 9484;
            break;
        case 253:
            rtx0     = 6112482;
            rtx0_inv = 9478;
            break;
        case 254:
            rtx0     = 6121956;
            rtx0_inv = 9472;
            break;
        case 255:
            rtx0     = 6131425;
            rtx0_inv = 9465;
            break;
        case 256:
            rtx0     = 6140887;
            rtx0_inv = 9459;
            break;
        case 257:
            rtx0     = 6150343;
            rtx0_inv = 9453;
            break;
        case 258:
            rtx0     = 6159794;
            rtx0_inv = 9447;
            break;
        case 259:
            rtx0     = 6169238;
            rtx0_inv = 9441;
            break;
        case 260:
            rtx0     = 6178675;
            rtx0_inv = 9435;
            break;
        case 261:
            rtx0     = 6188107;
            rtx0_inv = 9429;
            break;
        case 262:
            rtx0     = 6197533;
            rtx0_inv = 9423;
            break;
        case 263:
            rtx0     = 6206952;
            rtx0_inv = 9416;
            break;
        case 264:
            rtx0     = 6216366;
            rtx0_inv = 9410;
            break;
        case 265:
            rtx0     = 6225773;
            rtx0_inv = 9404;
            break;
        case 266:
            rtx0     = 6235174;
            rtx0_inv = 9398;
            break;
        case 267:
            rtx0     = 6244570;
            rtx0_inv = 9392;
            break;
        case 268:
            rtx0     = 6253959;
            rtx0_inv = 9386;
            break;
        case 269:
            rtx0     = 6263342;
            rtx0_inv = 9380;
            break;
        case 270:
            rtx0     = 6272719;
            rtx0_inv = 9374;
            break;
        case 271:
            rtx0     = 6282091;
            rtx0_inv = 9368;
            break;
        case 272:
            rtx0     = 6291456;
            rtx0_inv = 9362;
            break;
        case 273:
            rtx0     = 6300815;
            rtx0_inv = 9356;
            break;
        case 274:
            rtx0     = 6310169;
            rtx0_inv = 9350;
            break;
        case 275:
            rtx0     = 6319516;
            rtx0_inv = 9344;
            break;
        case 276:
            rtx0     = 6328857;
            rtx0_inv = 9338;
            break;
        case 277:
            rtx0     = 6338193;
            rtx0_inv = 9333;
            break;
        case 278:
            rtx0     = 6347523;
            rtx0_inv = 9327;
            break;
        case 279:
            rtx0     = 6356846;
            rtx0_inv = 9321;
            break;
        case 280:
            rtx0     = 6366164;
            rtx0_inv = 9315;
            break;
        case 281:
            rtx0     = 6375476;
            rtx0_inv = 9309;
            break;
        case 282:
            rtx0     = 6384782;
            rtx0_inv = 9303;
            break;
        case 283:
            rtx0     = 6394082;
            rtx0_inv = 9297;
            break;
        case 284:
            rtx0     = 6403377;
            rtx0_inv = 9291;
            break;
        case 285:
            rtx0     = 6412665;
            rtx0_inv = 9286;
            break;
        case 286:
            rtx0     = 6421948;
            rtx0_inv = 9280;
            break;
        case 287:
            rtx0     = 6431225;
            rtx0_inv = 9274;
            break;
        case 288:
            rtx0     = 6440496;
            rtx0_inv = 9268;
            break;
        case 289:
            rtx0     = 6449761;
            rtx0_inv = 9262;
            break;
        case 290:
            rtx0     = 6459021;
            rtx0_inv = 9257;
            break;
        case 291:
            rtx0     = 6468275;
            rtx0_inv = 9251;
            break;
        case 292:
            rtx0     = 6477523;
            rtx0_inv = 9245;
            break;
        case 293:
            rtx0     = 6486765;
            rtx0_inv = 9239;
            break;
        case 294:
            rtx0     = 6496001;
            rtx0_inv = 9234;
            break;
        case 295:
            rtx0     = 6505232;
            rtx0_inv = 9228;
            break;
        case 296:
            rtx0     = 6514457;
            rtx0_inv = 9222;
            break;
        case 297:
            rtx0     = 6523676;
            rtx0_inv = 9216;
            break;
        case 298:
            rtx0     = 6532890;
            rtx0_inv = 9211;
            break;
        case 299:
            rtx0     = 6542098;
            rtx0_inv = 9205;
            break;
        case 300:
            rtx0     = 6551300;
            rtx0_inv = 9199;
            break;
        case 301:
            rtx0     = 6560497;
            rtx0_inv = 9194;
            break;
        case 302:
            rtx0     = 6569688;
            rtx0_inv = 9188;
            break;
        case 303:
            rtx0     = 6578873;
            rtx0_inv = 9183;
            break;
        case 304:
            rtx0     = 6588053;
            rtx0_inv = 9177;
            break;
        case 305:
            rtx0     = 6597227;
            rtx0_inv = 9171;
            break;
        case 306:
            rtx0     = 6606395;
            rtx0_inv = 9166;
            break;
        case 307:
            rtx0     = 6615558;
            rtx0_inv = 9160;
            break;
        case 308:
            rtx0     = 6624716;
            rtx0_inv = 9154;
            break;
        case 309:
            rtx0     = 6633867;
            rtx0_inv = 9149;
            break;
        case 310:
            rtx0     = 6643013;
            rtx0_inv = 9143;
            break;
        case 311:
            rtx0     = 6652154;
            rtx0_inv = 9138;
            break;
        case 312:
            rtx0     = 6661289;
            rtx0_inv = 9132;
            break;
        case 313:
            rtx0     = 6670418;
            rtx0_inv = 9127;
            break;
        case 314:
            rtx0     = 6679542;
            rtx0_inv = 9121;
            break;
        case 315:
            rtx0     = 6688661;
            rtx0_inv = 9116;
            break;
        case 316:
            rtx0     = 6697774;
            rtx0_inv = 9110;
            break;
        case 317:
            rtx0     = 6706881;
            rtx0_inv = 9105;
            break;
        case 318:
            rtx0     = 6715983;
            rtx0_inv = 9099;
            break;
        case 319:
            rtx0     = 6725079;
            rtx0_inv = 9094;
            break;
        case 320:
            rtx0     = 6734170;
            rtx0_inv = 9088;
            break;
        case 321:
            rtx0     = 6743256;
            rtx0_inv = 9083;
            break;
        case 322:
            rtx0     = 6752336;
            rtx0_inv = 9077;
            break;
        case 323:
            rtx0     = 6761410;
            rtx0_inv = 9072;
            break;
        case 324:
            rtx0     = 6770479;
            rtx0_inv = 9066;
            break;
        case 325:
            rtx0     = 6779543;
            rtx0_inv = 9061;
            break;
        case 326:
            rtx0     = 6788601;
            rtx0_inv = 9056;
            break;
        case 327:
            rtx0     = 6797654;
            rtx0_inv = 9050;
            break;
        case 328:
            rtx0     = 6806702;
            rtx0_inv = 9045;
            break;
        case 329:
            rtx0     = 6815744;
            rtx0_inv = 9039;
            break;
        case 330:
            rtx0     = 6824781;
            rtx0_inv = 9034;
            break;
        case 331:
            rtx0     = 6833812;
            rtx0_inv = 9029;
            break;
        case 332:
            rtx0     = 6842838;
            rtx0_inv = 9023;
            break;
        case 333:
            rtx0     = 6851859;
            rtx0_inv = 9018;
            break;
        case 334:
            rtx0     = 6860874;
            rtx0_inv = 9013;
            break;
        case 335:
            rtx0     = 6869884;
            rtx0_inv = 9007;
            break;
        case 336:
            rtx0     = 6878889;
            rtx0_inv = 9002;
            break;
        case 337:
            rtx0     = 6887888;
            rtx0_inv = 8997;
            break;
        case 338:
            rtx0     = 6896883;
            rtx0_inv = 8991;
            break;
        case 339:
            rtx0     = 6905871;
            rtx0_inv = 8986;
            break;
        case 340:
            rtx0     = 6914855;
            rtx0_inv = 8981;
            break;
        case 341:
            rtx0     = 6923833;
            rtx0_inv = 8976;
            break;
        case 342:
            rtx0     = 6932806;
            rtx0_inv = 8970;
            break;
        case 343:
            rtx0     = 6941774;
            rtx0_inv = 8965;
            break;
        case 344:
            rtx0     = 6950736;
            rtx0_inv = 8960;
            break;
        case 345:
            rtx0     = 6959694;
            rtx0_inv = 8955;
            break;
        case 346:
            rtx0     = 6968646;
            rtx0_inv = 8949;
            break;
        case 347:
            rtx0     = 6977593;
            rtx0_inv = 8944;
            break;
        case 348:
            rtx0     = 6986534;
            rtx0_inv = 8939;
            break;
        case 349:
            rtx0     = 6995471;
            rtx0_inv = 8934;
            break;
        case 350:
            rtx0     = 7004402;
            rtx0_inv = 8929;
            break;
        case 351:
            rtx0     = 7013328;
            rtx0_inv = 8923;
            break;
        case 352:
            rtx0     = 7022249;
            rtx0_inv = 8918;
            break;
        case 353:
            rtx0     = 7031165;
            rtx0_inv = 8913;
            break;
        case 354:
            rtx0     = 7040075;
            rtx0_inv = 8908;
            break;
        case 355:
            rtx0     = 7048981;
            rtx0_inv = 8903;
            break;
        case 356:
            rtx0     = 7057881;
            rtx0_inv = 8898;
            break;
        case 357:
            rtx0     = 7066776;
            rtx0_inv = 8893;
            break;
        case 358:
            rtx0     = 7075666;
            rtx0_inv = 8888;
            break;
        case 359:
            rtx0     = 7084551;
            rtx0_inv = 8882;
            break;
        case 360:
            rtx0     = 7093431;
            rtx0_inv = 8877;
            break;
        case 361:
            rtx0     = 7102306;
            rtx0_inv = 8872;
            break;
        case 362:
            rtx0     = 7111176;
            rtx0_inv = 8867;
            break;
        case 363:
            rtx0     = 7120040;
            rtx0_inv = 8862;
            break;
        case 364:
            rtx0     = 7128900;
            rtx0_inv = 8857;
            break;
        case 365:
            rtx0     = 7137754;
            rtx0_inv = 8852;
            break;
        case 366:
            rtx0     = 7146604;
            rtx0_inv = 8847;
            break;
        case 367:
            rtx0     = 7155448;
            rtx0_inv = 8842;
            break;
        case 368:
            rtx0     = 7164287;
            rtx0_inv = 8837;
            break;
        case 369:
            rtx0     = 7173122;
            rtx0_inv = 8832;
            break;
        case 370:
            rtx0     = 7181951;
            rtx0_inv = 8827;
            break;
        case 371:
            rtx0     = 7190776;
            rtx0_inv = 8822;
            break;
        case 372:
            rtx0     = 7199595;
            rtx0_inv = 8817;
            break;
        case 373:
            rtx0     = 7208409;
            rtx0_inv = 8812;
            break;
        case 374:
            rtx0     = 7217219;
            rtx0_inv = 8807;
            break;
        case 375:
            rtx0     = 7226023;
            rtx0_inv = 8802;
            break;
        case 376:
            rtx0     = 7234823;
            rtx0_inv = 8797;
            break;
        case 377:
            rtx0     = 7243617;
            rtx0_inv = 8792;
            break;
        case 378:
            rtx0     = 7252407;
            rtx0_inv = 8787;
            break;
        case 379:
            rtx0     = 7261191;
            rtx0_inv = 8782;
            break;
        case 380:
            rtx0     = 7269971;
            rtx0_inv = 8777;
            break;
        case 381:
            rtx0     = 7278746;
            rtx0_inv = 8772;
            break;
        case 382:
            rtx0     = 7287516;
            rtx0_inv = 8767;
            break;
        case 383:
            rtx0     = 7296280;
            rtx0_inv = 8763;
            break;
        case 384:
            rtx0     = 7305041;
            rtx0_inv = 8758;
            break;
        case 385:
            rtx0     = 7313796;
            rtx0_inv = 8753;
            break;
        case 386:
            rtx0     = 7322546;
            rtx0_inv = 8748;
            break;
        case 387:
            rtx0     = 7331291;
            rtx0_inv = 8743;
            break;
        case 388:
            rtx0     = 7340032;
            rtx0_inv = 8738;
            break;
        case 389:
            rtx0     = 7348768;
            rtx0_inv = 8733;
            break;
        case 390:
            rtx0     = 7357499;
            rtx0_inv = 8728;
            break;
        case 391:
            rtx0     = 7366225;
            rtx0_inv = 8724;
            break;
        case 392:
            rtx0     = 7374946;
            rtx0_inv = 8719;
            break;
        case 393:
            rtx0     = 7383662;
            rtx0_inv = 8714;
            break;
        case 394:
            rtx0     = 7392374;
            rtx0_inv = 8709;
            break;
        case 395:
            rtx0     = 7401080;
            rtx0_inv = 8704;
            break;
        case 396:
            rtx0     = 7409782;
            rtx0_inv = 8700;
            break;
        case 397:
            rtx0     = 7418480;
            rtx0_inv = 8695;
            break;
        case 398:
            rtx0     = 7427172;
            rtx0_inv = 8690;
            break;
        case 399:
            rtx0     = 7435860;
            rtx0_inv = 8685;
            break;
        case 400:
            rtx0     = 7444542;
            rtx0_inv = 8680;
            break;
        case 401:
            rtx0     = 7453220;
            rtx0_inv = 8676;
            break;
        case 402:
            rtx0     = 7461894;
            rtx0_inv = 8671;
            break;
        case 403:
            rtx0     = 7470562;
            rtx0_inv = 8666;
            break;
        case 404:
            rtx0     = 7479226;
            rtx0_inv = 8661;
            break;
        case 405:
            rtx0     = 7487885;
            rtx0_inv = 8657;
            break;
        case 406:
            rtx0     = 7496540;
            rtx0_inv = 8652;
            break;
        case 407:
            rtx0     = 7505189;
            rtx0_inv = 8647;
            break;
        case 408:
            rtx0     = 7513834;
            rtx0_inv = 8643;
            break;
        case 409:
            rtx0     = 7522475;
            rtx0_inv = 8638;
            break;
        case 410:
            rtx0     = 7531110;
            rtx0_inv = 8633;
            break;
        case 411:
            rtx0     = 7539741;
            rtx0_inv = 8629;
            break;
        case 412:
            rtx0     = 7548367;
            rtx0_inv = 8624;
            break;
        case 413:
            rtx0     = 7556989;
            rtx0_inv = 8619;
            break;
        case 414:
            rtx0     = 7565606;
            rtx0_inv = 8615;
            break;
        case 415:
            rtx0     = 7574218;
            rtx0_inv = 8610;
            break;
        case 416:
            rtx0     = 7582826;
            rtx0_inv = 8605;
            break;
        case 417:
            rtx0     = 7591429;
            rtx0_inv = 8601;
            break;
        case 418:
            rtx0     = 7600027;
            rtx0_inv = 8596;
            break;
        case 419:
            rtx0     = 7608621;
            rtx0_inv = 8591;
            break;
        case 420:
            rtx0     = 7617210;
            rtx0_inv = 8587;
            break;
        case 421:
            rtx0     = 7625794;
            rtx0_inv = 8582;
            break;
        case 422:
            rtx0     = 7634374;
            rtx0_inv = 8578;
            break;
        case 423:
            rtx0     = 7642950;
            rtx0_inv = 8573;
            break;
        case 424:
            rtx0     = 7651520;
            rtx0_inv = 8568;
            break;
        case 425:
            rtx0     = 7660087;
            rtx0_inv = 8564;
            break;
        case 426:
            rtx0     = 7668648;
            rtx0_inv = 8559;
            break;
        case 427:
            rtx0     = 7677205;
            rtx0_inv = 8555;
            break;
        case 428:
            rtx0     = 7685758;
            rtx0_inv = 8550;
            break;
        case 429:
            rtx0     = 7694306;
            rtx0_inv = 8546;
            break;
        case 430:
            rtx0     = 7702849;
            rtx0_inv = 8541;
            break;
        case 431:
            rtx0     = 7711388;
            rtx0_inv = 8537;
            break;
        case 432:
            rtx0     = 7719922;
            rtx0_inv = 8532;
            break;
        case 433:
            rtx0     = 7728452;
            rtx0_inv = 8528;
            break;
        case 434:
            rtx0     = 7736977;
            rtx0_inv = 8523;
            break;
        case 435:
            rtx0     = 7745498;
            rtx0_inv = 8519;
            break;
        case 436:
            rtx0     = 7754014;
            rtx0_inv = 8514;
            break;
        case 437:
            rtx0     = 7762526;
            rtx0_inv = 8510;
            break;
        case 438:
            rtx0     = 7771033;
            rtx0_inv = 8505;
            break;
        case 439:
            rtx0     = 7779536;
            rtx0_inv = 8501;
            break;
        case 440:
            rtx0     = 7788035;
            rtx0_inv = 8496;
            break;
        case 441:
            rtx0     = 7796529;
            rtx0_inv = 8492;
            break;
        case 442:
            rtx0     = 7805018;
            rtx0_inv = 8487;
            break;
        case 443:
            rtx0     = 7813503;
            rtx0_inv = 8483;
            break;
        case 444:
            rtx0     = 7821984;
            rtx0_inv = 8478;
            break;
        case 445:
            rtx0     = 7830460;
            rtx0_inv = 8474;
            break;
        case 446:
            rtx0     = 7838931;
            rtx0_inv = 8469;
            break;
        case 447:
            rtx0     = 7847399;
            rtx0_inv = 8465;
            break;
        case 448:
            rtx0     = 7855862;
            rtx0_inv = 8461;
            break;
        case 449:
            rtx0     = 7864320;
            rtx0_inv = 8456;
            break;
        case 450:
            rtx0     = 7872774;
            rtx0_inv = 8452;
            break;
        case 451:
            rtx0     = 7881224;
            rtx0_inv = 8447;
            break;
        case 452:
            rtx0     = 7889669;
            rtx0_inv = 8443;
            break;
        case 453:
            rtx0     = 7898110;
            rtx0_inv = 8439;
            break;
        case 454:
            rtx0     = 7906546;
            rtx0_inv = 8434;
            break;
        case 455:
            rtx0     = 7914979;
            rtx0_inv = 8430;
            break;
        case 456:
            rtx0     = 7923406;
            rtx0_inv = 8426;
            break;
        case 457:
            rtx0     = 7931830;
            rtx0_inv = 8421;
            break;
        case 458:
            rtx0     = 7940249;
            rtx0_inv = 8417;
            break;
        case 459:
            rtx0     = 7948664;
            rtx0_inv = 8413;
            break;
        case 460:
            rtx0     = 7957074;
            rtx0_inv = 8408;
            break;
        case 461:
            rtx0     = 7965480;
            rtx0_inv = 8404;
            break;
        case 462:
            rtx0     = 7973882;
            rtx0_inv = 8400;
            break;
        case 463:
            rtx0     = 7982280;
            rtx0_inv = 8395;
            break;
        case 464:
            rtx0     = 7990673;
            rtx0_inv = 8391;
            break;
        case 465:
            rtx0     = 7999062;
            rtx0_inv = 8387;
            break;
        case 466:
            rtx0     = 8007446;
            rtx0_inv = 8382;
            break;
        case 467:
            rtx0     = 8015826;
            rtx0_inv = 8378;
            break;
        case 468:
            rtx0     = 8024203;
            rtx0_inv = 8374;
            break;
        case 469:
            rtx0     = 8032574;
            rtx0_inv = 8370;
            break;
        case 470:
            rtx0     = 8040942;
            rtx0_inv = 8365;
            break;
        case 471:
            rtx0     = 8049305;
            rtx0_inv = 8361;
            break;
        case 472:
            rtx0     = 8057664;
            rtx0_inv = 8357;
            break;
        case 473:
            rtx0     = 8066019;
            rtx0_inv = 8353;
            break;
        case 474:
            rtx0     = 8074369;
            rtx0_inv = 8348;
            break;
        case 475:
            rtx0     = 8082715;
            rtx0_inv = 8344;
            break;
        case 476:
            rtx0     = 8091057;
            rtx0_inv = 8340;
            break;
        case 477:
            rtx0     = 8099395;
            rtx0_inv = 8336;
            break;
        case 478:
            rtx0     = 8107729;
            rtx0_inv = 8331;
            break;
        case 479:
            rtx0     = 8116058;
            rtx0_inv = 8327;
            break;
        case 480:
            rtx0     = 8124383;
            rtx0_inv = 8323;
            break;
        case 481:
            rtx0     = 8132704;
            rtx0_inv = 8319;
            break;
        case 482:
            rtx0     = 8141021;
            rtx0_inv = 8315;
            break;
        case 483:
            rtx0     = 8149334;
            rtx0_inv = 8311;
            break;
        case 484:
            rtx0     = 8157642;
            rtx0_inv = 8306;
            break;
        case 485:
            rtx0     = 8165946;
            rtx0_inv = 8302;
            break;
        case 486:
            rtx0     = 8174247;
            rtx0_inv = 8298;
            break;
        case 487:
            rtx0     = 8182543;
            rtx0_inv = 8294;
            break;
        case 488:
            rtx0     = 8190834;
            rtx0_inv = 8290;
            break;
        case 489:
            rtx0     = 8199122;
            rtx0_inv = 8286;
            break;
        case 490:
            rtx0     = 8207405;
            rtx0_inv = 8281;
            break;
        case 491:
            rtx0     = 8215685;
            rtx0_inv = 8277;
            break;
        case 492:
            rtx0     = 8223960;
            rtx0_inv = 8273;
            break;
        case 493:
            rtx0     = 8232231;
            rtx0_inv = 8269;
            break;
        case 494:
            rtx0     = 8240498;
            rtx0_inv = 8265;
            break;
        case 495:
            rtx0     = 8248761;
            rtx0_inv = 8261;
            break;
        case 496:
            rtx0     = 8257020;
            rtx0_inv = 8257;
            break;
        case 497:
            rtx0     = 8265275;
            rtx0_inv = 8253;
            break;
        case 498:
            rtx0     = 8273525;
            rtx0_inv = 8249;
            break;
        case 499:
            rtx0     = 8281772;
            rtx0_inv = 8245;
            break;
        case 500:
            rtx0     = 8290014;
            rtx0_inv = 8240;
            break;
        case 501:
            rtx0     = 8298253;
            rtx0_inv = 8236;
            break;
        case 502:
            rtx0     = 8306487;
            rtx0_inv = 8232;
            break;
        case 503:
            rtx0     = 8314717;
            rtx0_inv = 8228;
            break;
        case 504:
            rtx0     = 8322943;
            rtx0_inv = 8224;
            break;
        case 505:
            rtx0     = 8331166;
            rtx0_inv = 8220;
            break;
        case 506:
            rtx0     = 8339384;
            rtx0_inv = 8216;
            break;
        case 507:
            rtx0     = 8347598;
            rtx0_inv = 8212;
            break;
        case 508:
            rtx0     = 8355808;
            rtx0_inv = 8208;
            break;
        case 509:
            rtx0     = 8364014;
            rtx0_inv = 8204;
            break;
        case 510:
            rtx0     = 8372216;
            rtx0_inv = 8200;
            break;
        case 511:
            rtx0     = 8380414;
            rtx0_inv = 8196;
            break;
    }
    xr = x & 0xffffff;

    if(xr == 0x7fffff || xr == 0x7ffffe || xr == 0x7ffffd) corner_flag = 1;
    else corner_flag = 0;

    if(ex == 0) ey = 0;
    else ey = 63 + (ex >> 1) + (ex  & 1) + corner_flag;
    my_extend = ((unsigned long)rtx0 << 14) + (unsigned long)rtx0_inv * (unsigned long)h;
    my_long = my_extend >> 14;
    my = (unsigned int)my_long;
    y = (ey << 23) | my;
    r = *((float *)&y);
    return r;
}

float fneg(float f){

    return -f;

}

int feq(float a, float b){

    return ( a == b ? 1 : 0);

}

int flt(float a, float b){

    return ( a < b ? 1 : 0);

}

int fle(float a, float b){

    return ( a <= b ? 1 : 0);

}

float itof(int x){
    unsigned int xbit,sx,se,mxa,mxb;
    unsigned int eya,sy,ey,my,mya,y;
    unsigned int flag1;
    unsigned int i,bit;
    float r;
    
    xbit = *((unsigned int *)&x);
    sx = xbit >> 31;
    mxa = xbit & 0x7fffffff;
    if(sx == 1){
	mxb = ((~mxa) + 1) & 0x7fffffff;
    }
    else mxb = mxa;
    for(i = 0;i < 31;i++){
	bit = (mxb >> (30-i)) & 1;
 	if(bit == 1) break;
    }
    se = i;
    sy = sx;
    if(se < 32) mya = mxb << se;
    else mya = 0;
    my = ((mya & 0x3fffffff) >> 7) + ((mya >> 6) & 1);
    if(((mya & 0x3fffffff) >> 6) == 0xffffff) flag1 = 1;
    else flag1 = 0;
    eya = 157 + flag1;
    if(xbit == 0x80000000) ey = 158;
    else if (se == 31) ey = 0;
    else ey = eya - se;
    y = (sy << 31) | (ey << 23) | my;
    r = *((float *)&y);   
    return r;
}

int ftoi(float f){
    unsigned int x,sx,ex,mx,se;
    unsigned int mya,myb,my,y;
    int r;
    x = *((unsigned int *)&f);
    sx = x >> 31;
    ex = (x >> 23) & 0xff;
    mx = x & 0x7fffff;
    mya = (1 << 30) | (mx << 7);
    if(157 > ex) se = 157 - ex;
    else se = 0;
    if(se > 31) se = 31;
    myb = mya >> se;
    if(sx) my = ((myb ^ 0x7fffffff) + 1) & 0x7fffffff;
    else my = myb;
    if(my == 0) y = 0;
    else y = (sx << 31) | my;
    r = *((int *)&y);
    return r;
}
