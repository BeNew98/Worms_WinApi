#include "GameEngineWindow.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEnginePlatform/GameEngineInput.h>

// LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM)

HWND GameEngineWindow::HWnd = nullptr;
HDC GameEngineWindow::WindowBackBufferHdc = nullptr;
float4 GameEngineWindow::WindowSize = { 800, 600 };
float4 GameEngineWindow::WindowPos = { 100, 100 };
float4 GameEngineWindow::ScreenSize = { 800, 600 };
GameEngineImage* GameEngineWindow::BackBufferImage = nullptr;
GameEngineImage* GameEngineWindow::DoubleBufferImage = nullptr;
bool GameEngineWindow::IsWindowUpdate = true;


LRESULT CALLBACK GameEngineWindow::MessageFunction(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
    switch (_message)
    {
    case WM_MOUSEMOVE:
    {
        int a = 0;
        break;
    }
    // �� �����찡 ���õ�.
    case WM_SETFOCUS:
    {
        int a = 0;
        break;
    }
    case WM_ACTIVATE:
    {
        int a = 0;
        break;
    }
    case WM_KILLFOCUS:
    {
        int a = 0;
        break;
    }
    case WM_KEYDOWN:
    {
        GameEngineInput::IsAnyKeyOn();
        break;
    }
    case WM_DESTROY:
    {
        // Message�Լ��� 0�� �����ϰ� �����.
        PostQuitMessage(0);
        IsWindowUpdate = false;
        break;
    }
    default:
        return DefWindowProc(_hWnd, _message, _wParam, _lParam);
    }

    return 0;
}

GameEngineWindow::GameEngineWindow()
{
}

GameEngineWindow::~GameEngineWindow()
{
}


void GameEngineWindow::WindowCreate(HINSTANCE _hInstance, const std::string_view& _TitleName, float4 _Size, float4 _Pos)
{

    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = &GameEngineWindow::MessageFunction;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInstance;
    // �ȳ����� �⺻ ������
    wcex.hIcon = nullptr; //LoadIcon(_hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // ��� 
    wcex.lpszMenuName = nullptr; //MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName = "GameEngineWindowDefault";
    wcex.hIconSm = nullptr; //LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    // GameEngineWindowDefault ��� �̸��� ������ Ŭ������ ����ش޶�� ��û�ϴ°�.
    if (0 == RegisterClassEx(&wcex))
    {
        MsgAssert("������ Ŭ���� ��Ͽ� �����߽��ϴ�.");
        return;
    }

    // hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����Ѵ�.

    HWnd = CreateWindow("GameEngineWindowDefault", _TitleName.data(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInstance, nullptr);

    if (!HWnd)
    {
        MsgAssert("������ Ŭ���� ������ �����߽��ϴ�.");
        return;
    }

    WindowBackBufferHdc = GetDC(HWnd);

    ShowWindow(HWnd, SW_SHOW);
    UpdateWindow(HWnd);

    SettingWindowSize(_Size);
    SettingWindowPos(_Pos);

    BackBufferImage = new GameEngineImage();
    BackBufferImage->ImageCreate(WindowBackBufferHdc);

    return;
}

void GameEngineWindow::DoubleBufferClear()
{
    DoubleBufferImage->ImageClear();
}

void GameEngineWindow::DoubleBufferRender()
{
    BackBufferImage->BitCopy(DoubleBufferImage, WindowSize.half(), WindowSize);
}

int GameEngineWindow::WindowLoop(void(*_Start)(), void(*_Loop)(), void(*_End)())
{
    // ����Ű. �Ƚᵵ ���� x
    // HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    if (nullptr != _Start)
    {
        _Start();
    }


    MSG msg = {};

    // ���� �Լ��� ����ɶ����� ���α׷��� ����

    // �⺻ �޽��� ����
    // GetMessage�� �� �����쿡 �������� ������� üũ����.
    // GetMessage�� �������� Ư���� ���� ���涧���� ���ߴ� �Լ�
    while (IsWindowUpdate)
    {
        // ������ �޼����� ó���Ѵ�.
        // GetMessage�� �����Լ��̱� ������ ���ʿ� ������ ����� �ִ� �޼��� ����� �ƴϴ�
        // => ������ �������� ���ƾ� �ϴµ�
        // GetMessage : �޼����� �־�� ���ϵǴ� �Լ�
        // �����쿡 �������� ����� ������ �Ѵ�.

        //PeekMessage �޼����� �ִ� ���� �����Ѵ�.
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))//PM_REMOVE : �׿��ִ� �޼��� �����ϱ�
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            //�޼����� �������� ������ ������
            if (nullptr != _Loop)
            {
                _Loop();

                GameEngineInput::IsAnyKeyOff();
            }
            continue;
        }

        if (nullptr != _Loop)
        {
            _Loop();
        }
        GameEngineInput::IsAnyKeyOff();
    }

    if (nullptr != _End)
    {
        _End();
    }

    if (nullptr != BackBufferImage)
    {
        delete BackBufferImage;
        BackBufferImage = nullptr;

        delete DoubleBufferImage;
        DoubleBufferImage = nullptr;
    }

    return (int)msg.wParam;
}

void GameEngineWindow::SettingWindowSize(float4 _Size)
{

    // Ÿ��Ʋ�� + �׵θ� ������ ũ����� ����� �ʿ���

    //          ��ġ  /    ũ��
    RECT Rc = { 0, 0, _Size.ix(), _Size.iy() };

    ScreenSize = _Size;

    // ���� ���ϴ� ũ�⸦ ������ Ÿ��Ʋ�ٱ��� ������ ũ�⸦ �����ִ� �Լ�.
    // ���ǵ� �־��־����.
    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);

    WindowSize = { static_cast<float>(Rc.right - Rc.left), static_cast<float>(Rc.bottom - Rc.top) };
    SetWindowPos(HWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);

    if (nullptr != DoubleBufferImage)
    {
        delete DoubleBufferImage;
        DoubleBufferImage = nullptr;
    }

    DoubleBufferImage = new GameEngineImage();
    DoubleBufferImage->ImageCreate(ScreenSize);
}
void GameEngineWindow::SettingWindowPos(float4 _Pos)
{
    WindowPos = _Pos;
    SetWindowPos(HWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);
}

float4 GameEngineWindow::GetMousePosition()
{
    POINT MoniterPoint;
    LPPOINT PointPtr = &MoniterPoint;
    GetCursorPos(PointPtr);
    ScreenToClient(HWnd, PointPtr);

    return { static_cast<float>(MoniterPoint.x),static_cast<float>(MoniterPoint.y) };
}