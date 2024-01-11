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
//エディットのタイプ
//=============================================
typedef enum
{
	EDITTYPE_MODEL = 0,
	EDITTYPE_CORRECTIONMODEL,
	EDITTYPE_MAX,
}EDITTYPE;

//=============================================
//モデルエディットの構想体の定義
//=============================================
typedef struct
{
	EDITTYPE EditType;
}Edit;

//=============================================
//モデルエディットの構想体の定義
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
	bool bUseGame; 
}EditModelInfo;

//プロトタイプ宣言
void InitEdit(void);
void UninitEdit(void);
void UpdateEdit(void);
void SaveModel(void);
void CorrectionModel(void);
void reSaveModel(void);
void DrawEdit(void);
void DebagEdit(void);
EditModelInfo* GetEditModelinfo(void);
//D3DXVECTOR3 GetEditCameraPos(void);

#endif // !_RESULT_H
