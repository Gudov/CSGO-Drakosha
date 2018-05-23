#include "draw.h"
#include "diretrix.h"
#include "memory.h"
#include "offsets.h"

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

typedef struct
{
	float flMatrix[4][4];
}WorldToScreenMatrix_t;

extern RECT winSize;

bool WorldToScreen(float * from, float * to)
{
	WorldToScreenMatrix_t WorldToScreenMatrix;
	WorldToScreenMatrix = mem->ReadMem<WorldToScreenMatrix_t>(ClientDLL + ViewMatrix);
	float w = 0.0f;

	to[0] = WorldToScreenMatrix.flMatrix[0][0] * from[0] + WorldToScreenMatrix.flMatrix[0][1] * from[1] + WorldToScreenMatrix.flMatrix[0][2] * from[2] + WorldToScreenMatrix.flMatrix[0][3];
	to[1] = WorldToScreenMatrix.flMatrix[1][0] * from[0] + WorldToScreenMatrix.flMatrix[1][1] * from[1] + WorldToScreenMatrix.flMatrix[1][2] * from[2] + WorldToScreenMatrix.flMatrix[1][3];
	w = WorldToScreenMatrix.flMatrix[3][0] * from[0] + WorldToScreenMatrix.flMatrix[3][1] * from[1] + WorldToScreenMatrix.flMatrix[3][2] * from[2] + WorldToScreenMatrix.flMatrix[3][3];

	if (w < 0.01f)
		return false;

	float invw = 1.0f / w;
	to[0] *= invw;
	to[1] *= invw;

	int width = (int)(winSize.right - winSize.left);
	int height = (int)(winSize.bottom - winSize.top);

	float x = width / 2;
	float y = height / 2;

	x += 0.5 * to[0] * width + 0.5;
	y -= 0.5 * to[1] * height + 0.5;

	to[0] = x + winSize.left;
	to[1] = y + winSize.top;

	return true;
}

void drawCrosshair()
{
	//// MARKED AS TECHONO HERESY <start>////
	DrawLine((winSize.right / 2), (winSize.bottom / 2), (winSize.right / 2) + 1, (winSize.bottom / 2) + 1, 255, 50, 50, 230, 2);
	DrawLine((winSize.right / 2) + 13, (winSize.bottom / 2), (winSize.right / 2) + 13 + 45, (winSize.bottom / 2), 255, 50, 50, 100, 2);
	DrawLine((winSize.right / 2) - 13, (winSize.bottom / 2), (winSize.right / 2) - 13 - 45, (winSize.bottom / 2), 255, 50, 50, 100, 2);
	//// MARKED AS TECHONO HERESY <end>////
}