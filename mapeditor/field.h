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
#define FIELD_WIDE	(500)
#define FIELD_DEPTH	(500)

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
void SetField(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWide, float fDepth, int nType);
D3DXVECTOR3 GetFieldPos(void);

#endif // _FIELD_H_ //定義されてなかったら

