#include "draw.h"
#include "diretrix.h"

#include <d3d9.h>
#include <d3dx9.h>

extern ID3DXLine* p_Line;		// WTF 
extern ID3DXFont* pFontSmall;	// если вставить в "diretrix.h"
extern ID3DXFont* pFont;		// все упадет
extern RECT winSize;

void DrawLine(float x, float y, float xx, float yy, int r, int g, int b, int a, int f)
{
	D3DXVECTOR2 dLine[2];

	p_Line->SetWidth(f);

	dLine[0].x = x;
	dLine[0].y = y;

	dLine[1].x = xx;
	dLine[1].y = yy;

	p_Line->Draw(dLine, 2, D3DCOLOR_ARGB(a, r, g, b));
}

void drawCrosshair()
{
	DrawLine((winSize.right / 2), (winSize.bottom / 2), (winSize.right / 2) + 1, (winSize.bottom / 2) + 1, 255, 50, 50, 230, 2);
	DrawLine((winSize.right / 2) + 13, (winSize.bottom / 2), (winSize.right / 2) + 13 + 45, (winSize.bottom / 2), 255, 50, 50, 100, 2);
	DrawLine((winSize.right / 2) - 13, (winSize.bottom / 2), (winSize.right / 2) - 13 - 45, (winSize.bottom / 2), 255, 50, 50, 100, 2);
}