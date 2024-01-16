//=============================================
//
//STGtest[input.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "input.h"

//�}�N����`
#define NUM_KEY_MAX	(256)
#define NUM_MOUSE_MAX	(3)
//�O���[�o���ϐ�
LPDIRECTINPUT8 g_pInput = NULL;	//directInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL; //���̓f�o�C�X�ւ̃|�C���^

//�L�[�{�[�h
BYTE g_aKeyStateTrigger[NUM_KEY_MAX]; //�L�[�{�[�h�̃g���K�[���
BYTE g_aKeyState[NUM_KEY_MAX]; //�L�[�{�[�h�̃v���X���

//�}�E�X
LPDIRECTINPUTDEVICE8 g_pDIMouse = NULL;	// �}�E�X�f�o�C�X
DIMOUSESTATE g_zdiMouseStateTrigger;	// �}�E�X�g���K�[���
DIMOUSESTATE g_zdiMouseState;			// �}�E�X�v���X���
DIMOUSESTATE g_zdiMouseMove; //�}�E�X���[�u
D3DXVECTOR3 g_MousePos;
D3DXVECTOR3 g_MouseMove;

//�R���g���[���[
XINPUT_STATE g_joyKeyState; //�W���C�p�b�h�̃v���X���
XINPUT_STATE g_joyKeyStateTrigger; //�W���C�p�b�h�̃g���K�[���
XINPUT_STATE g_joyKeyStateRepeat; //�W���C�p�b�h�̃��s�[�g���
XINPUT_STATE g_ajoyKeyStateRelease; //�R���g���[���[�̃����[�X���
XINPUT_STATE g_aJoypadCurrentTime; //�R���g���[���[�̌��݂̎���
XINPUT_STATE g_aJoypadExecLastTime; //�R���g���[���[�̍Ō�ɐ^��Ԃ�������
XINPUT_STATE g_JoypadInput; //�R���g���[���[�̓��͏��
D3DXVECTOR3 g_joyStickPos; //�X�e�B�b�N�̌X��
bool g_bAngle[STICKTYPE_MAX][STICKANGLE_MAX]; //�X�e�B�b�N�̓��͏��
DWORD g_aStickCurrentTime[STICKTYPE_MAX][STICKANGLE_MAX]; //�X�e�B�b�N�̌��݂̎���
DWORD g_aStickExecLastTime[STICKTYPE_MAX][STICKANGLE_MAX]; //�X�e�B�b�N�̌��݂̎���
STICKINPUT g_stick; //�X�e�B�b�N�̓��͏��
XINPUT_STATE g_XInput; //���͏��
XINPUT_VIBRATION g_JoypadMotor;
int g_nCntkey;
//=============================================
//�L�[�{�[�h�̏���������
//=============================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}
	//���̓f�o�C�X�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//�L�[�{�[�h�̃A�N�Z�X�����l��
	g_pDevKeyboard->Acquire();
	return S_OK;
}

//=============================================
//�L�[�{�[�h�̏I������
//=============================================
void UninitKeyboard(void)
{
	//���̓f�o�C�X�̔j��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();
		g_pDevKeyboard->Unacquire();
		g_pDevKeyboard = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//=============================================
//�L�[�{�[�h�̍X�V����
//=============================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX]; //���͏��
	int nCntKey;
	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			g_aKeyState[nCntKey] = aKeyState[nCntKey]; //�L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		g_pDevKeyboard->Acquire(); //�L�[�{�[�h�̃A�N�Z�X�����l��
	}
}

//=============================================
//�L�[�{�[�h�̏����擾
//=============================================
bool GetKeyboardPress(int nKey)
{
	return(g_aKeyState[nKey] & 0x80) != 0;
}
bool GetKeyboardTrigger(int nKey)
{
	return(g_aKeyStateTrigger[nKey] & 0x80) != 0;
}

