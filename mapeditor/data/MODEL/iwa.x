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
 23;
 1.34149;27.30765;2.99487;,
 11.57856;21.80841;0.10002;,
 3.41174;21.02824;-9.72348;,
 1.34149;27.30765;2.99487;,
 1.94973;20.21173;12.97168;,
 1.34149;27.30765;2.99487;,
 -8.83883;21.71184;-0.00000;,
 1.34149;27.30765;2.99487;,
 3.41174;21.02824;-9.72348;,
 16.51070;10.10370;-3.70749;,
 -0.22536;13.10888;-16.34889;,
 -2.03814;10.40681;17.02524;,
 -15.15319;11.98496;-3.84937;,
 -0.22536;13.10888;-16.34889;,
 8.26338;-1.34161;-10.12619;,
 -6.13915;-0.15350;-16.04680;,
 0.68928;0.44443;11.37218;,
 -12.43373;0.55598;-4.59872;,
 -6.13915;-0.15350;-16.04680;,
 0.00000;0.37300;0.00000;,
 0.00000;0.37300;0.00000;,
 0.00000;0.37300;0.00000;,
 0.00000;0.37300;0.00000;;
 
 16;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 4;2,1,9,10;,
 4;1,4,11,9;,
 4;4,6,12,11;,
 4;6,8,13,12;,
 4;10,9,14,15;,
 4;9,11,16,14;,
 4;11,12,17,16;,
 4;12,13,18,17;,
 3;15,14,19;,
 3;14,16,20;,
 3;16,17,21;,
 3;17,18,22;;
 
 MeshMaterialList {
  1;
  16;
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\thumb-gray-rock-texture-stone-texture-gray-stone-background-rock-background-natural-stone-texture.jpg";
   }
  }
 }
 MeshNormals {
  21;
  0.223249;0.964456;-0.141364;,
  0.054682;0.794115;-0.605303;,
  0.594038;0.774878;-0.216063;,
  0.689171;0.410778;0.596913;,
  -0.631825;0.551402;0.544751;,
  0.585559;0.163430;-0.793985;,
  0.782971;-0.198941;0.589388;,
  -0.804646;0.034133;0.592774;,
  0.489307;-0.086272;-0.867834;,
  0.745764;-0.438440;0.501604;,
  -0.768755;-0.345325;0.538299;,
  -0.086304;-0.995606;0.036338;,
  -0.524312;0.678491;0.514535;,
  -0.407575;0.741713;-0.532676;,
  0.768150;0.053778;0.638007;,
  -0.672072;0.363924;-0.644886;,
  -0.780779;0.046307;-0.623088;,
  -0.072103;-0.995576;0.060250;,
  -0.147984;-0.987895;0.046514;,
  -0.100474;-0.994863;0.012338;,
  -0.024334;-0.999365;0.026028;;
  16;
  3;0,2,1;,
  3;0,3,2;,
  3;12,4,4;,
  3;0,1,13;,
  4;1,2,5,5;,
  4;14,3,6,6;,
  4;4,4,7,7;,
  4;13,1,15,15;,
  4;5,5,8,8;,
  4;6,6,9,9;,
  4;7,7,10,10;,
  4;15,15,16,16;,
  3;17,18,11;,
  3;18,19,11;,
  3;19,20,11;,
  3;20,17,11;;
 }
 MeshTextureCoords {
  23;
  0.125000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.375000;0.000000;,
  0.500000;0.250000;,
  0.625000;0.000000;,
  0.750000;0.250000;,
  0.875000;0.000000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.125000;1.000000;,
  0.375000;1.000000;,
  0.625000;1.000000;,
  0.875000;1.000000;;
 }
}
