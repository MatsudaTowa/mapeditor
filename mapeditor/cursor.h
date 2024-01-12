//=============================================
//
//3D�e���v���[�g[cursor.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _CURSOR_H_ //��`����ĂȂ�������
#define _CURSOR_H_ //�Q��C���N���[�h�h�~

#include "main.h"

//=============================================
//�J�[�\���̍\�z�̂̒�`
//=============================================
typedef struct
{
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 pos;
	int IndexEdit;
}Cursol;

void InitCursor(void);
void UninitCursor(void);
void UpdateCursor(void);
void DrawCursor(void);
void SetCursor(D3DXVECTOR3 pos);

#endif // _CURSOR_H_ //��`����ĂȂ�������

