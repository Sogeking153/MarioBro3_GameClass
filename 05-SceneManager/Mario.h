#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"
#include "TimeCustom.h"

#include "debug.h"
#include "Game.h"


#define EFFECT_GAP 50

#define POS_Y_HOLD	1320
#define POS_Y_END_MAP	8700
#define MARIO_WALKING_SPEED		0.3f
#define MARIO_RUNNING_SPEED		0.7f

#define MARIO_ACCEL_WALK_X	0.0003f
#define MARIO_ACCEL_RUN_X	0.0005f
#define MARIO_VX_JUMP	0.3f
#define MARIO_VY_FLY_LANDING	0.06f
#define MARIO_VY_FLY_HIGH	0.3f

#define MARIO_VY_GO_DOWN_PIPE	0.1f
#define MARIO_VY_GO_UP_PIPE	0.1f

#define MARIO_VX_AUTO 0.3f
#define MARIO_TIME_TO_GO_PIPE	1000
#define MARIO_Y_ABOVE	900
#define MARIO_Y_BELOW	1170

#define MARIO_POS_X_UNDER_GROUND	6350
#define MARIO_POS_Y_UNDER_GROUND	1500

#define MARIO_POS_X_IN_GROUND	6984
#define MARIO_POS_Y_IN_GROUND	1170

#define MARIO_TIME_KICK	200
#define MARIO_TIME_THROW	200
#define MARIO_TIME_SPIN	350
#define MARIO_TIME_FLY_LANDING	300
#define MARIO_TIME_FLY_HIGH	360
#define MARIO_TIME_TO_SWITCH_SCENE	1000
#define MARIO_TIME_TO_SKID 200

#define MARIO_TIME_TO_STRANSFORM	1500
#define MARIO_TIME_TO_APPEAR_TAIL	600

#define MARIO_GAP_HOLDING_X	40
#define MARIO_GAP_HOLDING_Y	10

#define MARIO_WIDTH_SPIN	90
#define MARIO_HEIGHT_SPIN	5

#define MARIO_GAP_BEING_JUMPED	2
#define MARIO_GAP_JUMP	1


#define MARIO_JUMP_SPEED_Y		0.90f
#define MARIO_JUMP_RUN_SPEED_Y	1.1f

#define MARIO_GRAVITY			0.002f

#define MARIO_JUMP_DEFLECT_SPEED  0.7f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_STAND_SHOOT		700
#define MARIO_STATE_SPIN			800
#define MARIO_STATE_FLY_LANDING		820
#define MARIO_STATE_FLY_HIGH		840
#define MARIO_STATE_KICK			900
#define MARIO_STATE_TRANSFORM		950

#define MARIO_STATE_APPEAR_TAIL		1000

#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 50002
#define ID_ANI_MARIO_IDLE_LEFT 50003

#define ID_ANI_MARIO_WALKING_RIGHT 50000
#define ID_ANI_MARIO_WALKING_LEFT 50001

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_DIE 999

#define ID_ANI_MARIO_BIG_FIRE_IDLE_RIGHT 1700
#define ID_ANI_MARIO_BIG_FIRE_SHOOT_BULLET_RIGHT 1720
#define ID_ANI_MARIO_BIG_FIRE_FLY_SHOOT_BULLET_RIGHT 1750
//tail spin
#define ID_ANI_MARIO_BIG_TAIL_STAND_RIGHT 1900
#define ID_ANI_MARIO_BIG_TAIL_SPIN_RIGHT 1901
#define ID_ANI_MARIO_BIG_TAIL_JUMP_RIGHT 1915
#define ID_ANI_MARIO_BIG_TAIL_FLY_DOWN_RIGHT 1920

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

#pragma endregion

#define GROUND_Y 160.0f

#define	MARIO_LEVEL_SMALL		1
#define	MARIO_LEVEL_BIG			2
#define	MARIO_LEVEL_BIG_TAIL	3

#define MARIO_BIG_BBOX_WIDTH  14*3
#define MARIO_BIG_BBOX_HEIGHT 28*3
#define MARIO_BIG_SITTING_BBOX_WIDTH  14*3
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16*3


#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13*3
#define MARIO_SMALL_BBOX_HEIGHT 12*3

#define MARIO_TAIL_BBOX_WIDTH  21*3
#define MARIO_TAIL_BBOX_HEIGHT 28*3


#define MARIO_UNTOUCHABLE_TIME 2500

#pragma region ANIMATION_ID_NEW
#define MARIO_ANI_BIG_IDLE_RIGHT			400
#define MARIO_ANI_SMALL_IDLE_RIGHT			401
#define MARIO_ANI_TAIL_IDLE_RIGHT			402 


#define MARIO_ANI_BIG_WALKING_RIGHT			404
#define	MARIO_ANI_SMALL_WALKING_RIGHT		405
#define MARIO_ANI_TAIL_WALKING_RIGHT		406


#define MARIO_ANI_DIE				408

#define MARIO_ANI_BIG_JUMP_UP_RIGHT				409
#define MARIO_ANI_SMALL_JUMP_RIGHT				410
#define MARIO_ANI_TAIL_JUMP_UP_RIGHT			411

#define MARIO_ANI_BIG_SITDOWN_RIGT			413
#define MARIO_ANI_TAIL_SITDOWN_RIGHT		414


