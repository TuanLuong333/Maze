#pragma once
#define BASE_OBJECT_H_

#include"Declare.h"

class BaseObject
{
public:
	BaseObject();
	~BaseObject();

	void SetRect(const int& x, const int& y) { rect_.x = x,rect_.y = y; }
	SDL_Rect GetRect() const { return rect_; }
	SDL_Texture* GetObject() const { return p_object_; }
	virtual bool LoadImg(const string& path, SDL_Renderer* screen);
	void Render(SDL_Renderer* des, const SDL_Rect* clip = nullptr);
	void Free();
	SDL_Texture* LoadTexture(const string& path,SDL_Renderer* des);

protected:
	SDL_Texture* p_object_;
	SDL_Rect rect_;

};

