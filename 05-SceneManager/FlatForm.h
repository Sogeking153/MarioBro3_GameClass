#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define DO_DOI 24

class FlatForm : public CGameObject {
public:
	bool is_go_through = false;
	float dodoi = DO_DOI;
	float width;
	float height;
	FlatForm(float x, float y, float w, float h, bool is_go_through) : CGameObject(x, y) { width = w; height = h; this->is_go_through = is_go_through;
	}
	void Render();
	void Update(DWORD dt) {};
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	//virtual int IsCollidable() { return 1; };
	//virtual int IsBlocking() { return 1; }
	//int IsBlocking() { return 0; }
};

