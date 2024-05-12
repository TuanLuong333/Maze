
#pragma once
#define SLIME_H
#include"Wall.h"


#define UP_VAL 5
#define X_START 0
#define Y_START 465
#define SOUND_LIMIT -15

class Slime : public BaseObject
{
public:
	Slime();
	~Slime();

	enum WalkType
	{
		WALK_RIGHT = 0,
		WALK_LEFT = 1,
		WALK_UP = 2,
		WALK_DOWN = 3,
	};

	bool LoadImg(string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
	void SetClips();
	void DoPlayper(Map& map_data);
	void CheckMap(Map& map_data);
	void SetPos(const float& x, const float& y) { x_pos_ = x; y_pos_ = y; }
	int CheckPos();
	void SetStatus() { 
		status_ = -1;
		x_pos_ = X_START;
		y_pos_ = Y_START;
		x_val_ = 0;
		y_val_ = 0;
		status_ = -1;
		input_type_.left_ = 0;
		input_type_.right_ = 0;
		input_type_.down_ = 0;
		input_type_.up_ = 0;
		input_type_.jump_ = 0;
	};
	void GenerateWalkSkin();
	void SetSkinColor(const int& x) { SKIN_COLOR = x; }
	int GetX() const{ return x_pos_/TILE_SIZE; }
	int GetY() const { return y_pos_/TILE_SIZE; }
	void SetA(const int &change) { addition +=change; }
	int GetA() const { return addition; }
	bool GetBuff() const { return is_buffed; }
	void SetBuff(const bool& buff) { is_buffed = buff; }

private:
	float x_val_;
	float y_val_;
	float x_pos_;
	float y_pos_;
	int width_frame_;
	int height_frame_;
	SDL_Rect frame_clip_[8];
	Input input_type_;
	int frame_;
	int status_;
	int SKIN_COLOR;
	float addition;
	float PLAYER_SPEED;
	bool is_buffed;
};

