//=============================================
//
//�}�b�v�G�f�B�^�[[camera.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "camera.h"
#include "input.h"
#include "edit.h"
#include <stdio.h>

#define DAMPING_COEFFICIENT	(0.2f) //��R��
#define TEST_ROT	(0)
#define CAMERA_MOVE	(0.75f)
#define CAMERA_SPEED	(5.0f) //�Ǐ]

//�O���[�o���ϐ�
Camera g_Camera; //�J�������
bool g_bType;

//=============================================
//�J�����̏���������
//=============================================
void InitCamera(void)
{
	g_Camera.posV = D3DXVECTOR3(0.0f, 1020.0f, -13.0f); //���_
	g_Camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //����
	g_Camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_Camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.moveV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.moveR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.rotmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.type = CAMERATYPE_DEFAULT;

	//�Ίp���̒������Z�o����
//	g_Camera.fLength = sqrtf(100.0f * 100.0f + (-PLAYER_LENGTH_Z) * (-PLAYER_LENGTH_Z)) / 2.0f;

	D3DXVECTOR3 vecCamera = g_Camera.posR - g_Camera.posV;
	g_Camera.fLength = sqrtf(vecCamera.y * vecCamera.y + vecCamera.z * vecCamera.z);

	//�Ίp���̊p�x���Z�o����
	g_Camera.fAngle = atan2f(vecCamera.y, vecCamera.z);

	g_bType = false;

}

//=============================================
//�J�����̏I������
//=============================================
void UninitCamera(void)
{

}

//=============================================
//�J�����̍X�V����
//=============================================
void UpdateCamera(void)
{

	D3DXVECTOR3 vecCamera = g_Camera.posR - g_Camera.posV;
	//g_Camera.fLength = sqrtf(vecCamera.y * vecCamera.y + vecCamera.z * vecCamera.z);


	if (g_Camera.rot.y > D3DX_PI)
	{
		g_Camera.rot.y = -D3DX_PI;
		//		g_Camera.rot.y -= D3DX_PI* 2.0f;
	}

	if (g_Camera.rot.y < -D3DX_PI)
	{
		g_Camera.rot.y = D3DX_PI;
	}

	if (g_Camera.rot.x > D3DX_PI)
	{
		g_Camera.rot.x = -D3DX_PI;
		//		g_Camera.rot.y -= D3DX_PI* 2.0f;
	}

	if (g_Camera.rot.x < -D3DX_PI)
	{
		g_Camera.rot.x = D3DX_PI;
	}

	//D3DXVec3Normalize(&vec, &vec);

	//g_Camera.fAngle = atan2f(x, z) + ((D3DX_PI * 0.05f) * vec.x);

#ifdef _DEBUG

	if (GetKeyboardTrigger(DIK_F11) == true)
	{
		if (g_Camera.type != CAMERATYPE_TURN)
		{
			g_Camera.type = CAMERATYPE_TURN;
		}
		else
		{
			g_Camera.type = CAMERATYPE_DEFAULT;
		}
	}
	if (GetKeyboardTrigger(DIK_F10) == true)
	{
		if (g_Camera.type != CAMERATYPE_EDIT)
		{
			g_Camera.type = CAMERATYPE_EDIT;
		}
		else
		{
			g_Camera.type = CAMERATYPE_DEFAULT;
		}
	}

#endif // DEBUG
	if (g_Camera.type == CAMERATYPE_DEFAULT)
	{
		if (GetKeyboardPress(DIK_J) == true)
		{
			g_Camera.moveV.x -= sinf(D3DX_PI / 2 + g_Camera.rot.y) * CAMERA_MOVE;
			g_Camera.moveR.x -= sinf(D3DX_PI / 2 + g_Camera.rot.y) * CAMERA_MOVE;

			g_Camera.moveV.z -= cosf(D3DX_PI / 2 + g_Camera.rot.y) * CAMERA_MOVE;
			g_Camera.moveR.z -= cosf(D3DX_PI / 2 + g_Camera.rot.y) * CAMERA_MOVE;

		}

		if (GetKeyboardPress(DIK_L) == true)
		{
			g_Camera.moveV.x += sinf(D3DX_PI / 2 + g_Camera.rot.y) * CAMERA_MOVE;
			g_Camera.moveR.x += sinf(D3DX_PI / 2 + g_Camera.rot.y) * CAMERA_MOVE;

			g_Camera.moveV.z += cosf(D3DX_PI / 2 + g_Camera.rot.y) * CAMERA_MOVE;
			g_Camera.moveR.z += cosf(D3DX_PI / 2 + g_Camera.rot.y) * CAMERA_MOVE;

		}


		if (GetKeyboardPress(DIK_I) == true)
		{
			g_Camera.moveV.x -= sinf(D3DX_PI + g_Camera.rot.y) * CAMERA_MOVE;
			g_Camera.moveR.x -= sinf(D3DX_PI + g_Camera.rot.y) * CAMERA_MOVE;

			g_Camera.moveV.z -= cosf(D3DX_PI + g_Camera.rot.y) * CAMERA_MOVE;
			g_Camera.moveR.z -= cosf(D3DX_PI + g_Camera.rot.y) * CAMERA_MOVE;

		}

		if (GetKeyboardPress(DIK_K) == true)
		{
			g_Camera.moveV.x += sinf(D3DX_PI + g_Camera.rot.y) * CAMERA_MOVE;
			g_Camera.moveR.x += sinf(D3DX_PI + g_Camera.rot.y) * CAMERA_MOVE;

			g_Camera.moveV.z += cosf(D3DX_PI + g_Camera.rot.y) * CAMERA_MOVE;
			g_Camera.moveR.z += cosf(D3DX_PI + g_Camera.rot.y) * CAMERA_MOVE;

		}

		if (GetKeyboardPress(DIK_Q) == true || GetJoypadPress(JOYKEY_LB) == true)
		{
#if TEST_ROT
			g_Camera.rot.y -= 0.02f;

			g_Camera.fAngle -= 0.02f;

			g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.rot.y) * g_Camera.fLength;
			g_Camera.posR.y = g_Camera.posV.y - 100;
			g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.rot.y) * g_Camera.fLength;
#else
			g_Camera.rot.y -= 0.02f;


			g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.rot.y) * g_Camera.fLength;
			g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.rot.y) * g_Camera.fLength;
