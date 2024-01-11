//=============================================
//
//3D�e���v���[�g[main.cpp]
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
//�}�N����`
//=============================================
#define CLASS_NAME "WindowClass" //������
#define WINDOW_NAME "3D�e���v���[�g" //�L���v�V�����ɕ\��

//=============================================
//�O���[�o���ϐ�
//=============================================
LPDIRECT3D9 g_pD3D = NULL; //Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL; //Direct3D�f�o�C�X�ւ̃|�C���^
LPD3DXFONT g_pFont = NULL; //�t�H���g�ւ̃|�C���^
DWORD OldTime = timeGetTime();
int g_nCntFPS = 0;
bool g_bWireFrame; //���C���[�t���[��
bool g_bEdit; //�G�f�B�b�g���Ă邩
int g_nUseModel;
int g_ModelCnt;
ModelInfo g_aModelInfo[MAX_MODEL];

//=============================================
//���C���֐�
//=============================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	DWORD dwCurrentTime; //���ݎ���
	DWORD dwExecLastTime; //�Ō�ɏ��������Ƃ��̎���
	DWORD dwFrameCnt; //�t���[���J�E���g
	DWORD dwFPSLastTime; //�Ō�ɃJ�E���g����FPS

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX), //�������T�C�Y
		CS_CLASSDC, //�E�B���h�E�̃X�^�C��
		WindowProc, //�E�B���h�E�v���V�[�W��
		0, //�ʏ�͎g�p���Ȃ�
		0, //�ʏ�͎g�p���Ȃ�
		hInstance, //�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION), //�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW), //�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1), //�w�i�F
		NULL, //���j���[�o�[
		CLASS_NAME, //�E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION), //�t�@�C���A�C�R��
	};
	HWND hWnd; //�E�B���h�E�n���h��
	MSG msg; //���b�Z�[�W���i�[����
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,	//�g���E�B���h�E�X�^�C��
		CLASS_NAME, //�N���X�̖��O
		WINDOW_NAME, //�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW, //�E�B���h�E�X�^�C��
		CW_USEDEFAULT, //�E�B���h�E�̍����x���W
		CW_USEDEFAULT,//�E�B���h�E�̍����y���W
		SCREEN_WIDTH, //�E�B���h�E�̕�
		SCREEN_HEIGHT, //�E�B���h�E�̍���
		NULL, //�e�E�B���h�E�̃n���h��)
		NULL, //���j���[�n���h��
		hInstance, //�C���X�^���X�n���h��
		NULL); //�E�B���h�E�쐬�f�[�^

	//����������
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//���������s�����Ƃ�
		return -1;
	}
	timeBeginPeriod(1); //����\��ݒ�
	dwCurrentTime = 0; //������
	dwFrameCnt = 0;
	dwExecLastTime = timeGetTime(); //���ݎ���
	dwFPSLastTime = timeGetTime(); //���ݎ���
	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow); //�E�B���h�E�̕\����ݒ�
	UpdateWindow(hWnd); //�N���C�A���g�̈���X�V

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//�E�B���h�E�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg); //���z�L�[�𕶎��֕ϊ�
				DispatchMessage(&msg); //�E�B���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}
		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
				//FPS���v��
				g_nCntFPS = (dwFrameCnt * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime; //FPS�𑪒肵��������ۑ�
				dwFrameCnt = 0; //�t���[���J�E���g
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60����1�b�o��
				dwExecLastTime = dwCurrentTime; //�ŏI�����̐ݒ�
				//�X�V����
				Update();
				//�`�揈��
				Draw();
				dwFrameCnt++;
			}
		}
	}

	Uninit();
	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return(int)msg.wParam;
}

