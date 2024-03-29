//=============================================
//
//マップエディター[field.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "field.h"
#include "input.h"
//#include "enemy.h"
//#include "Screen.h"
//#include"bullet.h"
// 
//=============================================
//グローバル変数
//=============================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField = NULL;
LPDIRECT3DTEXTURE9 g_pTextureField = NULL; //テクスチャポインタ
//D3DXVECTOR3 g_movefield; //移動量
D3DXMATRIX	g_mtxWorldField;
Field g_afield[MAX_FIELD];

//=============================================
//ポリゴンの初期化処理
//=============================================
void InitField(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ground.jpeg",
		&g_pTextureField
	);

	for (int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
	{
		g_afield[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //床の初期位置
		g_afield[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //床の初期方向
		g_afield[nCnt].fWide = FIELD_WIDE; //床の横幅
		g_afield[nCnt].fDepth = FIELD_DEPTH; //床の縦幅
		g_afield[nCnt].bUse = false;
	}
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_FIELD, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffField, NULL);

	VERTEX_3D* pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-FIELD_WIDE, 0.0f, FIELD_DEPTH);
		pVtx[1].pos = D3DXVECTOR3(FIELD_WIDE, 0.0f, FIELD_DEPTH);
		pVtx[2].pos = D3DXVECTOR3(-FIELD_WIDE, 0.0f, -FIELD_DEPTH);
		pVtx[3].pos = D3DXVECTOR3(FIELD_WIDE, 0.0f, -FIELD_DEPTH);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャの座標指定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	g_pVtxBuffField->Unlock();
}

//=============================================
//ポリゴンの終了処理
//=============================================
void UninitField(void)
{
	//テクスチャの破棄
	if (g_pTextureField != NULL)
	{
		g_pTextureField->Release();
		g_pTextureField = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffField != NULL)
	{
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}
}

//=============================================
//ポリゴンの更新処理
//=============================================
void UpdateField(void)
{
	VERTEX_3D* pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);


	for (int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-g_afield[nCnt].fWide, 0.0f, g_afield[nCnt].fDepth);
		pVtx[1].pos = D3DXVECTOR3(g_afield[nCnt].fWide, 0.0f, g_afield[nCnt].fDepth);
		pVtx[2].pos = D3DXVECTOR3(-g_afield[nCnt].fWide, 0.0f, -g_afield[nCnt].fDepth);
		pVtx[3].pos = D3DXVECTOR3(g_afield[nCnt].fWide, 0.0f, -g_afield[nCnt].fDepth);
		pVtx += 4;
	}

	g_pVtxBuffField->Unlock();
}

//=============================================
//ポリゴンの描画処理
//=============================================
void DrawField(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス

	for (int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
	{
		if (g_afield[nCnt].bUse == true)
		{
			//マトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldField);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_afield[nCnt].rot.y, g_afield[nCnt].rot.x, g_afield[nCnt].rot.z);

			D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_afield[nCnt].pos.x, g_afield[nCnt].pos.y, g_afield[nCnt].pos.z);

			D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldField);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureField);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCnt, 2);
		}
	}
}

//=============================================
//ポリゴンの描画処理
//=============================================
void SetField(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWide, float fDepth, int nType)
{
	for (int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
	{
		if (g_afield[nCnt].bUse == false)
		{
			g_afield[nCnt].pos = pos;
			g_afield[nCnt].rot = rot;
			g_afield[nCnt].fWide = fWide;
			g_afield[nCnt].fDepth = fDepth;
			g_afield[nCnt].nType = nType;
			g_afield[nCnt].bUse = true;
			break;
		}
	}
}

D3DXVECTOR3 GetFieldPos(void)
{
	return g_afield->pos;
}