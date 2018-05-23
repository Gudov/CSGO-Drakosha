#pragma once

typedef void (*RenderFoo)(void); // void в параметрах выглядит логично, 

void setWindowRenderFoo( RenderFoo foo );
void initWindow( HINSTANCE hInstance );