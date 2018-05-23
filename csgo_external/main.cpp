#include <Windows.h>
#include "window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hSecInstance, LPSTR nCmdLine, INT nCmdShow)
{
	initWindow(hInstance);
	processMessages();
}