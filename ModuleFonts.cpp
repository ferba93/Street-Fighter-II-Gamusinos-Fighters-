#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFonts.h"
#include "SDL\include\SDL.h"

#include<string.h>

// Constructor
ModuleFonts::ModuleFonts() : Module()
{}

// Destructor
ModuleFonts::~ModuleFonts()
{}

// Load new texture from file path
int ModuleFonts::Load(const char* texture_path, const char* characters, uint rows)
{
	tiempo[0] = '9';
	tiempo[1] = '9';
	int id = -1;

	if(texture_path == nullptr || characters == nullptr || rows == 0)
	{
		LOG("Could not load font");
		return id;
	}

	SDL_Texture* tex = App->textures->Load(texture_path);

	if(tex == nullptr || strlen(characters) >= MAX_FONT_CHARS)
	{
		LOG("Could not load font at %s with characters '%s'", texture_path, characters);
		return id;
	}

	id = 0;
	for(; id < MAX_FONTS; ++id)
		if(fonts[id].graphic == nullptr)
			break;

	if(id == MAX_FONTS)
	{
		LOG("Cannot load font %s. Array is full (max %d).", texture_path, MAX_FONTS);
		return id;
	}

	App->textures->GetSize(tex, width, height);

	fonts[id].graphic = tex; // graphic: pointer to the texture
	fonts[id].rows = rows; // rows: rows of characters in the texture
	fonts[id].len = 0; // len: length of the table

	strcpy_s(fonts[id].table, characters);// table: array of chars to have the list of characters
	fonts[id].row_chars = strlen(characters);// row_chars: amount of chars per row of the texture
	fonts[id].char_w = width / fonts[id].row_chars;// char_w: width of each character
	fonts[id].char_h = height;// char_h: height of each character
	

	LOG("Successfully loaded BMP font from %s", texture_path);

	return id;
}

void ModuleFonts::UnLoad(int font_id)
{
	if(font_id >= 0 && font_id < MAX_FONTS && fonts[font_id].graphic != nullptr)
	{
		App->textures->Unload(fonts[font_id].graphic);
		fonts[font_id].graphic = nullptr;
		LOG("Successfully Unloaded BMP font_id %d", font_id);
	}
}

// Render text using a bitmap font
void ModuleFonts::BlitText(int x, int y, int font_id, const char* text) const
{
	if(text == nullptr || font_id < 0 || font_id >= MAX_FONTS || fonts[font_id].graphic == nullptr)
	{
		LOG("Unable to render text with bmp font id %d", font_id);
		return;
	}

	const Font* font = &fonts[font_id];		// font_id equival al numero de files que ocupa, no el que t�, i serveix per iterar per saber quina fila �s
	SDL_Rect rect;
	uint len = strlen(text);

	rect.w = font->char_w;
	rect.h = font->char_h;

	for(int i = 0; i < len; ++i)
	{
		for (int j = 0; j < fonts->row_chars; j++)
		if (fonts[font_id].table[j] == text[i]) {
			rect.x = 0 + (j * font->char_w);
			rect.y = 0;
			App->render->Blit(App->textures->Load("fonts/rtype_font.png"), x, y, &rect, false, 1);
			x += font->char_w;
		}
	}
}

void ModuleFonts::TimerBlit(int font_id, Module *module_call) {
	if (font_id < 0 || font_id >= MAX_FONTS || fonts[font_id].graphic == nullptr) {
		LOG("Unable to render text with bmp font id %d", font_id);
		return;
	}
	const Font* font = &fonts[font_id];
	SDL_Rect rect;
	int x = 170;
	int y = 30;
	int counter = 0;
	timer_timer++;
	if (timer_timer % 75 == 0) {
		if (tiempo[1] == '0') {
			if (tiempo[0] == '0') {
				end = 1;
			}		//WIN CONDITION
			else {
				tiempo[1] = '9';
				tiempo[0]--;
			}
		}
		else { tiempo[1]--; }
	}
	rect.w = font->char_w;
	rect.h = font->char_h;

	if (end == 0) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 11; j++) {
				if (fonts[font_id].table[j] == tiempo[counter]) {
					rect.x = 0 + (j * fonts->char_w);
					rect.y = 0;
					App->render->Blit(App->textures->Load("assets/images/ui/timer_list.png"), x, y, &rect, false, 1);
					x += fonts->char_w;
				}
			}
			counter = 1;
		}
	}
	else if (end == 1) {	// WIN CONDITION

	}
}