#endif
		}

		if (GetKeyboardPress(DIK_E) == true || GetJoypadPress(JOYKEY_B) == true)
		{
#if TEST_ROT

			g_Camera.rot.y += 0.02f;

			g_Camera.fAngle += 0.02f;

			g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.fAngle) * g_Camera.fLength;
			g_Camera.posR.y = g_Camera.posV.y - 100;
			g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.fAngle) * g_Camera.fLength;
#else
			g_Camera.rot.y += 0.02f;

			g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.rot.y) * g_Camera.fLength;
			g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.rot.y) * g_Camera.fLength;
#endif
		}

		if (GetKeyboardPress(DIK_U) == true || GetJoypadPress(JOYKEY_LB) == true)
		{
			g_Camera.rot.y-= 0.02f;
			g_Camera.posV.x = g_Camera.posR.x - sinf(g_Camera.rot.y) * g_Camera.fLength;
			g_Camera.posV.z = g_Camera.posR.z - cosf(g_Camera.rot.y) * g_Camera.fLength;
		}

		if (GetKeyboardPress(DIK_O) == true || GetJoypadPress(JOYKEY_RB) == true)
		{
			g_Camera.rot.y += 0.02f;
			g_Camera.posV.x = g_Camera.posR.x - sinf(g_Camera.rot.y) * g_Camera.fLength;
			g_Camera.posV.z = g_Camera.posR.z - cosf(g_Camera.rot.y) * g_Camera.fLength;
		}

		if (GetKeyboardPress(DIK_T) == true)
		{
			g_Camera.rot.x += 0.02f;
			g_Camera.posV.y = g_Camera.posR.y - sinf(g_Camera.rot.x) * g_Camera.fLength;
			g_Camera.posV.z = g_Camera.posR.z - cosf(g_Camera.rot.x) * g_Camera.fLength;
		}
		if (GetKeyboardPress(DIK_Y) == true)
		{
			g_Camera.rot.x -= 0.02f;
			g_Camera.posV.y = g_Camera.posR.y - sinf(g_Camera.rot.x) * g_Camera.fLength;
			g_Camera.posV.z = g_Camera.posR.z - cosf(g_Camera.rot.x) * g_Camera.fLength;
		}
	}

	else if (g_Camera.type == CAMERATYPE_EDIT)
	{
		EditCamera();
	}

	g_Camera.posV += g_Camera.moveV;
	g_Camera.posR += g_Camera.moveR;

	//�ړ��ʂ��X�V(�����j
	g_Camera.moveV.x += (0.0f - g_Camera.moveV.x) * DAMPING_COEFFICIENT;
	g_Camera.moveV.y += (0.0f - g_Camera.moveV.y) * DAMPING_COEFFICIENT;
	g_Camera.moveV.z += (0.0f - g_Camera.moveV.z) * DAMPING_COEFFICIENT;

	g_Camera.moveR.x += (0.0f - g_Camera.moveR.x) * DAMPING_COEFFICIENT;
	g_Camera.moveR.y += (0.0f - g_Camera.moveR.y) * DAMPING_COEFFICIENT;
	g_Camera.moveR.z += (0.0f - g_Camera.moveR.z) * DAMPING_COEFFICIENT;

	//g_Camera.pos = pPlayer->pos;

}

