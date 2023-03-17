#include <windows.h>
#include <unordered_map>

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#include <wincodec.h>

HINSTANCE hInst;                                // ��ǰʵ��
WCHAR szTitle[] = L"wndtest";                  // �������ı�
WCHAR szWindowClass[] = L"wndtest";            // ����������

ID2D1Factory* g_factory;
ID2D1HwndRenderTarget* g_render_target;
ID2D1SolidColorBrush* g_brush;

IDWriteFactory* g_write_factory;
IDWriteTextFormat* g_text_format;

ID2D1GradientStopCollection* g_gradient_stop_collection;
ID2D1LinearGradientBrush* g_linear_gradient_brush;
ID2D1RadialGradientBrush* g_radial_gradient_brush;

IWICImagingFactory* g_image_factory = NULL;
std::unordered_map<LPCWSTR, ID2D1Bitmap*> g_image_map;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
int                 InitD2D1(HWND hWnd);
int                 LoadImageToList(LPCWSTR file_name);
ID2D1Bitmap*        GetID2D1Bitmap(LPCWSTR file_name);
void                DestroyD2D1();
void                onPaint(HWND hWnd, WPARAM wParam, LPARAM lParam);
void                OnSize(LPARAM& lparam);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    MyRegisterClass(hInstance);

    // ִ��Ӧ�ó����ʼ��:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, L"");
    MSG msg;

    // ����Ϣѭ��:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = nullptr;

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

int InitD2D1(HWND hWnd)
{
    HRESULT h_result;
	h_result = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (S_OK != h_result)
    {
        return h_result;
    }

	h_result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_factory);
    if (S_OK != h_result)
    {
        return h_result;
    }

    RECT rect;
    GetClientRect(hWnd, &rect);

    h_result = g_factory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(rect.right - rect.left, rect.bottom - rect.top)),
        &g_render_target
    );
    if (S_OK != h_result)
    {
        return h_result;
    }

	h_result = g_render_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::WhiteSmoke), &g_brush);
    if (S_OK != h_result)
    {
        return h_result;
    }

    h_result = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(g_write_factory), reinterpret_cast<IUnknown**>(&g_write_factory));
    if (S_OK != h_result)
    {
        return h_result;
    }
	h_result = g_write_factory->CreateTextFormat(L"Arial", NULL, DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 16, L"", &g_text_format);
	if (S_OK != h_result)
	{
		return h_result;
	}

    D2D1_GRADIENT_STOP gradient_stops[3];
    gradient_stops[0].color = D2D1::ColorF(D2D1::ColorF::LightGreen);
    gradient_stops[0].position = 0.0f;
    gradient_stops[1].color = D2D1::ColorF(D2D1::ColorF::DarkGreen);
    gradient_stops[1].position = 0.5f;
    gradient_stops[2].color = D2D1::ColorF(D2D1::ColorF::Green);
    gradient_stops[2].position = 1.0f;

    // Create Interface
	h_result = g_render_target->CreateGradientStopCollection(gradient_stops, 3, &g_gradient_stop_collection);
    if (S_OK != h_result)
    {
        return h_result;
    }

	h_result = g_render_target->CreateLinearGradientBrush(
        D2D1::LinearGradientBrushProperties(D2D1::Point2F(0, 0), D2D1::Point2F(600, 600)),
        g_gradient_stop_collection, &g_linear_gradient_brush);
    if (S_OK != h_result)
    {
        return h_result;
    }

	h_result = g_render_target->CreateRadialGradientBrush(
        D2D1::RadialGradientBrushProperties(D2D1::Point2F(500, 500), D2D1::Point2F(), 1000.0f, 1000.0f),
        g_gradient_stop_collection, &g_radial_gradient_brush);
    if (S_OK != h_result)
    {
        return h_result;
    }

	h_result = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, __uuidof(g_image_factory), (LPVOID*)&g_image_factory);
    if (S_OK != h_result)
    {
        return h_result;
    }


    LoadImageToList(L"D:/ctodolist/WindowsProject1/WindowsProject1/gdi/resource/image/background/ndmz.bmp");
    LoadImageToList(L"D:/ctodolist/WindowsProject1/WindowsProject1/gdi/resource/image/picture/jiantou0.png");
    LoadImageToList(L"D:/ctodolist/WindowsProject1/WindowsProject1/gdi/resource/image/picture/hh.png");

    return 0;
}

