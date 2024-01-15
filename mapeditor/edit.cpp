//=============================================
//
//STGtest[edit.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "edit.h"
#include "model.h"
#include "input.h"
#include "camera.h"
#include "cursor.h"
#include <string.h>
#include <stdio.h>
//�}�N����`
#define NUM_KEY_MAX	(256)
#define MOVE_CURSOR	(2.0f) //�J�[�\���ړ��l
#define EDIT_WIDE	(1280) //�G��u����ő�l
#define EDIT_HEIGHT	(700) //�G��u����ő�l
#define ENEMY_LIFE	(3) //�G�̃��C�t
#define TIME_CHANGE	(5) //���Ԃ�i�߂�
#define EDIT_SELECT	(2) //�G�f�B�b�g�Z���N�g���i�G�E�u���b�N�j
#define NUM_TYPE_EDIT	(2) //�G�f�B�b�g�Œu������ (���f��)

//=============================================
//�O���[�o���ϐ�
//=============================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEdit = NULL;
LPDIRECT3DTEXTURE9 g_apTextureEdit[NUM_TYPE_EDIT][NUM_TEXTURE] = {}; //�e�N�X�`���|�C���^
Edit g_Edit; //�G�f�B�b�g���
LPD3DXMESH g_apMeshEditModel[NUM_MODEL];
LPD3DXBUFFER g_apBuffMatEditModel[NUM_MODEL];
DWORD g_anNumMatEditModel[NUM_MODEL];
EditModelInfo g_EditModelInfo[MAX_MODEL]; //���f���̃G�f�B�b�g���

bool g_bSave = true; //�Z�[�u�ł��邩
int g_nSaveModelCnt;
int g_nSave;
float g_fAlpha; //���l
float g_fFlash; //�_��
int g_nEditModelNumber; //�Ǐ]����J�����̑Ώ�

//=============================================
//���f���̎��
//=============================================
static const char* MODEL_NAME[NUM_MODEL] =
{
	"data\\MODEL\\iwa.x",
	"data\\MODEL\\hyoshiki.x"
};

//=============================================
//�G�f�B�b�g�̏���������
//=============================================
void InitEdit(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//int nCntEdit;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_Edit.EditType = EDITTYPE_MODEL;

	//�u���b�N�ɏ������ޏ��̏�����
	g_EditModelInfo[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_EditModelInfo[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_EditModelInfo[0].nType = 0;
	g_EditModelInfo[0].bUse = true;
	g_EditModelInfo[0].bUseGame = true;

	for (int nCnt = 1; nCnt < MAX_MODEL; nCnt++)
	{
		g_EditModelInfo[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_EditModelInfo[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_EditModelInfo[nCnt].nType = 0;
		g_EditModelInfo[nCnt].bUse = false;
		g_EditModelInfo[nCnt].bUseGame = false;
	}

	for (int nCnt = 0; nCnt < NUM_MODEL; nCnt++)
	{
		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(MODEL_NAME[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_apBuffMatEditModel[nCnt],
			NULL,
			&g_anNumMatEditModel[nCnt],
			&g_apMeshEditModel[nCnt]);


		D3DXMATERIAL* pMat; //�}�e���A���|�C���^
		pMat = (D3DXMATERIAL*)g_apBuffMatEditModel[nCnt]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_anNumMatEditModel[nCnt]; nCntMat++)
		{

			g_EditModelInfo[nCnt].Diffuse[nCntMat] = pMat[nCntMat].MatD3D.Diffuse;
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_apTextureEdit[nCnt][nCntMat]
				);
			}
		}
	}

	g_fAlpha = 0.2f;
	g_fFlash = 0.02f;
	g_nEditModelNumber = 0;
	g_nSaveModelCnt = 0;
	g_nSave = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_MODEL, D3DUSAGE_WRITEONLY, 4, D3DPOOL_MANAGED, &g_pVtxBuffEdit, NULL);

	VERTEX_3D* pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffEdit->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);


		//if (g_EditModelInfo[g_nSaveModelCnt].nType == BLOCKTYPE_SNOW)
		//{
		//	//�e�N�X�`�����W�̐ݒ�
		//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		//	pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		//	pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);
		//}
		//else
		//{
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		//}

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEdit->Unlock();
}

