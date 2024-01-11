//=============================================
//
//3D�e���v���[�g[camera.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"

#define PLAYER_LENGTH_X	(30.0f) //�v���C���[�ƃJ����X�̋���
#define PLAYER_LENGTH_Y	(100.0f) //�v���C���[�ƃJ����Y�̋���
#define PLAYER_LENGTH_Z	(200.0f) //�v���C���[�ƃJ����Z�̋���

typedef enum
{
	CAMERATYPE_PLAYER = 0,
	CAMERATYPE_DEFAULT,
	CAMERATYPE_TURN,
	CAMERATYPE_EDIT,
	CAMERATYPE_MAX,
}CAMERATYPE;


typedef struct
{
	D3DXVECTOR3	posV; //���_
	D3DXVECTOR3	posR; //�����_
	D3DXVECTOR3 vecU; //������x�N�g��
	D3DXVECTOR3 rot; //����
	D3DXVECTOR3 moveV;
	D3DXVECTOR3 moveR;
	D3DXMATRIX	mtxProjection; //�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView; //�r���[�}�g���b�N�X
	CAMERATYPE type;
	D3DXVECTOR3 rotmove; //��]��
	float fLength;
	float fAngle;
}Camera;

void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void PlayerCamera(void);
void EditCamera(void);
void TurnCamera(void);
void SetCamera(void);

void DebagCameraPos(void);

Camera* GetCamera(void);

