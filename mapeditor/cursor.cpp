//=============================================
//
//�}�b�v�G�f�B�^�[[cursor.h]
//Auther Matsuda Towa
//
//=============================================
#include "cursor.h"

//=============================================
//�}�N����`
//=============================================
#define CURSOR_WIDE	(20)
#define CURSOR_DEPTH	(20)

//=============================================
//�O���[�o���ϐ�
//=============================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCursor = NULL;
LPDIRECT3DTEXTURE9 g_pTextureCursor = NULL; //�e�N�X�`���|�C���^
Cursol g_Cursol; //�J�[�\���̏��̍\����

//=============================================
//�J�[�\���̏�����
//=============================================
void InitCursor(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\cursor.png",
		&g_pTextureCursor
	);

	g_Cursol.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�J�[�\���̏����ʒu
	g_Cursol.IndexEdit = 0; //�J�[�\�������킹�鏉����
	g_Cursol.bUse = false; //�g�p���Ȃ�

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffCursor, NULL);

	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffCursor->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-CURSOR_WIDE, CURSOR_DEPTH, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(CURSOR_WIDE, CURSOR_DEPTH, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-CURSOR_WIDE, -CURSOR_DEPTH, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(CURSOR_WIDE, -CURSOR_DEPTH, 0.0f);

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

	g_pVtxBuffCursor->Unlock();
}

//=============================================
//�J�[�\���̏I������
//=============================================
void UninitCursor(void)
{
	//�e�N�X�`���̔j��g_mtxWorldCursor
	if (g_pTextureCursor != NULL)
	{
		g_pTextureCursor->Release();
		g_pTextureCursor = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffCursor != NULL)
	{
		g_pVtxBuffCursor->Release();
		g_pVtxBuffCursor = NULL;
	}
}

//=============================================
//�J�[�\���̍X�V����
//=============================================
void UpdateCursor(void)
{

}

//=============================================
//�J�[�\���̕`�揈��
//=============================================
void DrawCursor(void)
{

	if (g_Cursol.bUse == true)
	{
		//�f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		D3DXMATRIX mtxTrans; //�v�Z�p�}�g���b�N�X

		D3DXMATRIX mtxView; //�r���[�}�g���b�N�X�擾�p

		//�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Cursol.mtxWorld);

		//�r���[�}�g���b�N�X���擾
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//�|���S���̐��ʂ��J�����Ɍ�����
		D3DXMatrixInverse(&g_Cursol.mtxWorld, NULL, &mtxView);

		g_Cursol.mtxWorld._41 = 0.0f;
		g_Cursol.mtxWorld._42 = 0.0f;
		g_Cursol.mtxWorld._43 = 0.0f;

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Cursol.pos.x, g_Cursol.pos.y, g_Cursol.pos.z);

		D3DXMatrixMultiply(&g_Cursol.mtxWorld, &g_Cursol.mtxWorld, &mtxTrans);

		//���C�g�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Cursol.mtxWorld);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffCursor, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureCursor);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		//���C�g��L���ɖ߂�
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}

//=============================================
//�J�[�\���̐ݒ菈��
//=============================================
void SetCursor(D3DXVECTOR3 pos)
{
	g_Cursol.pos = pos;
	g_Cursol.bUse = true; //�g�p����
}
