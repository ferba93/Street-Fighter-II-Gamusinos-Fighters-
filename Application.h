#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 14

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleParticles;
class ModuleRender;
class ModuleSceneKen;
class ModuleSceneSagat;
class ModulePlayer;
class ModuleFadeToBlack;
class ModuleWelcomePage;
class ModuleEndBattle;
class ModuleAudio;
class ModuleSecondPlayer;
class ModuleCollision;
class Module;

class Application
{
public:
	Uint32 frames = 0;
	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleParticles* particles;
	ModuleAudio* audio;
	ModuleSceneKen* scene_ken;
	ModuleSceneSagat* scene_Sagat;
	ModulePlayer* player;
	ModuleFadeToBlack* fade;
	ModuleWelcomePage* welcomePage;
	ModuleEndBattle* endBattle;
	ModuleSecondPlayer* player2;
	ModuleCollision* collisions;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__