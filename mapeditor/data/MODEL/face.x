xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 105;
 0.53802;20.00000;-0.25097;,
 -1.97261;19.23879;-3.13912;,
 -3.27949;19.23879;-0.51791;,
 0.53802;20.00000;-0.25097;,
 0.80496;19.23879;-4.06848;,
 0.53802;20.00000;-0.25097;,
 3.42617;19.23879;-2.76160;,
 0.53802;20.00000;-0.25097;,
 4.35553;19.23879;0.01598;,
 0.53802;20.00000;-0.25097;,
 3.04865;19.23879;2.63718;,
 0.53802;20.00000;-0.25097;,
 0.27107;19.23879;3.56654;,
 0.53802;20.00000;-0.25097;,
 -2.35013;19.23879;2.25966;,
 0.53802;20.00000;-0.25097;,
 -3.27949;19.23879;-0.51791;,
 -4.10102;17.07107;-5.58757;,
 -6.51583;17.07107;-0.74422;,
 1.03127;17.07107;-7.30482;,
 5.87462;17.07107;-4.89001;,
 7.59186;17.07107;0.24229;,
 5.17705;17.07107;5.08564;,
 0.04476;17.07107;6.80288;,
 -4.79859;17.07107;4.38807;,
 -6.51583;17.07107;-0.74422;,
 -5.52317;13.82683;-7.22357;,
 -8.67827;13.82683;-0.89543;,
 1.18248;13.82683;-9.46725;,
 7.51062;13.82683;-6.31216;,
 9.75431;13.82683;0.39350;,
 6.59921;13.82683;6.72165;,
 -0.10645;13.82683;8.96532;,
 -6.43459;13.82683;5.81024;,
 -8.67827;13.82683;-0.89543;,
 -6.02258;10.00000;-7.79807;,
 -9.43763;10.00000;-0.94853;,
 1.23558;10.00000;-10.22661;,
 8.08512;10.00000;-6.81156;,
 10.51366;10.00000;0.44660;,
 7.09861;10.00000;7.29613;,
 -0.15955;10.00000;9.72467;,
 -7.00908;10.00000;6.30962;,
 -9.43763;10.00000;-0.94853;,
 -5.52317;6.17316;-7.22357;,
 -8.67827;6.17316;-0.89543;,
 1.18248;6.17316;-9.46725;,
 7.51062;6.17316;-6.31216;,
 9.75431;6.17316;0.39350;,
 6.59921;6.17316;6.72165;,
 -0.10645;6.17316;8.96532;,
 -6.43459;6.17316;5.81024;,
 -8.67827;6.17316;-0.89543;,
 -4.10102;2.92893;-5.58757;,
 -6.51583;2.92893;-0.74422;,
 1.03127;2.92893;-7.30482;,
 5.87462;2.92893;-4.89001;,
 7.59186;2.92893;0.24229;,
 5.17705;2.92893;5.08564;,
 0.04476;2.92893;6.80288;,
 -4.79859;2.92893;4.38807;,
 -6.51583;2.92893;-0.74422;,
 -1.97261;0.76121;-3.13912;,
 -3.27949;0.76121;-0.51791;,
 0.80496;0.76121;-4.06848;,
 3.42617;0.76121;-2.76160;,
 4.35553;0.76121;0.01598;,
 3.04865;0.76121;2.63718;,
 0.27107;0.76121;3.56654;,
 -2.35013;0.76121;2.25966;,
 -3.27949;0.76121;-0.51791;,
 0.53802;0.00000;-0.25097;,
 0.53802;0.00000;-0.25097;,
 0.53802;0.00000;-0.25097;,
 0.53802;0.00000;-0.25097;,
 0.53802;0.00000;-0.25097;,
 0.53802;0.00000;-0.25097;,
 0.53802;0.00000;-0.25097;,
 0.53802;0.00000;-0.25097;,
 -2.17799;9.47114;-4.41701;,
 1.51226;9.47114;-14.18337;,
 -1.30145;7.34982;-4.35571;,
 1.51226;9.47114;-14.18337;,
 0.81470;6.47114;-4.20774;,
 1.51226;9.47114;-14.18337;,
 2.93085;7.34982;-4.05976;,
 1.51226;9.47114;-14.18337;,
 3.80739;9.47114;-3.99847;,
 1.51226;9.47114;-14.18337;,
 2.93085;11.59246;-4.05976;,
 1.51226;9.47114;-14.18337;,
 0.81470;12.47114;-4.20774;,
 1.51226;9.47114;-14.18337;,
 -1.30145;11.59246;-4.35571;,
 1.51226;9.47114;-14.18337;,
 -2.17799;9.47114;-4.41701;,
 0.81470;9.47114;-4.20774;,
 -2.17799;9.47114;-4.41701;,
 -1.30145;7.34982;-4.35571;,
 0.81470;6.47114;-4.20774;,
 2.93085;7.34982;-4.05976;,
 3.80739;9.47114;-3.99847;,
 2.93085;11.59246;-4.05976;,
 0.81470;12.47114;-4.20774;,
 -1.30145;11.59246;-4.35571;;
 
 80;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 4;2,1,17,18;,
 4;1,4,19,17;,
 4;4,6,20,19;,
 4;6,8,21,20;,
 4;8,10,22,21;,
 4;10,12,23,22;,
 4;12,14,24,23;,
 4;14,16,25,24;,
 4;18,17,26,27;,
 4;17,19,28,26;,
 4;19,20,29,28;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;27,26,35,36;,
 4;26,28,37,35;,
 4;28,29,38,37;,
 4;29,30,39,38;,
 4;30,31,40,39;,
 4;31,32,41,40;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 4;36,35,44,45;,
 4;35,37,46,44;,
 4;37,38,47,46;,
 4;38,39,48,47;,
 4;39,40,49,48;,
 4;40,41,50,49;,
 4;41,42,51,50;,
 4;42,43,52,51;,
 4;45,44,53,54;,
 4;44,46,55,53;,
 4;46,47,56,55;,
 4;47,48,57,56;,
 4;48,49,58,57;,
 4;49,50,59,58;,
 4;50,51,60,59;,
 4;51,52,61,60;,
 4;54,53,62,63;,
 4;53,55,64,62;,
 4;55,56,65,64;,
 4;56,57,66,65;,
 4;57,58,67,66;,
 4;58,59,68,67;,
 4;59,60,69,68;,
 4;60,61,70,69;,
 3;63,62,71;,
 3;62,64,72;,
 3;64,65,73;,
 3;65,66,74;,
 3;66,67,75;,
 3;67,68,76;,
 3;68,69,77;,
 3;69,70,78;,
 3;79,80,81;,
 3;81,82,83;,
 3;83,84,85;,
 3;85,86,87;,
 3;87,88,89;,
 3;89,90,91;,
 3;91,92,93;,
 3;93,94,95;,
 3;96,97,98;,
 3;96,98,99;,
 3;96,99,100;,
 3;96,100,101;,
 3;96,101,102;,
 3;96,102,103;,
 3;96,103,104;,
 3;96,104,97;;
 
 MeshMaterialList {
  3;
  80;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.338824;0.037647;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  74;
  -0.000000;1.000000;0.000000;,
  -0.379683;0.924735;-0.026550;,
  -0.249703;0.924735;-0.287250;,
  0.026550;0.924735;-0.379683;,
  0.287250;0.924735;-0.249703;,
  0.379684;0.924735;0.026550;,
  0.249703;0.924735;0.287251;,
  -0.026550;0.924735;0.379683;,
  -0.287250;0.924735;0.249703;,
  -0.703259;0.709230;-0.049177;,
  -0.462506;0.709230;-0.532053;,
  0.049177;0.709230;-0.703259;,
  0.532053;0.709230;-0.462506;,
  0.703259;0.709230;0.049177;,
  0.462506;0.709231;0.532053;,
  -0.049177;0.709231;0.703259;,
  -0.532052;0.709231;0.462506;,
  -0.920855;0.384551;-0.064393;,
  -0.605611;0.384551;-0.696675;,
  0.064393;0.384551;-0.920855;,
  0.696675;0.384551;-0.605611;,
  0.920855;0.384551;0.064392;,
  0.605610;0.384551;0.696676;,
  -0.064392;0.384550;0.920855;,
  -0.696675;0.384551;0.605611;,
  -0.997564;0.000000;-0.069757;,
  -0.656059;0.000000;-0.754710;,
  0.069756;0.000000;-0.997564;,
  0.754710;0.000000;-0.656059;,
  0.997564;0.000000;0.069756;,
  0.656059;0.000000;0.754710;,
  -0.069757;0.000000;0.997564;,
  -0.754709;0.000000;0.656059;,
  -0.920855;-0.384551;-0.064393;,
  -0.605610;-0.384551;-0.696675;,
  0.064393;-0.384551;-0.920855;,
  0.696675;-0.384551;-0.605610;,
  0.920855;-0.384551;0.064392;,
  0.605610;-0.384551;0.696675;,
  -0.064392;-0.384551;0.920855;,
  -0.696675;-0.384551;0.605611;,
  -0.703259;-0.709231;-0.049177;,
  -0.462506;-0.709231;-0.532052;,
  0.049177;-0.709231;-0.703259;,
  0.532052;-0.709231;-0.462506;,
  0.703259;-0.709231;0.049177;,
  0.462506;-0.709231;0.532052;,
  -0.049176;-0.709231;0.703259;,
  -0.532052;-0.709231;0.462506;,
  -0.379683;-0.924735;-0.026550;,
  -0.249703;-0.924735;-0.287250;,
  0.026550;-0.924735;-0.379683;,
  0.287250;-0.924735;-0.249703;,
  0.379683;-0.924735;0.026550;,
  0.249703;-0.924735;0.287250;,
  -0.026550;-0.924735;0.379683;,
  -0.287250;-0.924735;0.249703;,
  0.000000;-1.000000;0.000000;,
  -0.935449;0.000000;-0.353462;,
  -0.655591;-0.677285;-0.333893;,
  0.020045;-0.957826;-0.286648;,
  0.695680;-0.677285;-0.239403;,
  0.975537;0.000000;-0.219834;,
  0.695680;0.677285;-0.239403;,
  0.020044;0.957826;-0.286648;,
  -0.655591;0.677285;-0.333893;,
  -0.069757;-0.000000;0.997564;,
  -0.069756;-0.000000;0.997564;,
  -0.069756;0.000000;0.997564;,
  -0.069757;0.000000;0.997564;,
  -0.069757;0.000001;0.997564;,
  -0.069757;-0.000000;0.997564;,
  -0.069757;-0.000001;0.997564;,
  -0.069756;-0.000000;0.997564;;
  80;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,25,33,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,41,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,41,49,56;,
  3;49,50,57;,
  3;50,51,57;,
  3;51,52,57;,
  3;52,53,57;,
  3;53,54,57;,
  3;54,55,57;,
  3;55,56,57;,
  3;56,49,57;,
  3;58,59,59;,
  3;59,59,60;,
  3;60,61,61;,
  3;61,61,62;,
  3;62,63,63;,
  3;63,63,64;,
  3;64,65,65;,
  3;65,65,58;,
  3;66,67,68;,
  3;66,68,69;,
  3;66,69,70;,
  3;66,70,71;,
  3;66,71,72;,
  3;66,72,69;,
  3;66,69,73;,
  3;66,73,67;;
 }
 MeshTextureCoords {
  105;
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}