#include <Windows.h>
#include "window.h"
#include "diretrix.h"
#include "memory.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hSecInstance, LPSTR nCmdLine, INT nCmdShow)
{
	initWindow(hInstance);
	DirectXInit(getSelfHWND());
	initMemory();
	setWindowRenderFoo(Render);
	processMessages();
}