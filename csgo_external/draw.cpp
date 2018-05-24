#include "draw.h"
#include "diretrix.h"
#include "memory.h"
#include "offsets.h"

#include "classes.h"

#include <d3d9.h>
#include <d3dx9.h>

extern ID3DXLine* p_Line;		// WTF 
extern ID3DXFont* pFontSmall;	// если вставить в "diretrix.h"
extern ID3DXFont* pFont;		// все упадет
extern RECT winSize;

extern CPlayer* pEntity[32];
extern CLocalPlayer* pLocal;

extern CBoneMatrix cBoneMatrix;

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

void DrawBox(float x, float y, float width, float height, float px, int r, int g, int b, int a)
{
	D3DXVECTOR2 points[5];
	points[0] = D3DXVECTOR2(x, y);
	points[1] = D3DXVECTOR2(x + width, y);
	points[2] = D3DXVECTOR2(x + width, y + height);
	points[3] = D3DXVECTOR2(x, y + height);
	points[4] = D3DXVECTOR2(x, y);
	p_Line->SetWidth(1);
	p_Line->Draw(points, 5, D3DCOLOR_RGBA(r, g, b, a));
}

int DrawString(char* String, int x, int y, int r, int g, int b, ID3DXFont* ifont)
{
	RECT ShadowPos;
	ShadowPos.left = x + 1;
	ShadowPos.top = y + 1;
	RECT FontPos;
	FontPos.left = x;
	FontPos.top = y;
	//ifont->DrawTextA(0, String, strlen(String), &ShadowPos, DT_NOCLIP, D3DCOLOR_ARGB(255, r / 3, g / 3, b / 3));
	ifont->DrawTextA(0, String, strlen(String), &FontPos, DT_NOCLIP, D3DCOLOR_ARGB(255, r, g, b));
	return 0;
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

void DrawBone(int bone1, int bone2, DWORD BoneBase)
{
	float Bone1[3];
	float W2S_Bone1[3];
	cBoneMatrix.GetBonePos(BoneBase, bone2, Bone1);

	if (WorldToScreen(Bone1, W2S_Bone1))
	{
		float x;
		float y;
		x = (winSize.right / 2) - W2S_Bone1[0];
		y = (winSize.bottom / 2) - W2S_Bone1[1];

		DrawBox((winSize.right / 2) - x, (winSize.bottom / 2) - y, 4, 4, 1, 255, 255, 255, 255);
	}
}

void drawCrosshair()
{
	//// MARKED AS TECHONO HERESY <start>////
	DrawLine((winSize.right / 2), (winSize.bottom / 2), (winSize.right / 2) + 1, (winSize.bottom / 2) + 1, 255, 50, 50, 230, 2);
	DrawLine((winSize.right / 2) + 13, (winSize.bottom / 2), (winSize.right / 2) + 13 + 45, (winSize.bottom / 2), 255, 50, 50, 100, 2);
	DrawLine((winSize.right / 2) - 13, (winSize.bottom / 2), (winSize.right / 2) - 13 - 45, (winSize.bottom / 2), 255, 50, 50, 100, 2);
	//// MARKED AS TECHONO HERESY <end>////
}

void drawWH()
{
	//pLocal = new CLocalPlayer();
	pLocal->ReadData();

	for (int i = 0; i < 20; i++)
	{
		pEntity[i]->ReadData(i);

		if (	!pEntity[i]->BoneBase
			||	!pEntity[i]->isAlive
			)
		{
			continue;
		}

		float W2S[3];
		float W2S_Head[3];

		int radarx = pLocal->Pos[0] - pEntity[i]->Pos[0];
		radarx = radarx / -14;
		int radary = pLocal->Pos[1] - pEntity[i]->Pos[1];
		radary = radary / 14;

		if (pEntity[i]->Team == pLocal->Team)
		{
			DrawBox(145 + radarx, 50 + 145 + radary, 6, 6, 1, 0, 0, 255, 255);
		}
		else//Check if the player is not in our team
		{
			DrawBox(145 + radarx, 50 + 145 + radary, 6, 6, 1, 255, 0, 0, 255);
		}

		if (WorldToScreen(pEntity[i]->Pos, W2S) && WorldToScreen(pEntity[i]->HeadPos, W2S_Head))
		{
			int height = abs(W2S[1] - W2S_Head[1]);//abs = absolute http://www.cplusplus.com/reference/cstdlib/abs/
			int width = height / 2; //You can change this value to anything you would liek

			if (pLocal->Player != pEntity[i]->Player)
			{
				char heal[10];

				itoa(pEntity[i]->Health, heal, 10);

				//Check if the player is in our team
				if (pEntity[i]->Team == pLocal->Team)
				{
					DrawBox(W2S[0] - (width / 2), W2S[1] - height, width, height, 1, 0, 0, 255, 255);
				}
				else//Check if the player is not in our team
				{
					DrawBox(W2S[0] - (width / 2), W2S[1] - height, width, height, 1, 255, 0, 0, 255);
				}

				DrawString(heal, W2S[0] - (width / 2), W2S[1] - height, 255, 255, 255, pFont);

				DrawBone(7, 8, pEntity[i]->BoneBase);
			}
		}
	}
}

struct npos
{
	float x, y, z;
};

void drawCompass()
{
	//int coff = 3.14159265 / 180.0;
	//coff *= 20;
	char st[10];
	for ( int i = 0; i < 12; i++ )
	{
		npos pos = *((npos*)pLocal->Pos);
		pos.x += cos(i * 3.14159265 / 180.0 * 30) * 100;
		pos.y += sin(i * 3.14159265 / 180.0 * 30) * 100;
		pos.z += 40;

		npos inScreen;
		if (WorldToScreen((float*)&pos, (float*)&inScreen))
		{
			itoa(i*30, st, 10);
			DrawString(st, inScreen.x, inScreen.y, 255, 255, 255, pFont);
		}
	}
}