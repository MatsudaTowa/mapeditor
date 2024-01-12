//=============================================
//
//3Dテンプレート[cursor.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _CURSOR_H_ //定義されてなかったら
#define _CURSOR_H_ //２種インクルード防止

#include "main.h"

//=============================================
//カーソルの構想体の定義
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

#endif // _CURSOR_H_ //定義されてなかったら