#define MARIO_ANI_SMALL_JUMP_DOWN_RIGHT				416
#define MARIO_ANI_BIG_JUMP_DOWN_RIGHT				417
#define MARIO_ANI_TAIL_JUMP_DOWN_RIGHT				418


#define	MARIO_ANI_SMALL_RUN_RIGHT			        420
#define	MARIO_ANI_BIG_RUN							421
#define	MARIO_ANI_TAIL_RUN_RIGHT					422

#define  MARIO_ANI_TAIL_SPIN_TAIL_RIGHT			424


#define  MARIO_ANI_BIG_SKID				425
#define  MARIO_ANI_TAIL_SKID_LEFT		426
#define  MARIO_ANI_SMALL_SKID_LEFT		427


#define MARIO_ANI_SMALL_FLYING								430
#define MARIO_ANI_BIG_FLYING								431
#define MARIO_ANI_TAIL_FLY_HIGH									432


#define MARIO_ANI_SMALL_BRING_KOOMPASHELL_RIGHT	 		435
#define MARIO_ANI_BRING_KOOMPASHELL_RIGHT				436
#define MARIO_ANI_TAIL_BRING_KOOMPASHELL_RIGHT			437

#define	MARIO_ANI_SMALL_ROUSE_KOOMPASHELL_RIGHT		439
#define MARIO_ANI_ROUSE_KOOMPASHELL_RIGHT			440
#define MARIO_ANI_TAIL_ROUSE_KOOMPASHELL_RIGHT		441

#define MARIO_ANI_SMALL_STAND_HOLD  443
#define MARIO_ANI_BIG_STAND_HOLD    444
#define MARIO_ANI_TAIL_STAND_HOLD   445

#define MARIO_ANI_SMALL_GO_DOWN		447
#define MARIO_ANI_BIG_GO_DOWN		448
#define MARIO_ANI_TAIL_GO_DOWN		449

#define MARIO_ANI_ORANGE_FLY_DOWN	451
#define MARIO_ANI_SMALL_BRING_JUMP_RIGHT		452
#define MARIO_ANI_BIG_BRING_JUMP_RIGHT			453
#define MARIO_ANI_TAIL_BRING_JUMP_RIGHT			454
#define MARIO_ANI_TRANSFORM		456

#define MARIO_ANI_APEAR_TAIL		457

#define MARIO_ANI_SMALL_IN_MAP			763
#define MARIO_ANI_BIG_IN_MAP			764
#define MARIO_ANI_TAIL_IN_MAP			765

#define TO_BECOME_LEFT 100
#pragma endregion

#define MARIO_BIG_TAIL_BBOX_WIDTH  21*3
#define MARIO_BIG_TAIL_BBOX_HEIGHT 28*3

#define MARIO_BIG_TAIL_SITDOWN_BBOX_WIDTH  22*3
#define MARIO_BIG_TAIL_SITDOWN_BBOX_HEIGHT 16*3

#define MARIO_BIG_TAIL_SPIN_BBOX_WIDTH  48*3
#define MARIO_BIG_TAIL_BBOX_HEIGHT 28*3

class CMario : public CGameObject
{
public:
	bool is_moving_in_world_map;
	ULONGLONG time_to_appear_tail = 0;
	ULONGLONG time_to_transform = 0;

	int hit_brick_number = 0;
	int score = 0;

	bool is_on_the_ground = false;
	TimeCustom* untouchtable_timer = new TimeCustom(2500);
	//ULONGLONG time_to_switch_scene = 0;
	bool is_jumped = false;
	bool is_up_press = false;
	bool is_holding = false;
	bool is_skid = false;
	CGameObject* holding_something = NULL;
	bool IsOnTheFlatForm() { return isOnPlatform; }
	ULONGLONG fly_high_start = 0;
	ULONGLONG fly_start = 0;
	ULONGLONG spin_start = 0;
	ULONGLONG skid_start = 0;
	ULONGLONG change_ani = GetTickCount64();
	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int level; 
	int untouchable; 
	ULONGLONG untouchable_start;
	BOOLEAN isOnPlatform;
	int coin; 

	void OnCollisionWithPipe(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithPButton(LPCOLLISIONEVENT e);
	void OnCollisionWithBrickBlink(LPCOLLISIONEVENT e);
	void OnCollisionWithPiranaPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithVenusFireTrap(LPCOLLISIONEVENT e);

	void OnCollisionWithParaGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithBrickCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithSuperLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithVirtualBox(LPCOLLISIONEVENT e);
	void CollideWithItems(vector<LPGAMEOBJECT>* itemsMarioCanEat);

	int GetAniIdSmall();
	int GetAniIdBig();
	int GetAniIdTail();

//public:
	CMario(float x, float y, bool is_in_world_map) : CGameObject(x, y)
	{
		is_moving_in_world_map = is_in_world_map;
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 

		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
		coin = 0;
	}

	ULONGLONG time_to_go_down = 0;
	bool is_set_position = false;
	bool go_down = false;
	bool is_hit_bonus = false;
	bool is_auto = false;
	int card_end_scene = 0;
	void CollideWithEnemy();
	ULONGLONG kick_start = 0;
	bool is_kick = false;
	float vy_store = 0;
	bool jump_down_to_up = false;
	int GetLevel() { return level; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithFlatForm(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};