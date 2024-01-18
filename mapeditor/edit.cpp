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
#include "field.h"
#include "cursor.h"
#include <string.h>
#include <stdio.h>
//�}�N����`
#define NUM_KEY_MAX	(256)
#define MOVE_CURSOR	(2.0f) //�J�[�\���ړ��l
#define CHANGE_SIZE	(5.0f) //�ǂ̃T�C�Y�ύX
#define EDIT_WIDE	(1280) //�G��u����ő�l
#define EDIT_HEIGHT	(700) //�G��u����ő�l
#define ENEMY_LIFE	(3) //�G�̃��C�t
#define TIME_CHANGE	(5) //���Ԃ�i�߂�

//=============================================
//�O���[�o���ϐ�
//=============================================
LPDIRECT3DTEXTURE9 g_apModelTextureEdit[NUM_MODEL][NUM_TEXTURE] = {}; //�e�N�X�`���|�C���^
LPDIRECT3DTEXTURE9 g_apWallTextureEdit[NUM_WALL] = {}; //�e�N�X�`���|�C���^
LPDIRECT3DTEXTURE9 g_apFieldTextureEdit[NUM_FIELD] = {}; //�e�N�X�`���|�C���^

Edit g_Edit; //�G�f�B�b�g���
LPD3DXMESH g_apMeshEditModel[NUM_MODEL]; //���f���̃��b�V�����
LPD3DXBUFFER g_apBuffMatEditModel[NUM_MODEL]; //���f���̒��_�o�b�t�@���
DWORD g_anNumMatEditModel[NUM_MODEL]; //���f���̃}�e���A�����
EditModelInfo g_EditModelInfo[MAX_MODEL]; //���f���̃G�f�B�b�g���

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWallEdit = NULL; //�ǂ̒��_���
D3DXMATRIX	g_mtxWorldWallEdit; //�ǂ̃��[���h�}�g���b�N�X
EditWallInfo g_EditWallInfo[MAX_WALL]; //�ǂ̃G�f�B�b�g���

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFieldEdit = NULL; //���̒��_���
D3DXMATRIX	g_mtxWorldFieldEdit; //���̃��[���h�}�g���b�N�X
EditFieldInfo g_EditFieldInfo[MAX_WALL]; //���̃G�f�B�b�g���

bool g_bSave = true; //�Z�[�u�ł��邩
int g_nSaveModelCnt; //���f���̃Z�[�u���J�E���g
int g_nSaveWallCnt; //�ǂ̃Z�[�u���J�E���g
int g_nSaveFieldCnt; //���̃Z�[�u���J�E���g
int g_nSave;
int g_pVtx; //���_
int g_pVtxField;
float g_fAlpha; //���l
float g_fFlash; //�_��

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
//���̃e�N�X�`���̎��
//=============================================
static const char* FIELD_TEX_NAME[NUM_FIELD] =
{
	"data\\TEXTURE\\ground.jpeg",
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
	//�J�[�\���^�C�v������(true:press,false:trigger)
	g_Edit.bCursorType = true;
	//�Ǐ]���郂�f���̏�����
	g_Edit.nEditModelNumber = 0;
	//�Ǐ]����ǂ̏�����
	g_Edit.nEditWallNumber = 0;

	g_pVtx = 0;
	g_pVtxField = 0;

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
	g_nSaveModelCnt = 0;
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
	g_EditWallInfo[0].fWide = WALL_WIDE;
	g_EditWallInfo[0].fHeight = WALL_HEIGHT;
	g_EditWallInfo[0].bUse = true;
	g_EditWallInfo[0].bUseGame = true;

	for (int nCnt = 1; nCnt < MAX_WALL; nCnt++)
	{
		g_EditWallInfo[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_EditWallInfo[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_EditWallInfo[nCnt].nType = 0;
		g_EditWallInfo[nCnt].fWide = WALL_WIDE;
		g_EditWallInfo[nCnt].fHeight = WALL_HEIGHT;
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

	for (int nCntFieldTex = 0; nCntFieldTex < NUM_FIELD; nCntFieldTex++)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			FIELD_TEX_NAME[nCntFieldTex],
			&g_apFieldTextureEdit[nCntFieldTex]
		);
	}

	//�ǂɏ������ޏ��̏�����
	g_EditFieldInfo[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_EditFieldInfo[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_EditFieldInfo[0].nType = 0;
	g_EditFieldInfo[0].fWide = FIELD_WIDE;
	g_EditFieldInfo[0].fDepth = FIELD_DEPTH;
	g_EditFieldInfo[0].bUse = true;
	g_EditFieldInfo[0].bUseGame = true;

	for (int nCnt = 1; nCnt < MAX_FIELD; nCnt++)
	{
		g_EditFieldInfo[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_EditFieldInfo[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_EditFieldInfo[nCnt].nType = 0;
		g_EditFieldInfo[nCnt].fWide = FIELD_WIDE;
		g_EditFieldInfo[nCnt].fDepth = FIELD_DEPTH;
		g_EditFieldInfo[nCnt].bUse = false;
		g_EditFieldInfo[nCnt].bUseGame = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_FIELD, D3DUSAGE_WRITEONLY, 4, D3DPOOL_MANAGED, &g_pVtxBuffFieldEdit, NULL);

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffFieldEdit->Lock(0, 0, (void**)&pVtx, 0);
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

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffFieldEdit->Unlock();
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
		g_Edit.nEditModelNumber = g_nSaveModelCnt;

		if (g_EditModelInfo[g_Edit.nEditModelNumber].bUseGame == false)
		{
			g_EditModelInfo[g_Edit.nEditModelNumber].bUse = true; //���ɐݒu������͕̂\�����Ȃ�
		}
	}


	else if (GetKeyboardTrigger(DIK_2) == true)
	{//���܂Œu�������f���̕ҏW
		g_Edit.EditType = EDITTYPE_CORRECTIONMODEL;
		if (g_EditModelInfo[g_Edit.nEditModelNumber].bUseGame == false)
		{
			g_EditModelInfo[g_Edit.nEditModelNumber].bUse = false; //���ɐݒu������͕̂\�����Ȃ�
			g_Edit.nEditModelNumber = 0; //�ŏ��ɒu�������̂ɃJ�[�\�����ړ�;
		}
	}

	else if (GetKeyboardTrigger(DIK_3) == true)
	{//�ǂ�ݒu
		g_Edit.EditType = EDITTYPE_WALL;
		g_Edit.nEditWallNumber = g_nSaveWallCnt;

		if (g_EditWallInfo[g_Edit.nEditWallNumber].bUseGame == false)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].bUse = true; //���ɐݒu������͕̂\�����Ȃ�
		}
	}

	else if (GetKeyboardTrigger(DIK_4) == true)
	{//���܂Œu�����ǂ̕ҏW
		g_Edit.EditType = EDITTYPE_CORRECTIONWALL;

		if (g_EditWallInfo[g_Edit.nEditWallNumber].bUseGame == false)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].bUse = true; //���ɐݒu������͕̂\�����Ȃ�
			g_Edit.nEditWallNumber = 0; //�ŏ��ɒu�������̂ɃJ�[�\�����ړ�
			g_pVtx = 0; //�ŏ��ɒu�������̂̒��_
		}
	}
	else if (GetKeyboardTrigger(DIK_5) == true)
	{//����ݒu
		g_Edit.EditType = EDITTYPE_FIELD;
		g_Edit.nEditFieldNumber = g_nSaveFieldCnt;

		if (g_EditFieldInfo[g_Edit.nEditFieldNumber].bUseGame == false)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].bUse = true; //���ɐݒu������͕̂\�����Ȃ�
		}
	}
	else if (GetKeyboardTrigger(DIK_6) == true)
	{//���܂Œu�������̕ҏW
		g_Edit.EditType = EDITTYPE_CORRECTIONFIELD;

		if (g_EditFieldInfo[g_Edit.nEditFieldNumber].bUseGame == false)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].bUse = true; //���ɐݒu������͕̂\�����Ȃ�
			g_Edit.nEditFieldNumber = 0; //�ŏ��ɒu�������̂ɃJ�[�\�����ړ�
			g_pVtxField = 0; //�ŏ��ɒu�������̂̒��_
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
	else if (g_Edit.EditType == EDITTYPE_CORRECTIONWALL)
	{//�ǒu���Ȃ���
		CorrectionWall();
	}
	else if (g_Edit.EditType == EDITTYPE_FIELD)
	{//��
		SaveField();
	}
	else if (g_Edit.EditType == EDITTYPE_CORRECTIONFIELD)
	{//���u���Ȃ���
		CorrectionField();
	}

	if (GetKeyboardTrigger(DIK_F1) == true)
	{

		pCamera->posV = D3DXVECTOR3(0.0f, 1020.0f, -13.0f);
		pCamera->posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //����

	}

	if (GetKeyboardTrigger(DIK_F5) == true)
	{
		g_Edit.bCursorType = g_Edit.bCursorType ? false : true;
	}
}

//=============================================
//�Đݒu�p�֐��i�Ǘ��p�j
//=============================================
void reSaveEdit(void)
{

	if (GetKeyboardTrigger(DIK_1) == true)
	{//���f����ݒu
		g_Edit.EditType = EDITTYPE_MODEL;
		g_Edit.nEditModelNumber = g_nSaveModelCnt;

		if (g_EditModelInfo[g_Edit.nEditModelNumber].bUseGame == false)
		{
			g_EditModelInfo[g_Edit.nEditModelNumber].bUse = true; //���ɐݒu������͕̂\�����Ȃ�
		}
	}


	else if (GetKeyboardTrigger(DIK_2) == true)
	{//���܂Œu�������f���̕ҏW
		g_Edit.EditType = EDITTYPE_CORRECTIONMODEL;
		if (g_EditModelInfo[g_Edit.nEditModelNumber].bUseGame == false)
		{
			g_EditModelInfo[g_Edit.nEditModelNumber].bUse = false; //���ɐݒu������͕̂\�����Ȃ�
			g_Edit.nEditModelNumber = 0; //�ŏ��ɒu�������̂ɃJ�[�\�����ړ�;
		}
	}

	else if (GetKeyboardTrigger(DIK_3) == true)
	{//�ǂ�ݒu
		g_Edit.EditType = EDITTYPE_WALL;
		g_Edit.nEditWallNumber = g_nSaveWallCnt;

		if (g_EditWallInfo[g_Edit.nEditWallNumber].bUseGame == false)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].bUse = true; //���ɐݒu������͕̂\�����Ȃ�
		}
	}

	else if (GetKeyboardTrigger(DIK_4) == true)
	{//���܂Œu�����ǂ̕ҏW
		g_Edit.EditType = EDITTYPE_CORRECTIONWALL;

		if (g_EditWallInfo[g_Edit.nEditWallNumber].bUseGame == false)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].bUse = true; //���ɐݒu������͕̂\�����Ȃ�
			g_Edit.nEditWallNumber = 0; //�ŏ��ɒu�������̂ɃJ�[�\�����ړ�
			g_pVtx = 0; //�ŏ��ɒu�������̂̒��_
		}
	}
	else if (GetKeyboardTrigger(DIK_5) == true)
	{//����ݒu
		g_Edit.EditType = EDITTYPE_FIELD;
		g_Edit.nEditFieldNumber = g_nSaveFieldCnt;

		if (g_EditFieldInfo[g_Edit.nEditFieldNumber].bUseGame == false)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].bUse = true; //���ɐݒu������͕̂\�����Ȃ�
		}
	}
	else if (GetKeyboardTrigger(DIK_6) == true)
	{//���܂Œu�������̕ҏW
		g_Edit.EditType = EDITTYPE_CORRECTIONFIELD;

		if (g_EditFieldInfo[g_Edit.nEditFieldNumber].bUseGame == false)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].bUse = true; //���ɐݒu������͕̂\�����Ȃ�
			g_Edit.nEditFieldNumber = 0; //�ŏ��ɒu�������̂ɃJ�[�\�����ړ�
			g_pVtxField = 0; //�ŏ��ɒu�������̂̒��_
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
	else if (g_Edit.EditType == EDITTYPE_CORRECTIONWALL)
	{//�ǒu���Ȃ���
		CorrectionWall();
	}
	else if (g_Edit.EditType == EDITTYPE_FIELD)
	{//��
		SaveField();
	}
	else if (g_Edit.EditType == EDITTYPE_CORRECTIONFIELD)
	{//���u���Ȃ���
		CorrectionField();
	}

	if (GetKeyboardTrigger(DIK_F5) == true)
	{//�J�[�\���̓������؂�ւ�
		g_Edit.bCursorType = g_Edit.bCursorType ? false : true;
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
		g_EditModelInfo[g_Edit.nEditModelNumber].pos.z += MOVE_CURSOR
			;
	}
	if (GetKeyboardPress(DIK_S) == true)
	{
		g_EditModelInfo[g_Edit.nEditModelNumber].pos.z -= MOVE_CURSOR;
	}
	if (GetKeyboardPress(DIK_A) == true)
	{
		g_EditModelInfo[g_Edit.nEditModelNumber].pos.x -= MOVE_CURSOR;
	}
	if (GetKeyboardPress(DIK_D) == true)
	{
		g_EditModelInfo[g_Edit.nEditModelNumber].pos.x += MOVE_CURSOR;
	}

	if (GetKeyboardTrigger(DIK_RIGHT) == true)
	{
		g_EditModelInfo[g_Edit.nEditModelNumber].nType++;
		if (g_EditModelInfo[g_Edit.nEditModelNumber].nType >= NUM_MODEL)
		{
			g_EditModelInfo[g_Edit.nEditModelNumber].nType = 0;
		}
	}
	else if (GetKeyboardTrigger(DIK_LEFT) == true)
	{
		g_EditModelInfo[g_Edit.nEditModelNumber].nType--;
		if (g_EditModelInfo[g_Edit.nEditModelNumber].nType < 0)
		{
			g_EditModelInfo[g_Edit.nEditModelNumber].nType = NUM_MODEL -1;
		}
	}

	//���f���̐ݒu
	if (GetKeyboardTrigger(DIK_0) == true)
	{
		g_EditModelInfo[g_Edit.nEditModelNumber + 1].pos = g_EditModelInfo[g_Edit.nEditModelNumber].pos;
		g_EditModelInfo[g_Edit.nEditModelNumber + 1].rot = g_EditModelInfo[g_Edit.nEditModelNumber].rot;
		g_EditModelInfo[g_Edit.nEditModelNumber + 1].nType = g_EditModelInfo[g_Edit.nEditModelNumber].nType;
		g_EditModelInfo[g_Edit.nEditModelNumber + 1].bUse = true;
		g_EditModelInfo[g_Edit.nEditModelNumber].bUseGame = true;
		g_nSaveModelCnt++;
		g_Edit.nEditModelNumber++;
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
		g_Edit.nEditModelNumber++;
		if (g_Edit.nEditModelNumber >= g_nSaveModelCnt)
		{
			g_Edit.nEditModelNumber = 0;
		}
	}
	else if (GetKeyboardTrigger(DIK_DOWN) == true)
	{
		g_Edit.nEditModelNumber--;
		if (g_Edit.nEditModelNumber < 0)
		{
			g_Edit.nEditModelNumber = g_nSaveModelCnt - 1;
		}
	}

	if (GetKeyboardPress(DIK_W) == true)
	{
		g_EditModelInfo[g_Edit.nEditModelNumber].pos.z += MOVE_CURSOR
			;
	}
	if (GetKeyboardPress(DIK_S) == true)
	{
		g_EditModelInfo[g_Edit.nEditModelNumber].pos.z -= MOVE_CURSOR;
	}
	if (GetKeyboardPress(DIK_A) == true)
	{
		g_EditModelInfo[g_Edit.nEditModelNumber].pos.x -= MOVE_CURSOR;
	}
	if (GetKeyboardPress(DIK_D) == true)
	{
		g_EditModelInfo[g_Edit.nEditModelNumber].pos.x += MOVE_CURSOR;
	}

	if (GetKeyboardTrigger(DIK_RIGHT) == true)
	{
		g_EditModelInfo[g_Edit.nEditModelNumber].nType++;
		if (g_EditModelInfo[g_Edit.nEditModelNumber].nType >= NUM_MODEL)
		{
			g_EditModelInfo[g_Edit.nEditModelNumber].nType = 0;
		}
	}
	else if (GetKeyboardTrigger(DIK_LEFT) == true)
	{
		g_EditModelInfo[g_Edit.nEditModelNumber].nType--;
		if (g_EditModelInfo[g_Edit.nEditModelNumber].nType < 0)
		{
			g_EditModelInfo[g_Edit.nEditModelNumber].nType = NUM_MODEL - 1;
		}
	}

	//���f���̐ݒu
	if (GetKeyboardTrigger(DIK_0) == true)
	{
		g_EditModelInfo[g_Edit.nEditModelNumber].bUseGame = true;
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
			g_Edit.nEditModelNumber++;
		}
	}

	g_EditModelInfo[g_Edit.nEditModelNumber].bUse = true; //�ۑ�����Ă�Ō�̃��f���̎��̂��true��
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

	//�ǂ̏��ύX
	if (g_Edit.bCursorType == true)
	{//�v���X
		if (GetKeyboardPress(DIK_W) == true)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].pos.z += MOVE_CURSOR;
		}
		if (GetKeyboardPress(DIK_S) == true)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].pos.z -= MOVE_CURSOR;
		}
		if (GetKeyboardPress(DIK_A) == true)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].pos.x -= MOVE_CURSOR;
		}
		if (GetKeyboardPress(DIK_D) == true)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].pos.x += MOVE_CURSOR;
		}

		//�ǂ̃T�C�Y�ύX
		if (GetKeyboardPress(DIK_G) == true)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].fWide += CHANGE_SIZE;
			//���_���W�̐ݒ�
			pVtx[g_pVtx].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 1].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 2].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
			pVtx[g_pVtx + 3].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
		}
		//�ǂ̃T�C�Y�ύX
		if (GetKeyboardPress(DIK_F) == true)
		{
			if (g_EditWallInfo[g_Edit.nEditWallNumber].fWide > 0)
			{
				g_EditWallInfo[g_Edit.nEditWallNumber].fWide -= CHANGE_SIZE;
			}
			//���_���W�̐ݒ�
			pVtx[g_pVtx].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 1].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 2].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
			pVtx[g_pVtx + 3].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
		}
		//�ǂ̃T�C�Y�ύX
		if (GetKeyboardPress(DIK_B) == true)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].fHeight += CHANGE_SIZE;
			//���_���W�̐ݒ�
			pVtx[g_pVtx].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 1].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 2].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
			pVtx[g_pVtx + 3].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
		}
		//�ǂ̃T�C�Y�ύX
		if (GetKeyboardPress(DIK_V) == true)
		{
			if (g_EditWallInfo[g_Edit.nEditWallNumber].fHeight > 0)
			{
				g_EditWallInfo[g_Edit.nEditWallNumber].fHeight -= CHANGE_SIZE;

			}
			//���_���W�̐ݒ�
			pVtx[g_pVtx].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 1].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 2].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
			pVtx[g_pVtx + 3].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
		}

	}
	else if (g_Edit.bCursorType == false)
	{//�g���K�[
		if (GetKeyboardTrigger(DIK_W) == true)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].pos.z += MOVE_CURSOR;
		}
		if (GetKeyboardTrigger(DIK_S) == true)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].pos.z -= MOVE_CURSOR;
		}
		if (GetKeyboardTrigger(DIK_A) == true)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].pos.x -= MOVE_CURSOR;
		}
		if (GetKeyboardTrigger(DIK_D) == true)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].pos.x += MOVE_CURSOR;
		}

		//�ǂ̃T�C�Y�ύX
		if (GetKeyboardTrigger(DIK_G) == true)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].fWide += CHANGE_SIZE;
			//���_���W�̐ݒ�
			pVtx[g_pVtx].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 1].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 2].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
			pVtx[g_pVtx + 3].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
		}
		//�ǂ̃T�C�Y�ύX
		if (GetKeyboardTrigger(DIK_F) == true)
		{
			if (g_EditWallInfo[g_Edit.nEditWallNumber].fWide > 0)
			{
				g_EditWallInfo[g_Edit.nEditWallNumber].fWide -= CHANGE_SIZE;
			}
			//���_���W�̐ݒ�
			pVtx[g_pVtx].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 1].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 2].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
			pVtx[g_pVtx + 3].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
		}
		//�ǂ̃T�C�Y�ύX
		if (GetKeyboardTrigger(DIK_B) == true)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].fHeight += CHANGE_SIZE;
			//���_���W�̐ݒ�
			pVtx[g_pVtx].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 1].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 2].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
			pVtx[g_pVtx + 3].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
		}
		//�ǂ̃T�C�Y�ύX
		if (GetKeyboardTrigger(DIK_V) == true)
		{
			if (g_EditWallInfo[g_Edit.nEditWallNumber].fHeight > 0)
			{
				g_EditWallInfo[g_Edit.nEditWallNumber].fHeight -= CHANGE_SIZE;
			}
			//���_���W�̐ݒ�
			pVtx[g_pVtx].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 1].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 2].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
			pVtx[g_pVtx + 3].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
		}
	}
	//�ǂ�rot��]
	if (GetKeyboardTrigger(DIK_C) == true)
	{
		g_EditWallInfo[g_Edit.nEditWallNumber].rot.y += 1.57f;
		if (g_EditWallInfo[g_Edit.nEditWallNumber].rot.y > D3DX_PI)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].rot.y = -D3DX_PI;
		}
	}
	else if (GetKeyboardTrigger(DIK_Z) == true)
	{
		g_EditWallInfo[g_Edit.nEditWallNumber].rot.y -= 1.57f;
		if (g_EditWallInfo[g_Edit.nEditWallNumber].rot.y < -D3DX_PI)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].rot.y = D3DX_PI;
		}
	}

	//�ǂ̃^�C�v�ύX
	if (GetKeyboardTrigger(DIK_RIGHT) == true)
	{
		g_EditWallInfo[g_Edit.nEditWallNumber].nType++;
		if (g_EditWallInfo[g_Edit.nEditWallNumber].nType >= NUM_WALL)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].nType = 0;
		}
	}
	else if (GetKeyboardTrigger(DIK_LEFT) == true)
	{
		g_EditWallInfo[g_Edit.nEditWallNumber].nType--;
		if (g_EditWallInfo[g_Edit.nEditWallNumber].nType < 0)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].nType = NUM_WALL -1;
		}
	}

	//���f���̐ݒu
	if (GetKeyboardTrigger(DIK_0) == true)
	{
		g_EditWallInfo[g_Edit.nEditWallNumber + 1].pos = g_EditWallInfo[g_Edit.nEditWallNumber].pos;
		g_EditWallInfo[g_Edit.nEditWallNumber + 1].rot = g_EditWallInfo[g_Edit.nEditWallNumber].rot;
		g_EditWallInfo[g_Edit.nEditWallNumber + 1].nType = g_EditWallInfo[g_Edit.nEditWallNumber].nType;
		g_EditWallInfo[g_Edit.nEditWallNumber + 1].bUse = true;
		g_EditWallInfo[g_Edit.nEditWallNumber].bUseGame = true;
		g_nSaveWallCnt++;
		g_Edit.nEditWallNumber++;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		g_pVtx += 4;
	}

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
	LPDIRECT3DDEVICE9 pDevice;
	//int nCntEdit;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//Enemy* pEnemy = GetEnemy();
	VERTEX_3D* pVtx;
	g_pVtxBuffWallEdit->Lock(0, 0, (void**)&pVtx, 0);

	if (GetKeyboardTrigger(DIK_UP) == true)
	{
		g_Edit.nEditWallNumber++;
		g_pVtx += 4;
		if (g_Edit.nEditWallNumber >= g_nSaveWallCnt)
		{
			g_Edit.nEditWallNumber = 0;
			g_pVtx = 0;
		}
	}
	else if (GetKeyboardTrigger(DIK_DOWN) == true)
	{
		g_Edit.nEditWallNumber--;
		g_pVtx -= 4;
		if (g_Edit.nEditWallNumber < 0)
		{
			g_Edit.nEditWallNumber = g_nSaveWallCnt - 1;
			g_pVtx += 4 * (g_nSaveModelCnt - 1);
		}
	}

	//�ǂ̏��ύX
	if (g_Edit.bCursorType == true)
	{//�v���X
		if (GetKeyboardPress(DIK_W) == true)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].pos.z += MOVE_CURSOR;
		}
		if (GetKeyboardPress(DIK_S) == true)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].pos.z -= MOVE_CURSOR;
		}
		if (GetKeyboardPress(DIK_A) == true)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].pos.x -= MOVE_CURSOR;
		}
		if (GetKeyboardPress(DIK_D) == true)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].pos.x += MOVE_CURSOR;
		}

		//�ǂ̃T�C�Y�ύX
		if (GetKeyboardPress(DIK_G) == true)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].fWide += CHANGE_SIZE;
			//���_���W�̐ݒ�
			pVtx[g_pVtx].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 1].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 2].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
			pVtx[g_pVtx + 3].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
		}
		//�ǂ̃T�C�Y�ύX
		if (GetKeyboardPress(DIK_F) == true)
		{
			if (g_EditWallInfo[g_Edit.nEditWallNumber].fWide > 0)
			{
				g_EditWallInfo[g_Edit.nEditWallNumber].fWide -= CHANGE_SIZE;
			}
			//���_���W�̐ݒ�
			pVtx[g_pVtx].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 1].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 2].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
			pVtx[g_pVtx + 3].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
		}
		//�ǂ̃T�C�Y�ύX
		if (GetKeyboardPress(DIK_B) == true)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].fHeight += CHANGE_SIZE;
			//���_���W�̐ݒ�
			pVtx[g_pVtx].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 1].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 2].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
			pVtx[g_pVtx + 3].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
		}
		//�ǂ̃T�C�Y�ύX
		if (GetKeyboardPress(DIK_V) == true)
		{
			if (g_EditWallInfo[g_Edit.nEditWallNumber].fHeight > 0)
			{
				g_EditWallInfo[g_Edit.nEditWallNumber].fHeight -= CHANGE_SIZE;

			}
			//���_���W�̐ݒ�
			pVtx[g_pVtx].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 1].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 2].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
			pVtx[g_pVtx + 3].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
		}

	}
	else if (g_Edit.bCursorType == false)
	{//�g���K�[
		if (GetKeyboardTrigger(DIK_W) == true)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].pos.z += MOVE_CURSOR;
		}
		if (GetKeyboardTrigger(DIK_S) == true)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].pos.z -= MOVE_CURSOR;
		}
		if (GetKeyboardTrigger(DIK_A) == true)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].pos.x -= MOVE_CURSOR;
		}
		if (GetKeyboardTrigger(DIK_D) == true)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].pos.x += MOVE_CURSOR;
		}

		//�ǂ̃T�C�Y�ύX
		if (GetKeyboardTrigger(DIK_G) == true)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].fWide += CHANGE_SIZE;
			//���_���W�̐ݒ�
			pVtx[g_pVtx].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 1].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 2].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
			pVtx[g_pVtx + 3].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
		}
		//�ǂ̃T�C�Y�ύX
		if (GetKeyboardTrigger(DIK_F) == true)
		{
			if (g_EditWallInfo[g_Edit.nEditWallNumber].fWide > 0)
			{
				g_EditWallInfo[g_Edit.nEditWallNumber].fWide -= CHANGE_SIZE;
			}
			//���_���W�̐ݒ�
			pVtx[g_pVtx].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 1].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 2].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
			pVtx[g_pVtx + 3].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
		}
		//�ǂ̃T�C�Y�ύX
		if (GetKeyboardTrigger(DIK_B) == true)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].fHeight += CHANGE_SIZE;
			//���_���W�̐ݒ�
			pVtx[g_pVtx].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 1].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 2].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
			pVtx[g_pVtx + 3].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
		}
		//�ǂ̃T�C�Y�ύX
		if (GetKeyboardTrigger(DIK_V) == true)
		{
			if (g_EditWallInfo[g_Edit.nEditWallNumber].fHeight > 0)
			{
				g_EditWallInfo[g_Edit.nEditWallNumber].fHeight -= CHANGE_SIZE;
			}
			//���_���W�̐ݒ�
			pVtx[g_pVtx].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 1].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 2].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
			pVtx[g_pVtx + 3].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
		}
	}
	//�ǂ�rot��]
	if (GetKeyboardTrigger(DIK_C) == true)
	{
		g_EditWallInfo[g_Edit.nEditWallNumber].rot.y += 1.57f;
		if (g_EditWallInfo[g_Edit.nEditWallNumber].rot.y > D3DX_PI)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].rot.y = -D3DX_PI;
		}
	}
	else if (GetKeyboardTrigger(DIK_Z) == true)
	{
		g_EditWallInfo[g_Edit.nEditWallNumber].rot.y -= 1.57f;
		if (g_EditWallInfo[g_Edit.nEditWallNumber].rot.y < -D3DX_PI)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].rot.y = D3DX_PI;
		}
	}

	//�ǂ̃^�C�v�ύX
	if (GetKeyboardTrigger(DIK_RIGHT) == true)
	{
		g_EditWallInfo[g_Edit.nEditWallNumber].nType++;
		if (g_EditWallInfo[g_Edit.nEditWallNumber].nType >= NUM_WALL)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].nType = 0;
		}
	}
	else if (GetKeyboardTrigger(DIK_LEFT) == true)
	{
		g_EditWallInfo[g_Edit.nEditWallNumber].nType--;
		if (g_EditWallInfo[g_Edit.nEditWallNumber].nType < 0)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].nType = NUM_WALL - 1;
		}
	}

	//���f���̐ݒu
	if (GetKeyboardTrigger(DIK_0) == true)
	{
		g_EditWallInfo[g_Edit.nEditWallNumber].bUseGame = true;
	}

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

	g_pVtxBuffWallEdit->Unlock();

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
//�ǂ̓r������Z�[�u����
//=============================================
void reSaveWall(void)
{
	//�t�@�C���̓ǂݍ���
	FILE* pFile = fopen(WALL_FILE_BIN, "rb");

	if (pFile != NULL)
	{
		//�G�̎g�p���Ă鐔�̓ǂݍ���
		fread(&g_nSaveWallCnt, sizeof(int), 1, pFile);

		//�G�̎g�p�����A�G�̓ǂݍ���
		fread(&g_EditWallInfo[0], sizeof(EditWallInfo), g_nSaveWallCnt, pFile);

		//�t�@�C�������
		fclose(pFile);
	}

	else
	{
		return;
	}

	VERTEX_3D* pVtx;
	g_pVtxBuffWallEdit->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntUseWall = 0; nCntUseWall < MAX_WALL; nCntUseWall++)
	{
		if (g_EditWallInfo[nCntUseWall].bUse == true)
		{
			g_Edit.nEditWallNumber++;

			pVtx[g_pVtx].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 1].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 2].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
			pVtx[g_pVtx + 3].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);

			g_pVtx += 4;
		}
	}
	g_pVtxBuffWallEdit->Unlock();
	g_EditWallInfo[g_Edit.nEditWallNumber].bUse = true; //�ۑ�����Ă�Ō�̃��f���̎��̂��true��
}

