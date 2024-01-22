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
 -32.12615;47.14839;-23.05532;,
 32.12615;47.14972;-23.05532;,
 32.12615;-0.05542;-23.05532;,
 -32.12615;-0.05542;-23.05532;,
 32.12615;47.14972;-23.05532;,
 32.12615;47.14972;22.94402;,
 32.12615;-0.05542;22.94515;,
 32.12615;-0.05542;-23.05532;,
 -32.12615;47.14972;22.94402;,
 -32.12615;47.14839;-23.05532;,
 -32.12615;-0.05542;-23.05532;,
 -32.12615;-0.05542;22.94515;,
 26.55952;47.14839;17.19144;,
 -26.34643;47.14839;17.19144;,
 26.55952;47.14839;-17.25665;,
 -26.34643;47.14839;-17.25665;,
 11.11523;28.04940;13.42617;,
 -20.91206;28.04940;6.29079;,
 15.78936;28.04940;-4.09993;,
 -15.60081;28.04940;-11.78524;,
 -32.12615;113.76088;22.94402;,
 32.12615;113.76088;22.94402;,
 -32.12615;126.07599;8.60102;,
 32.12615;126.07599;8.60102;,
 32.12615;113.79132;8.60102;,
 -32.12615;113.79132;8.60102;,
 32.12615;126.07599;8.60102;,
 32.12615;126.07599;23.10511;,
 32.12615;113.79132;23.10511;,
 32.12615;113.79132;8.60102;,
 -32.12615;126.07599;23.10511;,
 -32.12615;126.07599;8.60102;,
 -32.12615;113.79132;8.60102;,
 -32.12615;113.79132;23.10511;,
 32.12615;126.07599;8.60102;,
 -32.12615;126.07599;8.60102;,
 -32.12615;113.79132;8.60102;,
 32.12615;113.79132;8.60102;;
 
 18;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;5,12,13,8;,
 4;1,14,12,5;,
 4;9,15,14,1;,
 4;8,13,15,9;,
 4;12,16,17,13;,
 4;14,18,16,12;,
 4;15,19,18,14;,
 4;13,17,19,15;,
 4;17,16,18,19;,
 4;8,20,21,5;,
 4;22,23,24,25;,
 4;26,27,28,29;,
 4;30,31,32,33;,
 4;30,27,34,35;,
 4;36,37,28,33;;
 
 MeshMaterialList {
  2;
  18;
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
  1,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.649600;0.649600;0.649600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.596000;0.800000;0.787200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  19;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000065;1.000000;-0.000123;,
  -0.301997;0.952585;-0.037143;,
  -0.302002;0.952589;-0.037011;,
  0.000060;1.000000;0.000056;,
  0.094456;0.367659;-0.925151;,
  -0.459694;0.886283;-0.056424;,
  -0.095100;0.462465;0.881523;,
  -0.000120;1.000000;-0.000116;,
  -0.000125;1.000000;0.000063;,
  0.904866;0.407848;0.121971;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  18;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;10,4,3,3;,
  4;11,5,4,10;,
  4;6,6,5,11;,
  4;3,3,6,6;,
  4;7,7,7,7;,
  4;5,8,8,4;,
  4;9,9,9,9;,
  4;12,12,12,12;,
  4;13,8,8,13;,
  4;0,0,0,0;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;;
 }
 MeshTextureCoords {
  38;
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
