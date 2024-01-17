//=============================================
//
//�}�b�v�G�f�B�^�[[field.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _FIELD_H_ //��`����ĂȂ�������
#define _FIELD_H_ //�Q��C���N���[�h�h�~

#include "main.h"

#define NUM_FIELD	(1) //�t�B�[���h�̎��
#define MAX_FIELD	(256) //�t�B�[���h�̎��

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	int nType;
	float fWide;
	float fDepth;
	bool bUse;
}Field;

void InitField(void);
void UninitField(void);
void UpdateField(void);
void DrawField(void);
D3DXVECTOR3 GetFieldPos(void);

#endif // _FIELD_H_ //��`����ĂȂ�������

