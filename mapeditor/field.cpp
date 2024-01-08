//=============================================
//
//3Dテンプレート[field.cpp]
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
//マクロ定義
//=============================================
#define FIELD_WIDE	(500)
#define FIELD_DEPTH	(500)

//=============================================
//グローバル変数
//=============================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField = NULL;
LPDIRECT3DTEXTURE9 g_pTextureField = NULL; //テクスチャポインタ
D3DXVECTOR3 g_posField; //位置
D3DXVECTOR3 g_rotField; //向き
//D3DXVECTOR3 g_movefield; //移動量
D3DXMATRIX	g_mtxWorldField;

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

	g_posField = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //プレイヤーの初期位置
	g_rotField = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //初期の移動速度

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffField, NULL);

	VERTEX_3D* pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

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
//ポリゴンの描画処理
//=============================================
void DrawField(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス

	//マトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldField);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotField.y, g_rotField.x, g_rotField.z);

	D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posField.x, g_posField.y, g_posField.z);

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
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

D3DXVECTOR3 GetFieldPos(void)
{
	return g_posField;
}