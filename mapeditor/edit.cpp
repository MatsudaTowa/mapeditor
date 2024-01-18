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
//マクロ定義
#define NUM_KEY_MAX	(256)
#define MOVE_CURSOR	(2.0f) //カーソル移動値
#define CHANGE_SIZE	(5.0f) //壁のサイズ変更
#define EDIT_WIDE	(1280) //敵を置ける最大値
#define EDIT_HEIGHT	(700) //敵を置ける最大値
#define ENEMY_LIFE	(3) //敵のライフ
#define TIME_CHANGE	(5) //時間を進める

//=============================================
//グローバル変数
//=============================================
LPDIRECT3DTEXTURE9 g_apModelTextureEdit[NUM_MODEL][NUM_TEXTURE] = {}; //テクスチャポインタ
LPDIRECT3DTEXTURE9 g_apWallTextureEdit[NUM_WALL] = {}; //テクスチャポインタ
LPDIRECT3DTEXTURE9 g_apFieldTextureEdit[NUM_FIELD] = {}; //テクスチャポインタ

Edit g_Edit; //エディット情報
LPD3DXMESH g_apMeshEditModel[NUM_MODEL]; //モデルのメッシュ情報
LPD3DXBUFFER g_apBuffMatEditModel[NUM_MODEL]; //モデルの頂点バッファ情報
DWORD g_anNumMatEditModel[NUM_MODEL]; //モデルのマテリアル情報
EditModelInfo g_EditModelInfo[MAX_MODEL]; //モデルのエディット情報

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWallEdit = NULL; //壁の頂点情報
D3DXMATRIX	g_mtxWorldWallEdit; //壁のワールドマトリックス
EditWallInfo g_EditWallInfo[MAX_WALL]; //壁のエディット情報

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFieldEdit = NULL; //床の頂点情報
D3DXMATRIX	g_mtxWorldFieldEdit; //床のワールドマトリックス
EditFieldInfo g_EditFieldInfo[MAX_WALL]; //床のエディット情報

bool g_bSave = true; //セーブできるか
int g_nSaveModelCnt; //モデルのセーブ数カウント
int g_nSaveWallCnt; //壁のセーブ数カウント
int g_nSaveFieldCnt; //床のセーブ数カウント
int g_nSave;
int g_pVtx; //頂点
int g_pVtxField;
float g_fAlpha; //α値
float g_fFlash; //点滅

//=============================================
//モデルの種類
//=============================================
static const char* MODEL_NAME[NUM_MODEL] =
{
	"data\\MODEL\\iwa.x",
	"data\\MODEL\\hyoshiki.x"
};

//=============================================
//壁のテクスチャの種類
//=============================================
static const char* WALL_TEX_NAME[NUM_WALL] =
{
	"data\\TEXTURE\\snow.jpg",
};

//=============================================
//床のテクスチャの種類
//=============================================
static const char* FIELD_TEX_NAME[NUM_FIELD] =
{
	"data\\TEXTURE\\ground.jpeg",
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

	//エディットの初期モード設定
	g_Edit.EditType = EDITTYPE_MODEL;
	//カーソルタイプ初期化(true:press,false:trigger)
	g_Edit.bCursorType = true;
	//追従するモデルの初期化
	g_Edit.nEditModelNumber = 0;
	//追従する壁の初期化
	g_Edit.nEditWallNumber = 0;

	g_pVtx = 0;
	g_pVtxField = 0;

	//モデルに書き込む情報の初期化
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
		//Xファイルの読み込み
		D3DXLoadMeshFromX(MODEL_NAME[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_apBuffMatEditModel[nCnt],
			NULL,
			&g_anNumMatEditModel[nCnt],
			&g_apMeshEditModel[nCnt]);


		D3DXMATERIAL* pMat; //マテリアルポインタ
		pMat = (D3DXMATERIAL*)g_apBuffMatEditModel[nCnt]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_anNumMatEditModel[nCnt]; nCntMat++)
		{

			g_EditModelInfo[nCnt].Diffuse[nCntMat] = pMat[nCntMat].MatD3D.Diffuse;
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//テクスチャの読み込み
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
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			WALL_TEX_NAME[nCntWallTex],
			&g_apWallTextureEdit[nCntWallTex]
		);
	}

	//壁に書き込む情報の初期化
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

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_MODEL, D3DUSAGE_WRITEONLY, 4, D3DPOOL_MANAGED, &g_pVtxBuffWallEdit, NULL);

	VERTEX_3D* pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffWallEdit->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-WALL_WIDE, WALL_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(WALL_WIDE, WALL_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-WALL_WIDE, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(WALL_WIDE, 0.0f, 0.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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

	//頂点バッファをアンロック
	g_pVtxBuffWallEdit->Unlock();

	for (int nCntFieldTex = 0; nCntFieldTex < NUM_FIELD; nCntFieldTex++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			FIELD_TEX_NAME[nCntFieldTex],
			&g_apFieldTextureEdit[nCntFieldTex]
		);
	}

	//壁に書き込む情報の初期化
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

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_FIELD, D3DUSAGE_WRITEONLY, 4, D3DPOOL_MANAGED, &g_pVtxBuffFieldEdit, NULL);

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffFieldEdit->Lock(0, 0, (void**)&pVtx, 0);
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

	//頂点バッファをアンロック
	g_pVtxBuffFieldEdit->Unlock();
}

