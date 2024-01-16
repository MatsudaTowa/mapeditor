//=============================================
//
//3D�e���v���[�g[wall.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _wall_H_ //��`����ĂȂ�������
#define _wall_H_ //�Q��C���N���[�h�h�~

//=============================================
//�}�N����`
//=============================================
#define MAX_WALL	(4) //�ǂ̐�
#define NUM_WALL	(1) //�ǂ̎��

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
void ColisionWall(void);
void DrawWall(void);


#endif // _POLYGON_H_ //��`����ĂȂ�������

