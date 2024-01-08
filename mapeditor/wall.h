//=============================================
//
//3Dテンプレート[wall.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _wall_H_ //定義されてなかったら
#define _wall_H_ //２種インクルード防止

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
}Wall;

void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void ColisionWall(void);
void DrawWall(void);


#endif // _POLYGON_H_ //定義されてなかったら

