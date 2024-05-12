
#pragma once
#define TEXT_H
#include"Slime.h"

class Text : public BaseObject
{
public:

	enum TextColor
	{
		RED_TEXT = 0,
		WHITE_TEXT = 1,
		BLACK_TEXT = 2,
	};

	Text();
	~Text();

	void SetText(const string& text) { str_val_ = text; };

	void SetColor(const int& type);

	void CreateGameText(TTF_Font* font, SDL_Renderer* des, int pos_of_x, int pos_of_y);

	int DemoMenu(SDL_Renderer* des, TTF_Font* font);

	bool CheckPos(const int& x, const int& y, SDL_Rect& rect);

	int ServiceProgram(SDL_Renderer* des, TTF_Font* font,string s1,string s2);

	int SkinShow(SDL_Renderer* des, TTF_Font* font);

	int SelectLevel(SDL_Renderer* des, TTF_Font* font);

	//void GiftAnnouncement(int value, SDL_Renderer* des, TTF_Font* font);



private:
	string str_val_;
	SDL_Color text_color_;
};