//=============================================
//終了処理
//=============================================
void UninitEdit(void)
{
	//モデルの破棄
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		//メッシュの破棄
		if (g_apMeshEditModel[g_EditModelInfo[nCnt].nType] != NULL)
		{
			g_apMeshEditModel[g_EditModelInfo[nCnt].nType]->Release();
			g_apMeshEditModel[g_EditModelInfo[nCnt].nType] = NULL;
		}

		//マテリアルの破棄
		if (g_apBuffMatEditModel[g_EditModelInfo[nCnt].nType] != NULL)
		{
			g_apBuffMatEditModel[g_EditModelInfo[nCnt].nType]->Release();
			g_apBuffMatEditModel[g_EditModelInfo[nCnt].nType] = NULL;
		}
	}

	//モデルの破棄
	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		//テクスチャの破棄
		if (g_apWallTextureEdit[g_EditWallInfo[nCnt].nType] != NULL)
		{
			g_apWallTextureEdit[g_EditWallInfo[nCnt].nType]->Release();
			g_apWallTextureEdit[g_EditWallInfo[nCnt].nType] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffWallEdit != NULL)
	{
		g_pVtxBuffWallEdit->Release();
		g_pVtxBuffWallEdit = NULL;
	}
}

//=============================================
//更新処理
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
	{//モデルを設置
		g_Edit.EditType = EDITTYPE_MODEL;
		g_Edit.nEditModelNumber = g_nSaveModelCnt;

		if (g_EditModelInfo[g_Edit.nEditModelNumber].bUseGame == false)
		{
			g_EditModelInfo[g_Edit.nEditModelNumber].bUse = true; //次に設置するものは表示しない
		}
	}


	else if (GetKeyboardTrigger(DIK_2) == true)
	{//今まで置いたモデルの編集
		g_Edit.EditType = EDITTYPE_CORRECTIONMODEL;
		if (g_EditModelInfo[g_Edit.nEditModelNumber].bUseGame == false)
		{
			g_EditModelInfo[g_Edit.nEditModelNumber].bUse = false; //次に設置するものは表示しない
			g_Edit.nEditModelNumber = 0; //最初に置いたものにカーソルを移動;
		}
	}

	else if (GetKeyboardTrigger(DIK_3) == true)
	{//壁を設置
		g_Edit.EditType = EDITTYPE_WALL;
		g_Edit.nEditWallNumber = g_nSaveWallCnt;

		if (g_EditWallInfo[g_Edit.nEditWallNumber].bUseGame == false)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].bUse = true; //次に設置するものは表示しない
		}
	}

	else if (GetKeyboardTrigger(DIK_4) == true)
	{//今まで置いた壁の編集
		g_Edit.EditType = EDITTYPE_CORRECTIONWALL;

		if (g_EditWallInfo[g_Edit.nEditWallNumber].bUseGame == false)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].bUse = true; //次に設置するものは表示しない
			g_Edit.nEditWallNumber = 0; //最初に置いたものにカーソルを移動
			g_pVtx = 0; //最初に置いたものの頂点
		}
	}
	else if (GetKeyboardTrigger(DIK_5) == true)
	{//床を設置
		g_Edit.EditType = EDITTYPE_FIELD;
		g_Edit.nEditFieldNumber = g_nSaveFieldCnt;

		if (g_EditFieldInfo[g_Edit.nEditFieldNumber].bUseGame == false)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].bUse = true; //次に設置するものは表示しない
		}
	}
	else if (GetKeyboardTrigger(DIK_6) == true)
	{//今まで置いた床の編集
		g_Edit.EditType = EDITTYPE_CORRECTIONFIELD;

		if (g_EditFieldInfo[g_Edit.nEditFieldNumber].bUseGame == false)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].bUse = true; //次に設置するものは表示しない
			g_Edit.nEditFieldNumber = 0; //最初に置いたものにカーソルを移動
			g_pVtxField = 0; //最初に置いたものの頂点
		}
	}

	if (g_Edit.EditType == EDITTYPE_MODEL)
	{//モデル
		SaveModel();
	}
	else if (g_Edit.EditType == EDITTYPE_CORRECTIONMODEL)
	{//モデル置きなおし
		CorrectionModel();
	}
	else if (g_Edit.EditType == EDITTYPE_WALL)
	{//壁
		SaveWall();
	}
	else if (g_Edit.EditType == EDITTYPE_CORRECTIONWALL)
	{//壁置きなおし
		CorrectionWall();
	}
	else if (g_Edit.EditType == EDITTYPE_FIELD)
	{//床
		SaveField();
	}
	else if (g_Edit.EditType == EDITTYPE_CORRECTIONFIELD)
	{//床置きなおし
		CorrectionField();
	}

	if (GetKeyboardTrigger(DIK_F1) == true)
	{

		pCamera->posV = D3DXVECTOR3(0.0f, 1020.0f, -13.0f);
		pCamera->posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //注視

	}

	if (GetKeyboardTrigger(DIK_F5) == true)
	{
		g_Edit.bCursorType = g_Edit.bCursorType ? false : true;
	}
}

