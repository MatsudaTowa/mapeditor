//=============================================
//
//STGtest[edit.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _EDIT_H
#define _EDIT_H

#include "main.h"

//=============================================
//構想体の定義
//=============================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 move;
	LPD3DXMESH pMesh;
	LPD3DXBUFFER pBuffMat;
	DWORD nNumMat;
	D3DXMATRIX mtxWorld;
	int nType;
	bool bUse;
}EditModelInfo;


//プロトタイプ宣言
void InitEdit(void);
void UninitEdit(void);
void UpdateEdit(void);
void SaveModel(void);
//void SaveBlock(void);
void reSaveModel(void);
//void reSaveBlock(void);
void DrawEdit(void);
//int GetEditSelect(void);
EditModelInfo* GetEditModelinfo(void);
//D3DXVECTOR3 GetEditCameraPos(void);

#endif // !_RESULT_H
