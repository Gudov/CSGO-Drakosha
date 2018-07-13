#include <Windows.h>
#include <dwmapi.h>
#include "window.h"

const MARGINS Margin = { 0, 0, 1920, 1080 }; //WTF

HWND hWnd;
HWND tWnd;

int WinTWidth;
int WinTHeight;

HWND getSelfHWND()
{
	return hWnd;
}

HWND getTargHWND()
{
	return tWnd;
}

int getWinTH()
{
	return WinTHeight;
}

int getWinTW()
{
	return WinTWidth;
}

char tWindowName[256] = "Counter-Strike: Global Offensive";

MSG Message;

RenderFoo renderFoo;

void setWindowRenderFoo( RenderFoo foo )
{
	renderFoo = foo;
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_PAINT:
		if (renderFoo != NULL)
		{
			renderFoo();
		}
		break;

	case WM_CREATE:
		DwmExtendFrameIntoClientArea(hWnd, &Margin);
		break;

	case WM_DESTROY:
		PostQuitMessage(1);
		return 0;

	case WM_CLOSE:
		exit(0);
		return 0;

	default:
		return DefWindowProc(hWnd, Message, wParam, lParam);
		break;
	}
	return 0;
}

void registerClassWin( HINSTANCE hInstance )
{
	WNDCLASSEX wClass;
	wClass.cbClsExtra = NULL;
	wClass.cbSize = sizeof(WNDCLASSEX);
	wClass.cbWndExtra = NULL;
	wClass.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	wClass.hCursor = LoadCursor(0, IDC_ARROW);
	wClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	wClass.hIconSm = LoadIcon(0, IDI_APPLICATION);
	wClass.hInstance = hInstance;
	wClass.lpfnWndProc = WinProc;
	wClass.lpszClassName = "Drakosha";
	wClass.lpszMenuName = "Drakosha";
	wClass.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&wClass))
		exit(1);
}

void SetWindowToTarget()
{
	while (true)
	{
		tWnd = FindWindow(0, tWindowName);
		if (tWnd)
		{
			RECT tSize;
			GetWindowRect(tWnd, &tSize);
			WinTWidth = tSize.right - tSize.left;
			WinTHeight = tSize.bottom - tSize.top;
			DWORD dwStyle = GetWindowLong(tWnd, GWL_STYLE);
			if (dwStyle & WS_BORDER)
			{
				tSize.top += 23;
				WinTHeight -= 23;
			}
			MoveWindow(hWnd, tSize.left, tSize.top, WinTWidth, WinTHeight, true);
		}
		else
		{
			exit(0);
		}
		Sleep(100);
	}
}

void createWindow()
{
	tWnd = FindWindow(0, tWindowName);
	if (tWnd)
	{
		RECT tSize;
		GetWindowRect(tWnd, &tSize);
		WinTWidth = tSize.right - tSize.left;
		WinTHeight = tSize.bottom - tSize.top;
		hWnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED, "Drakosha", "Drakosha", WS_POPUP, 1, 1, WinTWidth, WinTHeight, 0, 0, 0, 0);
		SetLayeredWindowAttributes(hWnd, 0, 1.0f, LWA_ALPHA);
		SetLayeredWindowAttributes(hWnd, 0, RGB(0, 0, 0), LWA_COLORKEY);
		ShowWindow(hWnd, SW_SHOW);
	}
}

void initWindow( HINSTANCE hInstance )
{
	renderFoo = NULL;
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SetWindowToTarget, 0, 0, 0);
	registerClassWin(hInstance);
	createWindow();
}

void processMessages()
{
	for (;;)
	{
		if (PeekMessage(&Message, hWnd, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&Message);
			TranslateMessage(&Message);
		}
		Sleep(1);
	}
}
