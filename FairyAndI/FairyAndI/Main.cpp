//＝＝＝ヘッダファイル読み込み＝＝＝//
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

//＝＝＝定数・マクロ定義＝＝＝//
#define FPS 1000 / 60
#define WINDOW_CAPTION "スケータガール RESTART"	//ウインドウのキャプション名
#define WINDOW_CLASS_NAME "SkaterGirl"			//ウインドウのクラス名

//＝＝＝プロトタイプ宣言＝＝＝//
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

//＝＝＝グローバル変数＝＝＝//
std::unique_ptr<LPDIRECT3D9> g_pD3D;			 //Direct3D オブジェクト
std::unique_ptr<LPDIRECT3DDEVICE9> g_pD3DDevice; //Deviceオブジェクト(描画に必要)

#ifdef _DEBUG
int	g_nCountFPS;		//FPSカウンタ
std::unique_ptr<LPD3DXFONT> g_pD3DXFont;	//フォントへのポインタ
#endif


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF  | _CRTDBG_LEAK_CHECK_DF);

    //---未使用宣言---//
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

    //---各種宣言---//
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
    HWND hWnd;
    MSG msgMsg;

    //---初期化処理---//
    setlocale(LC_ALL, "Japanese");
    g_pD3D.reset(new LPDIRECT3D9());
    g_pD3DDevice.reset(new LPDIRECT3DDEVICE9());

#ifdef _DEBUG
    g_pD3DXFont.reset(new LPD3DXFONT());
#endif

    //乱数シード値の初期化
    srand((unsigned int)time(NULL));

    //ウィンドウクラスの初期化
    const WNDCLASSEX wcex = { sizeof(WNDCLASSEX), CS_CLASSDC, WindowProc, 0, 0, hInstance, LoadIcon(wcex.hInstance, MAKEINTRESOURCE(APPLICATION_ICON)), LoadCursor(nullptr, IDC_ARROW), (HBRUSH)(COLOR_WINDOW + 1), nullptr, TEXT(WINDOW_CLASS_NAME), LoadIcon(wcex.hInstance, MAKEINTRESOURCE(APPLICATION_ICON_SMALL)) };

    //---ウィンドウ準備---//
	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//ウィンドウの作成
    hWnd = CreateWindowEx(0, TEXT(WINDOW_CLASS_NAME), TEXT(WINDOW_CAPTION), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_BORDER | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, (int)(SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2), (int)(SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)), nullptr, nullptr, hInstance, nullptr);
    if (!hWnd)
    {
        MessageBox(nullptr, TEXT("ウィンドウの作成に失敗しました"), TEXT("初期化エラー"), MB_OK);
        return -1;
    }

    //ウィンドウの表示
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    //COMライブラリの初期化
    if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
    {
        MessageBox(hWnd, TEXT("COMライブラリの初期化に失敗しました"), TEXT("初期化エラー"), MB_OK);
        return -1;
    }

	//データ初期化処理
	if (FAILED(Initialize(hInstance, hWnd)))
	{
        MessageBox(hWnd, TEXT("データの初期化に失敗しました"), TEXT("初期化エラー"), MB_OK);
		return -1;
	}

	//---フレーム制御初期化---//
    //分解能を設定
    if (timeBeginPeriod(1))
    {
        MessageBox(hWnd, TEXT("タイマー分解能を指定値に設定できませんでした"), TEXT("FPS設定エラー"), MB_OK);
        return -1;
    }

    //時間の初期化
    dwExecLastTime = dwFPSLastTime = timeGetTime();

    //フレーム数を初期化
	dwCurrentTime =	dwFrameCount = 0;

	//---メッセージループ---//
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
				//メッセージの翻訳とディスパッチ
				TranslateMessage(&msgMsg);
				DispatchMessage(&msgMsg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();

            //0.5秒ごとに実行
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
                //最終更新時間更新
				dwExecLastTime = dwCurrentTime;

				//更新処理
				Update();

				//描画処理
				Draw();

                //フレームカウントアップ
				++dwFrameCount;
			}
		}
	}

    //---終了処理---//
    UnInitialize();

    //分解能を戻す
    timeEndPeriod(1);

	//ウィンドウクラスの登録を解除
	UnregisterClass(TEXT(WINDOW_CLASS_NAME), wcex.hInstance);

    //COMライブラリを閉じる
    CoUninitialize();

    return (int)msgMsg.wParam;
}


