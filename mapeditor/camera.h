//=============================================
//
//マップエディター[camera.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"

#define DEFAULT_LENGTH_Y	(200.0f) //通常状態のYの距離
#define DEFAULT_LENGTH_Z	(500.0f) //通常状態のZの距離
#define EDIT_LENGTH_Y	(1020.0f) //通常状態のYの距離
#define EDIT_LENGTH_Z	(13.0f) //通常状態のZの距離

typedef enum
{
	CAMERATYPE_DEFAULT = 0,
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
	bool bCameraAngle;
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

