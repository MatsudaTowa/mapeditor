//=============================================
//
//3D�e���v���[�g[light.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "light.h"
#include "input.h"

//�}�N����`
#define NUM_LIGHT	(3) //���C�g�̎��

//�O���[�o���ϐ�
D3DLIGHT9 g_aLight[NUM_LIGHT];

//=============================================
//���C�g�̏���������
//=============================================
void InitLight(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXVECTOR3 vecDir; //�ݒ�����x�N�g��

	//���C�g���̃N���A
	ZeroMemory(&g_aLight[0], sizeof(D3DLIGHT9));

	for (int nCnt = 0; nCnt < NUM_LIGHT; nCnt++)
	{
		//���C�g�̎�ނ�ݒ�
		g_aLight[nCnt].Type = D3DLIGHT_DIRECTIONAL;

		//���C�g�̊g�U���̐ݒ�
		g_aLight[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		if (nCnt == 0)
		{
			//���C�g�̕�����ݒ�
			vecDir = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
		}
		else if (nCnt == 1)
		{
			//���C�g�̕�����ݒ�
			vecDir = D3DXVECTOR3(0.2f, 0.8f, 0.4f);
		}
		else if (nCnt == 2)
		{
			//���C�g�̕�����ݒ�
			vecDir = D3DXVECTOR3(-0.7f, -0.8f, -0.4f);
		}



		D3DXVec3Normalize(&vecDir, &vecDir); //���K��

		g_aLight[nCnt].Direction = vecDir;

		//���C�g��ݒ�
		pDevice->SetLight(nCnt, &g_aLight[nCnt]);

		//���C�g��L����
		pDevice->LightEnable(nCnt, TRUE);
	}
}

//=============================================
//���C�g�̏I������
//=============================================
void UninitLight(void)
{
}

//=============================================
//���C�g�̍X�V����
//=============================================
void UpdateLight(void)
{

}