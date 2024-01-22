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
 372;
 -26.98027;90.82863;-25.51935;,
 -21.83540;90.82863;-25.51935;,
 -21.83540;86.01298;-25.51935;,
 -26.98027;86.01298;-25.51935;,
 -0.27067;90.82863;-25.51935;,
 0.27067;90.82863;-25.51935;,
 0.27067;86.01298;-25.51935;,
 -0.27067;86.01298;-25.51935;,
 21.83540;90.82863;-25.51935;,
 26.98027;90.82863;-25.51935;,
 26.98027;86.01298;-25.51935;,
 21.83540;86.01298;-25.51935;,
 -21.83540;39.37566;-25.51935;,
 -26.98027;39.37566;-25.51935;,
 0.27067;39.37566;-25.51935;,
 -0.27067;39.37566;-25.51935;,
 26.98027;39.37566;-25.51935;,
 21.83540;39.37566;-25.51935;,
 -26.98027;35.37568;-25.51935;,
 -21.83540;35.37568;-25.51935;,
 -21.83540;5.37600;-25.51935;,
 -26.98027;5.37600;-25.51935;,
 -0.27067;35.37568;-25.51935;,
 0.27067;35.37568;-25.51935;,
 0.27067;5.37600;-25.51935;,
 -0.27067;5.37600;-25.51935;,
 21.83540;35.37568;-25.51935;,
 26.98027;35.37568;-25.51935;,
 26.98027;5.37600;-25.51935;,
 21.83540;5.37600;-25.51935;,
 -21.83540;0.56030;-25.51935;,
 -26.98027;0.56030;-25.51935;,
 0.27067;0.56030;-25.51935;,
 -0.27067;0.56030;-25.51935;,
 26.98027;0.56030;-25.51935;,
 21.83540;0.56030;-25.51935;,
 26.98027;90.82863;28.44119;,
 21.83540;90.82863;28.44119;,
 21.83540;86.01298;28.44119;,
 26.98027;86.01298;28.44119;,
 0.27067;90.82863;28.44119;,
 -0.27067;90.82863;28.44119;,
 -0.27067;86.01298;28.44119;,
 0.27067;86.01298;28.44119;,
 -21.83540;90.82863;28.44119;,
 -26.98027;90.82863;28.44119;,
 -26.98027;86.01298;28.44119;,
 -21.83540;86.01298;28.44119;,
 21.83540;39.37566;28.44119;,
 26.98027;39.37566;28.44119;,
 -0.27067;39.37566;28.44119;,
 0.27067;39.37566;28.44119;,
 -26.98027;39.37566;28.44119;,
 -21.83540;39.37566;28.44119;,
 26.98027;35.37568;28.44119;,
 21.83540;35.37568;28.44119;,
 21.83540;5.37600;28.44119;,
 26.98027;5.37600;28.44119;,
 0.27067;35.37568;28.44119;,
 -0.27067;35.37568;28.44119;,
 -0.27067;5.37600;28.44119;,
 0.27067;5.37600;28.44119;,
 -21.83540;35.37568;28.44119;,
 -26.98027;35.37568;28.44119;,
 -26.98027;5.37600;28.44119;,
 -21.83540;5.37600;28.44119;,
 21.83540;0.56030;28.44119;,
 26.98027;0.56030;28.44119;,
 -0.27067;0.56030;28.44119;,
 0.27067;0.56030;28.44119;,
 -26.98027;0.56030;28.44119;,
 -21.83540;0.56030;28.44119;,
 26.98027;90.82863;-20.12721;,
 26.98027;86.01298;-20.12721;,
 26.98027;86.01298;-25.51935;,
 26.98027;90.82863;-25.51935;,
 26.98027;90.82863;-20.12721;,
 26.98027;90.82863;-25.51935;,
 21.83540;90.82863;-25.51935;,
 21.83540;90.82863;-20.12721;,
 26.98027;39.37566;-20.12721;,
 26.98027;39.37566;-25.51935;,
 0.27067;90.82863;-20.12721;,
 0.27067;90.82863;-25.51935;,
 -0.27067;90.82863;-25.51935;,
 -0.27067;90.82863;-20.12721;,
 26.98027;35.37568;-20.12721;,
 26.98027;5.37600;-20.12721;,
 26.98027;5.37600;-25.51935;,
 26.98027;35.37568;-25.51935;,
 26.98027;0.56030;-20.12721;,
 26.98027;0.56030;-25.51935;,
 -21.83540;90.82863;-20.12721;,
 -21.83540;90.82863;-25.51935;,
 -26.98027;90.82863;-25.51935;,
 -26.98027;90.82863;-20.12721;,
 26.98027;0.56030;-20.12721;,
 21.83540;0.56030;-20.12721;,
 21.83540;0.56030;-25.51935;,
 26.98027;0.56030;-25.51935;,
 -26.98027;90.82863;-20.12721;,
 -26.98027;90.82863;-25.51935;,
 -26.98027;86.01298;-25.51935;,
 -26.98027;86.01298;-20.12721;,
 -26.98027;39.37566;-25.51935;,
 -26.98027;39.37566;-20.12721;,
 0.27067;0.56030;-20.12721;,
 -0.27067;0.56030;-20.12721;,
 -0.27067;0.56030;-25.51935;,
 0.27067;0.56030;-25.51935;,
 -26.98027;35.37568;-20.12721;,
 -26.98027;35.37568;-25.51935;,
 -26.98027;5.37600;-25.51935;,
 -26.98027;5.37600;-20.12721;,
 -21.83540;0.56030;-20.12721;,
 -26.98027;0.56030;-20.12721;,
 -26.98027;0.56030;-25.51935;,
 -21.83540;0.56030;-25.51935;,
 -26.98027;0.56030;-25.51935;,
 -26.98027;0.56030;-20.12721;,
 26.98027;90.82863;-18.95201;,
 26.98027;90.82863;28.44119;,
 26.98027;86.01298;28.44119;,
 26.98027;86.01298;-18.95201;,
 26.98027;90.82863;-18.95201;,
 21.83540;90.82863;-18.95201;,
 21.83540;90.82863;28.44119;,
 26.98027;39.37566;28.44119;,
 26.98027;39.37566;-18.95201;,
 0.27067;90.82863;-18.95201;,
 -0.27067;90.82863;-18.95201;,
 -0.27067;90.82863;28.44119;,
 0.27067;90.82863;28.44119;,
 26.98027;35.37568;-18.95201;,
 26.98027;35.37568;28.44119;,
 26.98027;5.37600;28.44119;,
 26.98027;5.37600;-18.95201;,
 26.98027;0.56030;28.44119;,
 26.98027;0.56030;-18.95201;,
 -21.83540;90.82863;-18.95201;,
 -26.98027;90.82863;-18.95201;,
 -26.98027;90.82863;28.44119;,
 -21.83540;90.82863;28.44119;,
 26.98027;0.56030;-18.95201;,
 21.83540;0.56030;28.44119;,
 21.83540;0.56030;-18.95201;,
 -26.98027;90.82863;-18.95201;,
 -26.98027;86.01298;-18.95201;,
 -26.98027;86.01298;28.44119;,
 -26.98027;39.37566;-18.95201;,
 -26.98027;39.37566;28.44119;,
 0.27067;0.56030;-18.95201;,
 0.27067;0.56030;28.44119;,
 -0.27067;0.56030;28.44119;,
 -0.27067;0.56030;-18.95201;,
 -26.98027;35.37568;-18.95201;,
 -26.98027;5.37600;-18.95201;,
 -26.98027;5.37600;28.44119;,
 -26.98027;35.37568;28.44119;,
 -21.83540;0.56030;-18.95201;,
 -21.83540;0.56030;28.44119;,
 -26.98027;0.56030;28.44119;,
 -26.98027;0.56030;-18.95201;,
 -26.98027;0.56030;-18.95201;,
 -1.78294;90.82863;-25.51935;,
 -1.78294;86.01298;-25.51935;,
 -1.78294;90.82863;-25.51935;,
 -1.78294;90.82863;-20.12721;,
 -1.78294;39.37566;-25.51935;,
 -1.78294;90.82863;-18.95201;,
 -1.78294;90.82863;28.44119;,
 -1.78294;35.37568;-25.51935;,
 -1.78294;5.37600;-25.51935;,
 -1.78294;90.82863;28.44119;,
 -1.78294;86.01298;28.44119;,
 -1.78294;0.56030;-25.51935;,
 -1.78294;39.37566;28.44119;,
 -1.78294;0.56030;-25.51935;,
 -1.78294;0.56030;-20.12721;,
 -1.78294;0.56030;-18.95201;,
 -1.78294;35.37568;28.44119;,
 -1.78294;5.37600;28.44119;,
 -1.78294;0.56030;28.44119;,
 -1.78294;0.56030;28.44119;,
 1.55932;90.82863;-25.51935;,
 1.55932;86.01298;-25.51935;,
 1.55932;90.82863;-25.51935;,
 1.55932;90.82863;-20.12721;,
 1.55932;39.37566;-25.51935;,
 1.55932;90.82863;-18.95201;,
 1.55932;90.82863;28.44119;,
 1.55932;35.37568;-25.51935;,
 1.55932;5.37600;-25.51935;,
 1.55932;90.82863;28.44119;,
 1.55932;86.01298;28.44119;,
 1.55932;0.56030;-25.51935;,
 1.55932;39.37566;28.44119;,
 1.55932;0.56030;-25.51935;,
 1.55932;0.56030;-20.12721;,
 1.55932;0.56030;-18.95201;,
 1.55932;35.37568;28.44119;,
 1.55932;5.37600;28.44119;,
 1.55932;0.56030;28.44119;,
 1.55932;0.56030;28.44119;,
 -0.27067;37.59824;-25.51935;,
 0.27067;37.59824;-25.51935;,
 -1.78294;37.59824;-25.51935;,
 1.55932;37.59824;-25.51935;,
 -21.83540;37.59824;-25.51935;,
 21.83540;37.59824;-25.51935;,
 -26.98027;37.59824;-25.51935;,
 26.98027;37.59824;-25.51935;,
 -26.98027;37.59824;-25.51935;,
 -26.98027;37.59824;-20.12721;,
 26.98027;37.59824;-25.51935;,
 26.98027;37.59824;-20.12721;,
 -26.98027;37.59824;-18.95201;,
 26.98027;37.59824;-18.95201;,
 -26.98027;37.59824;28.44119;,
 26.98027;37.59824;28.44119;,
 -26.98027;37.59824;28.44119;,
 -21.83540;37.59824;28.44119;,
 26.98027;37.59824;28.44119;,
 21.83540;37.59824;28.44119;,
 -1.78294;37.59824;28.44119;,
 1.55932;37.59824;28.44119;,
 -0.27067;37.59824;28.44119;,
 0.27067;37.59824;28.44119;,
 -0.27067;37.03673;-25.51935;,
 0.27067;37.03673;-25.51935;,
 -1.78294;37.03673;-25.51935;,
 1.55932;37.03673;-25.51935;,
 -21.83540;37.03673;-25.51935;,
 21.83540;37.03673;-25.51935;,
 -26.98027;37.03673;-25.51935;,
 26.98027;37.03673;-25.51935;,
 -26.98027;37.03673;-25.51935;,
 -26.98027;37.03673;-20.12721;,
 26.98027;37.03673;-25.51935;,
 26.98027;37.03673;-20.12721;,
 -26.98027;37.03673;-18.95201;,
 26.98027;37.03673;-18.95201;,
 -26.98027;37.03673;28.44119;,
 26.98027;37.03673;28.44119;,
 -26.98027;37.03673;28.44119;,
 -21.83540;37.03673;28.44119;,
 26.98027;37.03673;28.44119;,
 21.83540;37.03673;28.44119;,
 -1.78294;37.03673;28.44119;,
 1.55932;37.03673;28.44119;,
 -0.27067;37.03673;28.44119;,
 0.27067;37.03673;28.44119;,
 -4.08144;24.97308;-30.16191;,
 -2.27212;24.97308;-30.16191;,
 -2.27212;15.09161;-30.16191;,
 -4.08144;15.09161;-30.16191;,
 -2.27212;27.12196;-28.17089;,
 -2.27212;27.12196;-24.94755;,
 -2.27212;24.97308;-24.94755;,
 -2.27212;24.97308;-28.17089;,
 -2.27212;24.97308;-30.16191;,
 -2.27212;15.09161;-28.17089;,
 -2.27212;15.09161;-30.16191;,
 -2.27212;15.09161;-24.94755;,
 -2.27212;12.94271;-24.94755;,
 -2.27212;12.94271;-28.17089;,
 -4.08144;27.12196;-24.94755;,
 -4.08144;27.12196;-28.17089;,
 -4.08144;24.97308;-28.17089;,
 -4.08144;24.97308;-24.94755;,
 -4.08144;24.97308;-30.16191;,
 -4.08144;15.09161;-30.16191;,
 -4.08144;15.09161;-28.17089;,
 -4.08144;15.09161;-24.94755;,
 -4.08144;12.94271;-28.17089;,
 -4.08144;12.94271;-24.94755;,
 -2.27212;27.12196;-28.17089;,
 -4.08144;27.12196;-28.17089;,
 -4.08144;12.94271;-28.17089;,
 -2.27212;12.94271;-28.17089;,
 -4.08144;15.09161;-24.94755;,
 -4.08144;24.97308;-24.94755;,
 4.08144;24.97308;-30.16191;,
 4.08144;15.09161;-30.16191;,
 2.27212;15.09161;-30.16191;,
 2.27212;24.97308;-30.16191;,
 2.27212;27.12196;-28.17089;,
 2.27212;24.97308;-28.17089;,
 2.27212;24.97308;-24.94755;,
 2.27212;27.12196;-24.94755;,
 2.27212;24.97308;-30.16191;,
 2.27212;15.09161;-30.16191;,
 2.27212;15.09161;-28.17089;,
 2.27212;12.94271;-28.17089;,
 2.27212;12.94271;-24.94755;,
 2.27212;15.09161;-24.94755;,
 4.08144;27.12196;-24.94755;,
 4.08144;24.97308;-24.94755;,
 4.08144;24.97308;-28.17089;,
 4.08144;27.12196;-28.17089;,
 4.08144;15.09161;-28.17089;,
 4.08144;15.09161;-30.16191;,
 4.08144;24.97308;-30.16191;,
 4.08144;15.09161;-24.94755;,
 4.08144;12.94271;-24.94755;,
 4.08144;12.94271;-28.17089;,
 4.08144;27.12196;-28.17089;,
 2.27212;27.12196;-28.17089;,
 4.08144;12.94271;-28.17089;,
 2.27212;12.94271;-28.17089;,
 4.08144;15.09161;-24.94755;,
 4.08144;24.97308;-24.94755;,
 -4.08144;68.01630;-30.16191;,
 -2.27212;68.01630;-30.16191;,
 -2.27212;58.13479;-30.16191;,
 -4.08144;58.13479;-30.16191;,
 -2.27212;70.16514;-28.17089;,
 -2.27212;70.16514;-24.94755;,
 -2.27212;68.01630;-24.94755;,
 -2.27212;68.01630;-28.17089;,
 -2.27212;68.01630;-30.16191;,
 -2.27212;58.13479;-28.17089;,
 -2.27212;58.13479;-30.16191;,
 -2.27212;58.13479;-24.94755;,
 -2.27212;55.98590;-24.94755;,
 -2.27212;55.98590;-28.17089;,
 -4.08144;70.16514;-24.94755;,
 -4.08144;70.16514;-28.17089;,
 -4.08144;68.01630;-28.17089;,
 -4.08144;68.01630;-24.94755;,
 -4.08144;68.01630;-30.16191;,
 -4.08144;58.13479;-30.16191;,
 -4.08144;58.13479;-28.17089;,
 -4.08144;58.13479;-24.94755;,
 -4.08144;55.98590;-28.17089;,
 -4.08144;55.98590;-24.94755;,
 -2.27212;70.16514;-28.17089;,
 -4.08144;70.16514;-28.17089;,
 -4.08144;55.98590;-28.17089;,
 -2.27212;55.98590;-28.17089;,
 -4.08144;58.13479;-24.94755;,
 -4.08144;68.01630;-24.94755;,
 4.08144;68.01630;-30.16191;,
 4.08144;58.13479;-30.16191;,
 2.27212;58.13479;-30.16191;,
 2.27212;68.01630;-30.16191;,
 2.27212;70.16514;-28.17089;,
 2.27212;68.01630;-28.17089;,
 2.27212;68.01630;-24.94755;,
 2.27212;70.16514;-24.94755;,
 2.27212;68.01630;-30.16191;,
 2.27212;58.13479;-30.16191;,
 2.27212;58.13479;-28.17089;,
 2.27212;55.98590;-28.17089;,
 2.27212;55.98590;-24.94755;,
 2.27212;58.13479;-24.94755;,
 4.08144;70.16514;-24.94755;,
 4.08144;68.01630;-24.94755;,
 4.08144;68.01630;-28.17089;,
 4.08144;70.16514;-28.17089;,
 4.08144;58.13479;-28.17089;,
 4.08144;58.13479;-30.16191;,
 4.08144;68.01630;-30.16191;,
 4.08144;58.13479;-24.94755;,
 4.08144;55.98590;-24.94755;,
 4.08144;55.98590;-28.17089;,
 4.08144;70.16514;-28.17089;,
 2.27212;70.16514;-28.17089;,
 4.08144;55.98590;-28.17089;,
 2.27212;55.98590;-28.17089;,
 4.08144;58.13479;-24.94755;,
 4.08144;68.01630;-24.94755;;
 
 254;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;3,2,12,13;,
 4;7,6,14,15;,
 4;11,10,16,17;,
 4;18,19,20,21;,
 4;22,23,24,25;,
 4;26,27,28,29;,
 4;21,20,30,31;,
 4;25,24,32,33;,
 4;29,28,34,35;,
 4;36,37,38,39;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;39,38,48,49;,
 4;43,42,50,51;,
 4;47,46,52,53;,
 4;54,55,56,57;,
 4;58,59,60,61;,
 4;62,63,64,65;,
 4;57,56,66,67;,
 4;61,60,68,69;,
 4;65,64,70,71;,
 4;72,73,74,75;,
 4;76,77,78,79;,
 4;73,80,81,74;,
 4;82,83,84,85;,
 4;86,87,88,89;,
 4;87,90,91,88;,
 4;92,93,94,95;,
 4;96,97,98,99;,
 4;100,101,102,103;,
 4;103,102,104,105;,
 4;106,107,108,109;,
 4;110,111,112,113;,
 4;114,115,116,117;,
 4;113,112,118,119;,
 4;120,121,122,123;,
 4;120,123,73,72;,
 4;124,76,79,125;,
 4;124,125,126,121;,
 4;123,122,127,128;,
 4;123,128,80,73;,
 4;129,82,85,130;,
 4;129,130,131,132;,
 4;133,134,135,136;,
 4;133,136,87,86;,
 4;136,135,137,138;,
 4;136,138,90,87;,
 4;139,92,95,140;,
 4;139,140,141,142;,
 4;143,137,144,145;,
 4;143,145,97,96;,
 4;146,100,103,147;,
 4;146,147,148,141;,
 4;147,103,105,149;,
 4;147,149,150,148;,
 4;151,152,153,154;,
 4;151,154,107,106;,
 4;155,110,113,156;,
 4;155,156,157,158;,
 4;159,160,161,162;,
 4;159,162,115,114;,
 4;156,113,119,163;,
 4;156,163,161,157;,
 4;164,4,7,165;,
 4;164,165,2,1;,
 4;166,93,92,167;,
 4;166,167,85,84;,
 4;165,7,15,168;,
 4;165,168,12,2;,
 4;167,92,139,169;,
 4;167,169,130,85;,
 4;169,139,142,170;,
 4;169,170,131,130;,
 4;171,22,25,172;,
 4;171,172,20,19;,
 4;173,44,47,174;,
 4;173,174,42,41;,
 4;172,25,33,175;,
 4;172,175,30,20;,
 4;174,47,53,176;,
 4;174,176,50,42;,
 4;177,108,107,178;,
 4;177,178,114,117;,
 4;178,107,154,179;,
 4;178,179,159,114;,
 4;180,62,65,181;,
 4;180,181,60,59;,
 4;179,154,153,182;,
 4;179,182,160,159;,
 4;181,65,71,183;,
 4;181,183,68,60;,
 4;184,8,11,185;,
 4;184,185,6,5;,
 4;186,83,82,187;,
 4;186,187,79,78;,
 4;185,11,17,188;,
 4;185,188,14,6;,
 4;187,82,129,189;,
 4;187,189,125,79;,
 4;189,129,132,190;,
 4;189,190,126,125;,
 4;191,26,29,192;,
 4;191,192,24,23;,
 4;193,40,43,194;,
 4;193,194,38,37;,
 4;192,29,35,195;,
 4;192,195,32,24;,
 4;194,43,51,196;,
 4;194,196,48,38;,
 4;197,98,97,198;,
 4;197,198,106,109;,
 4;198,97,145,199;,
 4;198,199,151,106;,
 4;200,58,61,201;,
 4;200,201,56,55;,
 4;199,145,144,202;,
 4;199,202,152,151;,
 4;201,61,69,203;,
 4;201,203,66,56;,
 4;204,15,14,205;,
 4;204,206,168,15;,
 4;205,14,188,207;,
 4;206,208,12,168;,
 4;207,188,17,209;,
 4;208,210,13,12;,
 4;209,17,16,211;,
 4;212,213,105,104;,
 4;214,81,80,215;,
 4;213,216,149,105;,
 4;215,80,128,217;,
 4;216,218,150,149;,
 4;217,128,127,219;,
 4;220,221,53,52;,
 4;222,49,48,223;,
 4;221,224,176,53;,
 4;223,48,196,225;,
 4;224,226,50,176;,
 4;225,196,51,227;,
 4;226,227,51,50;,
 4;228,204,205,229;,
 4;228,229,23,22;,
 4;228,22,171,230;,
 4;228,230,206,204;,
 4;229,205,207,231;,
 4;229,231,191,23;,
 4;230,171,19,232;,
 4;230,232,208,206;,
 4;231,207,209,233;,
 4;231,233,26,191;,
 4;232,19,18,234;,
 4;232,234,210,208;,
 4;233,209,211,235;,
 4;233,235,27,26;,
 4;236,111,110,237;,
 4;236,237,213,212;,
 4;238,214,215,239;,
 4;238,239,86,89;,
 4;237,110,155,240;,
 4;237,240,216,213;,
 4;239,215,217,241;,
 4;239,241,133,86;,
 4;240,155,158,242;,
 4;240,242,218,216;,
 4;241,217,219,243;,
 4;241,243,134,133;,
 4;244,63,62,245;,
 4;244,245,221,220;,
 4;246,222,223,247;,
 4;246,247,55,54;,
 4;245,62,180,248;,
 4;245,248,224,221;,
 4;247,223,225,249;,
 4;247,249,200,55;,
 4;248,180,59,250;,
 4;248,250,226,224;,
 4;249,225,227,251;,
 4;249,251,58,200;,
 4;250,59,58,251;,
 4;250,251,227,226;,
 4;252,253,254,255;,
 4;256,257,258,259;,
 4;260,259,261,262;,
 4;261,263,264,265;,
 4;266,267,268,269;,
 4;268,270,271,272;,
 4;273,272,274,275;,
 4;266,257,276,277;,
 4;278,279,264,275;,
 3;256,259,260;,
 3;270,268,267;,
 4;277,276,253,252;,
 4;254,279,278,255;,
 3;272,271,274;,
 3;262,261,265;,
 4;272,280,263,261;,
 4;259,268,272,261;,
 4;258,281,268,259;,
 4;282,283,284,285;,
 4;286,287,288,289;,
 4;290,291,292,287;,
 4;292,293,294,295;,
 4;296,297,298,299;,
 4;298,300,301,302;,
 4;303,304,305,300;,
 4;296,306,307,289;,
 4;308,304,294,309;,
 3;286,290,287;,
 3;302,299,298;,
 4;306,282,285,307;,
 4;284,283,308,309;,
 3;300,305,301;,
 3;291,293,292;,
 4;300,292,295,310;,
 4;287,292,300,298;,
 4;288,287,298,311;,
 4;312,313,314,315;,
 4;316,317,318,319;,
 4;320,319,321,322;,
 4;321,323,324,325;,
 4;326,327,328,329;,
 4;328,330,331,332;,
 4;333,332,334,335;,
 4;326,317,336,337;,
 4;338,339,324,335;,
 3;316,319,320;,
 3;330,328,327;,
 4;337,336,313,312;,
 4;314,339,338,315;,
 3;332,331,334;,
 3;322,321,325;,
 4;332,340,323,321;,
 4;319,328,332,321;,
 4;318,341,328,319;,
 4;342,343,344,345;,
 4;346,347,348,349;,
 4;350,351,352,347;,
 4;352,353,354,355;,
 4;356,357,358,359;,
 4;358,360,361,362;,
 4;363,364,365,360;,
 4;356,366,367,349;,
 4;368,364,354,369;,
 3;346,350,347;,
 3;362,359,358;,
 4;366,342,345,367;,
 4;344,343,368,369;,
 3;360,365,361;,
 3;351,353,352;,
 4;360,352,355,370;,
 4;347,352,360,358;,
 4;348,347,358,371;;
 
 MeshMaterialList {
  6;
  254;
  3,
  0,
  3,
  3,
  0,
  3,
  3,
  0,
  3,
  3,
  0,
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
  0,
  3,
  3,
  3,
  3,
  3,
  3,
  0,
  3,
  3,
  3,
  3,
  0,
  0,
  3,
  3,
  0,
  0,
  3,
  3,
  0,
  3,
  0,
  0,
  3,
  3,
  0,
  0,
  3,
  0,
  3,
  3,
  0,
  0,
  3,
  3,
  0,
  0,
  3,
  3,
  3,
  3,
  3,
  3,
  1,
  0,
  0,
  3,
  3,
  3,
  4,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  0,
  0,
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
  1,
  3,
  0,
  0,
  3,
  3,
  4,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  0,
  0,
  3,
  3,
  3,
  3,
  3,
  3,
  0,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  0,
  0,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  0,
  0,
  3,
  0,
  0,
  3,
  3,
  0,
  0,
  3,
  3,
  0,
  0,
  3,
  3,
  0,
  0,
  3,
  0,
  0,
  0,
  0,
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
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.508000;0.618400;0.627200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.552000;0.382400;0.207200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.442400;0.244800;0.100000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.467200;0.467200;0.467200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  24;
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.365010;-0.931004;,
  0.000000;-0.365007;-0.931005;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.916420;-0.400218;,
  0.000000;-0.916419;-0.400220;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.365014;-0.931002;,
  0.000000;-0.365008;-0.931004;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.916422;-0.400214;,
  0.000000;-0.916419;-0.400220;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;1.000000;;
  254;
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
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
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;6,6,7,7;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;10,10,11,11;,
  4;12,12,13,13;,
  3;8,8,8;,
  3;9,9,9;,
  4;11,11,6,6;,
  4;7,12,12,7;,
  3;9,9,9;,
  3;8,8,8;,
  4;10,10,10,10;,
  4;14,14,14,14;,
  4;13,13,13,13;,
  4;6,7,7,6;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;10,11,11,10;,
  4;12,13,13,12;,
  3;9,9,9;,
  3;8,8,8;,
  4;11,6,6,11;,
  4;7,7,12,12;,
  3;8,8,8;,
  3;9,9,9;,
  4;10,10,10,10;,
  4;14,14,14,14;,
  4;13,13,13,13;,
  4;15,15,16,16;,
  4;17,17,17,17;,
  4;17,17,17,17;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  4;19,19,20,20;,
  4;21,21,22,22;,
  3;17,17,17;,
  3;18,18,18;,
  4;20,20,15,15;,
  4;16,21,21,16;,
  3;18,18,18;,
  3;17,17,17;,
  4;19,19,19,19;,
  4;23,23,23,23;,
  4;22,22,22,22;,
  4;15,16,16,15;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  4;17,17,17,17;,
  4;17,17,17,17;,
  4;17,17,17,17;,
  4;19,20,20,19;,
  4;21,22,22,21;,
  3;18,18,18;,
  3;17,17,17;,
  4;20,15,15,20;,
  4;16,16,21,21;,
  3;17,17,17;,
  3;18,18,18;,
  4;19,19,19,19;,
  4;23,23,23,23;,
  4;22,22,22,22;;
 }
 MeshTextureCoords {
  372;
  0.000000;0.000000;,
  0.200000;0.000000;,
  0.200000;0.200000;,
  0.000000;0.200000;,
  0.400000;0.000000;,
  0.600000;0.000000;,
  0.600000;0.200000;,
  0.400000;0.200000;,
  0.800000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.200000;,
  0.800000;0.200000;,
  0.200000;0.400000;,
  0.000000;0.400000;,
  0.600000;0.400000;,
  0.400000;0.400000;,
  1.000000;0.400000;,
  0.800000;0.400000;,
  0.000000;0.600000;,
  0.200000;0.600000;,
  0.200000;0.800000;,
  0.000000;0.800000;,
  0.400000;0.600000;,
  0.600000;0.600000;,
  0.600000;0.800000;,
  0.400000;0.800000;,
  0.800000;0.600000;,
  1.000000;0.600000;,
  1.000000;0.800000;,
  0.800000;0.800000;,
  0.200000;1.000000;,
  0.000000;1.000000;,
  0.600000;1.000000;,
  0.400000;1.000000;,
  1.000000;1.000000;,
  0.800000;1.000000;,
  0.000000;0.000000;,
  0.200000;0.000000;,
  0.200000;0.200000;,
  0.000000;0.200000;,
  0.400000;0.000000;,
  0.600000;0.000000;,
  0.600000;0.200000;,
  0.400000;0.200000;,
  0.800000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.200000;,
  0.800000;0.200000;,
  0.200000;0.400000;,
  0.000000;0.400000;,
  0.600000;0.400000;,
  0.400000;0.400000;,
  1.000000;0.400000;,
  0.800000;0.400000;,
  0.000000;0.600000;,
  0.200000;0.600000;,
  0.200000;0.800000;,
  0.000000;0.800000;,
  0.400000;0.600000;,
  0.600000;0.600000;,
  0.600000;0.800000;,
  0.400000;0.800000;,
  0.800000;0.600000;,
  1.000000;0.600000;,
  1.000000;0.800000;,
  0.800000;0.800000;,
  0.200000;1.000000;,
  0.000000;1.000000;,
  0.600000;1.000000;,
  0.400000;1.000000;,
  1.000000;1.000000;,
  0.800000;1.000000;,
  0.099930;0.000000;,
  0.099930;0.200000;,
  0.000000;0.200000;,
  0.000000;0.000000;,
  1.000000;0.900070;,
  1.000000;1.000000;,
  0.800000;1.000000;,
  0.800000;0.900070;,
  0.099930;0.400000;,
  0.000000;0.400000;,
  0.600000;0.900070;,
  0.600000;1.000000;,
  0.400000;1.000000;,
  0.400000;0.900070;,
  0.099930;0.600000;,
  0.099930;0.800000;,
  0.000000;0.800000;,
  0.000000;0.600000;,
  0.099930;1.000000;,
  0.000000;1.000000;,
  0.200000;0.900070;,
  0.200000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.900070;,
  1.000000;0.099930;,
  0.800000;0.099930;,
  0.800000;0.000000;,
  1.000000;0.000000;,
  0.900070;0.000000;,
  1.000000;0.000000;,
  1.000000;0.200000;,
  0.900070;0.200000;,
  1.000000;0.400000;,
  0.900070;0.400000;,
  0.600000;0.099930;,
  0.400000;0.099930;,
  0.400000;0.000000;,
  0.600000;0.000000;,
  0.900070;0.600000;,
  1.000000;0.600000;,
  1.000000;0.800000;,
  0.900070;0.800000;,
  0.200000;0.099930;,
  0.000000;0.099930;,
  0.000000;0.000000;,
  0.200000;0.000000;,
  1.000000;1.000000;,
  0.900070;1.000000;,
  0.121710;0.000000;,
  1.000000;0.000000;,
  1.000000;0.200000;,
  0.121710;0.200000;,
  1.000000;0.878290;,
  0.800000;0.878290;,
  0.800000;0.000000;,
  1.000000;0.400000;,
  0.121710;0.400000;,
  0.600000;0.878290;,
  0.400000;0.878290;,
  0.400000;0.000000;,
  0.600000;0.000000;,
  0.121710;0.600000;,
  1.000000;0.600000;,
  1.000000;0.800000;,
  0.121710;0.800000;,
  1.000000;1.000000;,
  0.121710;1.000000;,
  0.200000;0.878290;,
  0.000000;0.878290;,
  0.000000;0.000000;,
  0.200000;0.000000;,
  1.000000;0.121710;,
  0.800000;1.000000;,
  0.800000;0.121710;,
  0.878290;0.000000;,
  0.878290;0.200000;,
  0.000000;0.200000;,
  0.878290;0.400000;,
  0.000000;0.400000;,
  0.600000;0.121710;,
  0.600000;1.000000;,
  0.400000;1.000000;,
  0.400000;0.121710;,
  0.878290;0.600000;,
  0.878290;0.800000;,
  0.000000;0.800000;,
  0.000000;0.600000;,
  0.200000;0.121710;,
  0.200000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.121710;,
  0.878290;1.000000;,
  0.385970;0.000000;,
  0.385970;0.200000;,
  0.385970;1.000000;,
  0.385970;0.900070;,
  0.385970;0.400000;,
  0.385970;0.878290;,
  0.385970;0.000000;,
  0.385970;0.600000;,
  0.385970;0.800000;,
  0.614030;0.000000;,
  0.614030;0.200000;,
  0.385970;1.000000;,
  0.614030;0.400000;,
  0.385970;0.000000;,
  0.385970;0.099930;,
  0.385970;0.121710;,
  0.614030;0.600000;,
  0.614030;0.800000;,
  0.385970;1.000000;,
  0.614030;1.000000;,
  0.611950;0.000000;,
  0.611950;0.200000;,
  0.611950;1.000000;,
  0.611950;0.900070;,
  0.611950;0.400000;,
  0.611950;0.878290;,
  0.611950;0.000000;,
  0.611950;0.600000;,
  0.611950;0.800000;,
  0.388050;0.000000;,
  0.388050;0.200000;,
  0.611950;1.000000;,
  0.388050;0.400000;,
  0.611950;0.000000;,
  0.611950;0.099930;,
  0.611950;0.121710;,
  0.388050;0.600000;,
  0.388050;0.800000;,
  0.611950;1.000000;,
  0.388050;1.000000;,
  0.400000;0.488870;,
  0.600000;0.488870;,
  0.385970;0.488870;,
  0.611950;0.488870;,
  0.200000;0.488870;,
  0.800000;0.488870;,
  0.000000;0.488870;,
  1.000000;0.488870;,
  1.000000;0.488870;,
  0.900070;0.488870;,
  0.000000;0.488870;,
  0.099930;0.488870;,
  0.878290;0.488870;,
  0.121710;0.488870;,
  0.000000;0.488870;,
  1.000000;0.488870;,
  1.000000;0.488870;,
  0.800000;0.488870;,
  0.000000;0.488870;,
  0.200000;0.488870;,
  0.614030;0.488870;,
  0.388050;0.488870;,
  0.600000;0.488870;,
  0.400000;0.488870;,
  0.400000;0.516950;,
  0.600000;0.516950;,
  0.385970;0.516950;,
  0.611950;0.516950;,
  0.200000;0.516950;,
  0.800000;0.516950;,
  0.000000;0.516950;,
  1.000000;0.516950;,
  1.000000;0.516950;,
  0.900070;0.516950;,
  0.000000;0.516950;,
  0.099930;0.516950;,
  0.878290;0.516950;,
  0.121710;0.516950;,
  0.000000;0.516950;,
  1.000000;0.516950;,
  1.000000;0.516950;,
  0.800000;0.516950;,
  0.000000;0.516950;,
  0.200000;0.516950;,
  0.614030;0.516950;,
  0.388050;0.516950;,
  0.600000;0.516950;,
  0.400000;0.516950;,
  0.000000;0.333330;,
  1.000000;0.333330;,
  1.000000;0.666670;,
  0.000000;0.666670;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.500000;0.333330;,
  0.000000;0.333330;,
  0.500000;0.666670;,
  0.000000;0.666670;,
  1.000000;0.666670;,
  1.000000;1.000000;,
  0.500000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.333330;,
  0.000000;0.333330;,
  1.000000;0.333330;,
  1.000000;0.666670;,
  0.500000;0.666670;,
  0.000000;0.666670;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.666670;,
  1.000000;0.333330;,
  0.000000;0.333330;,
  0.000000;0.666670;,
  1.000000;0.666670;,
  1.000000;0.333330;,
  0.500000;0.000000;,
  0.500000;0.333330;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.333330;,
  0.000000;0.666670;,
  0.500000;0.666670;,
  0.500000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.666670;,
  0.000000;0.000000;,
  0.000000;0.333330;,
  0.500000;0.333330;,
  0.500000;0.000000;,
  0.500000;0.666670;,
  1.000000;0.666670;,
  1.000000;0.333330;,
  0.000000;0.666670;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.666670;,
  1.000000;0.333330;,
  0.000000;0.333330;,
  1.000000;0.333330;,
  1.000000;0.666670;,
  0.000000;0.666670;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.500000;0.333330;,
  0.000000;0.333330;,
  0.500000;0.666670;,
  0.000000;0.666670;,
  1.000000;0.666670;,
  1.000000;1.000000;,
  0.500000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.333330;,
  0.000000;0.333330;,
  1.000000;0.333330;,
  1.000000;0.666670;,
  0.500000;0.666670;,
  0.000000;0.666670;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.666670;,
  1.000000;0.333330;,
  0.000000;0.333330;,
  0.000000;0.666670;,
  1.000000;0.666670;,
  1.000000;0.333330;,
  0.500000;0.000000;,
  0.500000;0.333330;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.333330;,
  0.000000;0.666670;,
  0.500000;0.666670;,
  0.500000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.666670;,
  0.000000;0.000000;,
  0.000000;0.333330;,
  0.500000;0.333330;,
  0.500000;0.000000;,
  0.500000;0.666670;,
  1.000000;0.666670;,
  1.000000;0.333330;,
  0.000000;0.666670;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.666670;,
  1.000000;0.333330;;
 }
}