//=============================================
//再設置用関数（管理用）
//=============================================
void reSaveEdit(void)
{

	if (GetKeyboardTrigger(DIK_1) == true)
	{//モデルを設置
		g_Edit.EditType = EDITTYPE_MODEL;
		g_Edit.nEditModelNumber = g_nSaveModelCnt;

		if (g_EditModelInfo[g_Edit.nEditModelNumber].bUseGame == false)
		{
			g_EditModelInfo[g_Edit.nEditModelNumber].bUse = true; //次に設置するものは表示しない
		}
	}


	else if (GetKeyboardTrigger(DIK_2) == true)
	{//今まで置いたモデルの編集
		g_Edit.EditType = EDITTYPE_CORRECTIONMODEL;
		if (g_EditModelInfo[g_Edit.nEditModelNumber].bUseGame == false)
		{
			g_EditModelInfo[g_Edit.nEditModelNumber].bUse = false; //次に設置するものは表示しない
			g_Edit.nEditModelNumber = 0; //最初に置いたものにカーソルを移動;
		}
	}

	else if (GetKeyboardTrigger(DIK_3) == true)
	{//壁を設置
		g_Edit.EditType = EDITTYPE_WALL;
		g_Edit.nEditWallNumber = g_nSaveWallCnt;

		if (g_EditWallInfo[g_Edit.nEditWallNumber].bUseGame == false)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].bUse = true; //次に設置するものは表示しない
		}
	}

	else if (GetKeyboardTrigger(DIK_4) == true)
	{//今まで置いた壁の編集
		g_Edit.EditType = EDITTYPE_CORRECTIONWALL;

		if (g_EditWallInfo[g_Edit.nEditWallNumber].bUseGame == false)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].bUse = true; //次に設置するものは表示しない
			g_Edit.nEditWallNumber = 0; //最初に置いたものにカーソルを移動
			g_pVtx = 0; //最初に置いたものの頂点
		}
	}
	else if (GetKeyboardTrigger(DIK_5) == true)
	{//床を設置
		g_Edit.EditType = EDITTYPE_FIELD;
		g_Edit.nEditFieldNumber = g_nSaveFieldCnt;

		if (g_EditFieldInfo[g_Edit.nEditFieldNumber].bUseGame == false)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].bUse = true; //次に設置するものは表示しない
		}
	}
	else if (GetKeyboardTrigger(DIK_6) == true)
	{//今まで置いた床の編集
		g_Edit.EditType = EDITTYPE_CORRECTIONFIELD;

		if (g_EditFieldInfo[g_Edit.nEditFieldNumber].bUseGame == false)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].bUse = true; //次に設置するものは表示しない
			g_Edit.nEditFieldNumber = 0; //最初に置いたものにカーソルを移動
			g_pVtxField = 0; //最初に置いたものの頂点
		}
	}

	if (g_Edit.EditType == EDITTYPE_MODEL)
	{//モデル
		SaveModel();
	}
	else if (g_Edit.EditType == EDITTYPE_CORRECTIONMODEL)
	{//モデル置きなおし
		CorrectionModel();
	}
	else if (g_Edit.EditType == EDITTYPE_WALL)
	{//壁
		SaveWall();
	}
	else if (g_Edit.EditType == EDITTYPE_CORRECTIONWALL)
	{//壁置きなおし
		CorrectionWall();
	}
	else if (g_Edit.EditType == EDITTYPE_FIELD)
	{//床
		SaveField();
	}
	else if (g_Edit.EditType == EDITTYPE_CORRECTIONFIELD)
	{//床置きなおし
		CorrectionField();
	}

	if (GetKeyboardTrigger(DIK_F5) == true)
	{//カーソルの動き方切り替え
		g_Edit.bCursorType = g_Edit.bCursorType ? false : true;
	}
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

	//モデルの設置
	if (GetKeyboardTrigger(DIK_0) == true)
	{
		g_EditModelInfo[g_Edit.nEditModelNumber + 1].pos = g_EditModelInfo[g_Edit.nEditModelNumber].pos;
		g_EditModelInfo[g_Edit.nEditModelNumber + 1].rot = g_EditModelInfo[g_Edit.nEditModelNumber].rot;
		g_EditModelInfo[g_Edit.nEditModelNumber + 1].nType = g_EditModelInfo[g_Edit.nEditModelNumber].nType;
		g_EditModelInfo[g_Edit.nEditModelNumber + 1].bUse = true;
		g_EditModelInfo[g_Edit.nEditModelNumber].bUseGame = true;
		g_nSaveModelCnt++;
		g_Edit.nEditModelNumber++;
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

	//モデルの設置
	if (GetKeyboardTrigger(DIK_0) == true)
	{
		g_EditModelInfo[g_Edit.nEditModelNumber].bUseGame = true;
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
//=============================================
//モデルの途中からセーブ処理
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

	for (int nCntUseModel = 0; nCntUseModel < MAX_MODEL; nCntUseModel++)
	{
		if (g_EditModelInfo[nCntUseModel].bUse == true)
		{
			g_Edit.nEditModelNumber++;
		}
	}

	g_EditModelInfo[g_Edit.nEditModelNumber].bUse = true; //保存されてる最後のモデルの次のやつをtrueに
}

//=============================================
//壁のセーブ処理
//=============================================
void SaveWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//int nCntEdit;
	//デバイスの取得
	pDevice = GetDevice();

	//Enemy* pEnemy = GetEnemy();
	VERTEX_3D* pVtx;
	g_pVtxBuffWallEdit->Lock(0, 0, (void**)&pVtx, 0);

	//壁の情報変更
	if (g_Edit.bCursorType == true)
	{//プレス
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

		//壁のサイズ変更
		if (GetKeyboardPress(DIK_G) == true)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].fWide += CHANGE_SIZE;
			//頂点座標の設定
			pVtx[g_pVtx].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 1].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 2].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
			pVtx[g_pVtx + 3].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
		}
		//壁のサイズ変更
		if (GetKeyboardPress(DIK_F) == true)
		{
			if (g_EditWallInfo[g_Edit.nEditWallNumber].fWide > 0)
			{
				g_EditWallInfo[g_Edit.nEditWallNumber].fWide -= CHANGE_SIZE;
			}
			//頂点座標の設定
			pVtx[g_pVtx].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 1].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 2].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
			pVtx[g_pVtx + 3].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
		}
		//壁のサイズ変更
		if (GetKeyboardPress(DIK_B) == true)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].fHeight += CHANGE_SIZE;
			//頂点座標の設定
			pVtx[g_pVtx].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 1].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 2].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
			pVtx[g_pVtx + 3].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
		}
		//壁のサイズ変更
		if (GetKeyboardPress(DIK_V) == true)
		{
			if (g_EditWallInfo[g_Edit.nEditWallNumber].fHeight > 0)
			{
				g_EditWallInfo[g_Edit.nEditWallNumber].fHeight -= CHANGE_SIZE;

			}
			//頂点座標の設定
			pVtx[g_pVtx].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 1].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 2].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
			pVtx[g_pVtx + 3].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
		}

	}
	else if (g_Edit.bCursorType == false)
	{//トリガー
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

		//壁のサイズ変更
		if (GetKeyboardTrigger(DIK_G) == true)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].fWide += CHANGE_SIZE;
			//頂点座標の設定
			pVtx[g_pVtx].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 1].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 2].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
			pVtx[g_pVtx + 3].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
		}
		//壁のサイズ変更
		if (GetKeyboardTrigger(DIK_F) == true)
		{
			if (g_EditWallInfo[g_Edit.nEditWallNumber].fWide > 0)
			{
				g_EditWallInfo[g_Edit.nEditWallNumber].fWide -= CHANGE_SIZE;
			}
			//頂点座標の設定
			pVtx[g_pVtx].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 1].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 2].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
			pVtx[g_pVtx + 3].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
		}
		//壁のサイズ変更
		if (GetKeyboardTrigger(DIK_B) == true)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].fHeight += CHANGE_SIZE;
			//頂点座標の設定
			pVtx[g_pVtx].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 1].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 2].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
			pVtx[g_pVtx + 3].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
		}
		//壁のサイズ変更
		if (GetKeyboardTrigger(DIK_V) == true)
		{
			if (g_EditWallInfo[g_Edit.nEditWallNumber].fHeight > 0)
			{
				g_EditWallInfo[g_Edit.nEditWallNumber].fHeight -= CHANGE_SIZE;
			}
			//頂点座標の設定
			pVtx[g_pVtx].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 1].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 2].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
			pVtx[g_pVtx + 3].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
		}
	}
	//壁のrot回転
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

	//壁のタイプ変更
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

	//モデルの設置
	if (GetKeyboardTrigger(DIK_0) == true)
	{
		g_EditWallInfo[g_Edit.nEditWallNumber + 1].pos = g_EditWallInfo[g_Edit.nEditWallNumber].pos;
		g_EditWallInfo[g_Edit.nEditWallNumber + 1].rot = g_EditWallInfo[g_Edit.nEditWallNumber].rot;
		g_EditWallInfo[g_Edit.nEditWallNumber + 1].nType = g_EditWallInfo[g_Edit.nEditWallNumber].nType;
		g_EditWallInfo[g_Edit.nEditWallNumber + 1].bUse = true;
		g_EditWallInfo[g_Edit.nEditWallNumber].bUseGame = true;
		g_nSaveWallCnt++;
		g_Edit.nEditWallNumber++;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		g_pVtx += 4;
	}

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//モデルの設置
	if (GetKeyboardTrigger(DIK_F4) == true)
	{//セーブ処理
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

			//セーブ完了
			bSave = true;

		}
	}
}

