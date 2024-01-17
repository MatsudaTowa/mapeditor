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
//�G�f�B�b�g�̃^�C�v
//=============================================
typedef enum
{
	EDITTYPE_MODEL = 0,
	EDITTYPE_CORRECTIONMODEL,
	EDITTYPE_WALL,
	EDITTYPE_CORRECTIONWALL,
	EDITTYPE_MAX,
}EDITTYPE;

//=============================================
//���f���G�f�B�b�g�̍\�z�̂̒�`
//=============================================
typedef struct
{
	EDITTYPE EditType;
	bool bCursorType;
	int nEditModelNumber; //�Ǐ]����J�����̑Ώ�
	int nEditWallNumber; //�Ǐ]����J�����̑Ώ�

}Edit;

//=============================================
//���f���G�f�B�b�g�̍\�z�̂̒�`
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
//���G�f�B�b�g�̍\�z�̂̒�`
//=============================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	int nType;
	float fWide;
	float fHeight;
	bool bUse;
	bool bUseGame;
}EditWallInfo;

//=============================================
//���G�f�B�b�g�̍\�z�̂̒�`
//=============================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	int nType;
	float fWide;
	float fDepth;
	bool bUse;
	bool bUseGame;
}EditFieldInfo;

//=============================================
//�v���g�^�C�v�錾
//=============================================
void InitEdit(void);
void UninitEdit(void);
void UpdateEdit(void);
void reSaveEdit(void);
void SaveModel(void);
void CorrectionModel(void);
void reSaveModel(void);
void SaveWall(void);
void CorrectionWall(void);
void reSaveWall(void);
void SaveField(void);
void CorrectionField(void);
void reSaveField(void);
void DrawEdit(void);
void DebagEdit(void);
void DebagInfo(void);
EditModelInfo* GetEditModelinfo(void);
Edit* GetEdit(void);
//D3DXVECTOR3 GetEditCameraPos(void);

#endif // !_RESULT_H
