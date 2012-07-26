//contains all functions used to correct what arm is up
//Glen; June 21, 2012
//June 21,2010: verified everything.  How?  I found the max cell for each ring and made sure it was in the horizontal plane, as is expected.  This was done for each run.  Also did a visual inspection of algorithm.
//note: array == &array[0]

void arm_cor_4_to_1(double run[88])  //note: this means that it accepts a histogram with arm 4 up and converts it to one with arm 1 up
{
double arm_cor[88];
arm_cor[0] = run[3];
arm_cor[1] = run[4];
arm_cor[2] = run[5];
arm_cor[3] = run[6];
arm_cor[4] = run[7];
arm_cor[5] = run[0];
arm_cor[6] = run[1];
arm_cor[7] = run[2];

arm_cor[8] = run[11];
arm_cor[9] = run[12];
arm_cor[10] = run[13];
arm_cor[11] = run[14];
arm_cor[12] = run[15];
arm_cor[13] = run[8];
arm_cor[14] = run[9];
arm_cor[15] = run[10];

arm_cor[16] = run[19];
arm_cor[17] = run[20];
arm_cor[18] = run[21];
arm_cor[19] = run[22];
arm_cor[20] = run[23];
arm_cor[21] = run[16];
arm_cor[22] = run[17];
arm_cor[23] = run[18];

arm_cor[24] = run[27];
arm_cor[25] = run[28];
arm_cor[26] = run[29];
arm_cor[27] = run[30];
arm_cor[28] = run[31];
arm_cor[29] = run[24];
arm_cor[30] = run[25];
arm_cor[31] = run[26];

arm_cor[32] = run[35];
arm_cor[33] = run[36];
arm_cor[34] = run[37];
arm_cor[35] = run[38];
arm_cor[36] = run[39];
arm_cor[37] = run[32];
arm_cor[38] = run[33];
arm_cor[39] = run[34];

arm_cor[40] = run[43];
arm_cor[41] = run[44];
arm_cor[42] = run[45];
arm_cor[43] = run[46];
arm_cor[44] = run[47];
arm_cor[45] = run[40];
arm_cor[46] = run[41];
arm_cor[47] = run[42];

arm_cor[48] = run[51];
arm_cor[49] = run[52];
arm_cor[50] = run[53];
arm_cor[51] = run[54];
arm_cor[52] = run[55];
arm_cor[53] = run[48];
arm_cor[54] = run[49];
arm_cor[55] = run[50];

arm_cor[56] = run[59];
arm_cor[57] = run[60];
arm_cor[58] = run[61];
arm_cor[59] = run[62];
arm_cor[60] = run[63];
arm_cor[61] = run[56];
arm_cor[62] = run[57];
arm_cor[63] = run[58];

arm_cor[64] = run[67];
arm_cor[65] = run[68];
arm_cor[66] = run[69];
arm_cor[67] = run[70];
arm_cor[68] = run[71];
arm_cor[69] = run[64];
arm_cor[70] = run[65];
arm_cor[71] = run[66];

arm_cor[72] = run[75];
arm_cor[73] = run[76];
arm_cor[74] = run[77];
arm_cor[75] = run[78];
arm_cor[76] = run[79];
arm_cor[77] = run[72];
arm_cor[78] = run[73];
arm_cor[79] = run[74];

arm_cor[80] = run[83];
arm_cor[81] = run[84];
arm_cor[82] = run[85];
arm_cor[83] = run[86];
arm_cor[84] = run[87];
arm_cor[85] = run[80];
arm_cor[86] = run[81];
arm_cor[87] = run[82];

for(int ii = 0;ii < 88;ii++)
  {
  run[ii] = arm_cor[ii];
  }
}

