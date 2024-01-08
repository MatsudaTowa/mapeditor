//=============================================
//
//3Dテンプレート[Model.cpp]
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
//マクロ定義
//=============================================
#define DAMPING_COEFFICIENT	(0.2f) //抵抗力
#define MAX_MODEL	(256) //モデルの最大数 
#define MODEL_SHADOW_RADIUS	(40.0f)

//=============================================
//グローバル変数
//=============================================
LPDIRECT3DTEXTURE9 g_apTextureModel[NUM_MODEL][NUM_TEXTURE] = {}; //テクスチャポインタ
model g_aModel[MAX_MODEL];

//=============================================
//モデルの種類
//=============================================
static const char* MODEL_NAME[NUM_MODEL] =
{
	"data\\MODEL\\iwa.x",
	"data\\MODEL\\hyoshiki.x"
};

//=============================================
//テクスチャの種類
//=============================================
//static const char* TEXTURE_NAME[NUM_TEXTURE] =
//{
//	"data\\TEXTURE\\thumb-gray-rock-texture-stone-texture-gray-stone-background-rock-background-natural-stone-texture.jpg",
//	"data\\TEXTURE\\metal_00005.jpg",
//	"data\\TEXTURE\\yoshida.png",
//};

//=============================================
//ポリゴンの初期化処理
//=============================================
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	for (int nCntType = 0; nCntType < NUM_MODEL; nCntType++)
	{
		//Xファイルの読み込み
		D3DXLoadMeshFromX(MODEL_NAME[nCntType],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aModel[nCntType].pBuffMat,
			NULL,
			&g_aModel[nCntType].nNumMat,
			&g_aModel[nCntType].pMesh);

		D3DXMATERIAL* pMat; //マテリアルポインタ
		pMat = (D3DXMATERIAL*)g_aModel[nCntType].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_aModel[nCntType].nNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_apTextureModel[nCntType][nCntMat]
				);
			}
		}
	}

	int nNumVtx; //頂点数
	DWORD sizeFVF; //頂点フォーマットのサイズ
	BYTE* pVtxBuff; //頂点バッファのポインタ

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		//頂点数の取得
		nNumVtx = g_aModel[g_aModel[nCnt].nType].pMesh->GetNumVertices();
		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_aModel[g_aModel[nCnt].nType].pMesh->GetFVF());

		g_aModel[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //モデルの初期位置
		g_aModel[nCnt].Minpos = D3DXVECTOR3(100000.0f, 1000000.0f, 1000000.0f); //モデルの最小位置
		g_aModel[nCnt].Maxpos = D3DXVECTOR3(-10000.0f, -1000000.0f, -100000.0f); //モデルの最大位置
		g_aModel[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //初期の方向
		g_aModel[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //初期の移動速度
		g_aModel[nCnt].nShadow = -1;
		g_aModel[nCnt].nType = MODELTYPE_ROCK;
		g_aModel[nCnt].bUse = false;

		//頂点バッファのロック
		g_aModel[g_aModel[nCnt].nType].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//頂点座標の代入
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
//ポリゴンの終了処理
//=============================================
void UninitModel(void)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_aModel[nCnt].bUse == true)
		{
			//メッシュの破棄
			if (g_aModel[nCnt].pMesh != NULL)
			{
				g_aModel[nCnt].pMesh->Release();
				g_aModel[nCnt].pMesh = NULL;
			}

			//マテリアルの破棄
			if (g_aModel[nCnt].pBuffMat != NULL)
			{
				g_aModel[nCnt].pBuffMat->Release();
				g_aModel[nCnt].pBuffMat = NULL;
			}
		}
	}
}

//=============================================
//ポリゴンの更新処理
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
//ポリゴンの描画処理
//=============================================
void DrawModel(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DMATERIAL9 matDef; //現在のマテリアルの保存
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス

	//現在を取得
	pDevice->GetMaterial(&matDef);

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_aModel[nCnt].bUse == true)
		{
			//マトリックスの初期化
			D3DXMatrixIdentity(&g_aModel[nCnt].mtxWorld);

			//αテストを有効
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aModel[nCnt].rot.y, g_aModel[nCnt].rot.x, g_aModel[nCnt].rot.z);

			D3DXMatrixMultiply(&g_aModel[nCnt].mtxWorld, &g_aModel[nCnt].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aModel[nCnt].pos.x, g_aModel[nCnt].pos.y, g_aModel[nCnt].pos.z);

			D3DXMatrixMultiply(&g_aModel[nCnt].mtxWorld, &g_aModel[nCnt].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aModel[nCnt].mtxWorld);

			D3DXMATERIAL* pMat; //マテリアル

			pMat = (D3DXMATERIAL*)g_aModel[g_aModel[nCnt].nType].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aModel[g_aModel[nCnt].nType].nNumMat; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, g_apTextureModel[g_aModel[nCnt].nType][nCntMat]);

				//パーツの設定
				g_aModel[g_aModel[nCnt].nType].pMesh->DrawSubset(nCntMat);
			}
			//αテストを無効に
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

			////頂点バッファをデータストリームに設定
			//pDevice->SetStreamSource(0, g_pVtxBuffModel, 0, sizeof(VERTEX_3D));

			////頂点フォーマットの設定
			//pDevice->SetFVF(FVF_VERTEX_3D);

			////ポリゴンの描画
			//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}
	//保存してたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//=============================================
//ポリゴンの設定
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
//ポリゴンの情報取得
//=============================================
model* GetModel(void)
{
	return &g_aModel[0];
}