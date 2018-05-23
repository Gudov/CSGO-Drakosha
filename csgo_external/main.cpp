#include <Windows.h>
#include "window.h"
#include "diretrix.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hSecInstance, LPSTR nCmdLine, INT nCmdShow)
{
	initWindow(hInstance);
	DirectXInit(getSelfHWND());
	processMessages();
}