//=============================================
//���̃Z�[�u����
//=============================================
void SaveField(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//int nCntEdit;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//Enemy* pEnemy = GetEnemy();
	VERTEX_3D* pVtx;
	g_pVtxBuffFieldEdit->Lock(0, 0, (void**)&pVtx, 0);

	//�ǂ̏��ύX
	if (g_Edit.bCursorType == true)
	{//�v���X
		if (GetKeyboardPress(DIK_W) == true)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].pos.z += MOVE_CURSOR;
		}
		if (GetKeyboardPress(DIK_S) == true)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].pos.z -= MOVE_CURSOR;
		}
		if (GetKeyboardPress(DIK_A) == true)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].pos.x -= MOVE_CURSOR;
		}
		if (GetKeyboardPress(DIK_D) == true)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].pos.x += MOVE_CURSOR;
		}

		//�ǂ̃T�C�Y�ύX
		if (GetKeyboardPress(DIK_G) == true)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide += CHANGE_SIZE;
			//���_���W�̐ݒ�
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
		}
		//�ǂ̃T�C�Y�ύX
		if (GetKeyboardPress(DIK_F) == true)
		{
			if (g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide > 0)
			{
				g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide -= CHANGE_SIZE;
			}
			//���_���W�̐ݒ�
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
		}
		//�ǂ̃T�C�Y�ύX
		if (GetKeyboardPress(DIK_B) == true)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth += CHANGE_SIZE;
			//���_���W�̐ݒ�
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
		}
		//�ǂ̃T�C�Y�ύX
		if (GetKeyboardPress(DIK_V) == true)
		{
			if (g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth > 0)
			{
				g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth -= CHANGE_SIZE;

			}
			//���_���W�̐ݒ�
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
		}

	}
	else if (g_Edit.bCursorType == false)
	{//�g���K�[
		if (GetKeyboardTrigger(DIK_W) == true)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].pos.z += MOVE_CURSOR;
		}
		if (GetKeyboardTrigger(DIK_S) == true)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].pos.z -= MOVE_CURSOR;
		}
		if (GetKeyboardTrigger(DIK_A) == true)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].pos.x -= MOVE_CURSOR;
		}
		if (GetKeyboardTrigger(DIK_D) == true)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].pos.x += MOVE_CURSOR;
		}

		//�ǂ̃T�C�Y�ύX
		if (GetKeyboardTrigger(DIK_G) == true)
		{
			//���_���W�̐ݒ�
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
		}
		//�ǂ̃T�C�Y�ύX
		if (GetKeyboardTrigger(DIK_F) == true)
		{
			if (g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide > 0)
			{
				g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide -= CHANGE_SIZE;
			}
			//���_���W�̐ݒ�
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
		}
		//�ǂ̃T�C�Y�ύX
		if (GetKeyboardTrigger(DIK_B) == true)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth += CHANGE_SIZE;
			//���_���W�̐ݒ�
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
		}
		//�ǂ̃T�C�Y�ύX
		if (GetKeyboardTrigger(DIK_V) == true)
		{
			if (g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth > 0)
			{
				g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth -= CHANGE_SIZE;
			}
			//���_���W�̐ݒ�
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
		}
	}
	//�ǂ�rot��]
	if (GetKeyboardTrigger(DIK_C) == true)
	{
		g_EditFieldInfo[g_Edit.nEditFieldNumber].rot.y += 1.57f;
		if (g_EditFieldInfo[g_Edit.nEditFieldNumber].rot.y > D3DX_PI)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].rot.y = -D3DX_PI;
		}
	}
	else if (GetKeyboardTrigger(DIK_Z) == true)
	{
		g_EditFieldInfo[g_Edit.nEditFieldNumber].rot.y -= 1.57f;
		if (g_EditFieldInfo[g_Edit.nEditFieldNumber].rot.y < -D3DX_PI)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].rot.y = D3DX_PI;
		}
	}

	//�ǂ̃^�C�v�ύX
	if (GetKeyboardTrigger(DIK_RIGHT) == true)
	{
		g_EditFieldInfo[g_Edit.nEditFieldNumber].nType++;
		if (g_EditFieldInfo[g_Edit.nEditFieldNumber].nType >= NUM_FIELD)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].nType = 0;
		}
	}
	else if (GetKeyboardTrigger(DIK_LEFT) == true)
	{
		g_EditFieldInfo[g_Edit.nEditFieldNumber].nType--;
		if (g_EditFieldInfo[g_Edit.nEditFieldNumber].nType < 0)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].nType = NUM_WALL - 1;
		}
	}

	//���f���̐ݒu
	if (GetKeyboardTrigger(DIK_0) == true)
	{
		g_EditFieldInfo[g_Edit.nEditFieldNumber + 1].pos = g_EditFieldInfo[g_Edit.nEditFieldNumber].pos;
		g_EditFieldInfo[g_Edit.nEditFieldNumber + 1].rot = g_EditFieldInfo[g_Edit.nEditFieldNumber].rot;
		g_EditFieldInfo[g_Edit.nEditFieldNumber + 1].nType = g_EditFieldInfo[g_Edit.nEditFieldNumber].nType;
		g_EditFieldInfo[g_Edit.nEditFieldNumber + 1].bUse = true;
		g_EditFieldInfo[g_Edit.nEditFieldNumber].bUseGame = true;
		g_nSaveFieldCnt++;
		g_Edit.nEditFieldNumber++;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		g_pVtxField += 4;
	}

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
		int nNumField = 0;
		bool bSave = false;
		char aSave[256];
		FILE* pFile = fopen(FIELD_FILE_BIN, "wb");


		for (int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
		{
			if (g_EditFieldInfo[nCnt].bUseGame == true)
			{
				nNumField++;
			}
		}

		if (pFile != NULL)
		{
			fwrite(&nNumField, sizeof(int), 1, pFile);

			for (int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
			{
				if (g_EditFieldInfo[nCnt].bUseGame == true)
				{
					fwrite(&g_EditFieldInfo[nCnt], sizeof(EditFieldInfo), 1, pFile);
				}
			}
			fclose(pFile);

			//�Z�[�u����
			bSave = true;

		}
	}
}

//=============================================
//���̕ҏW����
//=============================================
void CorrectionField(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//int nCntEdit;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//Enemy* pEnemy = GetEnemy();
	VERTEX_3D* pVtx;
	g_pVtxBuffFieldEdit->Lock(0, 0, (void**)&pVtx, 0);

	//�ǂ̏��ύX
	if (g_Edit.bCursorType == true)
	{//�v���X
		if (GetKeyboardPress(DIK_W) == true)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].pos.z += MOVE_CURSOR;
		}
		if (GetKeyboardPress(DIK_S) == true)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].pos.z -= MOVE_CURSOR;
		}
		if (GetKeyboardPress(DIK_A) == true)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].pos.x -= MOVE_CURSOR;
		}
		if (GetKeyboardPress(DIK_D) == true)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].pos.x += MOVE_CURSOR;
		}

		if (GetKeyboardTrigger(DIK_UP) == true)
		{
			g_Edit.nEditFieldNumber++;
			g_pVtxField += 4;
			if (g_Edit.nEditFieldNumber >= g_nSaveFieldCnt)
			{
				g_Edit.nEditFieldNumber = 0;
				g_pVtxField = 0;
			}
		}
		else if (GetKeyboardTrigger(DIK_DOWN) == true)
		{
			g_Edit.nEditFieldNumber--;
			g_pVtxField -= 4;
			if (g_Edit.nEditFieldNumber < 0)
			{
				g_Edit.nEditFieldNumber = g_nSaveFieldCnt - 1;
				g_pVtxField += 4 * (g_nSaveFieldCnt - 1);
			}
		}

		//�ǂ̃T�C�Y�ύX
		if (GetKeyboardPress(DIK_G) == true)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide += CHANGE_SIZE;
			//���_���W�̐ݒ�
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
		}
		//�ǂ̃T�C�Y�ύX
		if (GetKeyboardPress(DIK_F) == true)
		{
			if (g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide > 0)
			{
				g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide -= CHANGE_SIZE;
			}
			//���_���W�̐ݒ�
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
		}
		//�ǂ̃T�C�Y�ύX
		if (GetKeyboardPress(DIK_B) == true)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth += CHANGE_SIZE;
			//���_���W�̐ݒ�
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
		}
		//�ǂ̃T�C�Y�ύX
		if (GetKeyboardPress(DIK_V) == true)
		{
			if (g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth > 0)
			{
				g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth -= CHANGE_SIZE;
			}
			//���_���W�̐ݒ�
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
		}

	}
	else if (g_Edit.bCursorType == false)
	{//�g���K�[
		if (GetKeyboardTrigger(DIK_W) == true)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].pos.z += MOVE_CURSOR;
		}
		if (GetKeyboardTrigger(DIK_S) == true)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].pos.z -= MOVE_CURSOR;
		}
		if (GetKeyboardTrigger(DIK_A) == true)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].pos.x -= MOVE_CURSOR;
		}
		if (GetKeyboardTrigger(DIK_D) == true)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].pos.x += MOVE_CURSOR;
		}

		//�ǂ̃T�C�Y�ύX
		if (GetKeyboardTrigger(DIK_G) == true)
		{
			//���_���W�̐ݒ�
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
		}
		//�ǂ̃T�C�Y�ύX
		if (GetKeyboardTrigger(DIK_F) == true)
		{
			if (g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide > 0)
			{
				g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide -= CHANGE_SIZE;
			}
			//���_���W�̐ݒ�
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
		}
		//�ǂ̃T�C�Y�ύX
		if (GetKeyboardTrigger(DIK_B) == true)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth += CHANGE_SIZE;
			//���_���W�̐ݒ�
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
		}
		//�ǂ̃T�C�Y�ύX
		if (GetKeyboardTrigger(DIK_V) == true)
		{
			if (g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth > 0)
			{
				g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth -= CHANGE_SIZE;
			}
			//���_���W�̐ݒ�
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
		}
	}
	//�ǂ�rot��]
	if (GetKeyboardTrigger(DIK_C) == true)
	{
		g_EditFieldInfo[g_Edit.nEditFieldNumber].rot.y += 1.57f;
		if (g_EditFieldInfo[g_Edit.nEditFieldNumber].rot.y > D3DX_PI)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].rot.y = -D3DX_PI;
		}
	}
	else if (GetKeyboardTrigger(DIK_Z) == true)
	{
		g_EditFieldInfo[g_Edit.nEditFieldNumber].rot.y -= 1.57f;
		if (g_EditFieldInfo[g_Edit.nEditFieldNumber].rot.y < -D3DX_PI)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].rot.y = D3DX_PI;
		}
	}

	//�ǂ̃^�C�v�ύX
	if (GetKeyboardTrigger(DIK_RIGHT) == true)
	{
		g_EditFieldInfo[g_Edit.nEditFieldNumber].nType++;
		if (g_EditFieldInfo[g_Edit.nEditFieldNumber].nType >= NUM_FIELD)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].nType = 0;
		}
	}
	else if (GetKeyboardTrigger(DIK_LEFT) == true)
	{
		g_EditFieldInfo[g_Edit.nEditFieldNumber].nType--;
		if (g_EditFieldInfo[g_Edit.nEditFieldNumber].nType < 0)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].nType = NUM_WALL - 1;
		}
	}

	//���f���̐ݒu
	if (GetKeyboardTrigger(DIK_0) == true)
	{
		g_EditFieldInfo[g_Edit.nEditFieldNumber].bUseGame = true;
		g_pVtxField += 4;
	}

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
		int nNumField = 0;
		bool bSave = false;
		char aSave[256];
		FILE* pFile = fopen(FIELD_FILE_BIN, "wb");


		for (int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
		{
			if (g_EditFieldInfo[nCnt].bUseGame == true)
			{
				nNumField++;
			}
		}

		if (pFile != NULL)
		{
			fwrite(&nNumField, sizeof(int), 1, pFile);

			for (int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
			{
				if (g_EditFieldInfo[nCnt].bUseGame == true)
				{
					fwrite(&g_EditFieldInfo[nCnt], sizeof(EditFieldInfo), 1, pFile);
				}
			}
			fclose(pFile);

			//�Z�[�u����
			bSave = true;

		}
	}
}

