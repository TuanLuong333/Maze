
#include"Text.h"
Text::Text()
{
	rect_.x = 0;
	rect_.y = 0;
}

Text::~Text()
{

}

void Text::SetColor(const int& type)
{
	if (type == RED_TEXT)
	{
		SDL_Color color = { 255,0,0 };
		text_color_ = color;
	}

	else if (type == WHITE_TEXT)
	{
		SDL_Color color = { 255,255,255 };
		text_color_ = color;
	}
	else
	{
		SDL_Color color = { 0,0,0 };
		text_color_ = color;
	}
}

void Text::CreateGameText(TTF_Font* font, SDL_Renderer* des, int pos_of_x, int pos_of_y)
{
	SDL_Surface* tempsurface = TTF_RenderText_Solid(font, str_val_.c_str(), text_color_);
	
	SDL_Texture* texture = SDL_CreateTextureFromSurface(des, tempsurface);


	if (tempsurface == nullptr) cout << "Loading surface in gametext function failed";

	SDL_Rect offset = { pos_of_x, pos_of_y, tempsurface->w, tempsurface->h };

	SDL_RenderCopy(des, texture, nullptr, &offset);

	SDL_FreeSurface(tempsurface);

	SDL_DestroyTexture(texture);
}

bool Text::CheckPos(const int& x, const int& y, SDL_Rect& rect)
{
	if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h)
		return true;

	return false;
}

int Text :: DemoMenu(SDL_Renderer* des, TTF_Font* font)
{ 
	
	menu_img = LoadTexture("image//Slime Go.png", des);
	
	if (menu_img == nullptr)
	{
		cout << "Error: Failed to load menu image." << SDL_GetError();
		return 1;
	}

	button_click = Mix_LoadWAV("gamesound//mixkit-player-jumping-in-a-video-game-2043 (1).wav");
	if (button_click == NULL)
	{
		printf("1Failed to load button click effect! SDL_mixer Error: %s\n", Mix_GetError());
		return -1;
	}

	SDL_RenderCopy(des, menu_img, nullptr, nullptr);
	SDL_RenderPresent(des);

	const int MenuItemNum = 4;

	SDL_Rect pos_arr[MenuItemNum];

	pos_arr[0].x = 170;
	pos_arr[0].y = 220;
	pos_arr[0].w = 140;
	pos_arr[0].h = 20;

	pos_arr[1].x = 170;
	pos_arr[1].y = 280;
	pos_arr[1].w = 50;
	pos_arr[1].h = 20;

	pos_arr[2].x = 170;
	pos_arr[2].y = 340;
	pos_arr[2].w = 200;
	pos_arr[2].h = 20;

	pos_arr[3].x = 170;
	pos_arr[3].y = 400;
	pos_arr[3].w = 200;
	pos_arr[3].h = 20;

	Text text_menu[MenuItemNum];

	text_menu[0].SetText("Play Game");
	text_menu[0].SetColor(BLACK_TEXT);
	text_menu[0].SetRect(pos_arr[0].x, pos_arr[0].y);

	text_menu[1].SetText("EXIT");
	text_menu[1].SetColor(BLACK_TEXT);
	text_menu[1].SetRect(pos_arr[1].x, pos_arr[1].y);

	text_menu[2].SetText("CHOOSE SKIN");
	text_menu[2].SetColor(BLACK_TEXT);
	text_menu[2].SetRect(pos_arr[2].x, pos_arr[2].y);

	text_menu[3].SetText("CHOOSE LEVEL");
	text_menu[3].SetColor(BLACK_TEXT);
	text_menu[3].SetRect(pos_arr[3].x, pos_arr[3].y);

	bool selected[MenuItemNum] = { 0,0,0,0 };

	int x_mouse = 0;
	int y_mouse = 0;

	SDL_Event e_mouse;

	while (true)
	{
		for (int i = 0; i < MenuItemNum; i++)
		{
			text_menu[i].CreateGameText(font, des, pos_arr[i].x, pos_arr[i].y);

		}
		while (SDL_PollEvent( & e_mouse))
		{
			switch (e_mouse.type)
			{
			case SDL_QUIT:
				return 1;
				break;
			case SDL_MOUSEMOTION:
			{
				x_mouse = e_mouse.motion.x;
				y_mouse = e_mouse.motion.y;

				for (int i = 0; i < MenuItemNum; i++)
				{
					if (CheckPos(x_mouse, y_mouse, pos_arr[i]))
					{
						if (selected[i] == false)
						{
							selected[i] = 1;
							text_menu[i].SetColor(RED_TEXT);
						}
					}
					else
					{
						if (selected[i] == true)
						{
							selected[i] = 0;
							text_menu[i].SetColor(BLACK_TEXT);
						}
					}
				}
			}
			break;

			case SDL_MOUSEBUTTONDOWN:
			{

				Mix_PlayChannel(-1, button_click, 0);
				x_mouse = e_mouse.button.x;
				y_mouse = e_mouse.button.y;

				for (int i = 0; i < MenuItemNum; i++)
				{
					if (CheckPos(x_mouse, y_mouse, pos_arr[i]))
					{
						Mix_PlayChannel(-1, button_click, 0);
						return i;
					}
				}
			}
			break;

			case SDL_KEYDOWN:
			{
				if (e_mouse.key.keysym.sym == SDLK_ESCAPE)
					return 1;
			}
			break;

			default:
				break;
			}
		}

		SDL_RenderPresent(des);
	}
	return 1;
}