//===========================================================================================================================================================================
//�}�E�X
//===========================================================================================================================================================================
//=============================================
//�}�E�X�̏���������
//=============================================
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}
	//���̓f�o�C�X�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysMouse, &g_pDIMouse, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDIMouse->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�
	if (FAILED(g_pDIMouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	// �f�o�C�X�̐ݒ�
	DIPROPDWORD diprop;
	g_MousePos = { 0.0f,0.0f,0.0f };
	g_MouseMove = { 0.0f,0.0f,0.0f };
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;

	if (FAILED(g_pDIMouse->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		// �f�o�C�X�̐ݒ�Ɏ��s
		return E_FAIL;
	}

	//�}�E�X�̃A�N�Z�X�����l��
	g_pDevKeyboard->Acquire();
	return S_OK;
}

//=============================================
//�}�E�X�̏I������
//=============================================
void UninitMouse(void)
{
	//���̓f�o�C�X�̔j��
	if (g_pDIMouse != NULL)
	{
		g_pDIMouse->Unacquire();
		g_pDIMouse->Unacquire();
		g_pDIMouse = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}


//=============================================
//�}�E�X�̍X�V����
//=============================================
void UpdateMouse(void)
{
	BYTE aMouseState[NUM_MOUSE_MAX]; //���͏��
	DIMOUSESTATE zdiMouseState;
	int nCntMouseButton;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDIMouse->GetDeviceState(sizeof(zdiMouseState), &zdiMouseState)))
	{

		//g_zdiMouseStateTrigger = (g_zdiMouseState ^ zdiMouseState) & zdiMouseState;
		g_zdiMouseState = zdiMouseState; //�}�E�X�̃v���X����ۑ�

	}
	else
	{
		g_pDIMouse->Acquire(); //�}�E�X�̃A�N�Z�X�����l��

	}

	//�{�^���̎擾
	for (nCntMouseButton = 0; nCntMouseButton < NUM_MOUSE_MAX; nCntMouseButton++)
	{

		/*
		DIMOUSESTATE�\���̂̒��Ɏg���ĂȂ��ϐ�������B
		*/
	}




	//ZeroMemory(&pMouseMove, sizeof(POINT));

	//D3DXVECTOR3 OldMousePos = g_MousePos;

	//POINT pMouseMove;

	////GetCursorPos(&pMouseMove);

	//g_MousePos.x = (float)pMouseMove.x;
	//g_MousePos.y = (float)pMouseMove.y;

	//g_MouseMove.x = g_MousePos.x - OldMousePos.x;
	//g_MouseMove.y = g_MousePos.y - OldMousePos.y;
	//g_MouseMove.z = g_MousePos.z - OldMousePos.z;

}

//=============================================
//�L�[�{�[�h�̏����擾
//=============================================
bool GetMousePress(int nKey)
{
	return(g_zdiMouseState.rgbButtons[nKey] & 0x80) != 0;
}
bool GetMouseTrigger(int nKey)
{
	return(g_zdiMouseStateTrigger.rgbButtons[nKey] & 0x80) != 0;
}
DIMOUSESTATE GetMouseState(void)
{
	return g_zdiMouseState;
}

//===========================================================================================================================================================================
//PAD
//===========================================================================================================================================================================

//=============================================
//joy�p�b�h������
//=============================================
HRESULT InitJoypad(void)
{
	//�������̃N���A
	memset(&g_joyKeyState, 0, sizeof(XINPUT_STATE));

	//�������̃N���A
	memset(&g_JoypadMotor, 0, sizeof(XINPUT_VIBRATION));

	//XInput�̃X�e�[�g��ݒ�(�L���ɂ���)
	XInputEnable(true);

	return S_OK;
}

//=============================================
//joy�p�b�h�I��
//=============================================
void UninitJoypad(void)
{
	//XInput�̃X�e�[�g��ݒ�(�����ɂ���)
	XInputEnable(false);
}

//=============================================
// �X�e�B�b�N
//=============================================

// �X�e�B�b�N�̓��͂�����p�b�h�t���O�ɕϊ�
WORD GetJoypadStick(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone)
{
	WORD wButtons = 0;

	if (sThumbY >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_UP;
	}
	else if (sThumbY <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;
	}

	if (sThumbX <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;
	}
	else if (sThumbX >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;
	}

	return wButtons;
}

//=============================================
//�W���C�p�b�h�̍X�V����
//=============================================
void UpdateJoypad(void)
{
	XINPUT_STATE joykeyState; //�W���C�p�b�h�̓��͏��

	//�W���C�p�b�h�̏�Ԃ��擾
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		WORD Button = joykeyState.Gamepad.wButtons;
		WORD OldButton = g_joyKeyState.Gamepad.wButtons;
		g_joyKeyStateTrigger.Gamepad.wButtons = Button & ~OldButton;    // �g���K�[����
		g_ajoyKeyStateRelease.Gamepad.wButtons = ~Button & OldButton;    // �����[�X����
		joykeyState.Gamepad.wButtons |= GetJoypadStick(g_joyKeyState.Gamepad.sThumbLX, g_joyKeyState.Gamepad.sThumbLY, JOYPAD_ZONE);

		// ���݂̎��Ԃ��擾����
		g_aJoypadCurrentTime.Gamepad.wButtons = timeGetTime();

		if (joykeyState.Gamepad.wButtons && ((g_aJoypadCurrentTime.Gamepad.wButtons - g_aJoypadExecLastTime.Gamepad.wButtons) > JOYPAD_SPEED))
		{
			// �Ō�ɐ^��Ԃ������Ԃ�ۑ�
			g_aJoypadExecLastTime.Gamepad.wButtons = g_aJoypadCurrentTime.Gamepad.wButtons;

			// �L�[�{�[�h�̃��s�[�g����ۑ�
			g_joyKeyStateRepeat = joykeyState;
		}
		else
		{
			// �L�[�{�[�h�̃��s�[�g����ۑ�
			g_joyKeyStateRepeat.Gamepad.wButtons = 0;
		}

		g_joyKeyState = joykeyState;                // �v���X����
	}
}

