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
#include "wall.h"
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
#define NUM_MODEL_EDIT	(2) //�G�f�B�b�g�Œu������ (���f��)
#define NUM_WALL_EDIT	(1) //�G�f�B�b�g�Œu������ (��)

//=============================================
//�O���[�o���ϐ�
//=============================================
LPDIRECT3DTEXTURE9 g_apModelTextureEdit[NUM_MODEL_EDIT][NUM_TEXTURE] = {}; //�e�N�X�`���|�C���^
LPDIRECT3DTEXTURE9 g_apWallTextureEdit[NUM_WALL_EDIT] = {}; //�e�N�X�`���|�C���^
Edit g_Edit; //�G�f�B�b�g���
LPD3DXMESH g_apMeshEditModel[NUM_MODEL]; //���f���̃��b�V�����
LPD3DXBUFFER g_apBuffMatEditModel[NUM_MODEL]; //���f���̒��_�o�b�t�@���
DWORD g_anNumMatEditModel[NUM_MODEL]; //���f���̃}�e���A�����
EditModelInfo g_EditModelInfo[MAX_MODEL]; //���f���̃G�f�B�b�g���

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWallEdit = NULL; //�ǂ̒��_���
D3DXMATRIX	g_mtxWorldWallEdit; //�ǂ̃��[���h�}�g���b�N�X
EditWallInfo g_EditWallInfo[MAX_WALL]; //�ǂ̃G�f�B�b�g���

bool g_bSave = true; //�Z�[�u�ł��邩
int g_nSaveModelCnt;
int g_nSaveWallCnt;
int g_nSave;
float g_fAlpha; //���l
float g_fFlash; //�_��
int g_nEditModelNumber; //�Ǐ]����J�����̑Ώ�
int g_nEditWallNumber; //�Ǐ]����J�����̑Ώ�

//=============================================
//���f���̎��
//=============================================
static const char* MODEL_NAME[NUM_MODEL] =
{
	"data\\MODEL\\iwa.x",
	"data\\MODEL\\hyoshiki.x"
};

