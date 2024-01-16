//=============================================
//
//マップエディター[shadow.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _shadow_H_ //定義されてなかったら
#define _shadow_H_ //２種インクルード防止

#include "main.h"

#define	MAX_SHADOW	(2048)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	float fRadius;
	int nNumber;
	bool bUse;
}Shadow;

void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);

int SetShadow(void);
void SetShadowPos(int nIdxShadow,D3DXVECTOR3 pos,float fRadius);
Shadow* GetShadow(void);

#endif // _POLYGON_H_ //定義されてなかったら

