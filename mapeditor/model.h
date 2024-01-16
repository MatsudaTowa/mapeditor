//=============================================
//
//3D�e���v���[�g[model.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _model_H_ //��`����ĂȂ�������
#define _model_H_ //�Q��C���N���[�h�h�~

#include "main.h"

#define MAX_MODEL	(256) //���f���̍ő吔
#define NUM_MODEL	(2) //���f���̎��
#define NUM_TEXTURE	(3) //�e�N�X�`����

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


#endif // _POLYGON_H_ //��`����ĂȂ�������

