//=============================================
//
//3D�e���v���[�g[Model.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "model.h"
#include "input.h"
#include "camera.h"
#include "field.h"
#include "shadow.h"

//=============================================
//�}�N����`
//=============================================
#define DAMPING_COEFFICIENT	(0.2f) //��R��
#define MAX_MODEL	(256) //���f���̍ő吔 
#define MODEL_SHADOW_RADIUS	(40.0f)

//=============================================
//�O���[�o���ϐ�
//=============================================
LPDIRECT3DTEXTURE9 g_apTextureModel[NUM_MODEL][NUM_TEXTURE] = {}; //�e�N�X�`���|�C���^
model g_aModel[MAX_MODEL];

//=============================================
//���f���̎��
//=============================================
static const char* MODEL_NAME[NUM_MODEL] =
{
	"data\\MODEL\\iwa.x",
	"data\\MODEL\\hyoshiki.x"
};

//=============================================
//�e�N�X�`���̎��
//=============================================
//static const char* TEXTURE_NAME[NUM_TEXTURE] =
//{
//	"data\\TEXTURE\\thumb-gray-rock-texture-stone-texture-gray-stone-background-rock-background-natural-stone-texture.jpg",
//	"data\\TEXTURE\\metal_00005.jpg",
//	"data\\TEXTURE\\yoshida.png",
//};

//=============================================
//�|���S���̏���������
//=============================================
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCntType = 0; nCntType < NUM_MODEL; nCntType++)
	{
		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(MODEL_NAME[nCntType],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aModel[nCntType].pBuffMat,
			NULL,
			&g_aModel[nCntType].nNumMat,
			&g_aModel[nCntType].pMesh);

		D3DXMATERIAL* pMat; //�}�e���A���|�C���^
		pMat = (D3DXMATERIAL*)g_aModel[nCntType].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_aModel[nCntType].nNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_apTextureModel[nCntType][nCntMat]
				);
			}
		}
	}

	int nNumVtx; //���_��
	DWORD sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff; //���_�o�b�t�@�̃|�C���^

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		//���_���̎擾
		nNumVtx = g_aModel[g_aModel[nCnt].nType].pMesh->GetNumVertices();
		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_aModel[g_aModel[nCnt].nType].pMesh->GetFVF());

		g_aModel[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //���f���̏����ʒu
		g_aModel[nCnt].Minpos = D3DXVECTOR3(100000.0f, 1000000.0f, 1000000.0f); //���f���̍ŏ��ʒu
		g_aModel[nCnt].Maxpos = D3DXVECTOR3(-10000.0f, -1000000.0f, -100000.0f); //���f���̍ő�ʒu
		g_aModel[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�����̕���
		g_aModel[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�����̈ړ����x
		g_aModel[nCnt].nShadow = -1;
		g_aModel[nCnt].nType = MODELTYPE_ROCK;
		g_aModel[nCnt].bUse = false;

		//���_�o�b�t�@�̃��b�N
		g_aModel[g_aModel[nCnt].nType].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			if (vtx.x > g_aModel[nCnt].Maxpos.x)
			{
				g_aModel[nCnt].Maxpos.x = vtx.x;
			}
			if (vtx.x < g_aModel[nCnt].Minpos.x)
			{
				g_aModel[nCnt].Minpos.x = vtx.x;
			}

			if (vtx.y > g_aModel[nCnt].Maxpos.y)
			{
				g_aModel[nCnt].Maxpos.y = vtx.y;
			}
			if (vtx.y < g_aModel[nCnt].Minpos.y)
			{
				g_aModel[nCnt].Minpos.y = vtx.y;
			}

			if (vtx.z > g_aModel[nCnt].Maxpos.z)
			{
				g_aModel[nCnt].Maxpos.z = vtx.z;
			}
			if (vtx.z < g_aModel[nCnt].Minpos.z)
			{
				g_aModel[nCnt].Minpos.z = vtx.z;
			}
		}

		g_aModel[g_aModel[nCnt].nType].pMesh->UnlockVertexBuffer();
	}
}

//=============================================
//�|���S���̏I������
//=============================================
void UninitModel(void)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_aModel[nCnt].bUse == true)
		{
			//���b�V���̔j��
			if (g_aModel[nCnt].pMesh != NULL)
			{
				g_aModel[nCnt].pMesh->Release();
				g_aModel[nCnt].pMesh = NULL;
			}

			//�}�e���A���̔j��
			if (g_aModel[nCnt].pBuffMat != NULL)
			{
				g_aModel[nCnt].pBuffMat->Release();
				g_aModel[nCnt].pBuffMat = NULL;
			}
		}
	}
}

//=============================================
//�|���S���̍X�V����
//=============================================
void UpdateModel(void)
{
	D3DXVECTOR3 pFieldPos = GetFieldPos();
	for(int nCnt = 0;nCnt<MAX_MODEL;nCnt++)
	{
		if (g_aModel[nCnt].bUse == true)
		{
			SetShadowPos(g_aModel[nCnt].nShadow, D3DXVECTOR3 (g_aModel[nCnt].pos.x, pFieldPos.y +0.1f,g_aModel[nCnt].pos.z), MODEL_SHADOW_RADIUS);
		}
	}
}

//=============================================
//�|���S���̕`�揈��
//=============================================
void DrawModel(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DMATERIAL9 matDef; //���݂̃}�e���A���̕ۑ�
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X

	//���݂��擾
	pDevice->GetMaterial(&matDef);

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_aModel[nCnt].bUse == true)
		{
			//�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aModel[nCnt].mtxWorld);

			//���e�X�g��L��
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aModel[nCnt].rot.y, g_aModel[nCnt].rot.x, g_aModel[nCnt].rot.z);

			D3DXMatrixMultiply(&g_aModel[nCnt].mtxWorld, &g_aModel[nCnt].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aModel[nCnt].pos.x, g_aModel[nCnt].pos.y, g_aModel[nCnt].pos.z);

			D3DXMatrixMultiply(&g_aModel[nCnt].mtxWorld, &g_aModel[nCnt].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aModel[nCnt].mtxWorld);

			D3DXMATERIAL* pMat; //�}�e���A��

			pMat = (D3DXMATERIAL*)g_aModel[g_aModel[nCnt].nType].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aModel[g_aModel[nCnt].nType].nNumMat; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_apTextureModel[g_aModel[nCnt].nType][nCntMat]);

				//�p�[�c�̐ݒ�
				g_aModel[g_aModel[nCnt].nType].pMesh->DrawSubset(nCntMat);
			}
			//���e�X�g�𖳌���
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

			////���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			//pDevice->SetStreamSource(0, g_pVtxBuffModel, 0, sizeof(VERTEX_3D));

			////���_�t�H�[�}�b�g�̐ݒ�
			//pDevice->SetFVF(FVF_VERTEX_3D);

			////�|���S���̕`��
			//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}
	//�ۑ����Ă��}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================
//�|���S���̐ݒ�
//=============================================
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot,ModelType nType)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_aModel[nCnt].bUse == false)
		{
			g_aModel[nCnt].pos = pos;
			g_aModel[nCnt].rot = rot;
			g_aModel[nCnt].nType = nType;
			g_aModel[nCnt].nShadow = SetShadow();
			g_aModel[nCnt].bUse = true;
			break;
		}
	}
}

//=============================================
//�|���S���̏��擾
//=============================================
model* GetModel(void)
{
	return &g_aModel[0];
}