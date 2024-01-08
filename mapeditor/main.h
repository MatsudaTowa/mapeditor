//=============================================
//
//3D�e���v���[�g[main.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _MAIN_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _MAIN_H_
#define DIRECTINPUT_VERSION (0x0800) //�x���Ώ��p

#include <windows.h>
#include "dinput.h" //���͏����ɕK�v
#include "d3dx9.h" //�`�揈���ɕK�v
#include "xaudio2.h"
#include "Xinput.h"
#include "model.h"

//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib") //�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib") //���̊g�����C�u����
#pragma comment(lib,"dxguid.lib")
#pragma	comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xinput.lib")
//�}�N����`
#define SCREEN_WIDTH	(1280) //�E�B���h�E�̕�
#define SCREEN_HEIGHT	(720) //�E�B���h�E�̍���
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE |D3DFVF_TEX1) //���W�ƃJ���[�ƃe�N�X�`��
#define FVF_VERTEX_3D	(D3DFVF_XYZ |D3DFVF_NORMAL| D3DFVF_DIFFUSE |D3DFVF_TEX1) //���W�ƃJ���[�ƃe�N�X�`��
#define TXT_MAX	(6000)
#define MODEL_FILE_BIN	"data\\Model.bin"
#define FILE_RANKING	"data\\rankingdata.txt"


//���_���(2D)�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos; //���_���W
	float rhw; //���W�ϊ��p�W���i1.0f�j
	D3DCOLOR col; //���_�J���[
	D3DXVECTOR2 tex; //�e�N�X�`��
}VERTEX_2D;

//���_���(3D)�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos; //���_���W
	D3DXVECTOR3 nor; //�@���x�N�g��
	D3DCOLOR col; //���_�J���[
	D3DXVECTOR2 tex; //�e�N�X�`��
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

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void LoadModel(void);
LPDIRECT3DDEVICE9 GetDevice(void);
LPD3DXFONT GetFont(void);
void WireFrame(void);

#endif // !_MAIN_H_ //���ꂪ��`����ĂȂ��Ƃ�x