//�������w�b�_�t�@�C���ǂݍ��݁�����//
#include <ctime>
#include <memory>
#include "InputManager.h"
#include "Main.h"
#include <XInput.h>
#include "Resource.h"
#include "SceneManager.h"
#include "SoundManager.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

//�������萔�E�}�N����`������//
#define FPS 1000 / 60
#define WINDOW_CAPTION "�X�P�[�^�K�[�� RESTART"	//�E�C���h�E�̃L���v�V������
#define WINDOW_CLASS_NAME "SkaterGirl"			//�E�C���h�E�̃N���X��

//�������v���g�^�C�v�錾������//
void Draw(void);
HRESULT Initialize(HINSTANCE, HWND);
void OnCreate(HWND, LPCREATESTRUCT);
HRESULT SetupEnvironment(HWND);
void UnInitialize(void);
void Update(void);
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

#ifdef _DEBUG
void DrawFPS(void);
#endif

//�������O���[�o���ϐ�������//
std::unique_ptr<LPDIRECT3D9> g_pD3D;			 //Direct3D �I�u�W�F�N�g
std::unique_ptr<LPDIRECT3DDEVICE9> g_pD3DDevice; //Device�I�u�W�F�N�g(�`��ɕK�v)

#ifdef _DEBUG
int	g_nCountFPS;		//FPS�J�E���^
std::unique_ptr<LPD3DXFONT> g_pD3DXFont;	//�t�H���g�ւ̃|�C���^
#endif


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF  | _CRTDBG_LEAK_CHECK_DF);

    //---���g�p�錾---//
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

    //---�e��錾---//
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
    HWND hWnd;
    MSG msgMsg;

    //---����������---//
    setlocale(LC_ALL, "Japanese");
    g_pD3D.reset(new LPDIRECT3D9());
    g_pD3DDevice.reset(new LPDIRECT3DDEVICE9());

#ifdef _DEBUG
    g_pD3DXFont.reset(new LPD3DXFONT());
