//=============================================
//
//3D�e���v���[�g[shadow.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "shadow.h"
#include "input.h"
//#include "enemy.h"
//#include "Screen.h"
//#include"bullet.h"

//=============================================
//�}�N����`
//=============================================
#define SHADOW_WIDE	(5)
#define SHADOW_DEPTH	(5)

//=============================================
//�O���[�o���ϐ�
//=============================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL; //�e�N�X�`���|�C���^
Shadow g_aShadow[MAX_SHADOW];
//D3DXVECTOR3 g_moveShadow; //�ړ���
D3DXMATRIX	g_mtxWorldShadow;

//=============================================
//�e�̏���������
//=============================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\shadow000.jpg",
		&g_pTextureShadow
	);

	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		g_aShadow[nCnt].pos = D3DXVECTOR3(0.0f, 0.05f, 0.0f); //�v���C���[�̏����ʒu
		g_aShadow[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�����̈ړ����x
		g_aShadow[nCnt].fRadius = SHADOW_WIDE; //�����̈ړ����x
		g_aShadow[nCnt].nNumber = -1; //�����̈ړ����x
		g_aShadow[nCnt].bUse = false; //�����̈ړ����x
	}
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW, 
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED, 
			&g_pVtxBuffShadow, 
			NULL);

		VERTEX_3D* pVtx;

		//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
		g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-g_aShadow[nCnt].fRadius, 0.0f, g_aShadow[nCnt].fRadius);
		pVtx[1].pos = D3DXVECTOR3(g_aShadow[nCnt].fRadius, 0.0f, g_aShadow[nCnt].fRadius);
		pVtx[2].pos = D3DXVECTOR3(-g_aShadow[nCnt].fRadius, 0.0f, -g_aShadow[nCnt].fRadius);
		pVtx[3].pos = D3DXVECTOR3(g_aShadow[nCnt].fRadius, 0.0f, -g_aShadow[nCnt].fRadius);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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
	g_pVtxBuffShadow->Unlock();
}

//=============================================
//�e�̏I������
//=============================================
void UninitShadow(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//=============================================
//�e�̍X�V����
//=============================================
void UpdateShadow(void)
{
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		if (g_aShadow[nCnt].bUse == true)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-g_aShadow[nCnt].fRadius, 0.0f, g_aShadow[nCnt].fRadius);
			pVtx[1].pos = D3DXVECTOR3(g_aShadow[nCnt].fRadius, 0.0f, g_aShadow[nCnt].fRadius);
			pVtx[2].pos = D3DXVECTOR3(-g_aShadow[nCnt].fRadius, 0.0f, -g_aShadow[nCnt].fRadius);
			pVtx[3].pos = D3DXVECTOR3(g_aShadow[nCnt].fRadius, 0.0f, -g_aShadow[nCnt].fRadius);

			//�@���x�N�g���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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
	}
	g_pVtxBuffShadow->Unlock();
}

//=============================================
//�e�̕`�揈��
//=============================================
void DrawShadow(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X

	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		if (g_aShadow[nCnt].bUse == true)
		{
			//���Z��������
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);

			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			//�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldShadow);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCnt].rot.y, g_aShadow[nCnt].rot.x, g_aShadow[nCnt].rot.z);

			D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCnt].pos.x, g_aShadow[nCnt].pos.y, g_aShadow[nCnt].pos.z);

			D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldShadow);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureShadow);

			//�e�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCnt, 2);


		}
	}
	//�ʏ�̍����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================
//�e�̐ݒ菈��
//=============================================
int SetShadow(void)
{
	int nCntShadow = -1;
	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		if (g_aShadow[nCnt].bUse == false)
		{
			g_aShadow[nCnt].bUse = true;
			nCntShadow = nCnt;
			break;
		}
	}
	return nCntShadow;
}

//=============================================
//�e�̈ʒu�̐ݒ菈��
//=============================================
void SetShadowPos(int nIdxShadow, D3DXVECTOR3 pos,float fRadius)
{
	g_aShadow[nIdxShadow].pos = pos;

	g_aShadow[nIdxShadow].fRadius = fRadius;
}

Shadow* GetShadow(void)
{
	return &g_aShadow[0];
}

