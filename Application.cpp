#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleSceneKen.h"
#include "ModuleSceneSagat.h"
#include "ModulePlayer1.h"
#include "ModuleFadeToBlack.h"
#include "ModuleWelcomePage.h"
#include "ModuleEndBattle.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleFonts.h"
#include "ModuleUI.h"
#include "ModuleFight.h"
#include "ModuleVsScreen.h"
#include "ModuleChSelection.h"
#include "ModuleSlowdown.h"
#include "SDL\include\SDL.h"

Application::Application()
{
	modules[0] = window = new ModuleWindow();
	modules[1] = input = new ModuleInput();
	modules[2] = textures = new ModuleTextures();
	modules[3] = fonts = new ModuleFonts();
	modules[4] = audio = new ModuleAudio();
	modules[5] = fight = new ModuleFight();
	modules[6] = scene_Sagat = new ModuleSceneSagat();
	modules[7] = scene_ken = new ModuleSceneKen();
	modules[8] = player1 = new ModulePlayer1();
	modules[9] = player2 = new ModulePlayer2();
	modules[10] = particles = new ModuleParticles();
	modules[11] = welcomePage = new ModuleWelcomePage();
	modules[12] = endBattle = new ModuleEndBattle();
	modules[13] = collisions = new ModuleCollision();
	modules[14] = UI = new ModuleUI();
	modules[15] = vsScreen = new ModuleVsScreen();
	modules[16] = chSelectionScreen = new ModuleChSelection();
	modules[17] = fade = new ModuleFadeToBlack();
	modules[18] = render = new ModuleRender();
	modules[19] = slowdown = new ModuleSlowdown();
}

Application::~Application()
{
	for (int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	player1->Disable();
	player2->Disable();
	particles->Disable();
	collisions->Disable();
	fight->Disable();
	scene_Sagat->Disable();
	scene_ken->Disable();
	endBattle->Disable();
	UI->Disable();
	vsScreen->Disable();
	chSelectionScreen->Disable();

	for (int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for (int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	App->frames++;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}

Uint32 Application::GetFrame() {
	return (SDL_GetTicks() / 100) % 6;
}