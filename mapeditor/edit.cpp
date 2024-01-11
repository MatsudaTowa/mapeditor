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
#include <string.h>
#include <stdio.h>
//マクロ定義
#define NUM_KEY_MAX	(256)
#define MOVE_CURSOR	(2.0f) //カーソル移動値
#define EDIT_WIDE	(1280) //敵を置ける最大値
#define EDIT_HEIGHT	(700) //敵を置ける最大値
#define ENEMY_LIFE	(3) //敵のライフ
#define TIME_CHANGE	(5) //時間を進める
#define EDIT_SELECT	(2) //エディットセレクト数（敵・ブロック）
#define NUM_TYPE_EDIT	(2) //エディットで置ける種類 (モデル)

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEdit = NULL;
LPDIRECT3DTEXTURE9 g_apTextureEdit[NUM_TYPE_EDIT][NUM_TEXTURE] = {}; //テクスチャポインタ
Edit g_Edit; //エディット情報
EditModelInfo g_EditModelInfo[MAX_MODEL]; //モデルのエディット情報

bool g_bSave = true; //セーブできるか
int g_nSaveModelCnt;
int g_nSave;
float g_fAlpha; //α値
float g_fFlash; //点滅
int g_nEditModelNumber; //追従するカメラの対象

//=============================================
//モデルの種類
//=============================================
static const char* MODEL_NAME[NUM_MODEL] =
{
	"data\\MODEL\\iwa.x",
	"data\\MODEL\\hyoshiki.x"
};

//=============================================
//エディットの初期化処理
//=============================================
void InitEdit(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//int nCntEdit;
	//デバイスの取得
	pDevice = GetDevice();

	g_Edit.EditType = EDITTYPE_MODEL;

	for (int nCnt = 0; nCnt < NUM_MODEL; nCnt++)
	{
		//Xファイルの読み込み
		D3DXLoadMeshFromX(MODEL_NAME[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_EditModelInfo[nCnt].pBuffMat,
			NULL,
			&g_EditModelInfo[nCnt].nNumMat,
			&g_EditModelInfo[nCnt].pMesh);


		D3DXMATERIAL* pMat; //マテリアルポインタ
		pMat = (D3DXMATERIAL*)g_EditModelInfo[nCnt].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_EditModelInfo[nCnt].nNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_apTextureEdit[nCnt][nCntMat]
				);
			}
		}
	}

	//ブロックに書き込む情報の初期化
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

	g_fAlpha = 0.2f;
	g_fFlash = 0.02f;
	g_nEditModelNumber = 0;
	g_nSaveModelCnt = 0;
	g_nSave = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_MODEL, D3DUSAGE_WRITEONLY, 4, D3DPOOL_MANAGED, &g_pVtxBuffEdit, NULL);

	VERTEX_3D* pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffEdit->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);


		//if (g_EditModelInfo[g_nSaveModelCnt].nType == BLOCKTYPE_SNOW)
		//{
		//	//テクスチャ座標の設定
		//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		//	pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		//	pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);
		//}
		//else
		//{
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		//}

		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffEdit->Unlock();
}

//=============================================
//終了処理
//=============================================
void UninitEdit(void)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		//メッシュの破棄
		if (g_EditModelInfo[nCnt].pMesh != NULL)
		{
			g_EditModelInfo[nCnt].pMesh->Release();
			g_EditModelInfo[nCnt].pMesh = NULL;
		}

		//マテリアルの破棄
		if (g_EditModelInfo[nCnt].pBuffMat != NULL)
		{
			g_EditModelInfo[nCnt].pBuffMat->Release();
			g_EditModelInfo[nCnt].pBuffMat = NULL;
		}
	}
}

//=============================================
//更新処理
//=============================================
void UpdateEdit(void)
{

	if (g_fAlpha >= 1.0f || g_fAlpha <= 0.0f)
	{
		g_fFlash *= -1.0f;
	}
	g_fAlpha += g_fFlash;


	//設置するものの選択
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
	{//オブジェクト
		SaveModel();
	}
	else if (g_Edit.EditType == EDITTYPE_CORRECTIONMODEL)
	{//オブジェクト置きなおし
		CorrectionModel();
	}


	Camera* pCamera = GetCamera();

	if (pCamera->type == CAMERATYPE_EDIT)
	{

		pCamera->posV = D3DXVECTOR3(g_EditModelInfo->pos.x - sinf(pCamera->rot.y) * 200.0f, g_EditModelInfo->pos.y + 100.0f, g_EditModelInfo->pos.z - cosf(pCamera->rot.y) * 200.0f);
		pCamera->posR = g_EditModelInfo->pos;

	}

	//return bSave;
//}
}

//=============================================
//モデルのセーブ処理
//=============================================
void SaveModel(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//int nCntEdit;
	//デバイスの取得
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

	//モデルの設置
	if (GetKeyboardTrigger(DIK_0) == true)
	{
		g_EditModelInfo[g_nEditModelNumber + 1].pos = g_EditModelInfo[g_nEditModelNumber].pos;
		g_EditModelInfo[g_nEditModelNumber + 1].rot = g_EditModelInfo[g_nEditModelNumber].rot;
		g_EditModelInfo[g_nEditModelNumber + 1].nType = g_EditModelInfo[g_nEditModelNumber].nType;
		g_EditModelInfo[g_nEditModelNumber + 1].bUse = true;
		g_EditModelInfo[g_nEditModelNumber].bUseGame = true;
		g_nSaveModelCnt++;
		g_nEditModelNumber++;
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);

	////テクスチャ座標の設定
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//モデルの設置
	if (GetKeyboardTrigger(DIK_F4) == true)
	{//セーブ処理
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

			//セーブ完了
			bSave = true;

		}
	}
}

//=============================================
//置いたモデルの編集
//=============================================
void CorrectionModel(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//int nCntEdit;
	//デバイスの取得
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

	//モデルの設置
	if (GetKeyboardTrigger(DIK_0) == true)
	{
		g_EditModelInfo[g_nEditModelNumber].bUseGame = true;
	}

	if (GetKeyboardTrigger(DIK_F4) == true)
	{//セーブ処理
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

			//セーブ完了
			bSave = true;

		}
	}
}

////=============================================
////ブロックのセーブ処理
////=============================================
//void SaveBlock(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//	pDevice = GetDevice();
//
//	VERTEX_3D* pVtx;
//
//	Player* pPlayer = GetPlayer();
//	g_pVtxBuffEdit->Lock(0, 0, (void**)&pVtx, 0);
//	if (GetKeyboardTrigger(DIK_W) == true)
//	{
//		g_EditModelInfo[g_nSaveModelCnt].pos.y -= BLOCK_CURSOR;
//	}
//	if (GetKeyboardTrigger(DIK_S) == true)
//	{
//		g_EditModelInfo[g_nSaveModelCnt].pos.y += BLOCK_CURSOR;
//	}
//	if (GetKeyboardTrigger(DIK_A) == true && g_EditModelInfo[g_nSaveModelCnt].pos.x > 0.0f)
//	{
//		g_EditModelInfo[g_nSaveModelCnt].pos.x -= BLOCK_CURSOR;
//	}
//	if (GetKeyboardTrigger(DIK_D) == true && g_EditModelInfo[g_nSaveModelCnt].pos.x < EDIT_WIDE)
//	{
//		g_EditModelInfo[g_nSaveModelCnt].pos.x += BLOCK_CURSOR;
//	}
//	if (GetKeyboardTrigger(DIK_1) == true)
//	{
//		g_EditModelInfo[g_nSaveModelCnt].pos =  pPlayer->pos;
//	}
//
//
//	if (GetKeyboardTrigger(DIK_RIGHT) == true)
//	{
//		g_EditModelInfo[g_nSaveModelCnt].nType++;
//		if (g_EditModelInfo[g_nSaveModelCnt].nType >= BLOCKTYPE_MAX)
//		{
//			g_EditModelInfo[g_nSaveModelCnt].nType = 0;
//		}
//	}
//	else if (GetKeyboardTrigger(DIK_LEFT) == true)
//	{
//		g_EditModelInfo[g_nSaveModelCnt].nType--;
//		if (g_EditModelInfo[g_nSaveModelCnt].nType < 0)
//		{
//			g_EditModelInfo[g_nSaveModelCnt].nType = BLOCKTYPE_MAX-1 ;
//		}
//	}
//
//	//ブロックの設置
//	if (GetKeyboardTrigger(DIK_0) == true)
//	{
//		g_EditModelInfo[g_nSaveModelCnt + 1].pos = g_EditModelInfo[g_nSaveModelCnt].pos;
//		g_EditModelInfo[g_nSaveModelCnt + 1].nType = g_EditModelInfo[g_nSaveModelCnt].nType;
//		g_EditModelInfo[g_nSaveModelCnt + 1].bUse = true;
//		g_nSaveModelCnt++;
//	}
//
//	D3DXVECTOR3 Vtx = ScreenConversion(g_EditModelInfo[g_nSaveModelCnt].pos);
//
//
//	pVtx += (VERTEX * g_nSaveModelCnt);
//
//	//頂点座標の設定
//	pVtx[0].pos.x = Vtx.x - BLOCK_RADIUS;
//	pVtx[0].pos.y = Vtx.y - BLOCK_RADIUS;
//	pVtx[0].pos.z = 0.0f;
//
//	pVtx[1].pos.x = Vtx.x + BLOCK_RADIUS;
//	pVtx[1].pos.y = Vtx.y - BLOCK_RADIUS;
//	pVtx[1].pos.z = 0.0f;
//
//	pVtx[2].pos.x = Vtx.x - BLOCK_RADIUS;
//	pVtx[2].pos.y = Vtx.y + BLOCK_RADIUS;
//	pVtx[2].pos.z = 0.0f;
//
//	pVtx[3].pos.x = Vtx.x + BLOCK_RADIUS;
//	pVtx[3].pos.y = Vtx.y + BLOCK_RADIUS;
//	pVtx[3].pos.z = 0.0f;
//
//	//pVtx[1].pos = D3DXVECTOR3(g_EditModelInfo[g_nSaveModelCnt].pos.x + (MOVE_CURSOR * 0.5f), g_EditModelInfo[g_nSaveModelCnt].pos.y, 0.0f);
//	//pVtx[2].pos = D3DXVECTOR3(g_EditModelInfo[g_nSaveModelCnt].pos.x - (MOVE_CURSOR * 0.5f), g_EditModelInfo[g_nSaveModelCnt].pos.y + MOVE_CURSOR, 0.0f);
//	//pVtx[3].pos = D3DXVECTOR3(g_EditModelInfo[g_nSaveModelCnt].pos.x + (MOVE_CURSOR * 0.5f), g_EditModelInfo[g_nSaveModelCnt].pos.y + MOVE_CURSOR, 0.0f);
//
//	//rhwの設定
//	pVtx[0].rhw = 1.0f;
//	pVtx[1].rhw = 1.0f;
//	pVtx[2].rhw = 1.0f;
//	pVtx[3].rhw = 1.0f;
//
//	//頂点カラーの設定
//	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);
//	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);
//	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);
//	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);
//
//
//	if (g_EditModelInfo[g_nSaveModelCnt].nType == BLOCKTYPE_SNOW)
//	{
//		//テクスチャ座標の設定
//		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);
//	}
//
//
//
//	//ブロック設置
//	if (GetKeyboardTrigger(DIK_F4) == true)
//	{//セーブ処理
//		int nNumBlock = 0;
//		bool bSave = false;
//		char aSave[256];
//		FILE* pFile = fopen(FILE_BLOCK, "wb");
//
//
//		for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
//		{
//			if (g_EditModelInfo[nCnt].bUse == true)
//			{
//				nNumBlock++;
//			}
//		}
//
//		if (pFile != NULL)
//		{
//			fwrite(&nNumBlock, sizeof(int), 1, pFile);
//			for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
//			{
//				if (g_EditModelInfo[nCnt].bUse == true)
//				{
//					fwrite(&g_EditModelInfo[nCnt], sizeof(EditBlockInfo), 1, pFile);
//				}
//			}
//			fclose(pFile);
//
//			//セーブ完了
//			bSave = true;
//
//		}
//
//	}
//}

//=============================================
//敵の途中からセーブ処理
//=============================================
void reSaveModel(void)
{
	//ファイルの読み込み
	FILE* pFile = fopen(MODEL_FILE_BIN, "rb");

	if (pFile != NULL)
	{
		//敵の使用してる数の読み込み
		fread(&g_nSaveModelCnt, sizeof(int), 1, pFile);

		//敵の使用数分、敵の読み込み
		fread(&g_EditModelInfo[0], sizeof(EditModelInfo), g_nSaveModelCnt, pFile);

		//ファイルを閉じる
		fclose(pFile);

	}

	else
	{
		return;
	}
}

