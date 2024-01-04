//=============================================
//
//3Dテンプレート[field.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _field_H_ //定義されてなかったら
#define _field_H_ //２種インクルード防止

void InitField(void);
void UninitField(void);
void UpdateField(void);
void DrawField(void);
D3DXVECTOR3 GetFieldPos(void);

#endif // _POLYGON_H_ //定義されてなかったら

