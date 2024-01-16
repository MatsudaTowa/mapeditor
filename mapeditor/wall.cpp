//=============================================
//
//�}�b�v�G�f�B�^�[[wall.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "wall.h"
#include "input.h"
//#include "enemy.h"
//#include "Screen.h"
//#include"bullet.h"

//=============================================
//�O���[�o���ϐ�
//=============================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL; //�e�N�X�`���|�C���^
//D3DXVECTOR3 g_movewall; //�ړ���
D3DXMATRIX	g_mtxWorldWall;
Wall g_aWall[MAX_WALL];


//=============================================
//�|���S���̏���������
//=============================================
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\snow.jpg",
		&g_pTextureWall
	);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL, 
		D3DUSAGE_WRITEONLY, 
		FVF_VERTEX_3D, 
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall, 
		NULL);

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		g_aWall[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCnt].nType = 0;
		g_aWall[nCnt].bUse = false;
	}

	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-500.0f, 200.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(500.0f, 200.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-500.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(500.0f, 0.0f, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`���̍��W�w��
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	g_pVtxBuffWall->Unlock();
}

//=============================================
//�|���S���̏I������
//=============================================
void UninitWall(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//=============================================
//�|���S���̍X�V����
//=============================================
void UpdateWall(void)
{
	/*if (GetKeyboardPress(DIK_UP) == true)
	{
		g_aWall.rot.x += 0.05f;
	}

	if (GetKeyboardPress(DIK_DOWN) == true)
	{
		g_aWall.rot.x -= 0.05f;
	}

	if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_aWall.rot.y -= 0.05f;
	}

	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		g_aWall.rot.y += 0.05f;
	}*/
}

//=============================================
//�|���S���̕`�揈��
//=============================================
void DrawWall(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		if (g_aWall[nCnt].bUse == true)
		{
			//�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldWall);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCnt].rot.y, g_aWall[nCnt].rot.x, g_aWall[nCnt].rot.z);

			D3DXMatrixMultiply(&g_mtxWorldWall, &g_mtxWorldWall, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aWall[nCnt].pos.x, g_aWall[nCnt].pos.y, g_aWall[nCnt].pos.z);

			D3DXMatrixMultiply(&g_mtxWorldWall, &g_mtxWorldWall, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldWall);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureWall);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCnt, 2);

			pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
			pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
		}
	}
}

void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nType)
{
	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		if (g_aWall[nCnt].bUse == false)
		{
			g_aWall[nCnt].pos = pos;
			g_aWall[nCnt].rot = rot;
			g_aWall[nCnt].nType = nType;
			g_aWall[nCnt].bUse = true;
			break;
		}
	}
}

