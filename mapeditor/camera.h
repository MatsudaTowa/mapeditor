//=============================================
//
//3Dテンプレート[camera.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"

#define PLAYER_LENGTH_X	(30.0f) //プレイヤーとカメラXの距離
#define PLAYER_LENGTH_Y	(100.0f) //プレイヤーとカメラYの距離
#define PLAYER_LENGTH_Z	(200.0f) //プレイヤーとカメラZの距離

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
	D3DXVECTOR3	posV; //視点
	D3DXVECTOR3	posR; //注視点
	D3DXVECTOR3 vecU; //上方向ベクトル
	D3DXVECTOR3 rot; //向き
	D3DXVECTOR3 moveV;
	D3DXVECTOR3 moveR;
	D3DXMATRIX	mtxProjection; //プロジェクションマトリックス
	D3DXMATRIX mtxView; //ビューマトリックス
	CAMERATYPE type;
	D3DXVECTOR3 rotmove; //回転量
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

