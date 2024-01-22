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
 106;
 -16.22194;8.09086;7.84718;,
 -16.22194;0.57570;7.84718;,
 -14.40384;0.57570;8.73906;,
 -14.40384;8.09086;8.73906;,
 -1.72387;8.09086;-18.62406;,
 0.20905;8.09086;-17.99694;,
 0.20905;0.57570;-17.99694;,
 -1.72387;0.57570;-18.62406;,
 1.44627;8.09086;-19.40570;,
 1.44627;0.57570;-19.40570;,
 14.72259;8.09086;-4.72827;,
 14.72259;0.57570;-4.72827;,
 16.00275;0.57570;-6.08054;,
 16.00275;8.09086;-6.08054;,
 -11.79132;89.65916;3.95914;,
 -13.62995;89.65916;3.11460;,
 -16.22194;89.65916;7.84718;,
 -14.40384;89.65916;8.73906;,
 -11.79132;8.09086;3.95914;,
 -11.79132;0.57570;3.95914;,
 -13.62995;8.09086;3.11460;,
 -13.62995;0.57570;3.11460;,
 -16.22194;0.57570;7.84718;,
 -16.22194;8.09086;7.84718;,
 -16.22194;83.91188;7.84718;,
 -13.62995;83.91188;3.11460;,
 -16.22194;83.91188;7.84718;,
 -14.40384;83.91188;8.73906;,
 -16.22194;89.65916;7.84718;,
 -11.79132;83.91188;3.95914;,
 -1.72387;83.91188;-18.62406;,
 -1.72387;89.65916;-18.62406;,
 0.20905;89.65916;-17.99694;,
 0.20905;83.91188;-17.99694;,
 1.44627;89.65916;-19.40570;,
 1.44627;83.91188;-19.40570;,
 14.72259;83.91188;-4.72827;,
 16.00275;83.91188;-6.08054;,
 16.00275;89.65916;-6.08054;,
 14.72259;89.65916;-4.72827;,
 -16.22194;38.90372;7.84718;,
 -13.62995;38.90372;3.11460;,
 -16.22194;38.90372;7.84718;,
 -14.40384;38.90372;8.73906;,
 -11.79132;38.90372;3.95914;,
 -1.72387;38.90372;-18.62406;,
 0.20905;38.90372;-17.99694;,
 1.44627;38.90372;-19.40570;,
 14.72259;38.90372;-4.72827;,
 16.00275;38.90372;-6.08054;,
 -16.22194;36.96576;7.84718;,
 -13.62995;36.96576;3.11460;,
 -16.22194;36.96576;7.84718;,
 -14.40384;36.96576;8.73906;,
 -11.79132;36.96576;3.95914;,
 -1.72387;36.96576;-18.62406;,
 0.20905;36.96576;-17.99694;,
 1.44627;36.96576;-19.40570;,
 14.72259;36.96576;-4.72827;,
 16.00275;36.96576;-6.08054;,
 -4.85014;89.65916;-12.91597;,
 -4.85014;83.91188;-12.91597;,
 -2.94199;89.65916;-12.23179;,
 -4.85014;38.90372;-12.91597;,
 -2.94199;83.91188;-12.23179;,
 0.20905;83.91188;-17.99694;,
 -4.85014;36.96576;-12.91597;,
 -2.94199;38.90372;-12.23179;,
 0.20905;38.90372;-17.99694;,
 -4.85014;8.09086;-12.91597;,
 -2.94199;36.96576;-12.23179;,
 0.20905;36.96576;-17.99694;,
 -4.85014;0.57570;-12.91597;,
 -2.94199;8.09086;-12.23179;,
 0.20905;8.09086;-17.99694;,
 -2.94199;0.57570;-12.23179;,
 4.93062;89.65916;-16.21608;,
 4.93062;83.91188;-16.21608;,
 3.68311;89.65916;-14.82086;,
 4.93062;38.90372;-16.21608;,
 3.68311;83.91188;-14.82086;,
 4.93062;36.96576;-16.21608;,
 3.68311;38.90372;-14.82086;,
 4.93062;8.09086;-16.21608;,
 3.68311;36.96576;-14.82086;,
 4.93062;0.57570;-16.21608;,
 3.68311;8.09086;-14.82086;,
 3.68311;0.57570;-14.82086;,
 13.30135;89.65916;-8.55344;,
 16.00275;89.65916;-6.08054;,
 16.00275;83.91188;-6.08054;,
 13.30135;83.91188;-8.55344;,
 12.02916;89.65916;-7.19067;,
 16.00275;38.90372;-6.08054;,
 13.30135;38.90372;-8.55344;,
 12.02916;83.91188;-7.19067;,
 16.00275;36.96576;-6.08054;,
 13.30135;36.96576;-8.55344;,
 12.02916;38.90372;-7.19067;,
 16.00275;8.09086;-6.08054;,
 13.30135;8.09086;-8.55344;,
 12.02916;36.96576;-7.19067;,
 16.00275;0.57570;-6.08054;,
 13.30135;0.57570;-8.55344;,
 12.02916;8.09086;-7.19067;,
 12.02916;0.57570;-7.19067;;
 
 86;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;5,8,9,6;,
 4;10,11,12,13;,
 4;14,15,16,17;,
 4;18,3,2,19;,
 4;20,21,22,23;,
 4;24,16,15,25;,
 4;26,27,17,28;,
 4;27,29,14,17;,
 4;30,31,32,33;,
 4;33,32,34,35;,
 4;36,37,38,39;,
 4;40,24,25,41;,
 4;42,43,27,26;,
 4;43,44,29,27;,
 4;45,30,33,46;,
 4;46,33,35,47;,
 4;48,49,37,36;,
 4;50,40,41,51;,
 4;50,51,20,23;,
 4;52,0,3,53;,
 4;52,53,43,42;,
 4;53,3,18,54;,
 4;53,54,44,43;,
 4;55,45,46,56;,
 4;55,56,5,4;,
 4;56,46,47,57;,
 4;56,57,8,5;,
 4;58,10,13,59;,
 4;58,59,49,48;,
 4;60,31,30,61;,
 4;60,61,25,15;,
 4;60,15,14,62;,
 4;60,62,32,31;,
 4;61,30,45,63;,
 4;61,63,41,25;,
 4;62,14,29,64;,
 4;62,64,65,32;,
 4;63,45,55,66;,
 4;63,66,51,41;,
 4;64,29,44,67;,
 4;64,67,68,65;,
 4;66,55,4,69;,
 4;66,69,20,51;,
 4;67,44,54,70;,
 4;67,70,71,68;,
 4;69,4,7,72;,
 4;69,72,21,20;,
 4;70,54,18,73;,
 4;70,73,74,71;,
 4;73,18,19,75;,
 4;73,75,6,74;,
 4;76,77,35,34;,
 4;76,34,32,78;,
 4;77,79,47,35;,
 4;78,32,65,80;,
 4;79,81,57,47;,
 4;80,65,68,82;,
 4;81,83,8,57;,
 4;82,68,71,84;,
 4;83,85,9,8;,
 4;84,71,74,86;,
 4;86,74,6,87;,
 4;88,89,90,91;,
 4;88,91,77,76;,
 4;88,76,78,92;,
 4;88,92,39,89;,
 4;91,90,93,94;,
 4;91,94,79,77;,
 4;92,78,80,95;,
 4;92,95,36,39;,
 4;94,93,96,97;,
 4;94,97,81,79;,
 4;95,80,82,98;,
 4;95,98,48,36;,
 4;97,96,99,100;,
 4;97,100,83,81;,
 4;98,82,84,101;,
 4;98,101,58,48;,
 4;100,99,102,103;,
 4;100,103,85,83;,
 4;101,84,86,104;,
 4;101,104,10,58;,
 4;104,86,87,105;,
 4;104,105,11,10;;
 
 MeshMaterialList {
  4;
  86;
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  2,
  3,
  3,
  2,
  3,
  2,
  2,
  3,
  2,
  3,
  3,
  2,
  3,
  3,
  3,
  3,
  3,
  1,
  3,
  3,
  2,
  2,
  1,
  3,
  3,
  1,
  2,
  2,
  3,
  3,
  1,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  2,
  3,
  3,
  2,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  1,
  3,
  3,
  2,
  2,
  1,
  3,
  3,
  1,
  2,
  2,
  3,
  3,
  1,
  3,
  3,
  3;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.545600;0.775200;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.545600;0.545600;0.545600;1.000000;;
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
  49;
  0.000000;1.000000;0.000000;,
  0.308603;0.000000;-0.951191;,
  -0.751371;0.000000;-0.659880;,
  -0.440422;0.000000;0.897791;,
  0.308603;0.000000;-0.951191;,
  0.726205;0.000000;0.687478;,
  -0.440422;0.000000;0.897791;,
  0.877485;0.000000;0.479605;,
  -0.751371;0.000000;-0.659880;,
  0.726205;0.000000;0.687478;,
  0.877487;0.000000;0.479601;,
  -0.877070;0.000000;-0.480363;,
  -0.877070;0.000000;-0.480363;,
  0.877485;0.000000;0.479605;,
  0.726205;0.000000;0.687478;,
  -0.877070;0.000000;-0.480363;,
  -0.440422;0.000000;0.897791;,
  -0.440422;0.000000;0.897791;,
  0.877485;0.000000;0.479605;,
  -0.877069;0.000000;-0.480364;,
  0.877486;0.000000;0.479602;,
  -0.877069;0.000000;-0.480364;,
  0.877486;0.000000;0.479602;,
  0.675221;0.000000;-0.737615;,
  -0.674746;0.000000;0.738050;,
  0.675221;0.000000;-0.737615;,
  0.675221;0.000000;-0.737616;,
  -0.674745;0.000000;0.738051;,
  -0.674745;0.000000;0.738051;,
  0.877487;0.000000;0.479601;,
  0.877487;0.000000;0.479601;,
  -0.877070;0.000000;-0.480363;,
  0.877487;0.000000;0.479601;,
  0.877487;0.000000;0.479601;,
  -0.877070;0.000000;-0.480363;,
  -0.877070;0.000000;-0.480363;,
  0.877486;0.000000;0.479602;,
  0.877485;0.000000;0.479605;,
  0.877485;0.000000;0.479604;,
  0.675222;0.000000;-0.737615;,
  -0.674746;0.000000;0.738050;,
  -0.674746;0.000000;0.738050;,
  -0.674746;0.000000;0.738050;,
  0.675221;0.000000;-0.737615;,
  -0.674745;0.000000;0.738051;,
  -0.674744;0.000000;0.738052;,
  -0.674744;0.000000;0.738052;,
  -0.674744;0.000000;0.738052;,
  -0.674744;0.000000;0.738052;;
  86;
  4;6,3,3,6;,
  4;4,4,4,4;,
  4;8,8,2,2;,
  4;9,5,5,9;,
  4;0,0,0,0;,
  4;10,29,30,10;,
  4;11,11,31,12;,
  4;12,31,11,11;,
  4;6,6,3,3;,
  4;32,10,10,33;,
  4;4,1,1,4;,
  4;8,2,2,8;,
  4;14,14,5,5;,
  4;15,12,11,11;,
  4;16,16,6,6;,
  4;32,10,10,32;,
  4;4,4,4,4;,
  4;8,8,8,8;,
  4;14,14,14,14;,
  4;15,15,11,11;,
  4;15,11,11,12;,
  4;17,6,6,17;,
  4;17,17,16,16;,
  4;33,29,10,10;,
  4;33,10,10,32;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;9,9,14,14;,
  4;19,34,35,19;,
  4;19,19,11,11;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;19,35,35,19;,
  4;19,19,11,11;,
  4;36,10,10,20;,
  4;36,20,13,37;,
  4;19,35,35,21;,
  4;19,21,11,11;,
  4;20,10,10,20;,
  4;20,20,13,13;,
  4;21,35,35,21;,
  4;21,21,11,11;,
  4;20,10,10,20;,
  4;20,20,18,13;,
  4;21,35,35,21;,
  4;21,21,11,11;,
  4;20,10,10,20;,
  4;20,20,7,18;,
  4;20,10,10,22;,
  4;20,22,38,7;,
  4;23,23,39,39;,
  4;0,0,0,0;,
  4;23,23,39,39;,
  4;24,40,40,24;,
  4;23,25,39,39;,
  4;24,40,40,24;,
  4;25,25,39,39;,
  4;24,40,40,24;,
  4;25,23,39,39;,
  4;24,40,41,24;,
  4;24,41,42,24;,
  4;26,43,43,26;,
  4;26,26,23,23;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;26,43,43,26;,
  4;26,26,23,23;,
  4;44,24,24,27;,
  4;44,27,45,46;,
  4;26,43,43,26;,
  4;26,26,25,23;,
  4;27,24,24,28;,
  4;27,28,45,45;,
  4;26,43,43,26;,
  4;26,26,25,25;,
  4;28,24,24,28;,
  4;28,28,47,45;,
  4;26,43,43,26;,
  4;26,26,23,25;,
  4;28,24,24,27;,
  4;28,27,45,47;,
  4;27,24,24,27;,
  4;27,27,48,45;;
 }
 MeshTextureCoords {
  106;
  1.000000;0.863940;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.863940;,
  0.250000;0.863940;,
  0.500000;0.863940;,
  0.500000;1.000000;,
  0.250000;1.000000;,
  0.750000;0.863940;,
  0.750000;1.000000;,
  1.000000;0.863940;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.863940;,
  0.089390;0.000000;,
  0.044700;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.089390;0.863940;,
  0.089390;1.000000;,
  0.044700;0.863940;,
  0.044700;1.000000;,
  0.000000;1.000000;,
  0.000000;0.863940;,
  0.000000;0.150610;,
  0.044700;0.150610;,
  1.000000;0.150610;,
  0.000000;0.150610;,
  1.000000;0.000000;,
  0.089390;0.150610;,
  0.250000;0.150610;,
  0.250000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.150610;,
  0.750000;0.000000;,
  0.750000;0.150610;,
  1.000000;0.150610;,
  0.000000;0.150610;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.445480;,
  0.044700;0.445480;,
  1.000000;0.445480;,
  0.000000;0.445480;,
  0.089390;0.445480;,
  0.250000;0.445480;,
  0.500000;0.445480;,
  0.750000;0.445480;,
  1.000000;0.445480;,
  0.000000;0.445480;,
  0.000000;0.467240;,
  0.044700;0.467240;,
  1.000000;0.467240;,
  0.000000;0.467240;,
  0.089390;0.467240;,
  0.250000;0.467240;,
  0.500000;0.467240;,
  0.750000;0.467240;,
  1.000000;0.467240;,
  0.000000;0.467240;,
  0.196090;0.000000;,
  0.196090;0.150610;,
  0.392180;0.000000;,
  0.196090;0.445480;,
  0.392180;0.150610;,
  0.500000;0.150610;,
  0.196090;0.467240;,
  0.392180;0.445480;,
  0.500000;0.445480;,
  0.196090;0.863940;,
  0.392180;0.467240;,
  0.500000;0.467240;,
  0.196090;1.000000;,
  0.392180;0.863940;,
  0.500000;0.863940;,
  0.392180;1.000000;,
  0.809840;0.000000;,
  0.809840;0.150610;,
  0.619680;0.000000;,
  0.809840;0.445480;,
  0.619680;0.150610;,
  0.809840;0.467240;,
  0.619680;0.445480;,
  0.809840;0.863940;,
  0.619680;0.467240;,
  0.809840;1.000000;,
  0.619680;0.863940;,
  0.619680;1.000000;,
  0.953600;0.000000;,
  1.000000;0.000000;,
  1.000000;0.150610;,
  0.953600;0.150610;,
  0.907210;0.000000;,
  1.000000;0.445480;,
  0.953600;0.445480;,
  0.907210;0.150610;,
  1.000000;0.467240;,
  0.953600;0.467240;,
  0.907210;0.445480;,
  1.000000;0.863940;,
  0.953600;0.863940;,
  0.907210;0.467240;,
  1.000000;1.000000;,
  0.953600;1.000000;,
  0.907210;0.863940;,
  0.907210;1.000000;;
 }
}
