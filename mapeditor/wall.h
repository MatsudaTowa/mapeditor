//=============================================
//
//�}�b�v�G�f�B�^�[[wall.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _wall_H_ //��`����ĂȂ�������
#define _wall_H_ //�Q��C���N���[�h�h�~

//=============================================
//�}�N����`
//=============================================
#define MAX_WALL	(256) //�ǂ̐�
#define NUM_WALL	(1) //�ǂ̎��
#define WALL_WIDE	(500.0f) //�ǂ̉���
#define WALL_HEIGHT	(200.0f) //�ǂ̏c��

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


#endif // _POLYGON_H_ //��`����ĂȂ�������

