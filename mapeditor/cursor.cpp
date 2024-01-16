//=============================================
//
//マップエディター[cursor.h]
//Auther Matsuda Towa
//
//=============================================
#include "cursor.h"

//=============================================
//マクロ定義
//=============================================
#define CURSOR_WIDE	(20)
#define CURSOR_DEPTH	(20)

//=============================================
//グローバル変数
//=============================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCursor = NULL;
LPDIRECT3DTEXTURE9 g_pTextureCursor = NULL; //テクスチャポインタ
Cursol g_Cursol; //カーソルの情報の構造体

//=============================================
//カーソルの初期化
//=============================================
void InitCursor(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\cursor.png",
		&g_pTextureCursor
	);

	g_Cursol.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //カーソルの初期位置
	g_Cursol.IndexEdit = 0; //カーソルを合わせる初期化
	g_Cursol.bUse = false; //使用しない

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffCursor, NULL);

	VERTEX_3D* pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffCursor->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-CURSOR_WIDE, CURSOR_DEPTH, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(CURSOR_WIDE, CURSOR_DEPTH, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-CURSOR_WIDE, -CURSOR_DEPTH, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(CURSOR_WIDE, -CURSOR_DEPTH, 0.0f);

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

	g_pVtxBuffCursor->Unlock();
}

//=============================================
//カーソルの終了処理
//=============================================
void UninitCursor(void)
{
	//テクスチャの破棄g_mtxWorldCursor
	if (g_pTextureCursor != NULL)
	{
		g_pTextureCursor->Release();
		g_pTextureCursor = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffCursor != NULL)
	{
		g_pVtxBuffCursor->Release();
		g_pVtxBuffCursor = NULL;
	}
}

//=============================================
//カーソルの更新処理
//=============================================
void UpdateCursor(void)
{

}

//=============================================
//カーソルの描画処理
//=============================================
void DrawCursor(void)
{

	if (g_Cursol.bUse == true)
	{
		//デバイスの取得
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		D3DXMATRIX mtxTrans; //計算用マトリックス

		D3DXMATRIX mtxView; //ビューマトリックス取得用

		//マトリックスの初期化
		D3DXMatrixIdentity(&g_Cursol.mtxWorld);

		//ビューマトリックスを取得
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//ポリゴンの正面をカメラに向ける
		D3DXMatrixInverse(&g_Cursol.mtxWorld, NULL, &mtxView);

		g_Cursol.mtxWorld._41 = 0.0f;
		g_Cursol.mtxWorld._42 = 0.0f;
		g_Cursol.mtxWorld._43 = 0.0f;

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Cursol.pos.x, g_Cursol.pos.y, g_Cursol.pos.z);

		D3DXMatrixMultiply(&g_Cursol.mtxWorld, &g_Cursol.mtxWorld, &mtxTrans);

		//ライトを無効にする
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Cursol.mtxWorld);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffCursor, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureCursor);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		//ライトを有効に戻す
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}

//=============================================
//カーソルの設定処理
//=============================================
void SetCursor(D3DXVECTOR3 pos)
{
	g_Cursol.pos = pos;
	g_Cursol.bUse = true; //使用する
}