//=====================================
//�W���C�p�b�h�̃v���X�����擾
//=====================================
bool GetJoypadPress(JOYKEY key)
{
	return (g_joyKeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//=====================================
//�W���C�p�b�h�̃g���K�[�����擾
//=====================================
bool GetJoypadTrigger(JOYKEY key)
{
	return (g_joyKeyStateTrigger.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//=====================================
//�W���C�p�b�h�̃��s�[�g�����擾
//=====================================
bool GetJoypadRepeat(JOYKEY key)
{
	//�L�[�������Ă����
	if (GetJoypadPress(key) == true)
	{
		if (GetJoypadTrigger(key) == true)
		{
			g_nCntkey = 0;
			return true;
		}

		g_nCntkey++; //�����Ă���Ԃ��J�E���g

		if (g_nCntkey >= JOYPAD_SPEED) //�����������
		{
			g_nCntkey = 0;
			return true;
		}
	}

	// ������΂�����
}

void UpdateStick(void)
{
	//�L�[�{�[�h�̏�Ԃ��擾
	if (XInputGetState(0, &g_XInput) == ERROR_SUCCESS)
	{
		for (int nCntStick = 0; nCntStick < STICKTYPE_MAX; nCntStick++)
		{
			float fX, fY; //�X�e�B�b�N��X���AY��

			switch (nCntStick)
			{
			case STICKTYPE_LEFT:
				fX = (GetXInputState()->Gamepad.sThumbLX);
				fY = (GetXInputState()->Gamepad.sThumbLY);
				break;
			case STICKTYPE_RIGHT:
				fX = (GetXInputState()->Gamepad.sThumbRX);
				fY = (GetXInputState()->Gamepad.sThumbRY);
				break;
			}

			//�p�x���擾
			g_stick.afAngle[nCntStick] = FindAngle(D3DXVECTOR3(fX, fY, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f)) * -1;

			//�X�e�B�b�N�̓|������擾
			g_stick.afTplDiameter[nCntStick] = fabsf(fX);

			if (g_stick.afTplDiameter[nCntStick] < fabsf(fY))
			{
				g_stick.afTplDiameter[nCntStick] = fabsf(fY);
			}

			g_stick.afTplDiameter[nCntStick] /= 32768.0f; //�|���Ă����Ԃ̏����l

			//�������̓t���O��������
			for (int nCntAngle = 0; nCntAngle < STICKANGLE_MAX; nCntAngle++)
			{
				g_bAngle[nCntStick][nCntAngle] = false;
			}

			if (g_stick.afTplDiameter[nCntStick] > 0.1f)
			{
				//�p�x���l�����ŏ�Ɉʒu���鎞�A��t���O��^�ɂ���
				if ((g_stick.afAngle[nCntStick] < D3DX_PI * -0.75) || (g_stick.afAngle[nCntStick] > D3DX_PI * 0.75))
				{
					g_bAngle[nCntStick][STICKANGLE_UP] = true;
				}

				//�p�x���l�����ŉ��Ɉʒu���鎞�A���t���O��^�ɂ���
				else if ((g_stick.afAngle[nCntStick] > D3DX_PI * -0.25) && (g_stick.afAngle[nCntStick] < D3DX_PI * 0.25))
				{
					g_bAngle[nCntStick][STICKANGLE_DOWN] = true;
				}

				//�p�x���l�����ō��Ɉʒu���鎞�A���t���O��^�ɂ���
				else if ((g_stick.afAngle[nCntStick] > D3DX_PI * -0.75) && (g_stick.afAngle[nCntStick] < D3DX_PI * -0.25))
				{
					g_bAngle[nCntStick][STICKANGLE_LEFT] = true;
				}

				//�p�x���l�����ŉE�Ɉʒu���鎞�A�E�t���O��^�ɂ���
				else if ((g_stick.afAngle[nCntStick] > D3DX_PI * 0.25) && (g_stick.afAngle[nCntStick] < D3DX_PI * 0.75))
				{
					g_bAngle[nCntStick][STICKANGLE_RIGHT] = true;
				}
			}

			//�p�x�ɉ��������͏���
			for (int nCntAngle = 0; nCntAngle < STICKANGLE_MAX; nCntAngle++)
			{
				//�X�e�B�b�N�̃g���K�[����ۑ�
				g_stick.abAngleTrigger[nCntStick][nCntAngle] = (g_stick.abAnglePress[nCntStick][nCntAngle] ^ g_bAngle[nCntStick][nCntAngle]) & g_bAngle[nCntStick][nCntAngle];

				//�X�e�B�b�N�̃����[�X����ۑ�
				g_stick.abAngleRelease[nCntStick][nCntAngle] = (g_stick.abAnglePress[nCntStick][nCntAngle] ^ g_bAngle[nCntStick][nCntAngle]) & ~g_bAngle[nCntStick][nCntAngle];

				//���݂̎��Ԃ��擾
				g_aStickCurrentTime[nCntStick][nCntAngle] = timeGetTime();

				if (g_bAngle[nCntStick][nCntAngle] && ((g_aStickCurrentTime[nCntStick][nCntAngle] - g_aStickExecLastTime[nCntStick][nCntAngle]) > JOYPAD_SPEED))
				{
					//�Ō�ɐ^��Ԃ������Ԃ�ۑ�
					g_aStickExecLastTime[nCntStick][nCntAngle] = g_aStickCurrentTime[nCntStick][nCntAngle];

					//�X�e�B�b�N�̃��s�[�g����ۑ�
					g_stick.abAngleRepeat[nCntStick][nCntAngle] = g_bAngle[nCntStick][nCntAngle];
				}
				else
				{
					//�X�e�B�b�N�̃��s�[�g����ۑ�
					g_stick.abAngleRepeat[nCntStick][nCntAngle] = 0;
				}

				//�X�e�B�b�N�̃v���X����ۑ�
				g_stick.abAnglePress[nCntStick][nCntAngle] = g_bAngle[nCntStick][nCntAngle];
			}
		}
	}
}

//2�_�̊p�x�����߂�
float FindAngle(D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos)
{
	float fAngle; //�p�x

	fAngle = atan2f(TargetPos.y - pos.y, TargetPos.x - pos.x);

	fAngle -= (D3DX_PI * 0.5f);
	fAngle *= -1.0f;

	return fAngle;
}

// �R���g���[���[�̓��͏��̎擾
XINPUT_STATE* GetXInputState(void)
{
	return &g_XInput;
}

// �X�e�B�b�N�̓��͏����擾
STICKINPUT GetStick(void)
{
	return g_stick;
}