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
	EDITTYPE_WALL,
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
	D3DXMATRIX mtxWorld;
	D3DCOLORVALUE Diffuse[MAX_MODEL];
	int nType;
	bool bUse;
	bool bUseGame; 
}EditModelInfo;

//=============================================
//壁エディットの構想体の定義
//=============================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	int nType;
	bool bUse;
	bool bUseGame;
}EditWallInfo;

//=============================================
//プロトタイプ宣言
//=============================================
void InitEdit(void);
void UninitEdit(void);
void UpdateEdit(void);
void SaveWall(void);
void CorrectionWall(void);
void reSaveWall(void);
void SaveModel(void);
void CorrectionModel(void);
void reSaveModel(void);
void DrawEdit(void);
void DebagEdit(void);
EditModelInfo* GetEditModelinfo(void);
//D3DXVECTOR3 GetEditCameraPos(void);

#endif // !_RESULT_H