#endif

    //�����V�[�h�l�̏�����
    srand((unsigned int)time(NULL));

    //�E�B���h�E�N���X�̏�����
    const WNDCLASSEX wcex = { sizeof(WNDCLASSEX), CS_CLASSDC, WindowProc, 0, 0, hInstance, LoadIcon(wcex.hInstance, MAKEINTRESOURCE(APPLICATION_ICON)), LoadCursor(nullptr, IDC_ARROW), (HBRUSH)(COLOR_WINDOW + 1), nullptr, TEXT(WINDOW_CLASS_NAME), LoadIcon(wcex.hInstance, MAKEINTRESOURCE(APPLICATION_ICON_SMALL)) };

    //---�E�B���h�E����---//
	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�E�B���h�E�̍쐬
    hWnd = CreateWindowEx(0, TEXT(WINDOW_CLASS_NAME), TEXT(WINDOW_CAPTION), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_BORDER | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, (int)(SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2), (int)(SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)), nullptr, nullptr, hInstance, nullptr);
    if (!hWnd)
    {
        MessageBox(nullptr, TEXT("�E�B���h�E�̍쐬�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        return -1;
    }

    //�E�B���h�E�̕\��
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    //COM���C�u�����̏�����
    if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
    {
        MessageBox(hWnd, TEXT("COM���C�u�����̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
        return -1;
    }

	//�f�[�^����������
	if (FAILED(Initialize(hInstance, hWnd)))
	{
        MessageBox(hWnd, TEXT("�f�[�^�̏������Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
		return -1;
	}

	//---�t���[�����䏉����---//
    //����\��ݒ�
    if (timeBeginPeriod(1))
    {
        MessageBox(hWnd, TEXT("�^�C�}�[����\���w��l�ɐݒ�ł��܂���ł���"), TEXT("FPS�ݒ�G���["), MB_OK);
        return -1;
    }

    //���Ԃ̏�����
    dwExecLastTime = dwFPSLastTime = timeGetTime();

    //�t���[������������
	dwCurrentTime =	dwFrameCount = 0;

	//---���b�Z�[�W���[�v---//
	while (true)
	{
		if (PeekMessage(&msgMsg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msgMsg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msgMsg);
				DispatchMessage(&msgMsg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();

            //0.5�b���ƂɎ��s
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
#ifdef _DEBUG
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
#endif
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= FPS)
			{
                //�ŏI�X�V���ԍX�V
				dwExecLastTime = dwCurrentTime;

				//�X�V����
				Update();

				//�`�揈��
				Draw();

                //�t���[���J�E���g�A�b�v
				++dwFrameCount;
			}
		}
	}

    //---�I������---//
    UnInitialize();

    //����\��߂�
    timeEndPeriod(1);

	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(TEXT(WINDOW_CLASS_NAME), wcex.hInstance);

    //COM���C�u���������
    CoUninitialize();

    return (int)msgMsg.wParam;
}


//�������֐���`������//
/////////////////////////////////////////////
//�֐����FWindowProc
//
//�@�\�F�E�B���h�E�v���V�[�W��
//
//�����F(HWND)�n���h��,(UINT)���b�Z�[�W�L���[,(WPARAM)�p�����[�^,(LPARAM)�p�����[�^
//
//�߂�l�F(LRESULT)�����̐���
/////////////////////////////////////////////
LRESULT CALLBACK WindowProc(HWND handle, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
        case WM_ACTIVATEAPP:
            XInputEnable(wparam ? true : false);
            break;

        case WM_CREATE:
            OnCreate(handle, (LPCREATESTRUCT)lparam);
            break;

	    case WM_DESTROY:
		    PostQuitMessage(0);
            break;

	    default:
		    break;
	}

	return DefWindowProc(handle, message, wparam, lparam);
}

/////////////////////////////////////////////
//�֐����FDraw
//
//�@�\�F�`�揈���̓����֐�
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void Draw(void)
{
    //�o�b�N�o�b�t�@���y�o�b�t�@���X�e���V���o�b�t�@�̃N���A
    (*g_pD3DDevice)->Clear(0, nullptr, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0F, 0);

    //Direct3D�ɂ��`��̊J�n
    if (SUCCEEDED((*g_pD3DDevice)->BeginScene()))
    {
        //�V�[���`��
        SCENEMANAGER::Draw();

#ifdef _DEBUG
        //FPS�\��
        DrawFPS();
#endif

        //Direct3D�ɂ��`��̏I��
        (*g_pD3DDevice)->EndScene();
    }

    //�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
    (*g_pD3DDevice)->Present(nullptr, nullptr, nullptr, nullptr);
}

/////////////////////////////////////////////
//�֐����FInitialize
//
//�@�\�F�������̓����֐�
//
//�����F(HINSTANCE)�C���X�^���X,(HWND)�n���h��
//
//�߂�l�F(HRESULT)�����̐���
/////////////////////////////////////////////
HRESULT Initialize(HINSTANCE instance, HWND handle)
{
    //---�e��錾---//
    HRESULT hResult;

    //---���ݒ�---//
    hResult = SetupEnvironment(handle);

    //---���͏�����---//
    if (SUCCEEDED(hResult))
    {
        hResult = INPUTMANAGER::Initialize(instance, handle);
    }

    //---�T�E���h������---//
    if (SUCCEEDED(hResult))
    {
        hResult = SOUNDMANAGER::Initialize();
    }

    //---�V�[��������---//
    if (SUCCEEDED(hResult))
    {
        hResult = SCENEMANAGER::Initialize();
    }

    //---�f�o�b�O�\��������---//
    if (SUCCEEDED(hResult))
    {
        hResult = SCENEMANAGER::Initialize();
    }

    if (SUCCEEDED(hResult))
    {
        return S_OK;
    }
    else
    {
        return S_FALSE;
    }
}

/////////////////////////////////////////////
//�֐����FOnCreate
//
//�@�\�F�E�B���h�E�̏ڍאݒ�
//
//�����F(HWND)�E�B���h�E�n���h��,(LPCREATESTRUCT)�T�C�Y
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void OnCreate(HWND handle, LPCREATESTRUCT lpcs)
{
    //---�e��錾---//
    RECT rcClnt;
    RECT rcWnd;
    SIZE sizeWnd;

    //---�E�B���h�E�T�C�Y�̐ݒ�---//
    GetWindowRect(handle, &rcWnd);
    GetClientRect(handle, &rcClnt);

    sizeWnd.cx = (LONG)((rcWnd.right - rcWnd.left) - (rcClnt.right - rcClnt.left) + SCREEN_WIDTH);
    sizeWnd.cy = (LONG)((rcWnd.bottom - rcWnd.top) - (rcClnt.bottom - rcClnt.top) + SCREEN_HEIGHT);

    SetWindowPos(handle, nullptr, 0, 0, sizeWnd.cx, sizeWnd.cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER);

    //---IME���͂̋֎~---//
    ImmAssociateContext(handle, nullptr);
}

/////////////////////////////////////////////
//�֐����FSetupEnvironment
//
//�@�\�F���ݒ�
//
//�����F(HWND)�n���h��
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
HRESULT SetupEnvironment(HWND handle)
{
    //---�e��錾---//
    D3DDISPLAYMODE d3ddm;
    D3DPRESENT_PARAMETERS d3dpp;

    //---Direct3D�I�u�W�F�N�g�̍쐬---//
    *g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    if (!*g_pD3D)
    {
        return E_FAIL;
    }

    //---���݂̃f�B�X�v���C���[�h���擾---//
    if (FAILED((*g_pD3D)->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
    {
        return E_FAIL;
    }

    //---�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�---//
    memset(&d3dpp, 0, sizeof(D3DPRESENT_PARAMETERS));	        //���[�N���[���N���A
    d3dpp.BackBufferCount = 1;						            //�o�b�N�o�b�t�@�̐�
    d3dpp.BackBufferWidth = (UINT)SCREEN_WIDTH;				    //�Q�[����ʃT�C�Y(��)
    d3dpp.BackBufferHeight = (UINT)SCREEN_HEIGHT;			    //�Q�[����ʃT�C�Y(����)
    d3dpp.BackBufferFormat = d3ddm.Format;				        //�o�b�N�o�b�t�@�t�H�[�}�b�g�̓f�B�X�v���C���[�h�ɍ��킹�Đݒ�
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	                //�f���M���ɓ������ăt���b�v����
    d3dpp.Windowed = TRUE;					                    //�E�B���h�E���[�h
    d3dpp.EnableAutoDepthStencil = TRUE;				        //�f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
    d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;		        //�f�v�X�o�b�t�@�Ƃ���24bit�A�X�e���V���o�b�t�@�Ƃ���8bit���g��
    d3dpp.FullScreen_RefreshRateInHz = 0;						//���t���b�V�����[�g
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	//���������M���ɓ������Ȃ�

    //---�f�o�C�X�I�u�W�F�N�g�̐���---//
    //[�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs�Ȃ�
    if (FAILED((*g_pD3D)->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, handle, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, g_pD3DDevice.get())))
    {
        //��L�̐ݒ肪���s������[�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A�ōs���A<���_����>��CPU�ōs�Ȃ�
        if (FAILED((*g_pD3D)->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, handle, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, g_pD3DDevice.get())))
        {
            //��L�̐ݒ肪���s������[�f�o�C�X�쐬����]<�`��>��<���_����>��CPU�ōs�Ȃ�
            if (FAILED((*g_pD3D)->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, handle, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, g_pD3DDevice.get())))
            {
                //���������s
                MessageBox(handle, TEXT("�f�o�C�X�I�u�W�F�N�g�̍쐬�Ɏ��s���܂���"), TEXT("�������G���["), MB_OK);
                return E_FAIL;
            }
        }
    }

    //---�����_�[�X�e�[�g�p�����[�^�̐ݒ�---//
    (*g_pD3DDevice)->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);			//���ʂ̃J�����O
    (*g_pD3DDevice)->SetRenderState(D3DRS_ZENABLE, TRUE);					//Z�o�b�t�@���g�p
    (*g_pD3DDevice)->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			//�A���t�@�u�����h���s��
    (*g_pD3DDevice)->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//�A���t�@�\�[�X�J���[�̎w��
    (*g_pD3DDevice)->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//�A���t�@�f�X�e�B�l�[�V�����J���[�̎w��

    //---�T���v���[�X�e�[�g�p�����[�^�̐ݒ�---//
    (*g_pD3DDevice)->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//�e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
    (*g_pD3DDevice)->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	//�e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
    (*g_pD3DDevice)->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	    //�e�N�X�`���g��t�B���^���[�h��ݒ�
    (*g_pD3DDevice)->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	    //�e�N�X�`���k���t�B���^���[�h��ݒ�

    //---�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�---//
    (*g_pD3DDevice)->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	//�A���t�@�u�����f�B���O����
    (*g_pD3DDevice)->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	//�ŏ��̃A���t�@����
    (*g_pD3DDevice)->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	//�Q�Ԗڂ̃A���t�@����

#ifdef _DEBUG
    //---���\���p�t�H���g��ݒ�---//
    D3DXCreateFont((*g_pD3DDevice), 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, TEXT("Terminal"), g_pD3DXFont.get());
#endif

    return S_OK;
}

/////////////////////////////////////////////
//�֐����FUnInitialize
//
//�@�\�F�I�������̓����֐�
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void UnInitialize(void)
{
    //---���͂̏I��---//
    INPUTMANAGER::Uninitialize();

    //---�V�[���̏I��---//
    SCENEMANAGER::Uninitialize();

    //---�T�E���h�̏I��---//
    SOUNDMANAGER::Uninitialize();

#ifdef _DEBUG
    //---���\���p�t�H���g�̊J��---//
    SAFE_RELEASE((*g_pD3DXFont));
#endif

    //---�f�o�C�X�̉��---//
    SAFE_RELEASE((*g_pD3DDevice));

    //---Direct3D�I�u�W�F�N�g�̊J��---//
    SAFE_RELEASE((*g_pD3D));
}

/////////////////////////////////////////////
//�֐����FUpdate
//
//�@�\�F�X�V�����̓����֐�
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void Update(void)
{
    //---���͂̍X�V---//
    INPUTMANAGER::Update();

	//---�V�[���̍X�V---//
    SCENEMANAGER::Update();
}

/////////////////////////////////////////////
//�֐����FGetDevice
//
//�@�\�F�f�o�C�X�̎擾
//
//�����F�Ȃ�
//
//�߂�l�F(LPDIRECT3DDEVICE9)�f�o�C�X
/////////////////////////////////////////////
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return *g_pD3DDevice;
}

#ifdef _DEBUG
/////////////////////////////////////////////
//�֐����FDrawFPS
//
//�@�\�F�t���[�����[�g�̕`��
//
//�����F�Ȃ�
//
//�߂�l�F�Ȃ�
/////////////////////////////////////////////
void DrawFPS(void)
{
	static RECT rRectangle = { 0, 0, (LONG)SCREEN_WIDTH, (LONG)SCREEN_HEIGHT };
    TCHAR szString[10];

	wsprintf(szString, TEXT("FPS:%d\n"), g_nCountFPS);

	//�e�L�X�g�`��
	(*g_pD3DXFont)->DrawText(nullptr, szString, -1, &rRectangle, DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 255));
}
#endif