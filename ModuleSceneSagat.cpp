#include "Globals.h"
#include "Application.h"
#include "ModuleSceneSagat.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleSecondPlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleSceneSagat::ModuleSceneSagat()
{
	// ground
	ground.x = 0;
	ground.y = 973;
	ground.w = 1024;
	ground.h = 49;

	// rocks
	rocks = {983, 159, 25, 25};

	// foreground
	foreground = { 0, 655, 692, 195 };

	// Background
	background = {0, 432, 633, 195};

	// flag animation
	palmtree.PushBack({699, 212, 325, 317}, 0.02f);
	palmtree.PushBack({696, 550, 328, 317}, 0.02f);
}

ModuleSceneSagat::~ModuleSceneSagat()
{}

// Load assets
bool ModuleSceneSagat::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("assets/images/sprites/stages/KenSagatStage.png");
	music = App->audio->LoadSong("assets/music/thailand_s_1.ogg");

	App->player->Enable();
	App->player2->Enable();
	App->particles->Enable();
	App->collisions->Enable();
	App->audio->PlaySongDelay(music, -1, 2000);

	return ret;
}

// Unload assets
bool ModuleSceneSagat::CleanUp()
{
	LOG("Unloading Sagat stage");

	App->player->Disable();
	App->player2->Disable();
	App->particles->Disable();
	App->collisions->Disable();

	App->textures->Unload(graphics);
	graphics = nullptr;
	App->audio->UnloadSong(music);
	music = nullptr;

	return true;
}

// Update: draw background
update_status ModuleSceneSagat::Update()
{
	// Draw everything --------------------------------------	
	App->render->Blit(graphics, 0, 0, &background, false, 0.5f);
	App->render->Blit(graphics, 0, -19, &foreground, false, 0.75f); // back of the room
	
	App->render->Blit(graphics, -243, 175, &ground, false, 0.75f);
	App->render->Blit(graphics, 174, 199, &rocks, false, 0.75f);
	App->render->Blit(graphics, 489, 168, &rocks, false, 0.75f);
	App->render->Blit(graphics, 364, 0, &(palmtree.GetCurrentFrame()), 0.75); // palmtree animation

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {
		Mix_FadeOutMusic(2000);
		App->fade->FadeToBlack(this, (Module*)App->endBattle, 5);
	}

	return UPDATE_CONTINUE;
}