//=============================================
//壁の編集
//=============================================
void CorrectionWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//int nCntEdit;
	//デバイスの取得
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

	//壁の情報変更
	if (g_Edit.bCursorType == true)
	{//プレス
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

		//壁のサイズ変更
		if (GetKeyboardPress(DIK_G) == true)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].fWide += CHANGE_SIZE;
			//頂点座標の設定
			pVtx[g_pVtx].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 1].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 2].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
			pVtx[g_pVtx + 3].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
		}
		//壁のサイズ変更
		if (GetKeyboardPress(DIK_F) == true)
		{
			if (g_EditWallInfo[g_Edit.nEditWallNumber].fWide > 0)
			{
				g_EditWallInfo[g_Edit.nEditWallNumber].fWide -= CHANGE_SIZE;
			}
			//頂点座標の設定
			pVtx[g_pVtx].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 1].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 2].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
			pVtx[g_pVtx + 3].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
		}
		//壁のサイズ変更
		if (GetKeyboardPress(DIK_B) == true)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].fHeight += CHANGE_SIZE;
			//頂点座標の設定
			pVtx[g_pVtx].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 1].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 2].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
			pVtx[g_pVtx + 3].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
		}
		//壁のサイズ変更
		if (GetKeyboardPress(DIK_V) == true)
		{
			if (g_EditWallInfo[g_Edit.nEditWallNumber].fHeight > 0)
			{
				g_EditWallInfo[g_Edit.nEditWallNumber].fHeight -= CHANGE_SIZE;

			}
			//頂点座標の設定
			pVtx[g_pVtx].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 1].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 2].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
			pVtx[g_pVtx + 3].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
		}

	}
	else if (g_Edit.bCursorType == false)
	{//トリガー
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

		//壁のサイズ変更
		if (GetKeyboardTrigger(DIK_G) == true)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].fWide += CHANGE_SIZE;
			//頂点座標の設定
			pVtx[g_pVtx].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 1].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 2].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
			pVtx[g_pVtx + 3].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
		}
		//壁のサイズ変更
		if (GetKeyboardTrigger(DIK_F) == true)
		{
			if (g_EditWallInfo[g_Edit.nEditWallNumber].fWide > 0)
			{
				g_EditWallInfo[g_Edit.nEditWallNumber].fWide -= CHANGE_SIZE;
			}
			//頂点座標の設定
			pVtx[g_pVtx].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 1].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 2].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
			pVtx[g_pVtx + 3].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
		}
		//壁のサイズ変更
		if (GetKeyboardTrigger(DIK_B) == true)
		{
			g_EditWallInfo[g_Edit.nEditWallNumber].fHeight += CHANGE_SIZE;
			//頂点座標の設定
			pVtx[g_pVtx].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 1].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 2].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
			pVtx[g_pVtx + 3].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
		}
		//壁のサイズ変更
		if (GetKeyboardTrigger(DIK_V) == true)
		{
			if (g_EditWallInfo[g_Edit.nEditWallNumber].fHeight > 0)
			{
				g_EditWallInfo[g_Edit.nEditWallNumber].fHeight -= CHANGE_SIZE;
			}
			//頂点座標の設定
			pVtx[g_pVtx].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 1].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, g_EditWallInfo[g_Edit.nEditWallNumber].fHeight, 0.0f);
			pVtx[g_pVtx + 2].pos = D3DXVECTOR3(-g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
			pVtx[g_pVtx + 3].pos = D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].fWide, 0.0f, 0.0f);
		}
	}
	//壁のrot回転
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

	//壁のタイプ変更
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

	//モデルの設置
	if (GetKeyboardTrigger(DIK_0) == true)
	{
		g_EditWallInfo[g_Edit.nEditWallNumber].bUseGame = true;
	}

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffWallEdit->Unlock();

	//モデルの設置
	if (GetKeyboardTrigger(DIK_F4) == true)
	{//セーブ処理
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

			//セーブ完了
			bSave = true;

		}
	}

}

