//=============================================
//
//3Dテンプレート[shadow.cpp]
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
//マクロ定義
//=============================================
#define SHADOW_WIDE	(5)
#define SHADOW_DEPTH	(5)

//=============================================
//グローバル変数
//=============================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL; //テクスチャポインタ
Shadow g_aShadow[MAX_SHADOW];
//D3DXVECTOR3 g_moveShadow; //移動量
D3DXMATRIX	g_mtxWorldShadow;

//=============================================
//影の初期化処理
//=============================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\shadow000.jpg",
		&g_pTextureShadow
	);

	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		g_aShadow[nCnt].pos = D3DXVECTOR3(0.0f, 0.05f, 0.0f); //プレイヤーの初期位置
		g_aShadow[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //初期の移動速度
		g_aShadow[nCnt].fRadius = SHADOW_WIDE; //初期の移動速度
		g_aShadow[nCnt].nNumber = -1; //初期の移動速度
		g_aShadow[nCnt].bUse = false; //初期の移動速度
	}
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW, 
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED, 
			&g_pVtxBuffShadow, 
			NULL);

		VERTEX_3D* pVtx;

		//頂点バッファをロックし頂点情報へのポインタを取得
		g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-g_aShadow[nCnt].fRadius, 0.0f, g_aShadow[nCnt].fRadius);
		pVtx[1].pos = D3DXVECTOR3(g_aShadow[nCnt].fRadius, 0.0f, g_aShadow[nCnt].fRadius);
		pVtx[2].pos = D3DXVECTOR3(-g_aShadow[nCnt].fRadius, 0.0f, -g_aShadow[nCnt].fRadius);
		pVtx[3].pos = D3DXVECTOR3(g_aShadow[nCnt].fRadius, 0.0f, -g_aShadow[nCnt].fRadius);

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
	g_pVtxBuffShadow->Unlock();
}

//=============================================
//影の終了処理
//=============================================
void UninitShadow(void)
{
	//テクスチャの破棄
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//=============================================
//影の更新処理
//=============================================
void UpdateShadow(void)
{
	VERTEX_3D* pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		if (g_aShadow[nCnt].bUse == true)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-g_aShadow[nCnt].fRadius, 0.0f, g_aShadow[nCnt].fRadius);
			pVtx[1].pos = D3DXVECTOR3(g_aShadow[nCnt].fRadius, 0.0f, g_aShadow[nCnt].fRadius);
			pVtx[2].pos = D3DXVECTOR3(-g_aShadow[nCnt].fRadius, 0.0f, -g_aShadow[nCnt].fRadius);
			pVtx[3].pos = D3DXVECTOR3(g_aShadow[nCnt].fRadius, 0.0f, -g_aShadow[nCnt].fRadius);

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
	}
	g_pVtxBuffShadow->Unlock();
}

//=============================================
//影の描画処理
//=============================================
void DrawShadow(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス

	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		if (g_aShadow[nCnt].bUse == true)
		{
			//減算合成処理
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);

			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			//マトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldShadow);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCnt].rot.y, g_aShadow[nCnt].rot.x, g_aShadow[nCnt].rot.z);

			D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCnt].pos.x, g_aShadow[nCnt].pos.y, g_aShadow[nCnt].pos.z);

			D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldShadow);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureShadow);

			//影の描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCnt, 2);


		}
	}
	//通常の合成に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================
//影の設定処理
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
//影の位置の設定処理
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