void arm_cor_3_to_1(double run[88])
{
double arm_cor[88];
arm_cor[0] = run[2];
arm_cor[1] = run[3];
arm_cor[2] = run[4];
arm_cor[3] = run[5];
arm_cor[4] = run[6];
arm_cor[5] = run[7];
arm_cor[6] = run[0];
arm_cor[7] = run[1];

arm_cor[8] = run[10];
arm_cor[9] = run[11];
arm_cor[10] = run[12];
arm_cor[11] = run[13];
arm_cor[12] = run[14];
arm_cor[13] = run[15];
arm_cor[14] = run[8];
arm_cor[15] = run[9];

arm_cor[16] = run[18];
arm_cor[17] = run[19];
arm_cor[18] = run[20];
arm_cor[19] = run[21];
arm_cor[20] = run[22];
arm_cor[21] = run[23];
arm_cor[22] = run[16];
arm_cor[23] = run[17];

arm_cor[24] = run[26];
arm_cor[25] = run[27];
arm_cor[26] = run[28];
arm_cor[27] = run[29];
arm_cor[28] = run[30];
arm_cor[29] = run[31];
arm_cor[30] = run[24];
arm_cor[31] = run[25];

arm_cor[32] = run[34];
arm_cor[33] = run[35];
arm_cor[34] = run[36];
arm_cor[35] = run[37];
arm_cor[36] = run[38];
arm_cor[37] = run[39];
arm_cor[38] = run[32];
arm_cor[39] = run[33];

arm_cor[40] = run[42];
arm_cor[41] = run[43];
arm_cor[42] = run[44];
arm_cor[43] = run[45];
arm_cor[44] = run[46];
arm_cor[45] = run[47];
arm_cor[46] = run[40];
arm_cor[47] = run[41];

arm_cor[48] = run[50];
arm_cor[49] = run[51];
arm_cor[50] = run[52];
arm_cor[51] = run[53];
arm_cor[52] = run[54];
arm_cor[53] = run[55];
arm_cor[54] = run[48];
arm_cor[55] = run[49];

arm_cor[56] = run[58];
arm_cor[57] = run[59];
arm_cor[58] = run[60];
arm_cor[59] = run[61];
arm_cor[60] = run[62];
arm_cor[61] = run[63];
arm_cor[62] = run[56];
arm_cor[63] = run[57];

arm_cor[64] = run[66];
arm_cor[65] = run[67];
arm_cor[66] = run[68];
arm_cor[67] = run[69];
arm_cor[68] = run[70];
arm_cor[69] = run[71];
arm_cor[70] = run[64];
arm_cor[71] = run[65];

arm_cor[72] = run[74];
arm_cor[73] = run[75];
arm_cor[74] = run[76];
arm_cor[75] = run[77];
arm_cor[76] = run[78];
arm_cor[77] = run[79];
arm_cor[78] = run[72];
arm_cor[79] = run[73];

arm_cor[80] = run[82];
arm_cor[81] = run[83];
arm_cor[82] = run[84];
arm_cor[83] = run[85];
arm_cor[84] = run[86];
arm_cor[85] = run[87];
arm_cor[86] = run[80];
arm_cor[87] = run[81];

for(int ii = 0;ii < 88;ii++)
  {
  run[ii] = arm_cor[ii];
  }
}

void arm_cor_2_to_1(double run[88])
{
double arm_cor[88];
arm_cor[0] = run[1];
arm_cor[1] = run[2];
arm_cor[2] = run[3];
arm_cor[3] = run[4];
arm_cor[4] = run[5];
arm_cor[5] = run[6];
arm_cor[6] = run[7];
arm_cor[7] = run[0];

arm_cor[8] = run[9];
arm_cor[9] = run[10];
arm_cor[10] = run[11];
arm_cor[11] = run[12];
arm_cor[12] = run[13];
arm_cor[13] = run[14];
arm_cor[14] = run[15];
arm_cor[15] = run[8];

arm_cor[16] = run[17];
arm_cor[17] = run[18];
arm_cor[18] = run[19];
arm_cor[19] = run[20];
arm_cor[20] = run[21];
arm_cor[21] = run[22];
arm_cor[22] = run[23];
arm_cor[23] = run[16];

arm_cor[24] = run[25];
arm_cor[25] = run[26];
arm_cor[26] = run[27];
arm_cor[27] = run[28];
arm_cor[28] = run[29];
arm_cor[29] = run[30];
arm_cor[30] = run[31];
arm_cor[31] = run[24];

arm_cor[32] = run[33];
arm_cor[33] = run[34];
arm_cor[34] = run[35];
arm_cor[35] = run[36];
arm_cor[36] = run[37];
arm_cor[37] = run[38];
arm_cor[38] = run[39];
arm_cor[39] = run[32];

arm_cor[40] = run[41];
arm_cor[41] = run[42];
arm_cor[42] = run[43];
arm_cor[43] = run[44];
arm_cor[44] = run[45];
arm_cor[45] = run[46];
arm_cor[46] = run[47];
arm_cor[47] = run[40];

arm_cor[48] = run[49];
arm_cor[49] = run[50];
arm_cor[50] = run[51];
arm_cor[51] = run[52];
arm_cor[52] = run[53];
arm_cor[53] = run[54];
arm_cor[54] = run[55];
arm_cor[55] = run[48];

arm_cor[56] = run[57];
arm_cor[57] = run[58];
arm_cor[58] = run[59];
arm_cor[59] = run[60];
arm_cor[60] = run[61];
arm_cor[61] = run[62];
arm_cor[62] = run[63];
arm_cor[63] = run[56];

arm_cor[64] = run[65];
arm_cor[65] = run[66];
arm_cor[66] = run[67];
arm_cor[67] = run[68];
arm_cor[68] = run[69];
arm_cor[69] = run[70];
arm_cor[70] = run[71];
arm_cor[71] = run[64];

arm_cor[72] = run[73];
arm_cor[73] = run[74];
arm_cor[74] = run[75];
arm_cor[75] = run[76];
arm_cor[76] = run[77];
arm_cor[77] = run[78];
arm_cor[78] = run[79];
arm_cor[79] = run[72];

arm_cor[80] = run[81];
arm_cor[81] = run[82];
arm_cor[82] = run[83];
arm_cor[83] = run[84];
arm_cor[84] = run[85];
arm_cor[85] = run[86];
arm_cor[86] = run[87];
arm_cor[87] = run[80];

for(int ii = 0;ii < 88;ii++)
  {
  run[ii] = arm_cor[ii];
  }
}

