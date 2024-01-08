//=============================================
//
//3Dテンプレート[main.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _MAIN_H_ //これが定義されてないとき

#define _MAIN_H_
#define DIRECTINPUT_VERSION (0x0800) //警告対処用

#include <windows.h>
#include "dinput.h" //入力処理に必要
#include "d3dx9.h" //描画処理に必要
#include "xaudio2.h"
#include "Xinput.h"
#include "model.h"

//ライブラリのリンク
#pragma comment(lib,"d3d9.lib") //描画処理に必要
#pragma comment(lib,"d3dx9.lib") //↑の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")
#pragma	comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xinput.lib")
//マクロ定義
#define SCREEN_WIDTH	(1280) //ウィンドウの幅
#define SCREEN_HEIGHT	(720) //ウィンドウの高さ
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE |D3DFVF_TEX1) //座標とカラーとテクスチャ
#define FVF_VERTEX_3D	(D3DFVF_XYZ |D3DFVF_NORMAL| D3DFVF_DIFFUSE |D3DFVF_TEX1) //座標とカラーとテクスチャ
#define TXT_MAX	(6000)
#define MODEL_FILE_BIN	"data\\Model.bin"
#define FILE_RANKING	"data\\rankingdata.txt"


//頂点情報(2D)の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos; //頂点座標
	float rhw; //座標変換用係数（1.0f）
	D3DCOLOR col; //頂点カラー
	D3DXVECTOR2 tex; //テクスチャ
}VERTEX_2D;

//頂点情報(3D)の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos; //頂点座標
	D3DXVECTOR3 nor; //法線ベクトル
	D3DCOLOR col; //頂点カラー
	D3DXVECTOR2 tex; //テクスチャ
}VERTEX_3D;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 move;
	LPD3DXMESH pMesh;
	LPD3DXBUFFER pBuffMat;
	DWORD nNumMat;
	D3DXMATRIX mtxWorld;
	ModelType nType;
	bool bUse;
}ModelInfo;

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void LoadModel(void);
LPDIRECT3DDEVICE9 GetDevice(void);
LPD3DXFONT GetFont(void);
void WireFrame(void);

#endif // !_MAIN_H_ //これが定義されてないときx