//=============================================
//�I������
//=============================================
void UninitEdit(void)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		//���b�V���̔j��
		if (g_apMeshEditModel[g_EditModelInfo[nCnt].nType] != NULL)
		{
			g_apMeshEditModel[g_EditModelInfo[nCnt].nType]->Release();
			g_apMeshEditModel[g_EditModelInfo[nCnt].nType] = NULL;
		}

		//�}�e���A���̔j��
		if (g_apBuffMatEditModel[g_EditModelInfo[nCnt].nType] != NULL)
		{
			g_apBuffMatEditModel[g_EditModelInfo[nCnt].nType]->Release();
			g_apBuffMatEditModel[g_EditModelInfo[nCnt].nType] = NULL;
		}
	}
}

//=============================================
//�X�V����
//=============================================
void UpdateEdit(void)
{
	//�ݒu������̂̑I��
	if (GetKeyboardTrigger(DIK_1) == true)
	{
		g_Edit.EditType = EDITTYPE_MODEL;
		g_nEditModelNumber = g_nSaveModelCnt;
	}

	else if (GetKeyboardTrigger(DIK_2) == true)
	{
		g_Edit.EditType = EDITTYPE_CORRECTIONMODEL;
	}

	if (g_Edit.EditType == EDITTYPE_MODEL)
	{//�I�u�W�F�N�g
		SaveModel();
	}
	else if (g_Edit.EditType == EDITTYPE_CORRECTIONMODEL)
	{//�I�u�W�F�N�g�u���Ȃ���
		CorrectionModel();
	}


	Camera* pCamera = GetCamera();

	if (pCamera->type == CAMERATYPE_EDIT)
	{

		pCamera->posV = D3DXVECTOR3(g_EditModelInfo->pos.x - sinf(pCamera->rot.y) * 200.0f, g_EditModelInfo->pos.y + 100.0f, g_EditModelInfo->pos.z - cosf(pCamera->rot.y) * 200.0f);
		pCamera->posR = g_EditModelInfo->pos;

	}
}

//=============================================
//���f���̃Z�[�u����
//=============================================
void SaveModel(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//int nCntEdit;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//Enemy* pEnemy = GetEnemy();
	VERTEX_3D* pVtx;
	g_pVtxBuffEdit->Lock(0, 0, (void**)&pVtx, 0);

	if (GetKeyboardPress(DIK_W) == true)
	{
		g_EditModelInfo[g_nEditModelNumber].pos.z += MOVE_CURSOR
			;
	}
	if (GetKeyboardPress(DIK_S) == true)
	{
		g_EditModelInfo[g_nEditModelNumber].pos.z -= MOVE_CURSOR;
	}
	if (GetKeyboardPress(DIK_A) == true)
	{
		g_EditModelInfo[g_nEditModelNumber].pos.x -= MOVE_CURSOR;
	}
	if (GetKeyboardPress(DIK_D) == true)
	{
		g_EditModelInfo[g_nEditModelNumber].pos.x += MOVE_CURSOR;
	}

	if (GetKeyboardTrigger(DIK_RIGHT) == true)
	{
		g_EditModelInfo[g_nEditModelNumber].nType++;
		if (g_EditModelInfo[g_nEditModelNumber].nType >= NUM_MODEL)
		{
			g_EditModelInfo[g_nEditModelNumber].nType = 0;
		}
	}
	else if (GetKeyboardTrigger(DIK_LEFT) == true)
	{
		g_EditModelInfo[g_nEditModelNumber].nType--;
		if (g_EditModelInfo[g_nEditModelNumber].nType < 0)
		{
			g_EditModelInfo[g_nEditModelNumber].nType = NUM_MODEL -1;
		}
	}

	//���f���̐ݒu
	if (GetKeyboardTrigger(DIK_0) == true)
	{
		g_EditModelInfo[g_nEditModelNumber + 1].pos = g_EditModelInfo[g_nEditModelNumber].pos;
		g_EditModelInfo[g_nEditModelNumber + 1].rot = g_EditModelInfo[g_nEditModelNumber].rot;
		g_EditModelInfo[g_nEditModelNumber + 1].nType = g_EditModelInfo[g_nEditModelNumber].nType;
		g_EditModelInfo[g_nEditModelNumber + 1].bUse = true;
		g_EditModelInfo[g_nEditModelNumber].bUseGame = true;
		g_nSaveModelCnt++;
		g_nEditModelNumber++;
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);

	////�e�N�X�`�����W�̐ݒ�
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���f���̐ݒu
	if (GetKeyboardTrigger(DIK_F4) == true)
	{//�Z�[�u����
		int nNumEnemy = 0;
		bool bSave = false;
		char aSave[256];
		FILE* pFile = fopen(MODEL_FILE_BIN, "wb");


		for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
		{
			if (g_EditModelInfo[nCnt].bUseGame == true)
			{
				nNumEnemy++;
			}
		}

		if (pFile != NULL)
		{
			fwrite(&nNumEnemy, sizeof(int), 1, pFile);

			for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
			{
				if (g_EditModelInfo[nCnt].bUseGame == true)
				{
					fwrite(&g_EditModelInfo[nCnt], sizeof(EditModelInfo), 1, pFile);
				}
			}
			fclose(pFile);

			//�Z�[�u����
			bSave = true;

		}
	}
}

