//=============================================
//
//マップエディター[field.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _FIELD_H_ //定義されてなかったら
#define _FIELD_H_ //２種インクルード防止

#include "main.h"

#define NUM_FIELD	(1) //フィールドの種類
#define MAX_FIELD	(256) //フィールドの種類

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

#endif // _FIELD_H_ //定義されてなかったら