//=============================================
//����������
//=============================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm; //�f�B�X�v���C
	D3DPRESENT_PARAMETERS d3dpp; //�v���[���e�[�V�����p�����[�^

	//Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	//���݂̃f�B�X�v���C���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//�f�o�C�X�̃v���[���e�[�V�����̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp)); //�[���N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH; //�Q�[����ʃT�C�Y�i�����j
	d3dpp.BackBufferHeight = SCREEN_HEIGHT; //�Q�[����ʃT�C�Y�i�����j
	d3dpp.BackBufferFormat = d3ddm.Format; //�`��
	d3dpp.BackBufferCount = 1; //�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; //�_�u���o�b�t�@�̐؂�ւ�
	d3dpp.EnableAutoDepthStencil = TRUE; //�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16; //�f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow; //�E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; //���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT; //�C���^�[�o��

	//Direct3D�f�o�C�X�̐����i�`�揈���ƒ��_�������n�[�h�E�F�A�ōs���j
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		//Direct3D�f�o�C�X�̐����i�`�揈���̓n�[�h�E�F�A�A���_������CPU�ōs��)
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			//Direct3D�̃f�o�C�X�̐����i�����Ƃ�CPU�j
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
	//�����^�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	
	g_bWireFrame = false; //���C���[�t���[����`�悵�Ȃ�
	g_bEdit = false; //�G�f�B�b�g�����Ȃ�
	g_ModelCnt = 0;
	g_nUseModel = 0;
	//�L�[�{�[�h�̏���������
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�̏���������
	if (FAILED(InitMouse(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//pad�̏���������
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
		"�����ӂ����", &g_pFont);


	return S_OK;
}

//=============================================
//�I������
//=============================================
void Uninit(void)
{
	//�}�E�X�̏I������
	UninitMouse();

	//�L�[�{�[�h�̏I������
	UninitKeyboard();

	//pad�̏I������
	UninitJoypad();

	UninitCamera();

	UninitLight();

	UninitField();

	UninitWall();

	UninitModel();

	UninitShadow();

	UninitEdit();

	//Direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3D�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//=============================================
//�X�V����
//=============================================
void Update(void)
{
	//�L�[�{�[�h�̍X�V����
	UpdateKeyboard();

	//�L�[�{�[�h�̍X�V����
	UpdateMouse();

	//pad�̍X�V����
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
	{//�G�f�B�b�g���ĂȂ��Ƃ�
		UpdateField();

		UpdateWall();

		UpdateModel();

		UpdateShadow();
	}

	//���C���[�t���[���؂�ւ�
	if (GetKeyboardTrigger(DIK_F9) == true)
	{
		g_bWireFrame = g_bWireFrame ? false : true;
		WireFrame();
	}

	//DWORD NowTime = timeGetTime(); //���񎞍�

	//DWORD DeltaTime = NowTime - OldTime; //�u�Ԍo�ߎ���

	//OldTime = NowTime;
	//
	//float fDeltaTime = DeltaTime / 60;

	//SetTime(fDeltaTime);
}

//=============================================
//�`�揈��
//=============================================
void Draw(void)
{
	//��ʃN���A�i�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A)
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��J�n
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
		//�`��I��
		g_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================
//�E�B���h�E�v���V�[�W��
//=============================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	switch (uMsg)
	{
	case WM_CLOSE:

		nID = MessageBox(hWnd, "�I�����܂����H", "�m�F", MB_YESNO | MB_ICONWARNING);
		if (nID == IDYES)
		{
			//�E�B���h�E��j������
			DestroyWindow(hWnd);
		}
		else
		{
			return 0; //0��Ԃ��Ȃ��ƏI�����Ă��܂�
		}
		break;

	case WM_DESTROY:
		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN: //�L�[�������ꂽ���̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE: //esc�L�[�������ꂽ
			nID = MessageBox(hWnd, "�I�����܂����H", "�m�F", MB_YESNO | MB_ICONWARNING);
			if (nID == IDYES)
			{
				//�E�B���h�E��j������
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
//���Ԃ̐ݒ�
//=============================================
void SetTime(DWORD time)
{
	//MSG msg; //���b�Z�[�W���i�[����
	//DWORD dwCurrentTime; //���ݎ���
	//DWORD dwExecLastTime; //�Ō�ɏ��������Ƃ��̎���
	//DWORD dwFrameCnt; //�t���[���J�E���g
	//DWORD dwFPSLastTime; //�Ō�ɃJ�E���g����FPS

	//dwCurrentTime = 0; //������
	//dwFrameCnt = 0;
	//dwExecLastTime = time; //���ݎ���
	//dwFPSLastTime = time; //���ݎ���

	////���b�Z�[�W���[�v
	//while (1)
	//{
	//	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
	//	{//�E�B���h�E�̏���
	//		if (msg.message == WM_QUIT)
	//		{//WM_QUIT���󂯎�����烁�b�Z�[�W���[�v�𔲂���
	//			break;
	//		}
	//		else
	//		{
	//			//���b�Z�[�W�̐ݒ�
	//			TranslateMessage(&msg); //���z�L�[�𕶎��֕ϊ�
	//			DispatchMessage(&msg); //�E�B���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
	//		}
	//	}
	//	else
	//	{//DirectX�̏���
	//		dwCurrentTime = time;
	//		if ((dwCurrentTime - dwFPSLastTime) >= 500)
	//		{//0.5�b�o��
	//			//FPS���v��
	//			g_nCntFPS = (dwFrameCnt * 1000) / (dwCurrentTime - dwFPSLastTime);
	//			dwFPSLastTime = dwCurrentTime; //FPS�𑪒肵��������ۑ�
	//			dwFrameCnt = 0; //�t���[���J�E���g
	//		}
	//		if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
	//		{//60����1�b�o��
	//			dwExecLastTime = dwCurrentTime; //�ŏI�����̐ݒ�
	//			////�X�V����
	//			//Update();
	//			////�`�揈��
	//			//Draw();
	//			dwFrameCnt++;
	//		}
	//	}
	//}
}

//=============================================
//���[�h
//=============================================
void LoadModel(void)
{
	//�t�@�C���̓ǂݍ���
	FILE* pFile = fopen(MODEL_FILE_BIN, "rb");

	if (pFile != NULL)
	{
		//�G�̎g�p���Ă鐔�̓ǂݍ���
		fread(&g_nUseModel, sizeof(int), 1, pFile);

		//�G�̎g�p�����A�G�̓ǂݍ���
		fread(&g_aModelInfo[0], sizeof(ModelInfo), g_nUseModel, pFile);

		//�t�@�C�������
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
//�f�o�C�X�̎擾
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
//���C���[�t���[��on:off
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