//=============================================
//�u�������f���̕ҏW
//=============================================
void CorrectionModel(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//int nCntEdit;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//Enemy* pEnemy = GetEnemy();
	VERTEX_3D* pVtx;
	g_pVtxBuffEdit->Lock(0, 0, (void**)&pVtx, 0);

	if (GetKeyboardTrigger(DIK_UP) == true)
	{
		g_nEditModelNumber++;
		if (g_nEditModelNumber >= g_nSaveModelCnt)
		{
			g_nEditModelNumber = 0;
		}
	}
	else if (GetKeyboardTrigger(DIK_DOWN) == true)
	{
		g_nEditModelNumber--;
		if (g_nEditModelNumber < 0)
		{
			g_nEditModelNumber = g_nSaveModelCnt - 1;
		}
	}

	if (GetKeyboardPress(DIK_W) == true)
	{
		g_EditModelInfo[g_nEditModelNumber].pos.z += MOVE_CURSOR
			;
	}
	if (GetKeyboardPress(DIK_S) == true)
	{
		g_EditModelInfo[g_nEditModelNumber].pos.z -= MOVE_CURSOR;
	}
	if (GetKeyboardPress(DIK_A) == true)
	{
		g_EditModelInfo[g_nEditModelNumber].pos.x -= MOVE_CURSOR;
	}
	if (GetKeyboardPress(DIK_D) == true)
	{
		g_EditModelInfo[g_nEditModelNumber].pos.x += MOVE_CURSOR;
	}

	if (GetKeyboardTrigger(DIK_RIGHT) == true)
	{
		g_EditModelInfo[g_nEditModelNumber].nType++;
		if (g_EditModelInfo[g_nEditModelNumber].nType >= NUM_MODEL)
		{
			g_EditModelInfo[g_nEditModelNumber].nType = 0;
		}
	}
	else if (GetKeyboardTrigger(DIK_LEFT) == true)
	{
		g_EditModelInfo[g_nEditModelNumber].nType--;
		if (g_EditModelInfo[g_nEditModelNumber].nType < 0)
		{
			g_EditModelInfo[g_nEditModelNumber].nType = NUM_MODEL - 1;
		}
	}

	//���f���̐ݒu
	if (GetKeyboardTrigger(DIK_0) == true)
	{
		g_EditModelInfo[g_nEditModelNumber].bUseGame = true;
	}

	if (GetKeyboardTrigger(DIK_F4) == true)
	{//�Z�[�u����
		int nNumEnemy = 0;
		bool bSave = false;
		char aSave[256];
		FILE* pFile = fopen(MODEL_FILE_BIN, "wb");


		for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
		{
			if (g_EditModelInfo[nCnt].bUseGame == true)
			{
				nNumEnemy++;
			}
		}

		if (pFile != NULL)
		{
			fwrite(&nNumEnemy, sizeof(int), 1, pFile);

			for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
			{
				if (g_EditModelInfo[nCnt].bUseGame == true)
				{
					fwrite(&g_EditModelInfo[nCnt], sizeof(EditModelInfo), 1, pFile);
				}
			}
			fclose(pFile);

			//�Z�[�u����
			bSave = true;
		}
	}
}
//=============================================
//�G�̓r������Z�[�u����
//=============================================
void reSaveModel(void)
{
	//�t�@�C���̓ǂݍ���
	FILE* pFile = fopen(MODEL_FILE_BIN, "rb");

	if (pFile != NULL)
	{
		//�G�̎g�p���Ă鐔�̓ǂݍ���
		fread(&g_nSaveModelCnt, sizeof(int), 1, pFile);

		//�G�̎g�p�����A�G�̓ǂݍ���
		fread(&g_EditModelInfo[0], sizeof(EditModelInfo), g_nSaveModelCnt, pFile);

		//�t�@�C�������
		fclose(pFile);
	}

	else
	{
		return;
	}

	for (int nCntUseModel = 0; nCntUseModel < MAX_MODEL; nCntUseModel++)
	{
		if (g_EditModelInfo[nCntUseModel].bUse == true)
		{
			g_nEditModelNumber++;
		}
	}

	g_EditModelInfo[g_nEditModelNumber].bUse = true; //�ۑ�����Ă�Ō�̃��f���̎��̂��true��
}

