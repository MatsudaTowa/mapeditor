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
 80;
 -33.93793;42.57880;-53.96708;,
 -30.06849;42.57880;-53.96708;,
 -30.06787;38.72188;-53.96708;,
 -33.93793;38.72221;-53.96708;,
 30.06849;42.57880;-53.96708;,
 30.06787;38.72188;-53.96708;,
 33.93793;42.57880;-53.96708;,
 33.93793;38.72221;-53.96708;,
 -30.06849;0.57035;-53.96708;,
 -33.93793;0.57035;-53.96708;,
 33.93793;0.57035;-53.96708;,
 30.06849;0.57035;-53.96708;,
 33.93793;42.57880;-53.96708;,
 33.93793;42.57880;-49.26646;,
 33.93793;38.72221;-49.26768;,
 33.93793;38.72221;-53.96708;,
 33.93793;42.57880;49.26646;,
 33.93793;38.72221;49.26768;,
 33.93793;42.57880;53.96708;,
 33.93793;38.72221;53.96708;,
 33.93793;0.57035;-49.26646;,
 33.93793;0.57035;-53.96708;,
 33.93793;0.57035;53.96708;,
 33.93793;0.57035;49.26646;,
 33.93793;42.57880;53.96708;,
 30.06849;42.57880;53.96708;,
 30.06787;38.72188;53.96708;,
 33.93793;38.72221;53.96708;,
 -30.06849;42.57880;53.96708;,
 -30.06787;38.72221;53.96708;,
 -33.93793;42.57880;53.96708;,
 -33.93793;38.72188;53.96708;,
 30.06849;0.57035;53.96708;,
 33.93793;0.57035;53.96708;,
 -33.93793;0.57035;53.96708;,
 -30.06849;0.57035;53.96708;,
 -33.93793;42.57880;53.96708;,
 -33.93793;42.57880;49.26646;,
 -33.93793;38.72221;49.26768;,
 -33.93793;38.72188;53.96708;,
 -33.93793;42.57880;-49.26646;,
 -33.93793;38.72221;-49.26768;,
 -33.93793;42.57880;-53.96708;,
 -33.93793;38.72221;-53.96708;,
 -33.93793;0.57035;49.26646;,
 -33.93793;0.57035;53.96708;,
 -33.93793;0.57035;-53.96708;,
 -33.93793;0.57035;-49.26646;,
 -30.06849;42.57880;53.96708;,
 -30.06849;42.57880;49.26646;,
 -33.93793;42.57880;49.26646;,
 30.06849;42.57880;53.96708;,
 30.06849;42.57880;49.26646;,
 33.93793;42.57880;49.26646;,
 -30.06849;42.57880;-49.26646;,
 -33.93793;42.57880;-49.26646;,
 30.06849;42.57880;-49.26646;,
 33.93793;42.57880;-49.26646;,
 -30.06849;42.57880;-53.96708;,
 -33.93793;42.57880;-53.96708;,
 30.06849;42.57880;-53.96708;,
 33.93793;42.57880;-53.96708;,
 -33.93793;0.57035;49.26646;,
 -30.06849;0.57035;49.26646;,
 -30.06849;0.57035;53.96708;,
 30.06849;0.57035;49.26646;,
 33.93793;0.57035;49.26646;,
 30.06849;0.57035;53.96708;,
 -33.93793;0.57035;-53.96708;,
 -30.06849;0.57035;-53.96708;,
 -30.06849;0.57035;-49.26646;,
 -33.93793;0.57035;-49.26646;,
 30.06849;0.57035;-53.96708;,
 33.93793;0.57035;-53.96708;,
 33.93793;0.57035;-49.26646;,
 30.06849;0.57035;-49.26646;,
 -30.06787;38.72188;-49.26768;,
 -30.06787;38.72188;49.26768;,
 30.06787;38.72188;49.26768;,
 30.06787;38.72188;-49.26768;;
 
 46;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;3,2,8,9;,
 4;5,7,10,11;,
 4;12,13,14,15;,
 4;13,16,17,14;,
 4;16,18,19,17;,
 4;15,14,20,21;,
 4;17,19,22,23;,
 4;24,25,26,27;,
 4;25,28,29,26;,
 4;28,30,31,29;,
 4;27,26,32,33;,
 4;29,31,34,35;,
 4;36,37,38,39;,
 4;37,40,41,38;,
 4;40,42,43,41;,
 4;39,38,44,45;,
 4;41,43,46,47;,
 4;36,48,49,50;,
 4;48,51,52,49;,
 4;51,18,53,52;,
 4;50,49,54,55;,
 4;49,52,56,54;,
 4;52,53,57,56;,
 4;55,54,58,59;,
 4;54,56,60,58;,
 4;56,57,61,60;,
 4;62,63,64,45;,
 4;65,66,22,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;41,47,70,76;,
 4;2,76,70,69;,
 4;64,63,77,29;,
 4;38,77,63,44;,
 4;76,77,38,41;,
 4;77,78,26,29;,
 4;76,2,5,79;,
 4;79,14,17,78;,
 4;26,78,65,67;,
 4;78,17,23,65;,
 4;14,79,75,20;,
 4;79,5,72,75;,
 4;78,77,76,79;;
 
 MeshMaterialList {
  1;
  46;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.656000;0.517600;0.304000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  20;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000032;1.000000;,
  1.000000;-0.000016;0.000000;,
  0.000027;-1.000000;0.000012;,
  0.000028;-1.000000;-0.000000;,
  1.000000;-0.000016;-0.000000;,
  0.000000;0.000032;-1.000000;,
  -0.000028;-1.000000;0.000000;,
  -0.000029;-1.000000;0.000012;,
  -0.000084;-1.000000;0.000000;,
  -0.000003;-1.000000;0.000035;,
  0.000084;-1.000000;-0.000000;,
  -1.000000;-0.000016;0.000000;,
  -0.000000;0.000032;-1.000000;,
  -0.000000;0.000032;1.000000;;
  46;
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;10,10,10,10;,
  4;7,7,7,7;,
  4;11,11,11,11;,
  4;12,13,14,14;,
  4;13,8,15,15;,
  4;12,5,5,9;,
  4;9,16,16,8;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;17,17,17,17;,
  4;8,13,12,9;;
 }
 MeshTextureCoords {
  80;
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.500000;,
  0.000000;0.500000;,
  0.666670;0.000000;,
  0.666670;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.666670;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.500000;,
  0.000000;0.500000;,
  0.666670;0.000000;,
  0.666670;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.666670;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.500000;,
  0.000000;0.500000;,
  0.666670;0.000000;,
  0.666670;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.666670;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.500000;,
  0.000000;0.500000;,
  0.666670;0.000000;,
  0.666670;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.666670;1.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.000000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  1.000000;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.333330;1.000000;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.666670;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.000000;0.333330;,
  0.666670;0.000000;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.666670;0.333330;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}