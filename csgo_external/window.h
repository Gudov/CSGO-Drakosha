#pragma once

typedef void (*RenderFoo)(void); // void � ���������� �������� �������, 

void setWindowRenderFoo( RenderFoo foo );
void initWindow( HINSTANCE hInstance );