//=============================================
//壁の途中からセーブ処理
//=============================================
void reSaveWall(void)
{
	//ファイルの読み込み
	FILE* pFile = fopen(WALL_FILE_BIN, "rb");

	if (pFile != NULL)
	{
		//敵の使用してる数の読み込み
		fread(&g_nSaveWallCnt, sizeof(int), 1, pFile);

		//敵の使用数分、敵の読み込み
		fread(&g_EditWallInfo[0], sizeof(EditWallInfo), g_nSaveWallCnt, pFile);

		//ファイルを閉じる
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
	g_EditWallInfo[g_Edit.nEditWallNumber].bUse = true; //保存されてる最後のモデルの次のやつをtrueに
}

//=============================================
//床のセーブ処理
//=============================================
void SaveField(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//int nCntEdit;
	//デバイスの取得
	pDevice = GetDevice();

	//Enemy* pEnemy = GetEnemy();
	VERTEX_3D* pVtx;
	g_pVtxBuffFieldEdit->Lock(0, 0, (void**)&pVtx, 0);

	//壁の情報変更
	if (g_Edit.bCursorType == true)
	{//プレス
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

		//壁のサイズ変更
		if (GetKeyboardPress(DIK_G) == true)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide += CHANGE_SIZE;
			//頂点座標の設定
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
		}
		//壁のサイズ変更
		if (GetKeyboardPress(DIK_F) == true)
		{
			if (g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide > 0)
			{
				g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide -= CHANGE_SIZE;
			}
			//頂点座標の設定
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
		}
		//壁のサイズ変更
		if (GetKeyboardPress(DIK_B) == true)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth += CHANGE_SIZE;
			//頂点座標の設定
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
		}
		//壁のサイズ変更
		if (GetKeyboardPress(DIK_V) == true)
		{
			if (g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth > 0)
			{
				g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth -= CHANGE_SIZE;

			}
			//頂点座標の設定
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
		}

	}
	else if (g_Edit.bCursorType == false)
	{//トリガー
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

		//壁のサイズ変更
		if (GetKeyboardTrigger(DIK_G) == true)
		{
			//頂点座標の設定
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
		}
		//壁のサイズ変更
		if (GetKeyboardTrigger(DIK_F) == true)
		{
			if (g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide > 0)
			{
				g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide -= CHANGE_SIZE;
			}
			//頂点座標の設定
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
		}
		//壁のサイズ変更
		if (GetKeyboardTrigger(DIK_B) == true)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth += CHANGE_SIZE;
			//頂点座標の設定
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
		}
		//壁のサイズ変更
		if (GetKeyboardTrigger(DIK_V) == true)
		{
			if (g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth > 0)
			{
				g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth -= CHANGE_SIZE;
			}
			//頂点座標の設定
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
		}
	}
	//壁のrot回転
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

	//壁のタイプ変更
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

	//モデルの設置
	if (GetKeyboardTrigger(DIK_0) == true)
	{
		g_EditFieldInfo[g_Edit.nEditFieldNumber + 1].pos = g_EditFieldInfo[g_Edit.nEditFieldNumber].pos;
		g_EditFieldInfo[g_Edit.nEditFieldNumber + 1].rot = g_EditFieldInfo[g_Edit.nEditFieldNumber].rot;
		g_EditFieldInfo[g_Edit.nEditFieldNumber + 1].nType = g_EditFieldInfo[g_Edit.nEditFieldNumber].nType;
		g_EditFieldInfo[g_Edit.nEditFieldNumber + 1].bUse = true;
		g_EditFieldInfo[g_Edit.nEditFieldNumber].bUseGame = true;
		g_nSaveFieldCnt++;
		g_Edit.nEditFieldNumber++;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		g_pVtxField += 4;
	}

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//モデルの設置
	if (GetKeyboardTrigger(DIK_F4) == true)
	{//セーブ処理
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

			//セーブ完了
			bSave = true;

		}
	}
}