int Text::ServiceProgram(SDL_Renderer* des, TTF_Font* font, string first_text,string second_text)
{
	pause_img = LoadTexture("image//pausepicture.png", des);

	if (pause_img == nullptr)
	{
		cout << "Error: Failed to load pause image." << SDL_GetError();
		return 1;
	}
	SDL_Rect renderpause = { 305,185,305,185 };
	SDL_RenderCopy(des, pause_img, nullptr, &renderpause);
	//SDL_RenderPresent(des);

	const int PauseItemNum = 2;

	SDL_Rect pos_arr[PauseItemNum];

	pos_arr[0].x = 400;
	pos_arr[0].y = 235;
	pos_arr[0].w = 130;
	pos_arr[0].h = 20;

	pos_arr[1].x = 420;
	pos_arr[1].y = 305;
	pos_arr[1].w = 80;
	pos_arr[1].h = 20;


	Text text_pause[PauseItemNum];

	text_pause[0].SetText(first_text);
	text_pause[0].SetColor(BLACK_TEXT);
	text_pause[0].SetRect(pos_arr[0].x, pos_arr[0].y);

	text_pause[1].SetText(second_text);
	text_pause[1].SetColor(BLACK_TEXT);
	text_pause[1].SetRect(pos_arr[1].x, pos_arr[1].y);

	bool selected[PauseItemNum] = { 0,0 };

	int x_mouse = 0;
	int y_mouse = 0;

	SDL_Event e_mouse;

	while (true)
	{
		for (int i = 0; i < PauseItemNum; i++)
		{
			text_pause[i].CreateGameText(font, des, pos_arr[i].x, pos_arr[i].y);

		}
		while (SDL_PollEvent(&e_mouse))
		{
			switch (e_mouse.type)
			{
			case SDL_QUIT:
				return 1;
				break;
			case SDL_MOUSEMOTION:
			{
				x_mouse = e_mouse.motion.x;
				y_mouse = e_mouse.motion.y;

				for (int i = 0; i < PauseItemNum; i++)
				{
					if (CheckPos(x_mouse, y_mouse, pos_arr[i]))
					{
						if (selected[i] == false)
						{
							selected[i] = 1;
							text_pause[i].SetColor(RED_TEXT);
						}
					}
					else
					{
						if (selected[i] == true)
						{
							selected[i] = 0;
							text_pause[i].SetColor(BLACK_TEXT);
						}
					}
				}
			}
			break;

			case SDL_MOUSEBUTTONDOWN:
			{
				x_mouse = e_mouse.button.x;
				y_mouse = e_mouse.button.y;

				for (int i = 0; i < PauseItemNum; i++)
				{
					if (CheckPos(x_mouse, y_mouse, pos_arr[i]))
					{
						Mix_PlayChannel(-1, button_click, 0);
						return i;
					}
				}
			}
			break;

			default:
				break;
			}
		}

		SDL_RenderPresent(des);
	}
	return 1;
}

