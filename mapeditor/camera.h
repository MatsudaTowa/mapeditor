//=============================================
//
//�}�b�v�G�f�B�^�[[camera.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"

#define DEFAULT_LENGTH_Y	(200.0f) //�ʏ��Ԃ�Y�̋���
#define DEFAULT_LENGTH_Z	(-500.0f) //�ʏ��Ԃ�Z�̋���
#define EDIT_LENGTH_Y	(1020.0f) //�ʏ��Ԃ�Y�̋���
#define EDIT_LENGTH_Z	(13.0f) //�ʏ��Ԃ�Z�̋���

typedef enum
{
	CAMERATYPE_DEFAULT = 0,
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
	bool bEditFollow;
	float fLength;
	float fAngle;
}Camera;

void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void EditCamera(void);
void TurnCamera(void);
void SetCamera(void);

void DebagCameraPos(void);

Camera* GetCamera(void);