int LoadImageToList(LPCWSTR file_name)
{
    HRESULT h_result;

    IWICBitmapDecoder* bitmapdecoder = NULL;
	h_result = g_image_factory->CreateDecoderFromFilename(file_name, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &bitmapdecoder);
    if (S_OK != h_result)
    {
        return h_result;
    }

    IWICBitmapFrameDecode* pframe = NULL;
	h_result = bitmapdecoder->GetFrame(0, &pframe);
	if (S_OK != h_result)
    {
		return h_result;
    }

    IWICFormatConverter* fmtcovter = NULL;
	h_result = g_image_factory->CreateFormatConverter(&fmtcovter);
	if (S_OK != h_result)
	{
		return h_result;
    }
	h_result = fmtcovter->Initialize(pframe, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);
	if (S_OK != h_result)
	{
		return h_result;
    }

	ID2D1Bitmap* bitmap = NULL;
    h_result = g_render_target->CreateBitmapFromWicBitmap(fmtcovter, NULL, &bitmap);
	if (S_OK != h_result)
	{
		return h_result;
    }
    g_image_map.emplace(file_name, bitmap);

    fmtcovter->Release();
    pframe->Release();
    bitmapdecoder->Release();

    return 0;
}

ID2D1Bitmap* GetID2D1Bitmap(LPCWSTR file_name)
{
    auto it = g_image_map.find(file_name);
    if (it == g_image_map.end())
    {
        return nullptr;
    }
    return it->second;
}

void DestroyD2D1()
{
    for (auto& pair : g_image_map)
    {
        pair.second->Release();
    }
    g_image_factory->Release();

    g_linear_gradient_brush->Release();
    g_radial_gradient_brush->Release();
    g_gradient_stop_collection->Release();
    g_text_format->Release();
    g_write_factory->Release();
    g_brush->Release();
    g_render_target->Release();
    g_factory->Release();
}

void onPaint(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    if (!g_render_target)
        return;

    g_render_target->BeginDraw();

    // Clear Background
    g_render_target->Clear(D2D1::ColorF(0.63f, 0.84f, 0.00f));

    // Draw Ellipse  
    D2D1_SIZE_F size = g_render_target->GetSize();
    D2D1_RECT_F r = { 0, 0, size.width, size.height };
    g_render_target->FillRectangle(&r, g_linear_gradient_brush);

    // Draw Image
    {
        ID2D1Bitmap* bitmap = GetID2D1Bitmap(L"D:/ctodolist/WindowsProject1/WindowsProject1/gdi/resource/image/background/ndmz.bmp");
        if (bitmap)
        {
            double x = 0.0;
            double y = 0.0;
            double w = 1.0;
            double h = 1.0;
			D2D1_RECT_F imgr = { size.width * x, size.height * y, size.width * w, size.height * h };
			g_render_target->DrawBitmap(bitmap, imgr);
        }
    }

    {
        ID2D1Bitmap* bitmap = GetID2D1Bitmap(TEXT("D:/ctodolist/WindowsProject1/WindowsProject1/gdi/resource/image/picture/jiantou0.png"));
        if (bitmap)
        {
            double x = 0.1;
            double y = 0.1;
            double w = 0.15;
            double h = 0.15;
			D2D1_RECT_F imgr = { size.width * x, size.height * y, size.width * w, size.height * h };
			g_render_target->DrawBitmap(bitmap, imgr);
        }
    }


    // Draw Text 
    {
		const wchar_t * text = L"Direct2D Draw Image";
		double x = 0.2;
		double y = 0.2;
		double w = 0.55;
		double h = 0.55;
		D2D1_RECT_F textr = { size.width * x, size.height * y, size.width * w, size.height * h };
		g_render_target->DrawText(text, wcslen(text),
			g_text_format,
            textr,
			g_brush);
    }

    g_render_target->EndDraw();
}

void OnSize(LPARAM& lparam)
{
    if (nullptr == g_render_target)
    {
        return;
    }
	UINT32 w = LOWORD(lparam);
	UINT32 h = HIWORD(lparam);
    bool is_change = false;
    if (w < 1024)
    {
        w = 1024;
        is_change = true;
    }
    if (h < 768)
    {
        h = 768;
        is_change = true;
    }

    if (is_change)
    {
        lparam = w + (h << 16);
    }
	g_render_target->Resize(D2D1::SizeU(LOWORD(lparam), HIWORD(lparam)));
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        onPaint(hWnd, wParam, lParam);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_CREATE:
    {
        InitD2D1(hWnd);
    }
    break;
    case WM_DESTROY:
    {
        DestroyD2D1();
        PostQuitMessage(0);
    }
    break;
    case WM_MOVE:
    {
        //InvalidateRect(hWnd, NULL, false);
    }
    break;
    case WM_SIZE:
    {
        return 1;
    }
    break;
    case WM_SIZING:
    {
        return 1;
        //InvalidateRect(hWnd, NULL, false);
    }
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
