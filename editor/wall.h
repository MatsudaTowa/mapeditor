//=============================================
//
//3D�e���v���[�g[wall.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _wall_H_ //��`����ĂȂ�������
#define _wall_H_ //�Q��C���N���[�h�h�~

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


#endif // _POLYGON_H_ //��`����ĂȂ�������

