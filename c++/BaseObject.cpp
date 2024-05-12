#include"BaseObject.h"

BaseObject::BaseObject() {
	p_object_ = nullptr;
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0;
	rect_.h = 0;

}
BaseObject::~ BaseObject() {
	Free();
}

bool BaseObject::LoadImg(const string& path, SDL_Renderer* screen) 
{

	SDL_Texture* new_texture = nullptr;
	SDL_Surface* firstload = IMG_Load(path.c_str());

	if (firstload != nullptr) {

		SDL_SetColorKey(firstload, SDL_TRUE, SDL_MapRGB(firstload->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));

		new_texture = SDL_CreateTextureFromSurface(screen, firstload);

		if (new_texture != nullptr) 
		{
			rect_.w = firstload->w;
			rect_.h = firstload->h;
		}
		else
		{
			rect_.w = 0;
			rect_.h = 0;
			cout << "load img baseobject sai roi con"<<SDL_GetError();
			return false;
		}
		SDL_FreeSurface(firstload);
	}

	p_object_ = new_texture;
	return true;
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip) 
{
	SDL_Rect renderquad = {rect_.x,rect_.y,rect_.w,rect_.h};
	if (p_object_ != nullptr) 
	{
		SDL_RenderCopy(des, p_object_, clip, &renderquad);
	}
		
	else cout << "p_object_ is null ne"<<endl;
}

void BaseObject::Free() {
	if (p_object_ != nullptr) {
		SDL_DestroyTexture(p_object_);
		p_object_ = nullptr;
		rect_.h = 0;
		rect_.w = 0;
	}
}

SDL_Texture* BaseObject :: LoadTexture(const string& path,SDL_Renderer* des)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		cout << "co loi o day111" << IMG_GetError();
		return nullptr;
	}
	newTexture = SDL_CreateTextureFromSurface(des, loadedSurface);
	SDL_FreeSurface(loadedSurface);

	if (newTexture == NULL)
	{
		cout << "co loi o day222" << SDL_GetError()<<endl;
	}
	return newTexture;
}