//＝＝＝関数定義＝＝＝//
/////////////////////////////////////////////
//関数名：WindowProc
//
//機能：ウィンドウプロシージャ
//
//引数：(HWND)ハンドル,(UINT)メッセージキュー,(WPARAM)パラメータ,(LPARAM)パラメータ
//
//戻り値：(LRESULT)処理の成否
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
//関数名：Draw
//
//機能：描画処理の統合関数
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void Draw(void)
{
    //バックバッファ＆Ｚバッファ＆ステンシルバッファのクリア
    (*g_pD3DDevice)->Clear(0, nullptr, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0F, 0);

    //Direct3Dによる描画の開始
    if (SUCCEEDED((*g_pD3DDevice)->BeginScene()))
    {
        //シーン描画
        SCENEMANAGER::Draw();

#ifdef _DEBUG
        //FPS表示
        DrawFPS();
#endif

        //Direct3Dによる描画の終了
        (*g_pD3DDevice)->EndScene();
    }

    //バックバッファとフロントバッファの入れ替え
    (*g_pD3DDevice)->Present(nullptr, nullptr, nullptr, nullptr);
}

/////////////////////////////////////////////
//関数名：Initialize
//
//機能：初期化の統合関数
//
//引数：(HINSTANCE)インスタンス,(HWND)ハンドル
//
//戻り値：(HRESULT)処理の成否
/////////////////////////////////////////////
HRESULT Initialize(HINSTANCE instance, HWND handle)
{
    //---各種宣言---//
    HRESULT hResult;

    //---環境設定---//
    hResult = SetupEnvironment(handle);

    //---入力初期化---//
    if (SUCCEEDED(hResult))
    {
        hResult = INPUTMANAGER::Initialize(instance, handle);
    }

    //---サウンド初期化---//
    if (SUCCEEDED(hResult))
    {
        hResult = SOUNDMANAGER::Initialize();
    }

    //---シーン初期化---//
    if (SUCCEEDED(hResult))
    {
        hResult = SCENEMANAGER::Initialize();
    }

    //---デバッグ表示初期化---//
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
//関数名：OnCreate
//
//機能：ウィンドウの詳細設定
//
//引数：(HWND)ウィンドウハンドル,(LPCREATESTRUCT)サイズ
//
//戻り値：なし
/////////////////////////////////////////////
void OnCreate(HWND handle, LPCREATESTRUCT lpcs)
{
    //---各種宣言---//
    RECT rcClnt;
    RECT rcWnd;
    SIZE sizeWnd;

    //---ウィンドウサイズの設定---//
    GetWindowRect(handle, &rcWnd);
    GetClientRect(handle, &rcClnt);

    sizeWnd.cx = (LONG)((rcWnd.right - rcWnd.left) - (rcClnt.right - rcClnt.left) + SCREEN_WIDTH);
    sizeWnd.cy = (LONG)((rcWnd.bottom - rcWnd.top) - (rcClnt.bottom - rcClnt.top) + SCREEN_HEIGHT);

    SetWindowPos(handle, nullptr, 0, 0, sizeWnd.cx, sizeWnd.cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER);

    //---IME入力の禁止---//
    ImmAssociateContext(handle, nullptr);
}

/////////////////////////////////////////////
//関数名：SetupEnvironment
//
//機能：環境設定
//
//引数：(HWND)ハンドル
//
//戻り値：なし
/////////////////////////////////////////////
HRESULT SetupEnvironment(HWND handle)
{
    //---各種宣言---//
    D3DDISPLAYMODE d3ddm;
    D3DPRESENT_PARAMETERS d3dpp;

    //---Direct3Dオブジェクトの作成---//
    *g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    if (!*g_pD3D)
    {
        return E_FAIL;
    }

    //---現在のディスプレイモードを取得---//
    if (FAILED((*g_pD3D)->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
    {
        return E_FAIL;
    }

    //---デバイスのプレゼンテーションパラメータの設定---//
    memset(&d3dpp, 0, sizeof(D3DPRESENT_PARAMETERS));	        //ワークをゼロクリア
    d3dpp.BackBufferCount = 1;						            //バックバッファの数
    d3dpp.BackBufferWidth = (UINT)SCREEN_WIDTH;				    //ゲーム画面サイズ(幅)
    d3dpp.BackBufferHeight = (UINT)SCREEN_HEIGHT;			    //ゲーム画面サイズ(高さ)
    d3dpp.BackBufferFormat = d3ddm.Format;				        //バックバッファフォーマットはディスプレイモードに合わせて設定
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	                //映像信号に同期してフリップする
    d3dpp.Windowed = TRUE;					                    //ウィンドウモード
    d3dpp.EnableAutoDepthStencil = TRUE;				        //デプスバッファ（Ｚバッファ）とステンシルバッファを作成
    d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;		        //デプスバッファとして24bit、ステンシルバッファとして8bitを使う
    d3dpp.FullScreen_RefreshRateInHz = 0;						//リフレッシュレート
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	//垂直同期信号に同期しない

    //---デバイスオブジェクトの生成---//
    //[デバイス作成制御]<描画>と<頂点処理>をハードウェアで行なう
    if (FAILED((*g_pD3D)->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, handle, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, g_pD3DDevice.get())))
    {
        //上記の設定が失敗したら[デバイス作成制御]<描画>をハードウェアで行い、<頂点処理>はCPUで行なう
        if (FAILED((*g_pD3D)->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, handle, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, g_pD3DDevice.get())))
        {
            //上記の設定が失敗したら[デバイス作成制御]<描画>と<頂点処理>をCPUで行なう
            if (FAILED((*g_pD3D)->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, handle, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, g_pD3DDevice.get())))
            {
                //初期化失敗
                MessageBox(handle, TEXT("デバイスオブジェクトの作成に失敗しました"), TEXT("初期化エラー"), MB_OK);
                return E_FAIL;
            }
        }
    }

    //---レンダーステートパラメータの設定---//
    (*g_pD3DDevice)->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);			//裏面のカリング
    (*g_pD3DDevice)->SetRenderState(D3DRS_ZENABLE, TRUE);					//Zバッファを使用
    (*g_pD3DDevice)->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			//アルファブレンドを行う
    (*g_pD3DDevice)->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//アルファソースカラーの指定
    (*g_pD3DDevice)->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//アルファデスティネーションカラーの指定

    //---サンプラーステートパラメータの設定---//
    (*g_pD3DDevice)->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//テクスチャアドレッシング方法(U値)を設定
    (*g_pD3DDevice)->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	//テクスチャアドレッシング方法(V値)を設定
    (*g_pD3DDevice)->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	    //テクスチャ拡大フィルタモードを設定
    (*g_pD3DDevice)->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	    //テクスチャ縮小フィルタモードを設定

    //---テクスチャステージステートの設定---//
    (*g_pD3DDevice)->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	//アルファブレンディング処理
    (*g_pD3DDevice)->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	//最初のアルファ引数
    (*g_pD3DDevice)->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	//２番目のアルファ引数

#ifdef _DEBUG
    //---情報表示用フォントを設定---//
    D3DXCreateFont((*g_pD3DDevice), 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, TEXT("Terminal"), g_pD3DXFont.get());
#endif

    return S_OK;
}

/////////////////////////////////////////////
//関数名：UnInitialize
//
//機能：終了処理の統合関数
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void UnInitialize(void)
{
    //---入力の終了---//
    INPUTMANAGER::Uninitialize();

    //---シーンの終了---//
    SCENEMANAGER::Uninitialize();

    //---サウンドの終了---//
    SOUNDMANAGER::Uninitialize();

#ifdef _DEBUG
    //---情報表示用フォントの開放---//
    SAFE_RELEASE((*g_pD3DXFont));
#endif

    //---デバイスの解放---//
    SAFE_RELEASE((*g_pD3DDevice));

    //---Direct3Dオブジェクトの開放---//
    SAFE_RELEASE((*g_pD3D));
}

/////////////////////////////////////////////
//関数名：Update
//
//機能：更新処理の統合関数
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void Update(void)
{
    //---入力の更新---//
    INPUTMANAGER::Update();

	//---シーンの更新---//
    SCENEMANAGER::Update();
}

/////////////////////////////////////////////
//関数名：GetDevice
//
//機能：デバイスの取得
//
//引数：なし
//
//戻り値：(LPDIRECT3DDEVICE9)デバイス
/////////////////////////////////////////////
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return *g_pD3DDevice;
}

#ifdef _DEBUG
/////////////////////////////////////////////
//関数名：DrawFPS
//
//機能：フレームレートの描画
//
//引数：なし
//
//戻り値：なし
/////////////////////////////////////////////
void DrawFPS(void)
{
	static RECT rRectangle = { 0, 0, (LONG)SCREEN_WIDTH, (LONG)SCREEN_HEIGHT };
    TCHAR szString[10];

	wsprintf(szString, TEXT("FPS:%d\n"), g_nCountFPS);

	//テキスト描画
	(*g_pD3DXFont)->DrawText(nullptr, szString, -1, &rRectangle, DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 255));
}
#endif