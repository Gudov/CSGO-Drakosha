#pragma once
#include <Windows.h>
#include <dwmapi.h>

typedef void (*RenderFoo)(void); // void � ���������� �������� �������

void setWindowRenderFoo( RenderFoo foo );
void initWindow( HINSTANCE hInstance );
void processMessages(void);		// void ������� ���, ��� ��� ����������
								// �������� ����� �����

HWND getSelfHWND();
HWND getTargHWND();

int getWinTH();
int getWinTW();