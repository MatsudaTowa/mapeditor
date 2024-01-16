//=============================================
//
//3Dテンプレート[model.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _model_H_ //定義されてなかったら
#define _model_H_ //２種インクルード防止

#include "main.h"

#define MAX_MODEL	(256) //モデルの最大数
#define NUM_MODEL	(2) //モデルの種類
#define NUM_TEXTURE	(3) //テクスチャ数

typedef enum
{
	MODELTYPE_ROCK = 0,
	MODELTYPE_SIGNBOARD,
	MODELTYPE_MAX,
}ModelType;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 Minpos;
	D3DXVECTOR3 Maxpos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 move;
	LPD3DXMESH pMesh;
	LPD3DXBUFFER pBuffMat;
	DWORD nNumMat;
	D3DXMATRIX mtxWorld;
	LPDIRECT3DTEXTURE9 pTexture;
	int nShadow;
	int nCntMat;
	ModelType nType;
	bool bUse;
}model;

void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, ModelType nType);

model* GetModel(void);


#endif // _POLYGON_H_ //定義されてなかったら