int Text::SkinShow(SDL_Renderer* des, TTF_Font* font)
{
	skin_img = LoadTexture("image//Skin_show.jpg", des);

	if (skin_img == nullptr)
	{
		cout << "Error: Failed to load menu image." << SDL_GetError();
		return 1;
	}

	SDL_RenderCopy(des, skin_img, nullptr, nullptr);
	//SDL_RenderPresent(des);

	const int SkinItemNum = 5;

	SDL_Rect pos_arr[SkinItemNum];

	pos_arr[0].x = 720;
	pos_arr[0].y = 405;
	pos_arr[0].w = 100;
	pos_arr[0].h = 20;

	pos_arr[1].x = 430;
	pos_arr[1].y = 405;
	pos_arr[1].w = 80;
	pos_arr[1].h = 20;

	pos_arr[2].x = 180;
	pos_arr[2].y = 405;
	pos_arr[2].w = 100;
	pos_arr[2].h = 20;

	pos_arr[3].x = 50;
	pos_arr[3].y = 75;
	pos_arr[3].w = 100;
	pos_arr[3].h = 20;

	pos_arr[4].x = 750;
	pos_arr[4].y = 75;
	pos_arr[4].w = 100;
	pos_arr[4].h = 20;

	Text text_menu[SkinItemNum];

	text_menu[0].SetText("BLUE");
	text_menu[0].SetColor(BLACK_TEXT);
	text_menu[0].SetRect(pos_arr[0].x, pos_arr[0].y);

	text_menu[1].SetText("GREEN");
	text_menu[1].SetColor(BLACK_TEXT);
	text_menu[1].SetRect(pos_arr[1].x, pos_arr[1].y);

	text_menu[2].SetText("RED");
	text_menu[2].SetColor(BLACK_TEXT);
	text_menu[2].SetRect(pos_arr[2].x, pos_arr[2].y);

	text_menu[3].SetText("BACK");
	text_menu[3].SetColor(BLACK_TEXT);
	text_menu[3].SetRect(pos_arr[3].x, pos_arr[3].y);

	text_menu[4].SetText("Play Game");
	text_menu[4].SetColor(BLACK_TEXT);
	text_menu[4].SetRect(pos_arr[4].x, pos_arr[4].y);

	bool selected[SkinItemNum] = { 0,0,0,0,0 };

	int x_mouse = 0;
	int y_mouse = 0;

	SDL_Event e_mouse;

	while (true)
	{
		for (int i = 0; i < SkinItemNum; i++)
		{
			text_menu[i].CreateGameText(font, des, pos_arr[i].x, pos_arr[i].y);

		}
		while (SDL_PollEvent(&e_mouse))
		{
			switch (e_mouse.type)
			{
			case SDL_QUIT:
				return 5;
				break;
			case SDL_MOUSEMOTION:
			{
				x_mouse = e_mouse.motion.x;
				y_mouse = e_mouse.motion.y;

				for (int i = 0; i < SkinItemNum; i++)
				{
					if (CheckPos(x_mouse, y_mouse, pos_arr[i]))
					{
						if (selected[i] == false)
						{
							selected[i] = 1;
							text_menu[i].SetColor(RED_TEXT);
						}
					}
					else
					{
						if (selected[i] == true)
						{
							selected[i] = 0;
							text_menu[i].SetColor(BLACK_TEXT);
						}
					}
				}
			}
			break;

			case SDL_MOUSEBUTTONDOWN:
			{
				x_mouse = e_mouse.button.x;
				y_mouse = e_mouse.button.y;

				for (int i = 0; i < SkinItemNum; i++)
				{
					if (CheckPos(x_mouse, y_mouse, pos_arr[i]))
					{
						Mix_PlayChannel(-1, button_click, 0);
						return i;
					}
				}
			}
			break;

			case SDL_KEYDOWN:
			{
				if (e_mouse.key.keysym.sym == SDLK_ESCAPE)
					return 1;
			}
			break;

			default:
				break;
			}
		}

		SDL_RenderPresent(des);
	}
	return 1;
}

