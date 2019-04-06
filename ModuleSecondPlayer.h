#ifndef __ModuleSecondPlayer_H__
#define __ModuleSecondPlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModuleSecondPlayer : public Module
{
public:
	ModuleSecondPlayer();
	~ModuleSecondPlayer();

	bool Start();
	update_status Update();

public:

	SDL_Texture* graphics2 = nullptr;
	Animation idle2;
	Animation forward2;
	Animation backward2;
	Animation lp2, lk2;
	Animation neutralJump2;
	iPoint position;
	Animation hdk;
	bool atacar = false;
	bool jump = false;
	int framesAtaque = 0;
	int framesJump = 0;
	int mov; //lp, mp, hp, lk, mk, hk
};

#endif