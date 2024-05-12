#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <iostream>
#include <fstream>
#include<windows.h>
#include <SDL_ttf.h>
#include<SDL_mixer.h>
#include<vector>
#include<algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SCREEN_WIDTH = 61*15;
const int SCREEN_HEIGHT = 37*15;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;


static string WalkSkin[4][4];
static TTF_Font* g_font_text = nullptr;
static TTF_Font* pause_font_text = nullptr;
static SDL_Window* window = nullptr;
static SDL_Surface* screensurface = nullptr;
static SDL_Event e;
static SDL_Renderer* ss = nullptr;
static SDL_Texture* gem = nullptr;
static SDL_Texture* menu_img = nullptr;
static SDL_Texture* skin_img = nullptr;
static SDL_Texture* pause_img = nullptr;
static SDL_Texture* gift_img = nullptr;
static Mix_Music* game_music = nullptr;
static Mix_Chunk* move_sound = nullptr;
static Mix_Chunk* button_click = nullptr;
static Mix_Chunk* P_sound = nullptr;
static Mix_Chunk* win_sound = nullptr;
static int sound_cnt = 0;
static int game_level = 1;
static int last;
static int change = 0;


#define BLANK_TILE 0
#define BUFF 30
#define TILE_SIZE 15
#define MAX_MAP_X 61
#define MAX_MAP_Y 37



typedef struct Input
{
	int left_;
	int right_;
	int up_;
	int down_;
	int jump_;
};

typedef struct Map
{

	int start_x_;
	int start_y_;
	int max_x_;
	int max_y_;
	int tile[MAX_MAP_Y][MAX_MAP_X];
	char* file_name_;
};


#endif


