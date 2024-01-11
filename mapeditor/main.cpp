//=============================================
//
//3Dテンプレート[main.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "camera.h"
#include "model.h"
#include "edit.h"
#include "field.h"
#include "light.h"
#include "model.h"
#include "shadow.h"
#include "wall.h"
#include<Mmsystem.h>
#include "input.h"
#pragma comment(lib,"winmm.lib")
#include<stdio.h>

//=============================================
//マクロ定義
//=============================================
#define CLASS_NAME "WindowClass" //文字列
#define WINDOW_NAME "3Dテンプレート" //キャプションに表示

//=============================================
//グローバル変数
//=============================================
LPDIRECT3D9 g_pD3D = NULL; //Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL; //Direct3Dデバイスへのポインタ
LPD3DXFONT g_pFont = NULL; //フォントへのポインタ
DWORD OldTime = timeGetTime();
int g_nCntFPS = 0;
bool g_bWireFrame; //ワイヤーフレーム
bool g_bEdit; //エディットしてるか
int g_nUseModel;
int g_ModelCnt;
ModelInfo g_aModelInfo[MAX_MODEL];

//=============================================
//メイン関数
//=============================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	DWORD dwCurrentTime; //現在時刻
	DWORD dwExecLastTime; //最後に処理したときの時刻
	DWORD dwFrameCnt; //フレームカウント
	DWORD dwFPSLastTime; //最後にカウントしたFPS

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX), //メモリサイズ
		CS_CLASSDC, //ウィンドウのスタイル
		WindowProc, //ウィンドウプロシージャ
		0, //通常は使用しない
		0, //通常は使用しない
		hInstance, //インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION), //タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW), //マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1), //背景色
		NULL, //メニューバー
		CLASS_NAME, //ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION), //ファイルアイコン
	};
	HWND hWnd; //ウィンドウハンドル
	MSG msg; //メッセージを格納する
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウを生成
	hWnd = CreateWindowEx(0,	//拡張ウィンドウスタイル
		CLASS_NAME, //クラスの名前
		WINDOW_NAME, //ウィンドウの名前
		WS_OVERLAPPEDWINDOW, //ウィンドウスタイル
		CW_USEDEFAULT, //ウィンドウの左上のx座標
		CW_USEDEFAULT,//ウィンドウの左上のy座標
		SCREEN_WIDTH, //ウィンドウの幅
		SCREEN_HEIGHT, //ウィンドウの高さ
		NULL, //親ウィンドウのハンドル)
		NULL, //メニューハンドル
		hInstance, //インスタンスハンドル
		NULL); //ウィンドウ作成データ

	//初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//初期化失敗したとき
		return -1;
	}
	timeBeginPeriod(1); //分解能を設定
	dwCurrentTime = 0; //初期化
	dwFrameCnt = 0;
	dwExecLastTime = timeGetTime(); //現在時刻
	dwFPSLastTime = timeGetTime(); //現在時刻
	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow); //ウィンドウの表示を設定
	UpdateWindow(hWnd); //クライアント領域を更新

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//ウィンドウの処理
			if (msg.message == WM_QUIT)
			{//WM_QUITを受け取ったらメッセージループを抜ける
				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg); //仮想キーを文字へ変換
				DispatchMessage(&msg); //ウィンドウプロシージャへメッセージを送出
			}
		}
		else
		{//DirectXの処理
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5秒経過
				//FPSを計測
				g_nCntFPS = (dwFrameCnt * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime; //FPSを測定した時刻を保存
				dwFrameCnt = 0; //フレームカウント
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60分の1秒経過
				dwExecLastTime = dwCurrentTime; //最終時刻の設定
				//更新処理
				Update();
				//描画処理
				Draw();
				dwFrameCnt++;
			}
		}
	}

	Uninit();
	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return(int)msg.wParam;
}

//=============================================
//初期化処理
//=============================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm; //ディスプレイ
	D3DPRESENT_PARAMETERS d3dpp; //プレゼンテーションパラメータ

	//Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	//現在のディスプレイを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//デバイスのプレゼンテーションの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp)); //ゼロクリア
	d3dpp.BackBufferWidth = SCREEN_WIDTH; //ゲーム画面サイズ（横幅）
	d3dpp.BackBufferHeight = SCREEN_HEIGHT; //ゲーム画面サイズ（高さ）
	d3dpp.BackBufferFormat = d3ddm.Format; //形式
	d3dpp.BackBufferCount = 1; //バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; //ダブルバッファの切り替え
	d3dpp.EnableAutoDepthStencil = TRUE; //デプスバッファとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16; //デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow; //ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; //リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT; //インターバル

	//Direct3Dデバイスの生成（描画処理と頂点処理をハードウェアで行う）
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		//Direct3Dデバイスの生成（描画処理はハードウェア、頂点処理はCPUで行う)
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			//Direct3Dのデバイスの生成（両方ともCPU）
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	//レンタステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	
	g_bWireFrame = false; //ワイヤーフレームを描画しない
	g_bEdit = false; //エディットをしない
	g_ModelCnt = 0;
	g_nUseModel = 0;
	//キーボードの初期化処理
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//キーボードの初期化処理
	if (FAILED(InitMouse(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//padの初期化処理
	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}

	InitCamera();

	InitLight();

	InitField();

	InitWall();

	InitModel();

	LoadModel();

	InitShadow();

	InitEdit();

	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"けいふぉんと", &g_pFont);


	return S_OK;
}