//=============================================
//�`�揈��
//=============================================
void DrawEdit(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//int nCntEdit;
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef; //���݂̃}�e���A���̕ۑ�
	//���݂��擾
	pDevice->GetMaterial(&matDef);

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_EditModelInfo[nCnt].bUse == true)
		{
			//�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_EditModelInfo[nCnt].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_EditModelInfo[nCnt].rot.y, g_EditModelInfo[nCnt].rot.x, g_EditModelInfo[nCnt].rot.z);

			D3DXMatrixMultiply(&g_EditModelInfo[nCnt].mtxWorld, &g_EditModelInfo[nCnt].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_EditModelInfo[nCnt].pos.x, g_EditModelInfo[nCnt].pos.y, g_EditModelInfo[nCnt].pos.z);

			D3DXMatrixMultiply(&g_EditModelInfo[nCnt].mtxWorld, &g_EditModelInfo[nCnt].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_EditModelInfo[nCnt].mtxWorld);

			D3DXMATERIAL* pMat; //�}�e���A��

			pMat = (D3DXMATERIAL*)g_apBuffMatEditModel[g_EditModelInfo[nCnt].nType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_anNumMatEditModel[g_EditModelInfo[nCnt].nType]; nCntMat++)
			{
				//if (nCntFrame == 60)
				//{
					//pMat[nCntMat].MatD3D.Diffuse.r = 1.0f;
					//pMat[nCntMat].MatD3D.Diffuse.g = 0.0f;
					//pMat[nCntMat].MatD3D.Diffuse.b = 0.0f;
					//pMat[nCntMat].MatD3D.Diffuse.a = 1.0f;
				//}

				//���̐F�ɖ߂�
				//pMat[nCntMat].MatD3D.Diffuse = g_EditModelInfo[nCnt].Diffuse[nCntMat];
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0,g_apTextureEdit[g_EditModelInfo[nCnt].nType][nCntMat]);

				//�p�[�c�̐ݒ�
				g_apMeshEditModel[g_EditModelInfo[nCnt].nType]->DrawSubset(nCntMat);
			}
		}
	}

	//�ۑ����Ă��}�e���A����߂�
	pDevice->SetMaterial(&matDef);

	SetCursor(D3DXVECTOR3(g_EditModelInfo[g_nEditModelNumber].pos.x, 40.0f, g_EditModelInfo[g_nEditModelNumber].pos.z));
}

//=============================================
//�G�f�B�b�g�̃f�o�b�O�\���i��ɑ�������j
//=============================================
void DebagEdit(void)
{
	LPD3DXFONT pFont = GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "������@\n[�J�����ړ�]\n�O�i:I ��i:K ��:J �E:L\n���f���ݒu���[�h:1	���f���ҏW���[�h:2\n���̐ݒu:0\n���̈ړ�	�O�i:W ��i:S ��:A �E:D\n�^�C�v�̐؂�ւ���or��");

	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

EditModelInfo* GetEditModelinfo(void)
{
	return &g_EditModelInfo[0];
}