#pragma once

#ifndef HDIRECTX_H
#define HDIRECTX_H
#include <Windows.h>

int DirectXInit(HWND hWnd);
void Render();

//extern ID3DXLine* p_Line;			// если это раскоментить
//extern ID3DXFont* pFontSmall;		// тут будет ќ„≈Ќ№ много ошибок
//extern ID3DXFont* pFont;			// и € не знаю в чем дело
//extern RECT winSize;				// watch draw.cpp

#endif