//=============================================
//床の編集処理
//=============================================
void CorrectionField(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//int nCntEdit;
	//デバイスの取得
	pDevice = GetDevice();

	//Enemy* pEnemy = GetEnemy();
	VERTEX_3D* pVtx;
	g_pVtxBuffFieldEdit->Lock(0, 0, (void**)&pVtx, 0);

	//壁の情報変更
	if (g_Edit.bCursorType == true)
	{//プレス
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

		//壁のサイズ変更
		if (GetKeyboardPress(DIK_G) == true)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide += CHANGE_SIZE;
			//頂点座標の設定
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
		}
		//壁のサイズ変更
		if (GetKeyboardPress(DIK_F) == true)
		{
			if (g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide > 0)
			{
				g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide -= CHANGE_SIZE;
			}
			//頂点座標の設定
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
		}
		//壁のサイズ変更
		if (GetKeyboardPress(DIK_B) == true)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth += CHANGE_SIZE;
			//頂点座標の設定
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
		}
		//壁のサイズ変更
		if (GetKeyboardPress(DIK_V) == true)
		{
			if (g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth > 0)
			{
				g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth -= CHANGE_SIZE;
			}
			//頂点座標の設定
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
		}

	}
	else if (g_Edit.bCursorType == false)
	{//トリガー
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

		//壁のサイズ変更
		if (GetKeyboardTrigger(DIK_G) == true)
		{
			//頂点座標の設定
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
		}
		//壁のサイズ変更
		if (GetKeyboardTrigger(DIK_F) == true)
		{
			if (g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide > 0)
			{
				g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide -= CHANGE_SIZE;
			}
			//頂点座標の設定
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
		}
		//壁のサイズ変更
		if (GetKeyboardTrigger(DIK_B) == true)
		{
			g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth += CHANGE_SIZE;
			//頂点座標の設定
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
		}
		//壁のサイズ変更
		if (GetKeyboardTrigger(DIK_V) == true)
		{
			if (g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth > 0)
			{
				g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth -= CHANGE_SIZE;
			}
			//頂点座標の設定
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField + 3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
		}
	}
	//壁のrot回転
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

	//壁のタイプ変更
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

	//モデルの設置
	if (GetKeyboardTrigger(DIK_0) == true)
	{
		g_EditFieldInfo[g_Edit.nEditFieldNumber].bUseGame = true;
		g_pVtxField += 4;
	}

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlpha);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//モデルの設置
	if (GetKeyboardTrigger(DIK_F4) == true)
	{//セーブ処理
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

			//セーブ完了
			bSave = true;

		}
	}
}

