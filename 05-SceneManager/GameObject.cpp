#include <d3dx9.h>
#include <algorithm>


#include "debug.h"
#include "Textures.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"

CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;	
	state = -1;
	isDeleted = false;
}

void CGameObject::DeleteWhenOutOfCam()
{
	if (x< CGame::GetInstance()->GetCamX() || x> CGame::GetInstance()->GetCamX() + SCREEN_WIDTH)
	{
		this->Delete();
		//DebugOut(L"[ERROR-----Delete---------] DINPUT::GetDeviceData failed. Error: %f\n", vx);
	}

	if (y< CGame::GetInstance()->GetCamY() || y> CGame::GetInstance()->GetCamY() + SCREEN_HEIGHT)
	{
		this->Delete();
		//DebugOut(L"[ERROR------Delete--------] DINPUT::GetDeviceData failed. Error: %f\n", vx);
	}
}

void CGameObject::CheckWetherBeingAttacked(CGameObject* obj_attack, int become_state)
{
	float ml, mt, mr, mb;
	float il, it, ir, ib;

	this->GetBoundingBox(il, it, ir, ib);
	obj_attack->GetBoundingBox(ml, mt, mr, mb);

	if (this->CheckOverLap(il, it, ir, ib, ml, mt, mr, mb))
	{

		//DebugOut(L"[INFO] checkoverlap func being attack \n");
		
		//DebugOut(L"[INFO] vy value: %f\n", vy);

		if (this->GetX() < obj_attack->GetX())
		{
			//DebugOut(L"[INFO] hello? %d\n", koompas->state);
			//koompas->is_minus_vx = true;//vx=is_minus_vx?-0.1:0.1;
			this->DirectionWhenBeingAttack = -1;
		}
		else
		{
			this->DirectionWhenBeingAttack = 1;
		}
		SetState(become_state);
	}
}

void CGameObject::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l,t,r,b; 

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy; 
	CGame::GetInstance()->GetCamPos(cx, cy);

	CGame::GetInstance()->Draw(x - cx, y - cy, bbox, &rect, BBOX_ALPHA);
}

CGameObject::~CGameObject()
{

}