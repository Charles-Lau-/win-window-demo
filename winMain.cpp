#include "winMain.h"
#include "cstdio"

HINSTANCE gInstance = 0;


//get hwnd of a WPF
HWND GetHwnd(HWND pa, int x, int y, int width, int height)
{
	System::Windows::Interop::HwndSourceParameters^ sourceParams = gcnew System::Windows::Interop::HwndSourceParameters(
		"hi" // NAME
	);
	sourceParams->PositionX = x;
	sourceParams->PositionY = y;
	sourceParams->Height = height;
	sourceParams->Width = width;
	sourceParams->ParentWindow = System::IntPtr(pa);
	sourceParams->WindowStyle =  WS_VISIBLE | WS_CHILD; // style
	System::Windows::Interop::HwndSource^ source = gcnew System::Windows::Interop::HwndSource(*sourceParams);

	WpfControlLibrary2::UserControl1 ^myPage = gcnew WpfControlLibrary2::UserControl1();
	//Assign a reference to the WPF page and a set of UI properties to a set of static properties in a class
	//that is designed for that purpose.
	/*WPFPageHost::initBackBrush = myPage->Background;
	WPFPageHost::initFontFamily = myPage->DefaultFontFamily;
	WPFPageHost::initFontSize = myPage->DefaultFontSize;
	WPFPageHost::initFontStyle = myPage->DefaultFontStyle;
	WPFPageHost::initFontWeight = myPage->DefaultFontWeight;
	WPFPageHost::initForeBrush = myPage->DefaultForeBrush;
	myPage->OnButtonClicked += gcnew WPFPage::ButtonClickHandler(WPFButtonClicked);*/
	source->RootVisual = myPage;
	return (HWND)source->Handle.ToPointer();
}


//窗口回调
LRESULT CALLBACK  WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	char buf[256] = { 0 };
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		//GetClientRect(hWnd, &rect);
	    GetHwnd(hwnd, 0, 0, 375, 250);
		//DWORD error = GetLastError();
		//CreateDataDisplay(hWnd, 275, rect.right - 375, 375);
		//CreateRadioButtons(hWnd);;
		break;
	default:
		break;

	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}



//注册窗口类
BOOL RegisterWindow(LPSTR lpClassName, WNDPROC wndProc) {
	WNDCLASSEX  wce = { 0 };
	wce.cbSize = sizeof(wce);
	wce.cbClsExtra = 0;
	wce.cbWndExtra = 0;
	wce.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wce.hCursor = NULL;
	wce.hIcon = NULL;
	wce.hIconSm = NULL;
	wce.hInstance = NULL;
	wce.lpfnWndProc = wndProc;
	wce.lpszClassName = lpClassName;
	wce.lpszMenuName = NULL;
	wce.style = CS_HREDRAW | CS_VREDRAW;
	ATOM nAtom = RegisterClassEx(&wce);
	if (!nAtom)
	{
		MessageBox(NULL, "注册失败", "Infor", MB_OK);
		return FALSE;
	}
	else
		return TRUE;
}

//创建主窗口

HWND CreateMain(LPSTR lpClassName, LPSTR  name) {
	HWND hwnd = CreateWindowEx(0, lpClassName, name, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, NULL, NULL);
	return hwnd;
}


//展示和更新主窗口
void Display(HWND hwnd) {
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
}


//消息循环
void Message() {
	MSG msg = {0};
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

[System::STAThreadAttribute]
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPreInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {

	gInstance = hInstance;
	//注册窗口类
	BOOL ret = RegisterWindow("Button", WndProc);
	if (!ret) {
		MessageBox(NULL, "注册窗口失败", "Info", MB_OK);
		return 0;
	}
	//创建窗口类
	HWND hwnd = CreateMain("Button", "window");

	//展示和更新窗口
	Display(hwnd);
	Message();
	return 0;
}