//=============================================
//�ǂ̃e�N�X�`���̎��
//=============================================
static const char* WALL_TEX_NAME[NUM_WALL] =
{
	"data\\TEXTURE\\snow.jpg",
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

	//�G�f�B�b�g�̏������[�h�ݒ�
	g_Edit.EditType = EDITTYPE_MODEL;

	//���f���ɏ������ޏ��̏�����
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
					&g_apModelTextureEdit[nCnt][nCntMat]
				);
			}
		}
	}

	g_fAlpha = 0.2f;
	g_fFlash = 0.02f;
	g_nEditModelNumber = 0;
	g_nSaveModelCnt = 0;
	g_nEditWallNumber = 0;
	g_nSaveWallCnt = 0;
	g_nSave = 0;

	for (int nCntWallTex = 0; nCntWallTex < NUM_WALL; nCntWallTex++)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			WALL_TEX_NAME[nCntWallTex],
			&g_apWallTextureEdit[nCntWallTex]
		);
	}

	//�ǂɏ������ޏ��̏�����
	g_EditWallInfo[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_EditWallInfo[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_EditWallInfo[0].nType = 0;
	g_EditWallInfo[0].bUse = true;
	g_EditWallInfo[0].bUseGame = true;

	for (int nCnt = 1; nCnt < MAX_WALL; nCnt++)
	{
		g_EditWallInfo[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_EditWallInfo[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_EditWallInfo[nCnt].nType = 0;
		g_EditWallInfo[nCnt].bUse = false;
		g_EditWallInfo[nCnt].bUseGame = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_MODEL, D3DUSAGE_WRITEONLY, 4, D3DPOOL_MANAGED, &g_pVtxBuffWallEdit, NULL);

	VERTEX_3D* pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffWallEdit->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-WALL_WIDE, WALL_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(WALL_WIDE, WALL_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-WALL_WIDE, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(WALL_WIDE, 0.0f, 0.0f);

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

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffWallEdit->Unlock();
}

//=============================================
//�I������
//=============================================
void UninitEdit(void)
{
	//���f���̔j��
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

	//���f���̔j��
	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_apWallTextureEdit[g_EditWallInfo[nCnt].nType] != NULL)
		{
			g_apWallTextureEdit[g_EditWallInfo[nCnt].nType]->Release();
			g_apWallTextureEdit[g_EditWallInfo[nCnt].nType] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffWallEdit != NULL)
	{
		g_pVtxBuffWallEdit->Release();
		g_pVtxBuffWallEdit = NULL;
	}
}

//=============================================
//�X�V����
//=============================================
void UpdateEdit(void)
{
	Camera* pCamera = GetCamera();
	if (g_fAlpha >= 1.0f || g_fAlpha <= 0.0f)
	{
		g_fFlash *= -1.0f;
	}
	g_fAlpha += g_fFlash;

	if (GetKeyboardTrigger(DIK_1) == true)
	{//���f����ݒu
		g_Edit.EditType = EDITTYPE_MODEL;
		g_nEditModelNumber = g_nSaveModelCnt;

		if (g_EditModelInfo[g_nEditModelNumber].bUseGame == false)
		{
			g_EditModelInfo[g_nEditModelNumber].bUse = true; //���ɐݒu������͕̂\�����Ȃ�
		}
	}


	else if (GetKeyboardTrigger(DIK_2) == true)
	{//���܂Œu�������f���̕ҏW
		g_Edit.EditType = EDITTYPE_CORRECTIONMODEL;
		if (g_EditModelInfo[g_nEditModelNumber].bUseGame == false)
		{
			g_EditModelInfo[g_nEditModelNumber].bUse = false; //���ɐݒu������͕̂\�����Ȃ�
			g_nEditModelNumber--;
		}
	}

	else if (GetKeyboardTrigger(DIK_3) == true)
	{//���܂Œu�������f���̕ҏW
		g_Edit.EditType = EDITTYPE_WALL;
		g_nEditWallNumber = g_nSaveWallCnt;

		if (g_EditWallInfo[g_nEditWallNumber].bUseGame == false)
		{
			g_EditWallInfo[g_nEditWallNumber].bUse = true; //���ɐݒu������͕̂\�����Ȃ�
		}
	}

	if (g_Edit.EditType == EDITTYPE_MODEL)
	{//���f��
		SaveModel();
	}
	else if (g_Edit.EditType == EDITTYPE_CORRECTIONMODEL)
	{//���f���u���Ȃ���
		CorrectionModel();
	}
	else if (g_Edit.EditType == EDITTYPE_WALL)
	{//��
		SaveWall();
	}

	if (GetKeyboardTrigger(DIK_F1) == true)
	{

		pCamera->posV = D3DXVECTOR3(0.0f, 1020.0f, -13.0f);
		pCamera->posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //����

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
	g_pVtxBuffWallEdit->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffWallEdit->Lock(0, 0, (void**)&pVtx, 0);

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
//���f���̓r������Z�[�u����
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
//�ǂ̃Z�[�u����
//=============================================
void SaveWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//int nCntEdit;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//Enemy* pEnemy = GetEnemy();
	VERTEX_3D* pVtx;
	g_pVtxBuffWallEdit->Lock(0, 0, (void**)&pVtx, 0);

	if (GetKeyboardTrigger(DIK_W) == true)
	{
		g_EditWallInfo[g_nEditWallNumber].pos.z += MOVE_CURSOR;
	}
	if (GetKeyboardTrigger(DIK_S) == true)
	{
		g_EditWallInfo[g_nEditWallNumber].pos.z -= MOVE_CURSOR;
	}
	if (GetKeyboardTrigger(DIK_A) == true)
	{
		g_EditWallInfo[g_nEditWallNumber].pos.x -= MOVE_CURSOR;
	}
	if (GetKeyboardTrigger(DIK_D) == true)
	{
		g_EditWallInfo[g_nEditWallNumber].pos.x += MOVE_CURSOR;
	}

	if (GetKeyboardTrigger(DIK_RIGHT) == true)
	{
		g_EditWallInfo[g_nEditWallNumber].nType++;
		if (g_EditWallInfo[g_nEditWallNumber].nType >= NUM_WALL)
		{
			g_EditWallInfo[g_nEditWallNumber].nType = 0;
		}
	}
	else if (GetKeyboardTrigger(DIK_LEFT) == true)
	{
		g_EditWallInfo[g_nEditWallNumber].nType--;
		if (g_EditWallInfo[g_nEditWallNumber].nType < 0)
		{
			g_EditWallInfo[g_nEditWallNumber].nType = NUM_WALL -1;
		}
	}

	//���f���̐ݒu
	if (GetKeyboardTrigger(DIK_0) == true)
	{
		g_EditWallInfo[g_nEditWallNumber + 1].pos = g_EditWallInfo[g_nEditWallNumber].pos;
		g_EditWallInfo[g_nEditWallNumber + 1].rot = g_EditWallInfo[g_nEditWallNumber].rot;
		g_EditWallInfo[g_nEditWallNumber + 1].nType = g_EditWallInfo[g_nEditWallNumber].nType;
		g_EditWallInfo[g_nEditWallNumber + 1].bUse = true;
		g_EditWallInfo[g_nEditWallNumber].bUseGame = true;
		g_nSaveWallCnt++;
		g_nEditWallNumber++;
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-WALL_WIDE, WALL_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(WALL_WIDE, WALL_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-WALL_WIDE, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(WALL_WIDE, 0.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���f���̐ݒu
	if (GetKeyboardTrigger(DIK_F4) == true)
	{//�Z�[�u����
		int nNumEnemy = 0;
		bool bSave = false;
		char aSave[256];
		FILE* pFile = fopen(WALL_FILE_BIN, "wb");


		for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
		{
			if (g_EditWallInfo[nCnt].bUseGame == true)
			{
				nNumEnemy++;
			}
		}

		if (pFile != NULL)
		{
			fwrite(&nNumEnemy, sizeof(int), 1, pFile);

			for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
			{
				if (g_EditWallInfo[nCnt].bUseGame == true)
				{
					fwrite(&g_EditWallInfo[nCnt], sizeof(EditWallInfo), 1, pFile);
				}
			}
			fclose(pFile);

			//�Z�[�u����
			bSave = true;

		}
	}
}

//=============================================
//�ǂ̕ҏW
//=============================================
void CorrectionWall(void)
{
}

//=============================================
//�ǂ̓r������Z�[�u����
//=============================================
void reSaveWall(void)
{
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


	if (g_Edit.EditType == EDITTYPE_MODEL || g_Edit.EditType == EDITTYPE_CORRECTIONMODEL)
	{//���f���ݒu�̎�
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
					pDevice->SetTexture(0, g_apModelTextureEdit[g_EditModelInfo[nCnt].nType][nCntMat]);

					//�p�[�c�̐ݒ�
					g_apMeshEditModel[g_EditModelInfo[nCnt].nType]->DrawSubset(nCntMat);
				}
			}
		}

		//�ۑ����Ă��}�e���A����߂�
		pDevice->SetMaterial(&matDef);

		SetCursor(D3DXVECTOR3(g_EditModelInfo[g_nEditModelNumber].pos.x, 40.0f, g_EditModelInfo[g_nEditModelNumber].pos.z));
	}
	else if (g_Edit.EditType == EDITTYPE_WALL || g_Edit.EditType == EDITTYPE_CORRECTIONWALL)
	{//�ǐݒu�̎�
		for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
		{
			if (g_EditWallInfo[nCnt].bUse == true)
			{
				//�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_mtxWorldWallEdit);

				//�����𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_EditWallInfo[nCnt].rot.y, g_EditWallInfo[nCnt].rot.x, g_EditWallInfo[nCnt].rot.z);

				D3DXMatrixMultiply(&g_mtxWorldWallEdit, &g_mtxWorldWallEdit, &mtxRot);

				//�ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_EditWallInfo[nCnt].pos.x, g_EditWallInfo[nCnt].pos.y, g_EditWallInfo[nCnt].pos.z);

				D3DXMatrixMultiply(&g_mtxWorldWallEdit, &g_mtxWorldWallEdit, &mtxTrans);

				//���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldWallEdit);

				//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
				pDevice->SetStreamSource(0, g_pVtxBuffWallEdit, 0, sizeof(VERTEX_3D));

				//���_�t�H�[�}�b�g�̐ݒ�
				pDevice->SetFVF(FVF_VERTEX_3D);

				for (int nCntTex = 0; nCntTex < NUM_WALL; nCntTex++)
				{
					//�e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_apWallTextureEdit[nCntTex]);
				}

				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCnt, 2);

				pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
				pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
			}
		}
	}
}

//=============================================
//�G�f�B�b�g�̃f�o�b�O�\���i��ɑ�������j
//=============================================
void DebagEdit(void)
{
	LPD3DXFONT pFont = GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "������@\n[�J�����ړ�]\n�O�i:I ��i:K ��:J �E:L\n���f���ݒu���[�h:1 ���f���ҏW���[�h:2 �ǐݒu���[�h:3\n���̐ݒu:0\n���̈ړ�	�O�i:W ��i:S ��:A �E:D\n�^�C�v�̐؂�ւ���or��");

	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//=============================================
//�G�f�B�b�g�̃f�o�b�O�\���i�I������Ă���̂̏��j
//=============================================
void DebagInfo(void)
{
	LPD3DXFONT pFont = GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n\n\n\n\n\n\n[���f��]\npos:%.1f,%.1f,%.1f\nrot:%.1f,%.1f,%.1f\n\n[��]\npos:%.1f,%.1f,%.1f\nrot:%.1f,%.1f,%.1f",
		g_EditModelInfo[g_nEditModelNumber].pos.x,
		g_EditModelInfo[g_nEditModelNumber].pos.y,
		g_EditModelInfo[g_nEditModelNumber].pos.z,
		g_EditModelInfo[g_nEditModelNumber].rot.x,
		g_EditModelInfo[g_nEditModelNumber].rot.y,
		g_EditModelInfo[g_nEditModelNumber].rot.z,
		g_EditWallInfo[g_nEditWallNumber].pos.x,
		g_EditWallInfo[g_nEditWallNumber].pos.y,
		g_EditWallInfo[g_nEditWallNumber].pos.z,
		g_EditWallInfo[g_nEditWallNumber].rot.x,
		g_EditWallInfo[g_nEditWallNumber].rot.y,
		g_EditWallInfo[g_nEditWallNumber].rot.z);
	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

EditModelInfo* GetEditModelinfo(void)
{
	return &g_EditModelInfo[0];
}