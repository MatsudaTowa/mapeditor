//=============================================
//
//3Dテンプレート[light.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "light.h"
#include "input.h"

//マクロ定義
#define NUM_LIGHT	(3) //ライトの種類

//グローバル変数
D3DLIGHT9 g_aLight[NUM_LIGHT];

//=============================================
//ライトの初期化処理
//=============================================
void InitLight(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXVECTOR3 vecDir; //設定方向ベクトル

	//ライト情報のクリア
	ZeroMemory(&g_aLight[0], sizeof(D3DLIGHT9));

	for (int nCnt = 0; nCnt < NUM_LIGHT; nCnt++)
	{
		//ライトの種類を設定
		g_aLight[nCnt].Type = D3DLIGHT_DIRECTIONAL;

		//ライトの拡散光の設定
		g_aLight[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		if (nCnt == 0)
		{
			//ライトの方向を設定
			vecDir = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
		}
		else if (nCnt == 1)
		{
			//ライトの方向を設定
			vecDir = D3DXVECTOR3(0.2f, 0.8f, 0.4f);
		}
		else if (nCnt == 2)
		{
			//ライトの方向を設定
			vecDir = D3DXVECTOR3(-0.7f, -0.8f, -0.4f);
		}



		D3DXVec3Normalize(&vecDir, &vecDir); //正規化

		g_aLight[nCnt].Direction = vecDir;

		//ライトを設定
		pDevice->SetLight(nCnt, &g_aLight[nCnt]);

		//ライトを有効化
		pDevice->LightEnable(nCnt, TRUE);
	}
}

//=============================================
//ライトの終了処理
//=============================================
void UninitLight(void)
{
}

//=============================================
//ライトの更新処理
//=============================================
void UpdateLight(void)
{

}