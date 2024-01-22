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
 154;
 -92.02323;63.79909;-24.12557;,
 0.00000;63.79909;-24.12557;,
 0.00000;0.18495;-24.12557;,
 -92.02323;0.18495;-24.12557;,
 92.02323;63.79952;-24.12557;,
 92.02323;0.18495;-24.12557;,
 92.02323;63.79952;-24.12557;,
 92.02323;63.79952;23.99478;,
 92.02323;0.18495;23.99478;,
 92.02323;0.18495;-24.12557;,
 92.02323;63.79952;23.99478;,
 0.00000;63.79952;23.99478;,
 0.00000;0.18495;23.99478;,
 92.02323;0.18495;23.99478;,
 -92.02323;63.79952;23.99478;,
 -92.02323;0.18495;23.99478;,
 -92.02323;63.79952;23.99478;,
 -92.02323;63.79909;-24.12557;,
 -92.02323;0.18495;-24.12557;,
 -92.02323;0.18495;23.99478;,
 86.05590;63.79909;4.27037;,
 21.36698;63.79909;3.85760;,
 87.12531;63.79909;-20.67990;,
 0.00000;63.79909;-24.12557;,
 21.14662;63.79909;-21.39955;,
 86.54158;48.58261;4.24562;,
 21.35150;48.58249;4.02532;,
 86.77922;48.58261;-20.19092;,
 21.64412;48.58261;-21.13964;,
 -10.76692;63.79909;18.17917;,
 -81.56209;63.79909;17.69758;,
 -10.43040;63.79909;-17.15043;,
 -81.18800;63.79909;-17.18269;,
 57.12686;44.72172;-3.48482;,
 45.06256;44.72172;-3.41599;,
 57.09873;44.72172;-13.69954;,
 45.08640;44.72172;-13.61637;,
 -30.24218;63.15710;4.89471;,
 -26.63992;63.15710;4.89471;,
 -26.63992;67.25358;1.29247;,
 -30.24218;63.15710;1.29247;,
 -23.03769;63.15710;4.89471;,
 -23.03769;67.25358;1.29247;,
 -19.43546;63.15710;4.89471;,
 -19.43546;63.15710;1.29247;,
 -33.84439;63.15710;1.29247;,
 -30.24218;67.25358;-2.30976;,
 -33.84439;63.15710;-2.30976;,
 -23.03769;63.15710;-2.30976;,
 -26.63992;63.15710;-2.30976;,
 -15.83322;63.15710;1.29247;,
 -15.83322;63.15710;-2.30976;,
 -19.43546;67.25358;-2.30976;,
 -30.24218;67.25358;-5.91200;,
 -33.84439;63.15710;-5.91200;,
 -26.63992;63.15710;-5.91200;,
 -23.03769;63.15710;-5.91200;,
 -19.43546;67.25358;-5.91200;,
 -15.83322;63.15710;-5.91200;,
 -30.24218;63.15710;-9.51424;,
 -33.84439;63.15710;-9.51424;,
 -23.03769;67.25358;-9.51424;,
 -26.63992;67.25358;-9.51424;,
 -15.83322;63.15710;-9.51424;,
 -19.43546;63.15710;-9.51424;,
 -26.63992;63.15710;-13.11648;,
 -30.24218;63.15710;-13.11648;,
 -23.03769;63.15710;-13.11648;,
 -19.43546;63.15710;-13.11648;,
 -52.38632;63.15710;15.91523;,
 -48.78408;63.15710;15.91523;,
 -48.78408;67.25358;12.31299;,
 -52.38632;63.15710;12.31299;,
 -45.18183;63.15710;15.91523;,
 -45.18183;67.25358;12.31299;,
 -41.57961;63.15710;15.91523;,
 -41.57961;63.15710;12.31299;,
 -55.98857;63.15710;12.31299;,
 -52.38632;67.25358;8.71076;,
 -55.98857;63.15710;8.71076;,
 -45.18183;63.15710;8.71076;,
 -48.78408;63.15710;8.71076;,
 -37.97738;63.15710;12.31299;,
 -37.97738;63.15710;8.71076;,
 -41.57961;67.25358;8.71076;,
 -52.38632;67.25358;5.10852;,
 -55.98857;63.15710;5.10852;,
 -48.78408;63.15710;5.10852;,
 -45.18183;63.15710;5.10852;,
 -41.57961;67.25358;5.10852;,
 -37.97738;63.15710;5.10852;,
 -52.38632;63.15710;1.50625;,
 -55.98857;63.15710;1.50625;,
 -45.18183;67.25358;1.50625;,
 -48.78408;67.25358;1.50625;,
 -37.97738;63.15710;1.50625;,
 -41.57961;63.15710;1.50625;,
 -48.78408;63.15710;-2.09599;,
 -52.38632;63.15710;-2.09599;,
 -45.18183;63.15710;-2.09599;,
 -41.57961;63.15710;-2.09599;,
 -72.70198;63.15710;4.89471;,
 -69.09973;63.15710;4.89471;,
 -69.09973;67.25358;1.29247;,
 -72.70198;63.15710;1.29247;,
 -65.49749;63.15710;4.89471;,
 -65.49749;67.25358;1.29247;,
 -61.89522;63.15710;4.89471;,
 -61.89522;63.15710;1.29247;,
 -76.30419;63.15710;1.29247;,
 -72.70198;67.25358;-2.30976;,
 -76.30419;63.15710;-2.30976;,
 -65.49749;63.15710;-2.30976;,
 -69.09973;63.15710;-2.30976;,
 -58.29301;63.15710;1.29247;,
 -58.29301;63.15710;-2.30976;,
 -61.89522;67.25358;-2.30976;,
 -72.70198;67.25358;-5.91200;,
 -76.30419;63.15710;-5.91200;,
 -69.09973;63.15710;-5.91200;,
 -65.49749;63.15710;-5.91200;,
 -61.89522;67.25358;-5.91200;,
 -58.29301;63.15710;-5.91200;,
 -72.70198;63.15710;-9.51424;,
 -76.30419;63.15710;-9.51424;,
 -65.49749;67.25358;-9.51424;,
 -69.09973;67.25358;-9.51424;,
 -58.29301;63.15710;-9.51424;,
 -61.89522;63.15710;-9.51424;,
 -69.09973;63.15710;-13.11648;,
 -72.70198;63.15710;-13.11648;,
 -65.49749;63.15710;-13.11648;,
 -61.89522;63.15710;-13.11648;,
 50.31870;88.08700;6.36659;,
 47.56411;92.85819;6.36659;,
 47.56411;80.13558;-2.80017;,
 50.31870;76.76189;0.57353;,
 53.07335;92.85813;6.36659;,
 53.07330;80.13554;-2.80017;,
 50.31870;88.08700;6.36659;,
 50.31870;76.76189;0.57353;,
 50.31870;62.64117;11.57860;,
 47.56414;62.64117;16.34968;,
 47.56411;84.00780;15.53402;,
 50.31870;80.63407;12.16035;,
 53.07327;62.64122;16.34968;,
 53.07330;84.00780;15.53402;,
 50.31870;62.64117;11.57860;,
 50.31870;80.63407;12.16035;,
 47.56411;92.85819;6.36659;,
 50.31870;88.08700;6.36659;,
 53.07335;92.85813;6.36659;,
 50.31870;88.08700;6.36659;,
 50.83485;80.58088;-0.26898;;
 
 111;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;6,7,8,9;,
 4;10,11,12,13;,
 4;11,14,15,12;,
 4;16,17,18,19;,
 4;7,20,21,11;,
 4;4,22,20,7;,
 4;23,24,22,4;,
 4;11,21,24,23;,
 4;20,25,26,21;,
 4;22,27,25,20;,
 4;27,22,24,28;,
 4;28,24,21,26;,
 4;11,29,30,16;,
 4;23,31,29,11;,
 4;17,32,31,23;,
 4;16,30,32,17;,
 4;29,31,32,30;,
 4;25,33,34,26;,
 4;27,35,33,25;,
 4;28,36,35,27;,
 4;34,36,28,26;,
 4;34,33,35,36;,
 4;37,38,39,40;,
 4;38,41,42,39;,
 4;41,43,44,42;,
 4;45,40,46,47;,
 4;39,42,48,49;,
 4;44,50,51,52;,
 4;47,46,53,54;,
 4;46,49,55,53;,
 4;49,48,56,55;,
 4;48,52,57,56;,
 4;52,51,58,57;,
 4;54,53,59,60;,
 4;55,56,61,62;,
 4;57,58,63,64;,
 4;59,62,65,66;,
 4;62,61,67,65;,
 4;61,64,68,67;,
 3;49,46,40;,
 3;49,40,39;,
 3;44,48,42;,
 3;44,52,48;,
 3;56,64,61;,
 3;56,57,64;,
 3;62,59,55;,
 3;53,55,59;,
 4;69,70,71,72;,
 4;70,73,74,71;,
 4;73,75,76,74;,
 4;77,72,78,79;,
 4;71,74,80,81;,
 4;76,82,83,84;,
 4;79,78,85,86;,
 4;78,81,87,85;,
 4;81,80,88,87;,
 4;80,84,89,88;,
 4;84,83,90,89;,
 4;86,85,91,92;,
 4;87,88,93,94;,
 4;89,90,95,96;,
 4;91,94,97,98;,
 4;94,93,99,97;,
 4;93,96,100,99;,
 3;81,78,72;,
 3;81,72,71;,
 3;76,80,74;,
 3;76,84,80;,
 3;88,96,93;,
 3;88,89,96;,
 3;94,91,87;,
 3;85,87,91;,
 4;101,102,103,104;,
 4;102,105,106,103;,
 4;105,107,108,106;,
 4;109,104,110,111;,
 4;103,106,112,113;,
 4;108,114,115,116;,
 4;111,110,117,118;,
 4;110,113,119,117;,
 4;113,112,120,119;,
 4;112,116,121,120;,
 4;116,115,122,121;,
 4;118,117,123,124;,
 4;119,120,125,126;,
 4;121,122,127,128;,
 4;123,126,129,130;,
 4;126,125,131,129;,
 4;125,128,132,131;,
 3;113,110,104;,
 3;113,104,103;,
 3;108,112,106;,
 3;108,116,112;,
 3;120,128,125;,
 3;120,121,128;,
 3;126,123,119;,
 3;117,119,123;,
 4;133,134,135,136;,
 4;134,137,138,135;,
 4;137,139,140,138;,
 4;141,142,143,144;,
 4;142,145,146,143;,
 4;145,147,148,146;,
 4;144,143,149,150;,
 4;143,146,151,149;,
 4;146,148,152,151;,
 3;138,153,135;,
 3;153,136,135;,
 3;138,140,153;;
 
 MeshMaterialList {
  4;
  111;
  3,
  3,
  3,
  3,
  3,
  3,
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
  2,
  2,
  2,
  2,
  1,
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
  2;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.580000;0.580000;0.580000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.432800;0.128800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  164;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000005;1.000000;-0.000013;,
  -0.000038;1.000000;-0.000012;,
  -0.000039;1.000000;0.000029;,
  0.000004;1.000000;0.000027;,
  0.004880;-0.004647;-0.999977;,
  -0.999641;-0.005274;-0.026279;,
  -0.012731;0.024584;0.999617;,
  0.000008;1.000000;-0.000025;,
  -0.000008;1.000000;-0.000025;,
  -0.000008;1.000000;-0.000002;,
  0.000008;1.000000;-0.000001;,
  0.055147;0.986034;-0.157146;,
  -0.044511;0.986514;-0.157509;,
  -0.045048;0.986030;0.160361;,
  0.054712;0.985425;0.161070;,
  -1.000000;0.000000;0.000000;,
  -0.000003;1.000000;-0.000026;,
  -0.000004;1.000000;0.000013;,
  0.999874;0.015822;0.001454;,
  0.000012;1.000000;-0.000038;,
  0.000012;1.000000;-0.000002;,
  -0.066991;0.969183;-0.237057;,
  0.083015;0.968064;-0.236559;,
  -0.067810;0.968055;0.241392;,
  0.082362;0.966657;0.242469;,
  -0.343496;0.874083;0.343497;,
  -0.179296;0.800935;0.571276;,
  0.179297;0.800935;0.571275;,
  0.343497;0.874082;0.343497;,
  -0.343498;0.874082;0.343496;,
  -0.343497;0.874082;0.343497;,
  0.343497;0.874082;0.343497;,
  0.343496;0.874082;0.343497;,
  -0.571278;0.800934;0.179296;,
  -0.227352;0.828553;-0.511674;,
  -0.294243;0.909309;-0.294243;,
  0.571275;0.800936;0.179296;,
  -0.571278;0.800934;-0.179296;,
  0.294242;0.909309;0.294243;,
  -0.294243;0.909309;0.294243;,
  -0.712347;0.626401;-0.316517;,
  0.571275;0.800936;-0.179296;,
  -0.343498;0.874082;-0.343496;,
  -0.343497;0.874082;-0.343497;,
  -0.316517;0.626402;0.712347;,
  0.316518;0.626402;0.712346;,
  0.343497;0.874082;-0.343497;,
  0.343496;0.874082;-0.343497;,
  -0.343496;0.874083;-0.343497;,
  -0.179296;0.800935;-0.571276;,
  0.179297;0.800935;-0.571276;,
  0.343497;0.874082;-0.343497;,
  -0.343497;0.874082;0.343496;,
  -0.179297;0.800935;0.571275;,
  0.179297;0.800935;0.571275;,
  0.343498;0.874082;0.343496;,
  -0.343496;0.874083;0.343497;,
  -0.343496;0.874082;0.343497;,
  0.343498;0.874082;0.343496;,
  0.343497;0.874082;0.343497;,
  -0.571274;0.800936;0.179297;,
  -0.227353;0.828553;-0.511674;,
  -0.294243;0.909308;-0.294243;,
  0.571276;0.800935;0.179296;,
  -0.571275;0.800936;-0.179295;,
  0.294243;0.909309;0.294241;,
  -0.294243;0.909309;0.294241;,
  -0.712348;0.626401;-0.316515;,
  0.571276;0.800935;-0.179295;,
  -0.343497;0.874083;-0.343495;,
  -0.343497;0.874083;-0.343496;,
  -0.316519;0.626404;0.712343;,
  0.316520;0.626404;0.712343;,
  0.343498;0.874083;-0.343495;,
  0.343498;0.874083;-0.343494;,
  -0.343497;0.874082;-0.343497;,
  -0.179296;0.800935;-0.571276;,
  0.179297;0.800935;-0.571275;,
  0.343498;0.874082;-0.343496;,
  -0.343495;0.874083;0.343497;,
  -0.179296;0.800935;0.571276;,
  0.179295;0.800935;0.571276;,
  0.343494;0.874083;0.343498;,
  -0.343499;0.874082;0.343496;,
  -0.343497;0.874082;0.343497;,
  0.343496;0.874082;0.343497;,
  0.343499;0.874082;0.343496;,
  -0.571279;0.800933;0.179296;,
  -0.227352;0.828553;-0.511674;,
  -0.294241;0.909309;-0.294242;,
  0.571278;0.800933;0.179296;,
  -0.571279;0.800933;-0.179296;,
  0.294242;0.909309;0.294243;,
  -0.294241;0.909309;0.294242;,
  -0.712343;0.626405;-0.316519;,
  0.571278;0.800933;-0.179296;,
  -0.343499;0.874082;-0.343496;,
  -0.343497;0.874082;-0.343497;,
  -0.316516;0.626402;0.712347;,
  0.316515;0.626402;0.712347;,
  0.343496;0.874082;-0.343497;,
  0.343499;0.874082;-0.343496;,
  -0.343495;0.874083;-0.343498;,
  -0.179296;0.800935;-0.571276;,
  0.179295;0.800935;-0.571276;,
  0.343494;0.874083;-0.343498;,
  -0.316517;0.626402;-0.712347;,
  0.316518;0.626402;-0.712346;,
  0.712345;0.626403;0.316518;,
  0.712345;0.626403;-0.316518;,
  -0.712347;0.626401;0.316517;,
  0.600487;0.528041;0.600490;,
  -0.600487;0.528041;-0.600490;,
  0.600490;0.528039;-0.600488;,
  -0.600490;0.528039;0.600488;,
  0.600490;0.528039;0.600488;,
  -0.600490;0.528039;-0.600488;,
  -0.600487;0.528041;0.600490;,
  0.600487;0.528041;-0.600490;,
  -0.316518;0.626401;-0.712347;,
  0.316519;0.626401;-0.712347;,
  0.712347;0.626401;0.316518;,
  0.712347;0.626402;-0.316516;,
  -0.712348;0.626400;0.316517;,
  0.600489;0.528039;0.600489;,
  -0.600489;0.528039;-0.600489;,
  0.600490;0.528039;-0.600488;,
  -0.600490;0.528039;0.600488;,
  0.600493;0.528041;0.600485;,
  -0.600493;0.528041;-0.600485;,
  -0.600491;0.528041;0.600485;,
  0.600491;0.528041;-0.600485;,
  -0.316516;0.626402;-0.712347;,
  0.316515;0.626402;-0.712347;,
  0.712344;0.626404;0.316518;,
  0.712344;0.626404;-0.316518;,
  -0.712343;0.626405;0.316519;,
  0.600487;0.528041;0.600490;,
  -0.600487;0.528041;-0.600490;,
  0.600485;0.528042;-0.600491;,
  -0.600485;0.528042;0.600491;,
  0.600485;0.528042;0.600491;,
  -0.600485;0.528042;-0.600491;,
  -0.600487;0.528041;0.600490;,
  0.600487;0.528041;-0.600490;,
  -0.914491;-0.400405;0.058164;,
  0.000006;0.584577;-0.811338;,
  -0.789436;-0.326072;0.520065;,
  -0.433091;0.311606;-0.845774;,
  -0.828136;-0.003725;-0.560515;,
  -0.000000;0.038147;0.999272;,
  -0.843952;-0.196315;-0.499204;,
  0.000002;0.408285;0.912854;,
  -0.000009;-0.984873;0.173275;,
  0.914488;-0.400411;0.058166;,
  0.789431;-0.326076;0.520069;,
  0.828136;-0.003725;-0.560514;,
  0.843951;-0.196317;-0.499205;,
  0.000004;0.719439;0.694556;,
  0.613773;-0.248284;-0.749425;,
  -0.752168;-0.043403;-0.657541;;
  111;
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;18,18,18,18;,
  4;4,4,3,19;,
  4;5,5,4,4;,
  4;20,6,5,5;,
  4;19,3,6,20;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;21,21,21,21;,
  4;19,11,10,22;,
  4;20,12,11,19;,
  4;23,13,12,20;,
  4;22,10,13,23;,
  4;11,12,13,10;,
  4;24,15,14,25;,
  4;26,16,15,24;,
  4;27,17,16,26;,
  4;14,17,27,25;,
  4;14,15,16,17;,
  4;28,29,29,33;,
  4;29,30,30,29;,
  4;30,31,34,30;,
  4;32,33,36,36;,
  4;109,110,38,37;,
  4;34,35,39,39;,
  4;36,36,40,40;,
  4;111,111,41,112;,
  4;37,38,42,41;,
  4;38,113,43,42;,
  4;39,39,44,44;,
  4;40,40,46,45;,
  4;41,42,48,47;,
  4;44,44,50,49;,
  4;46,52,52,51;,
  4;52,53,53,52;,
  4;53,49,54,53;,
  3;111,111,114;,
  3;37,115,109;,
  3;116,116,110;,
  3;117,113,117;,
  3;118,118,48;,
  3;119,43,119;,
  3;47,120,120;,
  3;112,121,121;,
  4;55,56,56,60;,
  4;56,57,57,56;,
  4;57,58,61,57;,
  4;59,60,63,63;,
  4;122,123,65,64;,
  4;61,62,66,66;,
  4;63,63,67,67;,
  4;124,124,68,125;,
  4;64,65,69,68;,
  4;65,126,70,69;,
  4;66,66,71,71;,
  4;67,67,73,72;,
  4;68,69,75,74;,
  4;71,71,77,76;,
  4;73,79,79,78;,
  4;79,80,80,79;,
  4;80,76,81,80;,
  3;124,124,127;,
  3;64,128,122;,
  3;129,129,123;,
  3;130,126,130;,
  3;131,131,75;,
  3;132,70,132;,
  3;74,133,133;,
  3;125,134,134;,
  4;82,83,83,87;,
  4;83,84,84,83;,
  4;84,85,88,84;,
  4;86,87,90,90;,
  4;135,136,92,91;,
  4;88,89,93,93;,
  4;90,90,94,94;,
  4;137,137,95,138;,
  4;91,92,96,95;,
  4;92,139,97,96;,
  4;93,93,98,98;,
  4;94,94,100,99;,
  4;95,96,102,101;,
  4;98,98,104,103;,
  4;100,106,106,105;,
  4;106,107,107,106;,
  4;107,103,108,107;,
  3;137,137,140;,
  3;91,141,135;,
  3;142,142,136;,
  3;143,139,143;,
  3;144,144,102;,
  3;145,97,145;,
  3;101,146,146;,
  3;138,147,147;,
  4;148,148,150,150;,
  4;149,149,151,149;,
  4;157,157,158,158;,
  4;152,152,154,154;,
  4;153,153,155,155;,
  4;159,159,160,160;,
  4;154,154,148,148;,
  4;155,155,161,161;,
  4;160,160,157,157;,
  3;156,156,156;,
  3;162,162,162;,
  3;151,163,163;;
 }
 MeshTextureCoords {
  154;
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.500000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.200000;0.000000;,
  0.400000;0.000000;,
  0.400000;0.200000;,
  0.200000;0.200000;,
  0.600000;0.000000;,
  0.600000;0.200000;,
  0.800000;0.000000;,
  0.800000;0.200000;,
  0.000000;0.200000;,
  0.200000;0.400000;,
  0.000000;0.400000;,
  0.600000;0.400000;,
  0.400000;0.400000;,
  1.000000;0.200000;,
  1.000000;0.400000;,
  0.800000;0.400000;,
  0.200000;0.600000;,
  0.000000;0.600000;,
  0.400000;0.600000;,
  0.600000;0.600000;,
  0.800000;0.600000;,
  1.000000;0.600000;,
  0.200000;0.800000;,
  0.000000;0.800000;,
  0.600000;0.800000;,
  0.400000;0.800000;,
  1.000000;0.800000;,
  0.800000;0.800000;,
  0.400000;1.000000;,
  0.200000;1.000000;,
  0.600000;1.000000;,
  0.800000;1.000000;,
  0.200000;0.000000;,
  0.400000;0.000000;,
  0.400000;0.200000;,
  0.200000;0.200000;,
  0.600000;0.000000;,
  0.600000;0.200000;,
  0.800000;0.000000;,
  0.800000;0.200000;,
  0.000000;0.200000;,
  0.200000;0.400000;,
  0.000000;0.400000;,
  0.600000;0.400000;,
  0.400000;0.400000;,
  1.000000;0.200000;,
  1.000000;0.400000;,
  0.800000;0.400000;,
  0.200000;0.600000;,
  0.000000;0.600000;,
  0.400000;0.600000;,
  0.600000;0.600000;,
  0.800000;0.600000;,
  1.000000;0.600000;,
  0.200000;0.800000;,
  0.000000;0.800000;,
  0.600000;0.800000;,
  0.400000;0.800000;,
  1.000000;0.800000;,
  0.800000;0.800000;,
  0.400000;1.000000;,
  0.200000;1.000000;,
  0.600000;1.000000;,
  0.800000;1.000000;,
  0.200000;0.000000;,
  0.400000;0.000000;,
  0.400000;0.200000;,
  0.200000;0.200000;,
  0.600000;0.000000;,
  0.600000;0.200000;,
  0.800000;0.000000;,
  0.800000;0.200000;,
  0.000000;0.200000;,
  0.200000;0.400000;,
  0.000000;0.400000;,
  0.600000;0.400000;,
  0.400000;0.400000;,
  1.000000;0.200000;,
  1.000000;0.400000;,
  0.800000;0.400000;,
  0.200000;0.600000;,
  0.000000;0.600000;,
  0.400000;0.600000;,
  0.600000;0.600000;,
  0.800000;0.600000;,
  1.000000;0.600000;,
  0.200000;0.800000;,
  0.000000;0.800000;,
  0.600000;0.800000;,
  0.400000;0.800000;,
  1.000000;0.800000;,
  0.800000;0.800000;,
  0.400000;1.000000;,
  0.200000;1.000000;,
  0.600000;1.000000;,
  0.800000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.333330;,
  0.125000;0.333330;,
  0.125000;0.000000;,
  0.000000;0.666670;,
  0.125000;0.666670;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.750000;0.000000;,
  0.750000;0.333330;,
  0.875000;0.333330;,
  0.875000;0.000000;,
  0.750000;0.666670;,
  0.875000;0.666670;,
  0.750000;1.000000;,
  0.875000;1.000000;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  1.000000;0.666670;,
  1.000000;1.000000;,
  0.000000;0.000000;;
 }
}
