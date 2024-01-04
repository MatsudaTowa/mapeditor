//=============================================
//
//STGtest[input.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _INPUT_H_ //��`����ĂȂ�������
#define _INPUT_H_ //�Q��C���N���[�h�h�~
#include "main.h"

//�}�N����`
#define JOYPAD_ZONE (1)
#define JOYPAD_SPEED (15)

//�L�[�̎��
typedef enum
{
    JOYKEY_UP = 0,
    JOYKEY_DOWN,
    JOYKEY_LEFT,
    JOYKEY_RIGHT,
    JOYKEY_START,
    JOYKEY_BACK,
    JOYKEY_L3,
    JOYKEY_R3,
    JOYKEY_LB,
    JOYKEY_RB,
    JOYKEY_LT,
    JOYKEY_RT,
    JOYKEY_A,
    JOYKEY_B,
    JOYKEY_X,
    JOYKEY_Y,
    JOYKEY_MAX
}JOYKEY;

//�X�e�B�b�N�̔ԍ�
typedef enum
{
    STICKTYPE_LEFT = 0, // ���X�e�B�b�N
    STICKTYPE_RIGHT, // �E�X�e�B�b�N
    STICKTYPE_MAX
}STICKTYPE;

//�X�e�B�b�N�̕���
typedef enum
{
    STICKANGLE_UP = 0, // ��
    STICKANGLE_DOWN,   // ��
    STICKANGLE_LEFT,   // ��
    STICKANGLE_RIGHT,  // �E
    STICKANGLE_MAX,
}STICKANGLE;

//�X�e�B�b�N�̓��͏��
typedef struct
{
    float afTplDiameter[STICKTYPE_MAX];                      // �X�e�B�b�N�̓|���
    float afAngle[STICKTYPE_MAX];                            // �X�e�B�b�N�̊p�x
    bool abAnglePress[STICKTYPE_MAX][STICKANGLE_MAX];        // �X�e�B�b�N�̕����v���X���
    bool abAngleTrigger[STICKTYPE_MAX][STICKANGLE_MAX];      // �X�e�B�b�N�̕����g���K�[���
    bool abAngleRepeat[STICKTYPE_MAX][STICKANGLE_MAX];       // �X�e�B�b�N�̕������s�[�g���
    bool abAngleRelease[STICKTYPE_MAX][STICKANGLE_MAX];      // �X�e�B�b�N�̕��������[�X���
}STICKINPUT;


HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);

HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd);
void UninitMouse(void);
void UpdateMouse(void);
bool GetMousePress(int nKey);
bool GetMouseTrigger(int nKey);
D3DXVECTOR3 GetMouseMove(void);
//void GetMouseState(HWND hWnd);


HRESULT InitJoypad(void);
void UninitJoypad(void);
void UpdateJoypad(void);
bool GetJoypadTrigger(JOYKEY key);
bool GetJoypadPress(JOYKEY key);
bool GetJoypadRepeat(JOYKEY key);
XINPUT_STATE* GetXInputState(void);
void UpdateStick(void);
STICKINPUT GetStick(void);
float FindAngle(D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos);
WORD GetJoypadStick(SHORT sThumbx, SHORT sThumby, SHORT sDeaZone);
#endif // _INPUT_H_ //��`����ĂȂ�������

