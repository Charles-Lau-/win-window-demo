#include "winMain.h"

HINSTANCE gInstance = 0;

//���ڻص�
LRESULT CALLBACK  WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;

	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}



//ע�ᴰ����
BOOL RegisterWindow(LPSTR lpClassName, WNDPROC wndProc) {
	WNDCLASSEX  wce = { 0 };
	wce.cbSize = sizeof(wce);
	wce.cbClsExtra = 0;
	wce.cbWndExtra = 0;
	wce.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wce.hCursor = NULL;
	wce.hIcon = NULL;
	wce.hIconSm = NULL;
	wce.hInstance = gInstance;
	wce.lpfnWndProc = wndProc;
	wce.lpszClassName = "Main";
	wce.lpszMenuName = NULL;
	wce.style = CS_HREDRAW | CS_VREDRAW;
	ATOM nAtom = RegisterClassEx(&wce);
	if (!nAtom)
	{
		MessageBox(NULL, "ע��ʧ��", "Infor", MB_OK);
		return FALSE;
	}
	else
		return TRUE;
}

//����������
HWND CreateMain(LPSTR lpClassName, LPSTR  name) {
	HWND hwnd = CreateWindowEx(0, "Main", "Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, gInstance, NULL);
	return hwnd;
}


//չʾ�͸���������
void Display(HWND hwnd) {
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
}


//��Ϣѭ��
void Message() {
	MSG msg = {0};
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPreInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {

	gInstance = hInstance;
	//ע�ᴰ����
	BOOL ret = RegisterWindow("Main", WndProc);
	if (!ret) {
		MessageBox(NULL, "ע�ᴰ��ʧ��", "Info", MB_OK);
		return 0;
	}
	//����������
	HWND hwnd = CreateMain("Main", "window");
	//չʾ�͸��´���
	Display(hwnd);
	Message();
	return 0;
}