////=============================================
////ブロックの途中からセーブ処理
////=============================================
//void reSaveBlock(void)
//{
//	//ファイルの読み込み
//	FILE* pFile = fopen(FILE_BLOCK, "rb");
//
//	if (pFile != NULL)
//	{
//		//ブロックの使用してる数の読み込み
//		fread(&g_nSaveModelCnt, sizeof(int), 1, pFile);
//
//		//ブロックの使用数分、敵の読み込み
//		fread(&g_EditModelInfo[0], sizeof(EditBlockInfo), g_nSaveModelCnt, pFile);
//
//		//ファイルを閉じる
//		fclose(pFile);
//
//	}
//
//	else
//	{
//		return;
//	}
//
//	//nFrame++;
//	//int nAnswer = nFrame / 60;
//	//if (nAnswer == 1)
//	//{
//	//for (int nCnt = 0; nCnt < g_nUseBlock; nCnt++)
//	//{
//	//	Setblock(g_BlockInfo[nCnt].pos, g_BlockInfo[nCnt].nType);
//	//}
//	//	nFrame = 0;
//	//}
//}

//=============================================
//描画処理
//=============================================
void DrawEdit(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//int nCntEdit;
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
	D3DMATERIAL9 matDef; //現在のマテリアルの保存
	//現在を取得
	pDevice->GetMaterial(&matDef);

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_EditModelInfo[nCnt].bUse == true)
		{
			//マトリックスの初期化
			D3DXMatrixIdentity(&g_EditModelInfo[nCnt].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_EditModelInfo[nCnt].rot.y, g_EditModelInfo[nCnt].rot.x, g_EditModelInfo[nCnt].rot.z);

			D3DXMatrixMultiply(&g_EditModelInfo[nCnt].mtxWorld, &g_EditModelInfo[nCnt].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_EditModelInfo[nCnt].pos.x, g_EditModelInfo[nCnt].pos.y, g_EditModelInfo[nCnt].pos.z);

			D3DXMatrixMultiply(&g_EditModelInfo[nCnt].mtxWorld, &g_EditModelInfo[nCnt].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_EditModelInfo[nCnt].mtxWorld);

			D3DXMATERIAL* pMat; //マテリアル

			pMat = (D3DXMATERIAL*)g_EditModelInfo[g_EditModelInfo[nCnt].nType].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_EditModelInfo[g_EditModelInfo[nCnt].nType].nNumMat; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0,g_apTextureEdit[g_EditModelInfo[nCnt].nType][nCntMat]);

				//パーツの設定
				g_EditModelInfo[g_EditModelInfo[nCnt].nType].pMesh->DrawSubset(nCntMat);
			}

		}
	}
	//保存してたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
		//}
	//}

	//else if (g_nEditSelect == 1)
	//{//ブロック
	//	for (int nCntEdit = 0; nCntEdit < MAX_BLOCK; nCntEdit++)
	//	{
	//		//if (g_EditModelInfo[nCntEdit].bUse == true)
	//		//{
	//		for (int nCnt = 6; nCnt < NUM_TYPE_EDIT; nCnt++)
	//		{
	//			if (g_EditModelInfo[nCntEdit].nType + 6 == nCnt)
	//			{
	//				//テクスチャの設定
	//				pDevice->SetTexture(0, g_apTextureEdit[nCnt]);
	//			}
	//		}

	//		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
	//			VERTEX * nCntEdit,
	//			2);

	//	}
	//	//}
	//}
}

//=============================================
//エディットのデバッグ表示（主に操作説明）
//=============================================
void DebagEdit(void)
{
	LPD3DXFONT pFont = GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "操作方法\n[カメラ移動]\n前進:I 後進:K 左:J 右:L\nモデル設置モード:1	モデル編集モード:2\n物の設置:0\n物の移動	前進:W 後進:S 左:A 右:D");

	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

EditModelInfo* GetEditModelinfo(void)
{
	return &g_EditModelInfo[0];
}

//EditBlockInfo* GetEditBlockinfo(void)
//{
//	return &g_EditModelInfo[0];
//}


////現在設置するものの確認（デバック表示用）
//int GetEditSelect(void)
//{
//	return g_nEditSelect;
//}