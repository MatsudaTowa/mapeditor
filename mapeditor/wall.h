//=============================================
//
//マップエディター[wall.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _wall_H_ //定義されてなかったら
#define _wall_H_ //２種インクルード防止

//=============================================
//マクロ定義
//=============================================
#define MAX_WALL	(256) //壁の数
#define NUM_WALL	(1) //壁の種類
#define WALL_WIDE	(500.0f) //壁の横幅
#define WALL_HEIGHT	(200.0f) //壁の縦幅

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	int nType;
	bool bUse;
}Wall;

void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos,D3DXVECTOR3 rot, int nType);


#endif // _POLYGON_H_ //定義されてなかったら