//=============================================
//���̓r������Z�[�u����
//=============================================
void reSaveField(void)
{
	//�t�@�C���̓ǂݍ���
	FILE* pFile = fopen(FIELD_FILE_BIN, "rb");

	if (pFile != NULL)
	{
		//���̎g�p���Ă鐔�̓ǂݍ���
		fread(&g_nSaveFieldCnt, sizeof(int), 1, pFile);

		//���̎g�p�����A�G�̓ǂݍ���
		fread(&g_EditFieldInfo[0], sizeof(EditFieldInfo), g_nSaveFieldCnt, pFile);

		//�t�@�C�������
		fclose(pFile);
	}

	else
	{
		return;
	}

	VERTEX_3D* pVtx;
	g_pVtxBuffFieldEdit->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntUseField = 0; nCntUseField < MAX_FIELD; nCntUseField++)
	{
		if (g_EditFieldInfo[nCntUseField].bUseGame == true)
		{
			g_Edit.nEditFieldNumber++;

			//���_���W�̐ݒ�
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField+1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField+2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField+3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);

			g_pVtxField += 4;
		}
	}
	g_pVtxBuffFieldEdit->Unlock();
	g_EditFieldInfo[g_Edit.nEditFieldNumber].bUse = true; //�ۑ�����Ă�Ō�̏��̎��̂��true��
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

		SetCursor(D3DXVECTOR3(g_EditModelInfo[g_Edit.nEditModelNumber].pos.x, 40.0f, g_EditModelInfo[g_Edit.nEditModelNumber].pos.z));
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
				SetCursor(D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].pos.x, 40.0f, g_EditWallInfo[g_Edit.nEditWallNumber].pos.z));

			}
		}
	}
	else if (g_Edit.EditType == EDITTYPE_FIELD || g_Edit.EditType == EDITTYPE_CORRECTIONFIELD)
	{//���ݒu�̎�
		for (int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
		{
			if (g_EditFieldInfo[nCnt].bUse == true)
			{
				//�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_mtxWorldFieldEdit);

				//�����𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_EditFieldInfo[nCnt].rot.y, g_EditFieldInfo[nCnt].rot.x, g_EditFieldInfo[nCnt].rot.z);

				D3DXMatrixMultiply(&g_mtxWorldFieldEdit, &g_mtxWorldFieldEdit, &mtxRot);

				//�ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_EditFieldInfo[nCnt].pos.x, g_EditFieldInfo[nCnt].pos.y, g_EditFieldInfo[nCnt].pos.z);

				D3DXMatrixMultiply(&g_mtxWorldFieldEdit, &g_mtxWorldFieldEdit, &mtxTrans);

				//���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldFieldEdit);

				//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
				pDevice->SetStreamSource(0, g_pVtxBuffFieldEdit, 0, sizeof(VERTEX_3D));

				//���_�t�H�[�}�b�g�̐ݒ�
				pDevice->SetFVF(FVF_VERTEX_3D);

				for (int nCntTex = 0; nCntTex < NUM_FIELD; nCntTex++)
				{
					//�e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_apFieldTextureEdit[nCntTex]);
				}

				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCnt, 2);

				pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
				pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
				SetCursor(D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].pos.x, 40.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].pos.z));

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

	sprintf(&aStr[0], "������@\n[�J�����ړ�]\n�O�i:I ��i:K ��:J �E:L\n���f���ݒu���[�h:1 ���f���ҏW���[�h:2 �ǐݒu���[�h:3 �ǕҏW���[�h:4 ���ݒu���[�h:5 ���ҏW���[�h:6\n���̐ݒu:0\n���̈ړ�	�O�i:W ��i:S ��:A �E:D\n�^�C�v�̐؂�ւ���or�� �J�[�\���؂�ւ���or��");

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

	sprintf(&aStr[0], "\n\n\n\n\n\n\n\n[���f��]\npos:%.1f,%.1f,%.1f\nrot:%.1f,%.1f,%.1f\n\n[��]\npos:%.1f,%.1f,%.1f\nrot:%.1f,%.1f,%.1f\nwide:%.1f\nheight:%.1f\n\n[��]\npos:%.1f,%.1f,%.1f\nrot:%.1f,%.1f,%.1f\nwide:%.1f\ndepth:%.1f",
		g_EditModelInfo[g_Edit.nEditModelNumber].pos.x,
		g_EditModelInfo[g_Edit.nEditModelNumber].pos.y,
		g_EditModelInfo[g_Edit.nEditModelNumber].pos.z,
		g_EditModelInfo[g_Edit.nEditModelNumber].rot.x,
		g_EditModelInfo[g_Edit.nEditModelNumber].rot.y,
		g_EditModelInfo[g_Edit.nEditModelNumber].rot.z,
		g_EditWallInfo[g_Edit.nEditWallNumber].pos.x,
		g_EditWallInfo[g_Edit.nEditWallNumber].pos.y,
		g_EditWallInfo[g_Edit.nEditWallNumber].pos.z,
		g_EditWallInfo[g_Edit.nEditWallNumber].rot.x,
		g_EditWallInfo[g_Edit.nEditWallNumber].rot.y,
		g_EditWallInfo[g_Edit.nEditWallNumber].rot.z,
		g_EditWallInfo[g_Edit.nEditWallNumber].fWide,
		g_EditWallInfo[g_Edit.nEditWallNumber].fHeight,
		g_EditFieldInfo[g_Edit.nEditFieldNumber].pos.x,
		g_EditFieldInfo[g_Edit.nEditFieldNumber].pos.y,
		g_EditFieldInfo[g_Edit.nEditFieldNumber].pos.z,
		g_EditFieldInfo[g_Edit.nEditFieldNumber].rot.x,
		g_EditFieldInfo[g_Edit.nEditFieldNumber].rot.y,
		g_EditFieldInfo[g_Edit.nEditFieldNumber].rot.z,
		g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide,
		g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

EditModelInfo* GetEditModelinfo(void)
{
	return &g_EditModelInfo[0];
}

Edit* GetEdit(void)
{
	return &g_Edit;
}
