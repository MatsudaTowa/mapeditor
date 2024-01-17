//=============================================
//
//�}�b�v�G�f�B�^�[[field.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "field.h"
#include "input.h"
//#include "enemy.h"
//#include "Screen.h"
//#include"bullet.h"

//=============================================
//�}�N����`
//=============================================
#define FIELD_WIDE	(500)
#define FIELD_DEPTH	(500)

//=============================================
//�O���[�o���ϐ�
//=============================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField = NULL;
LPDIRECT3DTEXTURE9 g_pTextureField = NULL; //�e�N�X�`���|�C���^
//D3DXVECTOR3 g_movefield; //�ړ���
D3DXMATRIX	g_mtxWorldField;
Field g_field[MAX_FIELD];

//=============================================
//�|���S���̏���������
//=============================================
void InitField(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ground.jpeg",
		&g_pTextureField
	);

	for (int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
	{
		g_field[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //���̏����ʒu
		g_field[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //���̏�������
		g_field[nCnt].fWide = FIELD_WIDE; //���̉���
		g_field[nCnt].fDepth = FIELD_DEPTH; //���̏c��
		g_field[nCnt].bUse = false;
	}
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_FIELD, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffField, NULL);

	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-FIELD_WIDE, 0.0f, FIELD_DEPTH);
		pVtx[1].pos = D3DXVECTOR3(FIELD_WIDE, 0.0f, FIELD_DEPTH);
		pVtx[2].pos = D3DXVECTOR3(-FIELD_WIDE, 0.0f, -FIELD_DEPTH);
		pVtx[3].pos = D3DXVECTOR3(FIELD_WIDE, 0.0f, -FIELD_DEPTH);

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
	g_pVtxBuffField->Unlock();
}

//=============================================
//�|���S���̏I������
//=============================================
void UninitField(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureField != NULL)
	{
		g_pTextureField->Release();
		g_pTextureField = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffField != NULL)
	{
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}
}

//=============================================
//�|���S���̍X�V����
//=============================================
void UpdateField(void)
{
	//if (GetKeyboardPress(DIK_UP) == true)
	//{
	//	g_rotField.x += 0.05f;
	//}

	//if (GetKeyboardPress(DIK_DOWN) == true)
	//{
	//	g_rotField.x -= 0.05f;
	//}

	//if (GetKeyboardPress(DIK_RIGHT) == true)
	//{
	//	g_rotField.y -= 0.05f;
	//}

	//if (GetKeyboardPress(DIK_LEFT) == true)
	//{
	//	g_rotField.y += 0.05f;
	//}
}

//=============================================
//�|���S���̕`�揈��
//=============================================
void DrawField(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X

	for (int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
	{
		if (g_field[nCnt].bUse == true)
		{
			//�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldField);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_field[nCnt].rot.y, g_field[nCnt].rot.x, g_field[nCnt].rot.z);

			D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_field[nCnt].pos.x, g_field[nCnt].pos.y, g_field[nCnt].pos.z);

			D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldField);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffField, 4 * nCnt, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureField);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}
}

D3DXVECTOR3 GetFieldPos(void)
{
	return g_field->pos;
}