//=============================================
//床の途中からセーブ処理
//=============================================
void reSaveField(void)
{
	//ファイルの読み込み
	FILE* pFile = fopen(FIELD_FILE_BIN, "rb");

	if (pFile != NULL)
	{
		//床の使用してる数の読み込み
		fread(&g_nSaveFieldCnt, sizeof(int), 1, pFile);

		//床の使用数分、敵の読み込み
		fread(&g_EditFieldInfo[0], sizeof(EditFieldInfo), g_nSaveFieldCnt, pFile);

		//ファイルを閉じる
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

			//頂点座標の設定
			pVtx[g_pVtxField].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField+1].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField+2].pos = D3DXVECTOR3(-g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);
			pVtx[g_pVtxField+3].pos = D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].fWide, 0.0f, -g_EditFieldInfo[g_Edit.nEditFieldNumber].fDepth);

			g_pVtxField += 4;
		}
	}
	g_pVtxBuffFieldEdit->Unlock();
	g_EditFieldInfo[g_Edit.nEditFieldNumber].bUse = true; //保存されてる最後の床の次のやつをtrueに
}

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


	if (g_Edit.EditType == EDITTYPE_MODEL || g_Edit.EditType == EDITTYPE_CORRECTIONMODEL)
	{//モデル設置の時
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

					//元の色に戻す
					//pMat[nCntMat].MatD3D.Diffuse = g_EditModelInfo[nCnt].Diffuse[nCntMat];
					//マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//テクスチャの設定
					pDevice->SetTexture(0, g_apModelTextureEdit[g_EditModelInfo[nCnt].nType][nCntMat]);

					//パーツの設定
					g_apMeshEditModel[g_EditModelInfo[nCnt].nType]->DrawSubset(nCntMat);
				}
			}
		}

		//保存してたマテリアルを戻す
		pDevice->SetMaterial(&matDef);

		SetCursor(D3DXVECTOR3(g_EditModelInfo[g_Edit.nEditModelNumber].pos.x, 40.0f, g_EditModelInfo[g_Edit.nEditModelNumber].pos.z));
	}
	else if (g_Edit.EditType == EDITTYPE_WALL || g_Edit.EditType == EDITTYPE_CORRECTIONWALL)
	{//壁設置の時
		for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
		{
			if (g_EditWallInfo[nCnt].bUse == true)
			{
				//マトリックスの初期化
				D3DXMatrixIdentity(&g_mtxWorldWallEdit);

				//向きを反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_EditWallInfo[nCnt].rot.y, g_EditWallInfo[nCnt].rot.x, g_EditWallInfo[nCnt].rot.z);

				D3DXMatrixMultiply(&g_mtxWorldWallEdit, &g_mtxWorldWallEdit, &mtxRot);

				//位置を反映
				D3DXMatrixTranslation(&mtxTrans, g_EditWallInfo[nCnt].pos.x, g_EditWallInfo[nCnt].pos.y, g_EditWallInfo[nCnt].pos.z);

				D3DXMatrixMultiply(&g_mtxWorldWallEdit, &g_mtxWorldWallEdit, &mtxTrans);

				//ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldWallEdit);

				//頂点バッファをデータストリームに設定
				pDevice->SetStreamSource(0, g_pVtxBuffWallEdit, 0, sizeof(VERTEX_3D));

				//頂点フォーマットの設定
				pDevice->SetFVF(FVF_VERTEX_3D);

				for (int nCntTex = 0; nCntTex < NUM_WALL; nCntTex++)
				{
					//テクスチャの設定
					pDevice->SetTexture(0, g_apWallTextureEdit[nCntTex]);
				}

				//ポリゴンの描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCnt, 2);

				pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
				pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
				SetCursor(D3DXVECTOR3(g_EditWallInfo[g_Edit.nEditWallNumber].pos.x, 40.0f, g_EditWallInfo[g_Edit.nEditWallNumber].pos.z));

			}
		}
	}
	else if (g_Edit.EditType == EDITTYPE_FIELD || g_Edit.EditType == EDITTYPE_CORRECTIONFIELD)
	{//床設置の時
		for (int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
		{
			if (g_EditFieldInfo[nCnt].bUse == true)
			{
				//マトリックスの初期化
				D3DXMatrixIdentity(&g_mtxWorldFieldEdit);

				//向きを反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_EditFieldInfo[nCnt].rot.y, g_EditFieldInfo[nCnt].rot.x, g_EditFieldInfo[nCnt].rot.z);

				D3DXMatrixMultiply(&g_mtxWorldFieldEdit, &g_mtxWorldFieldEdit, &mtxRot);

				//位置を反映
				D3DXMatrixTranslation(&mtxTrans, g_EditFieldInfo[nCnt].pos.x, g_EditFieldInfo[nCnt].pos.y, g_EditFieldInfo[nCnt].pos.z);

				D3DXMatrixMultiply(&g_mtxWorldFieldEdit, &g_mtxWorldFieldEdit, &mtxTrans);

				//ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldFieldEdit);

				//頂点バッファをデータストリームに設定
				pDevice->SetStreamSource(0, g_pVtxBuffFieldEdit, 0, sizeof(VERTEX_3D));

				//頂点フォーマットの設定
				pDevice->SetFVF(FVF_VERTEX_3D);

				for (int nCntTex = 0; nCntTex < NUM_FIELD; nCntTex++)
				{
					//テクスチャの設定
					pDevice->SetTexture(0, g_apFieldTextureEdit[nCntTex]);
				}

				//ポリゴンの描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCnt, 2);

				pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
				pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
				SetCursor(D3DXVECTOR3(g_EditFieldInfo[g_Edit.nEditFieldNumber].pos.x, 40.0f, g_EditFieldInfo[g_Edit.nEditFieldNumber].pos.z));

			}
		}
	}
}

//=============================================
//エディットのデバッグ表示（主に操作説明）
//=============================================
void DebagEdit(void)
{
	LPD3DXFONT pFont = GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "操作方法\n[カメラ移動]\n前進:I 後進:K 左:J 右:L\nモデル設置モード:1 モデル編集モード:2 壁設置モード:3 壁編集モード:4 床設置モード:5 床編集モード:6\n物の設置:0\n物の移動	前進:W 後進:S 左:A 右:D\nタイプの切り替え→or← カーソル切り替え↑or↓");

	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//=============================================
//エディットのデバッグ表示（選択されてるものの情報）
//=============================================
void DebagInfo(void)
{
	LPD3DXFONT pFont = GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n\n\n\n\n\n\n[モデル]\npos:%.1f,%.1f,%.1f\nrot:%.1f,%.1f,%.1f\n\n[壁]\npos:%.1f,%.1f,%.1f\nrot:%.1f,%.1f,%.1f\nwide:%.1f\nheight:%.1f\n\n[床]\npos:%.1f,%.1f,%.1f\nrot:%.1f,%.1f,%.1f\nwide:%.1f\ndepth:%.1f",
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
	//テキストの描画
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