//=============================================
//終了処理
//=============================================
void Uninit(void)
{
	//マウスの終了処理
	UninitMouse();

	//キーボードの終了処理
	UninitKeyboard();

	//padの終了処理
	UninitJoypad();

	UninitCamera();

	UninitLight();

	UninitField();

	UninitWall();

	UninitModel();

	UninitShadow();

	UninitEdit();

	//Direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3Dオブジェクトの破棄
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//=============================================
//更新処理
//=============================================
void Update(void)
{
	//キーボードの更新処理
	UpdateKeyboard();

	//キーボードの更新処理
	UpdateMouse();

	//padの更新処理
	UpdateJoypad();

	UpdateCamera();

	UpdateLight();

	if (GetKeyboardTrigger(DIK_F2) == true)
	{
		g_bEdit = g_bEdit ? false : true;
	}

	if (g_bEdit == true)
	{
		UpdateEdit();
	}
	else
	{//エディットしてないとき
		UpdateField();

		UpdateWall();

		UpdateModel();

		UpdateShadow();
	}

	//ワイヤーフレーム切り替え
	if (GetKeyboardTrigger(DIK_F9) == true)
	{
		g_bWireFrame = g_bWireFrame ? false : true;
		WireFrame();
	}

	//DWORD NowTime = timeGetTime(); //今回時刻

	//DWORD DeltaTime = NowTime - OldTime; //瞬間経過時間

	//OldTime = NowTime;
	//
	//float fDeltaTime = DeltaTime / 60;

	//SetTime(fDeltaTime);
}

//=============================================
//描画処理
//=============================================
void Draw(void)
{
	//画面クリア（バックバッファ＆Zバッファのクリア)
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		SetCamera();

		if (g_bEdit == true)
		{
			DrawEdit();
		}

		DrawField();

		DrawWall();

		DrawModel();

		DrawShadow();

		DebagCameraPos();
		//描画終了
		g_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================
//ウィンドウプロシージャ
//=============================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	switch (uMsg)
	{
	case WM_CLOSE:

		nID = MessageBox(hWnd, "終了しますか？", "確認", MB_YESNO | MB_ICONWARNING);
		if (nID == IDYES)
		{
			//ウィンドウを破棄する
			DestroyWindow(hWnd);
		}
		else
		{
			return 0; //0を返さないと終了してしまう
		}
		break;

	case WM_DESTROY:
		//WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN: //キーが押された時のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE: //escキーが押された
			nID = MessageBox(hWnd, "終了しますか？", "確認", MB_YESNO | MB_ICONWARNING);
			if (nID == IDYES)
			{
				//ウィンドウを破棄する
				DestroyWindow(hWnd);
			}
			break;

		}
		break;

	case WM_LBUTTONDOWN:
		SetFocus(hWnd);
		break;

	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


//=============================================
//時間の設定
//=============================================
void SetTime(DWORD time)
{
	//MSG msg; //メッセージを格納する
	//DWORD dwCurrentTime; //現在時刻
	//DWORD dwExecLastTime; //最後に処理したときの時刻
	//DWORD dwFrameCnt; //フレームカウント
	//DWORD dwFPSLastTime; //最後にカウントしたFPS

	//dwCurrentTime = 0; //初期化
	//dwFrameCnt = 0;
	//dwExecLastTime = time; //現在時刻
	//dwFPSLastTime = time; //現在時刻

	////メッセージループ
	//while (1)
	//{
	//	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
	//	{//ウィンドウの処理
	//		if (msg.message == WM_QUIT)
	//		{//WM_QUITを受け取ったらメッセージループを抜ける
	//			break;
	//		}
	//		else
	//		{
	//			//メッセージの設定
	//			TranslateMessage(&msg); //仮想キーを文字へ変換
	//			DispatchMessage(&msg); //ウィンドウプロシージャへメッセージを送出
	//		}
	//	}
	//	else
	//	{//DirectXの処理
	//		dwCurrentTime = time;
	//		if ((dwCurrentTime - dwFPSLastTime) >= 500)
	//		{//0.5秒経過
	//			//FPSを計測
	//			g_nCntFPS = (dwFrameCnt * 1000) / (dwCurrentTime - dwFPSLastTime);
	//			dwFPSLastTime = dwCurrentTime; //FPSを測定した時刻を保存
	//			dwFrameCnt = 0; //フレームカウント
	//		}
	//		if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
	//		{//60分の1秒経過
	//			dwExecLastTime = dwCurrentTime; //最終時刻の設定
	//			////更新処理
	//			//Update();
	//			////描画処理
	//			//Draw();
	//			dwFrameCnt++;
	//		}
	//	}
	//}
}

//=============================================
//ロード
//=============================================
void LoadModel(void)
{
	//ファイルの読み込み
	FILE* pFile = fopen(MODEL_FILE_BIN, "rb");

	if (pFile != NULL)
	{
		//敵の使用してる数の読み込み
		fread(&g_nUseModel, sizeof(int), 1, pFile);

		//敵の使用数分、敵の読み込み
		fread(&g_aModelInfo[0], sizeof(ModelInfo), g_nUseModel, pFile);

		//ファイルを閉じる
		fclose(pFile);

	}

	else
	{
		return;
	}

	for (int nCnt = 0; nCnt < g_nUseModel; nCnt++)
	{
		SetModel(g_aModelInfo[nCnt].pos, g_aModelInfo[nCnt].rot, g_aModelInfo[nCnt].nType);
	}
}

//=============================================
//デバイスの取得
//=============================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

LPD3DXFONT GetFont(void)
{
	return g_pFont;
}

//=============================================
//ワイヤーフレームon:off
//=============================================
void WireFrame(void)
{
	if (g_bWireFrame == true)
	{
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	if (g_bWireFrame == false)
	{
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
}