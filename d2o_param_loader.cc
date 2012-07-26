//These parameters are up to date as of July 13, 2010
#include <iostream>

//legend
//param[0] = A
//param[1] = a1
//param[2] = a2
//param[3] = a3
//param[4] = a4
//param[5] = e2
//param[6] = e3
//param[7] = e4
//param[8] = -0.00500;
//param[9] = 0.00144;
//param[10] = -0.00470;
//param[11] = 0.00250;
//d_param[0] = 0.00105;
//d_param[1] = 0.00903; 
//d_param[2] = 0.01384;
//d_param[3] = 0.01788;
//d_param[4] = 0.02300;
//d_param[5] = 0.00358;
//d_param[6] = 0.00167;
//d_param[7] = 0.00125;
//d_param[8] = 0.01859;
//d_param[9] = 0.01149;
//d_param[10] = 0.00898;
//d_param[11] = 0.00601

void d2o_param_loader(int run, int background)
{
switch (run)
  {
  case 142:
    if(background == 1)
      {
      param[0] = 0.12380;
      param[1] = 0.03460;
      param[2] = -0.88750;
      param[3] = -0.05790;
      param[4] = -0.08850;
      param[5] = 0.43090;
      param[6] = 0.00560;
      param[7] = 0.00200;
      param[8] = -0.00500;
      param[9] = 0.00144;
      param[10] = -0.00470;
      param[11] = 0.00250;

      d_param[0] = 0.00105;
      d_param[1] = 0.00903; 
      d_param[2] = 0.01384;
      d_param[3] = 0.01788;
      d_param[4] = 0.02300;
      d_param[5] = 0.00358;
      d_param[6] = 0.00167;
      d_param[7] = 0.00125;
      d_param[8] = 0.01859;
      d_param[9] = 0.01149;
      d_param[10] = 0.00898;
      d_param[11] = 0.00601;
      }
    else
      {
      param[0] = 0.12680;
      param[1] = 0.04780;
      param[2] = -0.86310;
      param[3] = -0.05300;
      param[4] = -0.07710;
      param[5] = 0.42400;
      param[6] = 0.00580;
      param[7] = 0.00220;
      param[8] = -0.00540;
      param[9] = 0.01480;
      param[10] = -0.00560;
      param[11] = 0.00250;

      d_param[0] = 0.00099;
      d_param[1] = 0.00805;
      d_param[2] = 0.01193;
      d_param[3] = 0.01550;
      d_param[4] = 0.01854;
      d_param[5] = 0.00265;
      d_param[6] = 0.00133;
      d_param[7] = 0.00095;
      d_param[8] = 0.01624;
      d_param[9] = 0.00998;
      d_param[10] = 0.00679;
      d_param[11] = 0.00484;
      }

    cout << "Loading parameters for run " << run << ".\n";
    break;
  case 143:
    if(background == 1)
      {
      param[0] = 0.09800;
      param[1] = 0.03930;
      param[2] = -0.87180;
      param[3] = -0.05050;
      param[4] = -0.05100;
      param[5] = 0.42870;
      param[6] = 0.00590;
      param[7] = 0.00130;
      param[8] = 0.01240;
      param[9] = 0.02000;
      param[10] = -0.00360;
      param[11] = 0.00270;

      d_param[0] = 0.00085;
      d_param[1] = 0.00979;
      d_param[2] = 0.01479;
      d_param[3] = 0.01948;
      d_param[4] = 0.02508;
      d_param[5] = 0.00397;
      d_param[6] = 0.00190;
      d_param[7] = 0.00135;
      d_param[8] = 0.01928;
      d_param[9] = 0.01191;
      d_param[10] = 0.00993;
      d_param[11] = 0.00662;
      }
    else
      {
      param[0] = 0.10030;
      param[1] = 0.05310;
      param[2] = -0.84500;
      param[3] = -0.03820;
      param[4] = -0.03690;
      param[5] = 0.42130;
      param[6] = 0.00560;
      param[7] = 0.00120;
      param[8] = 0.01050;
      param[9] = 0.01990;
      param[10] = -0.00620;
      param[11] = 0.00270;

      d_param[0] = 0.00083;
      d_param[1] = 0.00876;
      d_param[2] = 0.01299;
      d_param[3] = 0.01699;
      d_param[4] = 0.02097;
      d_param[5] = 0.00314;
      d_param[6] = 0.00155;
      d_param[7] = 0.00109;
      d_param[8] = 0.01701;
      d_param[9] = 0.01056;
      d_param[10] = 0.00791;
      d_param[11] = 0.00546;
      }
    cout << "Loading parameters for run " << run << ".\n";
    break;
  case 149:
    if (background == 1)
      {
      param[0] = 0.08400;
      param[1] = 0.04370;
      param[2] = -0.89280;
      param[3] = -0.08090;
      param[4] = -0.07450;
      param[5] = 0.43690;
      param[6] = 0.00750;
      param[7] = 0.00330;
      param[8] = 0.03980;
      param[9] = 0.01390;
      param[10] = -0.01430;
      param[11] = -0.00060;

      d_param[0] = 0.00078;
      d_param[1] = 0.00893;
      d_param[2] = 0.01471;
      d_param[3] = 0.01969;
      d_param[4] = 0.02532;
      d_param[5] = 0.00428;
      d_param[6] = 0.00209;
      d_param[7] = 0.00133;
      d_param[8] = 0.02097;
      d_param[9] = 0.01281;
      d_param[10] = 0.01087;
      d_param[11] = 0.00692;
      }
    else
      {
      param[0] = 0.08590;
      param[1] = 0.04920;
      param[2] = -0.88160;
      param[3] = -0.09210;
      param[4] = -0.08040;
      param[5] = 0.42880;
      param[6] = 0.00710;
      param[7] = 0.00370;
      param[8] = 0.03490;
      param[9] = 0.01260;
      param[10] = -0.01840;
      param[11] = -0.00060;

      d_param[0] = 0.00075;
      d_param[1] = 0.00814;
      d_param[2] = 0.01350;
      d_param[3] = 0.01750;
      d_param[4] = 0.02131;
      d_param[5] = 0.00335;
      d_param[6] = 0.00174;
      d_param[7] = 0.00107;
      d_param[8] = 0.01850;
      d_param[9] = 0.01138;
      d_param[10] = 0.00860;
      d_param[11] = 0.00579;
      }
    cout << "Loading parameters for run " << run << ".\n";
    break;
  case 150:
    if (background == 1)
      {
      param[0] = 0.08170;
      param[1] = 0.03810;
      param[2] = -0.86630;
      param[3] = -0.03680;
      param[4] = -0.02660;
      param[5] = 0.43070;
      param[6] = 0.00310;
      param[7] = 0.00410;
      param[8] = 0.04780;
      param[9] = 0.02860;
      param[10] = -0.02090;
      param[11] = 0.00010;

      d_param[0] = 0.00083;
      d_param[1] = 0.00935;
      d_param[2] = 0.01484;
      d_param[3] = 0.01930;
      d_param[4] = 0.02479;
      d_param[5] = 0.00421;
      d_param[6] = 0.00197;
      d_param[7] = 0.00137;
      d_param[8] = 0.02097;
      d_param[9] = 0.01280;
      d_param[10] = 0.01057;
      d_param[11] = 0.00665;
      }
    else
      {
      param[0] = 0.08340;
      param[1] = 0.03760;
      param[2] = -0.86670;
      param[3] = -0.06070;
      param[4] = -0.04140;
      param[5] = 0.42400;
      param[6] = 0.00310;
      param[7] = 0.00450;
      param[8] = 0.04240;
      param[9] = 0.02650;
      param[10] = -0.02130;
      param[11] = 0.00120;

      d_param[0] = 0.00069;
      d_param[1] = 0.00855;
      d_param[2] = 0.01358;
      d_param[3] = 0.01718;
      d_param[4] = 0.02102;
      d_param[5] = 0.00339;
      d_param[6] = 0.00161;
      d_param[7] = 0.01110;
      d_param[8] = 0.01864;
      d_param[9] = 0.01139;
      d_param[10] = 0.00856;
      d_param[11] = 0.00561;
      }
    cout << "Loading parameters for run " << run << ".\n";
    break;
  case 152:
    if (background == 1)
      {
      param[0] = 0.12550;
      param[1] = 0.00130;
      param[2] = -0.90420;
      param[3] = -0.04550;
      param[4] = -0.06590;
      param[5] = 0.42920;
      param[6] = 0.00040;
      param[7] = 0.00200;
      param[8] = -0.02250;
      param[9] = 0.01790;
      param[10] = -0.00670;
      param[11] = 0.00560;

      d_param[0] = 0.00110;
      d_param[1] = 0.00883;
      d_param[2] = 0.01345;
      d_param[3] = 0.01872;
      d_param[4] = 0.02472;
      d_param[5] = 0.00444;
      d_param[6] = 0.00203;
      d_param[7] = 0.00135;
      d_param[8] = 0.01921;
      d_param[9] = 0.01187;
      d_param[10] = 0.01063;
      d_param[11] = 0.00685;
      }
    else
      {
      param[0] = 0.12900;
      param[1] = 0.01540;
      param[2] = -0.87410;
      param[3] = -0.03520;
      param[4] = -0.05750;
      param[5] = 0.42150;
      param[6] = 0.00000;
      param[7] = 0.00190;
      param[8] = -0.01880;
      param[9] = 0.01790;
      param[10] = -0.00490;
      param[11] = 0.00430;

      d_param[0] = 0.00101;
      d_param[1] = 0.00804;
      d_param[2] = 0.01176;
      d_param[3] = 0.01610;
      d_param[4] = 0.02022;
      d_param[5] = 0.00333;
      d_param[6] = 0.00163;
      d_param[7] = 0.00099;
      d_param[8] = 0.01654;
      d_param[9] = 0.01021;
      d_param[10] = 0.00814;
      d_param[11] = 0.00533;
      }
    cout << "Loading parameters for run " << run << ".\n";
    break;
  case 153:
    if (background == 1)
      {
      param[0] = 0.05000;
      param[1] = 0.03000;
      param[2] = -0.87800;
      param[3] = -0.02240;
      param[4] = -0.04430;
      param[5] = 0.42370;
      param[6] = 0.00480;
      param[7] = 0.00260;
      param[8] = -0.00950;
      param[9] = 0.02330;
      param[10] = -0.00480;
      param[11] = 0.00170;
 
      d_param[0] = 0.00052;
      d_param[1] = 0.01186;
      d_param[2] = 0.01809;
      d_param[3] = 0.02403;
      d_param[4] = 0.03171;
      d_param[5] = 0.00584;
      d_param[6] = 0.00254;
      d_param[7] = 0.00174;
      d_param[8] = 0.02312;
      d_param[9] = 0.01426;
      d_param[10] = 0.01368;
      d_param[11] = 0.00855;
      }
    else
      {
      param[0] = 0.05120;
      param[1] = 0.04480;
      param[2] = -0.84430;
      param[3] = -0.00870;
      param[4] = -0.03740;
      param[5] = 0.41590;
      param[6] = 0.00400;
      param[7] = 0.00250;
      param[8] = -0.00800;
      param[9] = 0.02300;
      param[10] = -0.00670;
      param[11] = -0.00040;
 
      d_param[0] = 0.00055;
      d_param[1] = 0.01087;
      d_param[2] = 0.01617;
      d_param[3] = 0.02148;
      d_param[4] = 0.02756;
      d_param[5] = 0.00490;
      d_param[6] = 0.00219;
      d_param[7] = 0.00146;
      d_param[8] = 0.02071;
      d_param[9] = 0.01275;
      d_param[10] = 0.01157;
      d_param[11] = 0.00728;
      }
    cout << "Loading parameters for run " << run << ".\n";
    break;
  case 154:
    if (background == 1)
      {
      cerr << "ERROR: parameters are not available for run 154 with background suppression.\n";
      return;
      }
    else 
      {
      param[0] = 0.0023;
      param[1] = 0.5617;
      param[2] = 0.3012;
      param[3] = 0.2207;
      param[4] = -0.2455;
      param[5] = 0.1064;
      param[6] = 0.0196;
      param[7] = 0.0299;
      param[8] = -0.1057;
      param[9] = -0.0598;
      param[10] = -0.0241;
      param[11] = 0.0061;

      d_param[0] = 0.00015;
      d_param[1] = 0.06415;
      d_param[2] = 0.09662;
      d_param[3] = 0.11909;
      d_param[4] = 0.14993;
      d_param[5] = 0.03134;
      d_param[6] = 0.01389;
      d_param[7] = 0.00879;
      d_param[8] = 0.0804;
      d_param[9] = 0.0542;
      d_param[10] = 0.07595;
      d_param[11] = 0.04633;
      }
    cout << "Loading parameters for run " << run << ".\n";
    break;
  case 155:
    if (background == 1)
      {
      param[0] = 0.02460;
      param[1] = -0.00820;
      param[2] = -0.80000;
      param[3] = -0.01540;
      param[4] = -0.15450;
      param[5] = 0.43360;
      param[6] = 0.00010;
      param[7] = 0.00920;
      param[8] = -0.06560;
      param[9] = 0.03890;
      param[10] = 0.00360;
      param[11] = 0.01040;

      d_param[0] = 0.00042;
      d_param[1] = 0.01984;
      d_param[2] = 0.03114;
      d_param[3] = 0.04099;
      d_param[4] = 0.05702;
      d_param[5] = 0.01138;
      d_param[6] = 0.00530;
      d_param[7] = 0.00353;
      d_param[8] = 0.03795;
      d_param[9] = 0.02389;
      d_param[10] = 0.02698;
      d_param[11] = 0.01724;
      }
    else 
      {
      param[0] = 0.02750;
      param[1] = 0.03510;
      param[2] = -0.71310;
      param[3] = -0.01510;
      param[4] = -0.15270;
      param[5] = 0.39880;
      param[6] = 0.00210;
      param[7] = 0.01080;
      param[8] = -0.05790;
      param[9] = 0.03370;
      param[10] = -0.00240;
      param[11] = 0.00090;

      d_param[0] = 0.00031;
      d_param[1] = 0.01609;
      d_param[2] = 0.02251;
      d_param[3] = 0.03004;
      d_param[4] = 0.03875;
      d_param[5] = 0.00689;
      d_param[6] = 0.00359;
      d_param[7] = 0.00238;
      d_param[8] = 0.02586;
      d_param[9] = 0.01676;
      d_param[10] = 0.01662;
      d_param[11] = 0.01182;
      }
    cout << "Loading parameters for run " << run << ".\n";
    break;
  case 157:
    if (background == 1)
      {
      param[0] = 0.02820;
      param[1] = -0.05610;
      param[2] = -0.84790;
      param[3] = -0.01080;
      param[4] = -0.17070;
      param[5] = 0.43660;
      param[6] = -0.00060;
      param[7] = 0.00640;
      param[8] = -0.01740;
      param[9] = 0.02330;
      param[10] = -0.01310;
      param[11] = 0.00060;

      d_param[0] = 0.00047;
      d_param[1] = 0.01971;
      d_param[2] = 0.03153;
      d_param[3] = 0.04310;
      d_param[4] = 0.05789;
      d_param[5] = 0.01139;
      d_param[6] = 0.00519;
      d_param[7] = 0.00341;
      d_param[8] = 0.03601;
      d_param[9] = 0.02281;
      d_param[10] = 0.02691;
      d_param[11] = 0.01682;
      }
    else 
      {
      param[0] = 0.03110;
      param[1] = -0.01820;
      param[2] = -0.78550;
      param[3] = -0.02040;
      param[4] = -0.18140;
      param[5] = 0.40790;
      param[6] = -0.00070;
      param[7] = 0.00720;
      param[8] = -0.02370;
      param[9] = 0.01590;
      param[10] = -0.01490;
      param[11] = -0.00360;

      d_param[0] = 0.00039;
      d_param[1] = 0.01657;
      d_param[2] = 0.02382;
      d_param[3] = 0.03256;
      d_param[4] = 0.04090;
      d_param[5] = 0.00716;
      d_param[6] = 0.00369;
      d_param[7] = 0.00234;
      d_param[8] = 0.02537;
      d_param[9] = 0.01626;
      d_param[10] = 0.01718;
      d_param[11] = 0.01194;
      }
    cout << "Loading parameters for run " << run << ".\n";
    break;
  case 158:
    if (background == 1)
      {
      param[0] = 0.02710;
      param[1] = -0.05640;
      param[2] = -0.83660;
      param[3] = -0.03080;
      param[4] = -0.19130;
      param[5] = 0.42590;
      param[6] = 0.00460;
      param[7] = 0.00610;
      param[8] = 0.03070;
      param[9] = 0.02610;
      param[10] = 0.00340;
      param[11] = 0.00260;

      d_param[0] = 0.00049;
      d_param[1] = 0.02363;
      d_param[2] = 0.03540;
      d_param[3] = 0.04496;
      d_param[4] = 0.05788;
      d_param[5] = 0.01180;
      d_param[6] = 0.00540;
      d_param[7] = 0.00382;
      d_param[8] = 0.03661;
      d_param[9] = 0.02283;
      d_param[10] = 0.02803;
      d_param[11] = 0.01784;
      }
    else 
      {
      param[0] = 0.02990;
      param[1] = -0.00790;
      param[2] = -0.75240;
      param[3] = -0.02720;
      param[4] = -0.17310;
      param[5] = 0.39590;
      param[6] = 0.00270;
      param[7] = 0.00700;
      param[8] = 0.01370;
      param[9] = 0.01330;
      param[10] = -0.01060;
      param[11] = -0.00010;

      d_param[0] = 0.00035;
      d_param[1] = 0.01770;
      d_param[2] = 0.02534;
      d_param[3] = 0.03289;
      d_param[4] = 0.04039;
      d_param[5] = 0.00781;
      d_param[6] = 0.00373;
      d_param[7] = 0.00243;
      d_param[8] = 0.02593;
      d_param[9] = 0.01665;
      d_param[10] = 0.01866;
      d_param[11] = 0.01245;
      }
    cout << "Loading parameters for run " << run << ".\n";
    break;
  case 159:
    if (background == 1)
      {
      param[0] = 0.01350;
      param[1] = -0.01890;
      param[2] = -0.76140;
      param[3] = 0.00120;
      param[4] = -0.22500;
      param[5] = 0.42840;
      param[6] = 0.00560;
      param[7] = 0.01180;
      param[8] = 0.03200;
      param[9] = 0.01730;
      param[10] = -0.02530;
      param[11] = 0.01230;

      d_param[0] = 0.00029;
      d_param[1] = 0.02788;
      d_param[2] = 0.04049;
      d_param[3] = 0.05322;
      d_param[4] = 0.06744;
      d_param[5] = 0.01409;
      d_param[6] = 0.00635;
      d_param[7] = 0.00433;
      d_param[8] = 0.04301;
      d_param[9] = 0.02738;
      d_param[10] = 0.03246;
      d_param[11] = 0.02064;
      }
    else 
      {
      param[0] = 0.01500;
      param[1] = 0.02940;
      param[2] = -0.68450;
      param[3] = -0.01240;
      param[4] = -0.19580;
      param[5] = 0.39570;
      param[6] = 0.00530;
      param[7] = 0.01200;
      param[8] = 0.01580;
      param[9] = 0.00640;
      param[10] = -0.03850;
      param[11] = 0.00440;

      d_param[0] = 0.00026;
      d_param[1] = 0.02036;
      d_param[2] = 0.02930;
      d_param[3] = 0.03842;
      d_param[4] = 0.04660;
      d_param[5] = 0.00915;
      d_param[6] = 0.00431;
      d_param[7] = 0.00284;
      d_param[8] = 0.03120;
      d_param[9] = 0.02049;
      d_param[10] = 0.02138;
      d_param[11] = 0.01431;
      }
    cout << "Loading parameters for run " << run << ".\n";
    break;
  default:
    cerr << "ERROR: run " << run << " parameters not found.\n";
    return;
  }
return;
}