int Text::SelectLevel(SDL_Renderer* des, TTF_Font* font)
{
	skin_img = LoadTexture("image//level_pic.jpg", des);

	if (skin_img == nullptr)
	{
		cout << "Error: Failed to load menu image." << SDL_GetError();
		return 1;
	}

	SDL_RenderCopy(des, skin_img, nullptr, nullptr);
	SDL_RenderPresent(des);

	const int SkinItemNum = 4;

	SDL_Rect pos_arr[SkinItemNum];

	pos_arr[0].x = 430;
	pos_arr[0].y = 240;
	pos_arr[0].w = 80;
	pos_arr[0].h = 20;

	pos_arr[1].x = 410;
	pos_arr[1].y = 385;
	pos_arr[1].w = 120;
	pos_arr[1].h = 20;

	pos_arr[2].x = 120;
	pos_arr[2].y = 330;
	pos_arr[2].w = 100;
	pos_arr[2].h = 20;

	pos_arr[3].x = 785;
	pos_arr[3].y = 330;
	pos_arr[3].w = 100;
	pos_arr[3].h = 20;

	Text text_menu[SkinItemNum];

	text_menu[0].SetText("Easy");
	text_menu[0].SetColor(BLACK_TEXT);
	text_menu[0].SetRect(pos_arr[0].x, pos_arr[0].y);

	text_menu[1].SetText("Medium");
	text_menu[1].SetColor(BLACK_TEXT);
	text_menu[1].SetRect(pos_arr[1].x, pos_arr[1].y);

	text_menu[2].SetText("BACK");
	text_menu[2].SetColor(BLACK_TEXT);
	text_menu[2].SetRect(pos_arr[2].x, pos_arr[2].y);

	text_menu[3].SetText("PLAY");
	text_menu[3].SetColor(BLACK_TEXT);
	text_menu[3].SetRect(pos_arr[3].x, pos_arr[3].y);

	bool selected[SkinItemNum] = { 0,0,0,0 };

	int x_mouse = 0;
	int y_mouse = 0;

	SDL_Event e_mouse;

	while (true)
	{
		for (int i = 0; i < SkinItemNum; i++)
		{
			text_menu[i].CreateGameText(font, des, pos_arr[i].x, pos_arr[i].y);

		}
		while (SDL_PollEvent(&e_mouse))
		{
			switch (e_mouse.type)
			{
			case SDL_QUIT:
				return -1;
				break;
			case SDL_MOUSEMOTION:
			{
				x_mouse = e_mouse.motion.x;
				y_mouse = e_mouse.motion.y;

				for (int i = 0; i < SkinItemNum; i++)
				{
					if (CheckPos(x_mouse, y_mouse, pos_arr[i]))
					{
						if (selected[i] == false)
						{
							selected[i] = 1;
							text_menu[i].SetColor(RED_TEXT);
						}
					}
					else
					{
						if (selected[i] == true)
						{
							selected[i] = 0;
							text_menu[i].SetColor(BLACK_TEXT);
						}
					}
				}
			}
			break;

			case SDL_MOUSEBUTTONDOWN:
			{
				x_mouse = e_mouse.button.x;
				y_mouse = e_mouse.button.y;

				for (int i = 0; i < SkinItemNum; i++)
				{
					if (CheckPos(x_mouse, y_mouse, pos_arr[i]))
					{
						Mix_PlayChannel(-1, button_click, 0);
						return i;
					}
				}
			}
			break;

			case SDL_KEYDOWN:
			{
				if (e_mouse.key.keysym.sym == SDLK_ESCAPE)
					return -1;
			}
			break;

			default:
				break;
			}
		}

		SDL_RenderPresent(des);
	}
	return -1;
}

/*
void Text:: GiftAnnouncement(int value, SDL_Renderer* des, TTF_Font* font)
{
	//if (true)
	//{
		srand(time(NULL));
		//int value = rand()%4+1;
		// ham hien man hinh nho Function(int value)

		string content[4] = { "INCREASE SPEED","DECREASE SPEED","BEING STUNNED","RANDOM POSITION" };

		gift_img = LoadTexture("C://Users//ASUS//Pictures//Saved Pictures//pausepicture.png", des);

		if (gift_img == nullptr)
		{
			cout << "Error: Failed to load gift image." << SDL_GetError();
		}
		SDL_Rect rendergift = { 305,185,305,185 };
		SDL_RenderCopy(des, gift_img, nullptr, &rendergift);

		SDL_Rect gift_rect = { 310,235,140,20 };

		Text text;

		text.SetText(content[value - 1]);
		text.SetColor(BLACK_TEXT);
		text.SetRect(gift_rect.x, gift_rect.y);
		text.CreateGameText(font, des, gift_rect.x, gift_rect.y);

		SDL_RenderPresent(des);
		SDL_Delay(1200);

	//}

}
*/
