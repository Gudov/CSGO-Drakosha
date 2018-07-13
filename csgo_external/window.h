#pragma once
#include <Windows.h>
#include <dwmapi.h>

typedef void (*RenderFoo)(void); // void в параметрах выгл€дит логично

void setWindowRenderFoo( RenderFoo foo );
void initWindow( HINSTANCE hInstance );
void processMessages(void);		// void говорит нам, вот это объ€вление
								// попробую такой стиль

HWND getSelfHWND();
HWND getTargHWND();

int getWinTH();
int getWinTW();