//=============================================
//�G�f�B�b�g�J�[�\���Ǐ]
//=============================================
void EditCamera(void)
{
	EditModelInfo* pEditModel = GetEditModelinfo();
	Edit* pEdit = GetEdit();

	g_Camera.posR = pEditModel[pEdit->nEditModelNumber].pos;

	if (GetKeyboardPress(DIK_Q) == true || GetJoypadPress(JOYKEY_X) == true)
	{
		g_Camera.rot.y -= 0.02f;
	}

	if (GetKeyboardPress(DIK_E) == true || GetJoypadPress(JOYKEY_B) == true)
	{
		g_Camera.rot.y += 0.02f;
	}

	if (GetKeyboardPress(DIK_U) == true || GetJoypadPress(JOYKEY_LB) == true)
	{
		g_Camera.rot.y -= 0.02f;
		g_Camera.posV.x = g_Camera.posR.x - sinf(g_Camera.rot.y) * PLAYER_LENGTH_Z;
		g_Camera.posV.z = g_Camera.posR.z - cosf(g_Camera.rot.y) * PLAYER_LENGTH_Z;
	}

	if (GetKeyboardPress(DIK_O) == true || GetJoypadPress(JOYKEY_RB) == true)
	{
		g_Camera.rot.y += 0.02f;
		g_Camera.posV.x = g_Camera.posR.x - sinf(g_Camera.rot.y) * PLAYER_LENGTH_Z;
		g_Camera.posV.z = g_Camera.posR.z - cosf(g_Camera.rot.y) * PLAYER_LENGTH_Z;
	}

	if (GetKeyboardPress(DIK_T) == true)
	{
		g_Camera.rot.x += 0.02f;
		g_Camera.posV.y = g_Camera.posR.y - sinf(g_Camera.rot.x) * PLAYER_LENGTH_Z;
		g_Camera.posV.z = g_Camera.posR.z - cosf(g_Camera.rot.x) * PLAYER_LENGTH_Z;
	}
	if (GetKeyboardPress(DIK_Y) == true)
	{
		g_Camera.rot.x -= 0.02f;
		g_Camera.posV.y = g_Camera.posR.y - sinf(g_Camera.rot.x) * PLAYER_LENGTH_Z;
		g_Camera.posV.z = g_Camera.posR.z - cosf(g_Camera.rot.x) * PLAYER_LENGTH_Z;
	}

}

//=============================================
//������]�̃J����
//=============================================
void TurnCamera(void)
{
	g_Camera.rot.y -= 0.01f;
	g_Camera.posV.x = g_Camera.posR.x - sinf(g_Camera.rot.y) * g_Camera.fLength;
	g_Camera.posV.z = g_Camera.posR.z - cosf(g_Camera.rot.y) * g_Camera.fLength;
}

//=============================================
//�J�����̐ݒ菈��
//=============================================
void SetCamera(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		3000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_Camera.mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera.mtxView);

	D3DXVECTOR3 posV = g_Camera.posV;
	D3DXVECTOR3 posR = g_Camera.posR;

	posV.y += -15.0f;
	posR.y += 0.0f;

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_Camera.mtxView,
		&posV,
		&posR,
		&g_Camera.vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_Camera.mtxView);
}

void DebagCameraPos(void)
{
	LPD3DXFONT pFont = GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n[�J�������]\nposV:%.1f,%.1f,%.1f\nposR:%.1f,%.1f,%.1f", g_Camera.posV.x, g_Camera.posV.y, g_Camera.posV.z
		,g_Camera.posR.x, g_Camera.posR.y, g_Camera.posR.z);

	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

Camera* GetCamera(void)
{
	return &g_Camera;
}