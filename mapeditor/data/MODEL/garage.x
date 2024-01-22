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
 38;
 -94.81870;107.09203;10.45434;,
 -94.81870;117.32448;15.87815;,
 94.81870;117.32448;15.87815;,
 94.81870;107.09203;10.45434;,
 -94.81870;97.25413;15.87815;,
 94.81870;97.25413;15.87815;,
 -94.81870;85.16809;10.45434;,
 94.81870;85.16809;10.45434;,
 -94.81870;74.06165;15.87815;,
 94.81870;74.06165;15.87815;,
 -94.81870;60.97900;10.45434;,
 94.81870;60.97900;10.45434;,
 -94.81870;47.90382;15.87815;,
 94.81870;47.90382;15.87815;,
 -94.81870;35.11670;10.45434;,
 94.81870;35.11670;10.45434;,
 -94.81870;22.63765;15.87815;,
 94.81870;22.63765;15.87815;,
 -94.81870;11.09870;10.45434;,
 94.81870;11.09870;10.45434;,
 94.81870;-0.16037;15.87815;,
 -94.81870;-0.16037;15.87815;,
 -94.81870;138.92422;-20.02578;,
 94.81870;138.92422;-20.02578;,
 94.81870;117.52311;-20.02578;,
 -94.81870;117.52311;-20.02578;,
 94.81870;138.92422;-20.02578;,
 94.81870;138.92422;10.24967;,
 94.81870;117.52311;10.24967;,
 94.81870;117.52311;-20.02578;,
 -94.81870;138.92422;10.24967;,
 -94.81870;138.92422;-20.02578;,
 -94.81870;117.52311;-20.02578;,
 -94.81870;117.52311;10.24967;,
 94.81870;138.92422;-20.02578;,
 -94.81870;138.92422;-20.02578;,
 -94.81870;117.52311;-20.02578;,
 94.81870;117.52311;-20.02578;;
 
 15;
 4;0,1,2,3;,
 4;4,0,3,5;,
 4;6,4,5,7;,
 4;8,6,7,9;,
 4;10,8,9,11;,
 4;12,10,11,13;,
 4;14,12,13,15;,
 4;16,14,15,17;,
 4;18,16,17,19;,
 4;18,19,20,21;,
 4;22,23,24,25;,
 4;26,27,28,29;,
 4;30,31,32,33;,
 4;30,27,34,35;,
 4;36,37,28,33;;
 
 MeshMaterialList {
  2;
  15;
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
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.661600;0.661600;0.661600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.426400;0.426400;0.426400;1.000000;;
   5.000000;
   0.810000;0.810000;0.810000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  16;
  0.000000;0.468335;-0.883551;,
  0.000000;-0.433996;-0.900915;,
  0.000000;-0.008224;-0.999966;,
  0.000000;-0.041002;-0.999159;,
  0.000000;-0.016227;-0.999868;,
  0.000000;-0.030631;-0.999531;,
  0.000000;-0.000101;-1.000000;,
  0.000000;0.003973;-0.999992;,
  0.000000;-0.004421;-0.999990;,
  0.000000;0.014697;-0.999892;,
  0.000000;-0.004763;-0.999989;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  15;
  4;2,0,0,2;,
  4;3,2,2,3;,
  4;4,3,3,4;,
  4;5,4,4,5;,
  4;6,5,5,6;,
  4;7,6,6,7;,
  4;8,7,7,8;,
  4;9,8,8,9;,
  4;10,9,9,10;,
  4;10,10,1,1;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;;
 }
 MeshTextureCoords {
  38;
  0.000000;0.087100;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.087100;,
  0.000000;0.170830;,
  1.000000;0.170830;,
  0.000000;0.273710;,
  1.000000;0.273710;,
  0.000000;0.368240;,
  1.000000;0.368240;,
  0.000000;0.479600;,
  1.000000;0.479600;,
  0.000000;0.590890;,
  1.000000;0.590890;,
  0.000000;0.699730;,
  1.000000;0.699730;,
  0.000000;0.805950;,
  1.000000;0.805950;,
  0.000000;0.904170;,
  1.000000;0.904170;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
