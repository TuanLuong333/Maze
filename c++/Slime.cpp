
#include"Slime.h"

Slime::Slime()
{
	frame_ = 0;
	x_pos_ = X_START;
	y_pos_ = Y_START;
	x_val_ = 0;
	y_val_ = 0;
	width_frame_ = 0;
	height_frame_ = 0;
	status_ = -1;
	input_type_.left_ = 0;
	input_type_.right_ = 0;
	input_type_.down_ = 0;
	input_type_.up_ = 0;
	input_type_.jump_ = 0;
	SKIN_COLOR = 1;//1 BLUE,2 GREEN,3 RED
	addition = 0.00;
	PLAYER_SPEED = 5;
	is_buffed = false;
}

Slime :: ~Slime()
{

}

bool Slime::LoadImg(string path, SDL_Renderer* screen)
{
	bool ok = BaseObject::LoadImg(path, screen);
	if (ok == true) 
	{
		width_frame_ = rect_.w / 8;
		height_frame_ = rect_.h;
	}
	SetClips();
	return ok;
}

void Slime::SetClips()
{
	if (width_frame_ > 0 && height_frame_ > 0)
	{
		frame_clip_[0].x = 0;
		frame_clip_[0].y = 0;
		frame_clip_[0].w = width_frame_;
		frame_clip_[0].h = height_frame_;

		frame_clip_[1].x = width_frame_;
		frame_clip_[1].y = 0;
		frame_clip_[1].w = width_frame_;
		frame_clip_[1].h = height_frame_;

		frame_clip_[2].x = 2*width_frame_;
		frame_clip_[2].y = 0;
		frame_clip_[2].w = width_frame_;
		frame_clip_[2].h = height_frame_;

		frame_clip_[3].x = 3 * width_frame_;
		frame_clip_[3].y = 0;
		frame_clip_[3].w = width_frame_;
		frame_clip_[3].h = height_frame_;

		frame_clip_[4].x = 4 * width_frame_;
		frame_clip_[4].y = 0;
		frame_clip_[4].w = width_frame_;
		frame_clip_[4].h = height_frame_;

		frame_clip_[5].x = 5 * width_frame_;
		frame_clip_[5].y = 0;
		frame_clip_[5].w = width_frame_;
		frame_clip_[5].h = height_frame_;

		frame_clip_[6].x = 6 * width_frame_;
		frame_clip_[6].y = 0;
		frame_clip_[6].w = width_frame_;
		frame_clip_[6].h = height_frame_;

		frame_clip_[7].x = 7 * width_frame_;
		frame_clip_[7].y = 0;
		frame_clip_[7].w = width_frame_;
		frame_clip_[7].h = height_frame_;

	}
}

void Slime::Show(SDL_Renderer* des)
{
	if (p_object_ == nullptr)
	{
		cout << "Error: Image not loaded!" << endl;
		return;
	}

	if (status_ == WALK_LEFT)
	{
		LoadImg(WalkSkin[SKIN_COLOR][0], des);
	}
	else if (status_ == WALK_RIGHT)
	{
		LoadImg(WalkSkin[SKIN_COLOR][1], des);
	}
	else if (status_ == WALK_UP)
	{
		LoadImg(WalkSkin[SKIN_COLOR][2], des);
	}
	else if (status_ == WALK_DOWN)
	{
		LoadImg(WalkSkin[SKIN_COLOR][3], des);
	}
		
	if (input_type_.left_ == 1 || input_type_.right_ == 1 || input_type_.up_ == 1 || input_type_.down_ == 1)
	{
		frame_++;
	}
	else {

		frame_ = 0;
	}

	if (frame_ >= 8)
	{
		frame_ = 0;
	}

	rect_.x = x_pos_;
	rect_.y = y_pos_;

	SDL_Rect* current_clip = &frame_clip_[frame_];

	SDL_Rect renderQuad = { rect_.x,rect_.y,width_frame_,height_frame_ };

	SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);


}

void Slime::HandleInputAction(SDL_Event events, SDL_Renderer* screen) {

 	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym) 
		{
		case SDLK_RIGHT:
		{
			status_ = WALK_RIGHT;
			input_type_.right_= 1;
			input_type_.left_ = 0;
			input_type_.up_ = 0;
			input_type_.down_ = 0;
			if (sound_cnt >= 0 && sound_cnt <3)
			{
				sound_cnt++;
				Mix_PlayChannel(-1, move_sound, 0);
			}
			if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT])
			{
				if (sound_cnt == 3)
				{
					sound_cnt = SOUND_LIMIT;
				}
				else if (sound_cnt >= SOUND_LIMIT && sound_cnt<0)
				{
					sound_cnt++;
				}

			}
		}
		break;
		case SDLK_LEFT:
		{
			status_ = WALK_LEFT;
			input_type_.left_ = 1;
			input_type_.right_ = 0;
			input_type_.up_ = 0;
			input_type_.down_ = 0;
			if (sound_cnt >= 0 && sound_cnt < 3)
			{
				sound_cnt++;
				Mix_PlayChannel(-1, move_sound, 0);
			}
			if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT])
			{
				if (sound_cnt == 3)
				{
					sound_cnt = SOUND_LIMIT;
				}
				else if (sound_cnt >= SOUND_LIMIT && sound_cnt < 0)
				{
					sound_cnt++;
				}

			}
		}
		     break;
		case SDLK_DOWN:
		{
			status_ = WALK_DOWN;
			input_type_.right_ = 0;
			input_type_.left_ = 0;
			input_type_.up_ = 0;
			input_type_.down_ = 1;
			if (sound_cnt >= 0 && sound_cnt < 3)
			{
				sound_cnt++;
				Mix_PlayChannel(-1, move_sound, 0);
			}
			if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN])
			{
				if (sound_cnt == 3)
				{
					sound_cnt = SOUND_LIMIT;
				}
				else if (sound_cnt >= SOUND_LIMIT && sound_cnt < 0)
				{
					sound_cnt++;
				}

			}
		}
		break;
		case SDLK_UP:
		{
			status_ = WALK_UP;
			input_type_.right_ = 0;
			input_type_.left_ = 0;
			input_type_.up_ = 1;
			input_type_.down_ = 0; 
			if (sound_cnt >= 0 && sound_cnt < 3)
			{
				sound_cnt++;
				Mix_PlayChannel(-1, move_sound, 0);
			}
			if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP])
			{
				if (sound_cnt == 3)
				{
					sound_cnt = SOUND_LIMIT;
				}
				else if (sound_cnt >= SOUND_LIMIT && sound_cnt < 0)
				{
					sound_cnt++;
				}

			}

		}
		break;
		    
		}
	}
	else if(events.type == SDL_KEYUP) 
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			input_type_.right_ = 0;
			sound_cnt = 0;
		}
		break;
		case SDLK_LEFT:
		{
			input_type_.left_ = 0;
			sound_cnt = 0;
		}
		break;
		case SDLK_UP:
		{
			input_type_.up_ = 0;
			sound_cnt = 0;
		}
		break;
		case SDLK_DOWN:
		{
			input_type_.down_ = 0;
			sound_cnt = 0;
		}
		break;
		
		}
	}

	
}

void Slime::DoPlayper(Map& map_data)
{
	x_val_ = 0;
	y_val_ = 0;
	if (input_type_.left_ == 1)
	{
		x_val_ -= (PLAYER_SPEED + addition);
		//x_pos_ -= PLAYER_SPEED;
	}
	else if (input_type_.right_ == 1)
	{
		x_val_ += (PLAYER_SPEED + addition);
		//x_pos_ += PLAYER_SPEED;
	}
	else if (input_type_.up_ == 1) {
	//	y_pos_ -= PLAYER_SPEED / 2;
		y_val_ -= 2* (PLAYER_SPEED + addition) /3;
	}
	else if (input_type_.down_ == 1)
	{
		//y_pos_ += PLAYER_SPEED / 2;
		y_val_ += 2* (PLAYER_SPEED + addition) /3 ;
	}

	CheckMap(map_data);
	
}

void Slime::CheckMap(Map& map_data)
{
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;

	//horizontal
	int height_min = height_frame_;
	x1 = (x_pos_ +x_val_) / TILE_SIZE;
	x2 = (x_pos_ +x_val_ + width_frame_-1) / TILE_SIZE;

	y1 = (y_pos_) / TILE_SIZE;
	y2 = (y_pos_ + height_min-1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (x_val_ > 0)
		{
			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y2][x2];

			if (val1 == 29 || val1 == 30)
			{
				map_data.tile[y1][x2] = 0;
			}
			else if (val2 == 29 || val2 == 30)
			{
				map_data.tile[y2][x2] = 0;
			}

			else if (val1 != BLANK_TILE || val2 != BLANK_TILE )
			{
				x_pos_ = x2 * TILE_SIZE;
				x_pos_ -= (width_frame_ + 1);
				x_val_ = 0;
			}
		}
		else if (x_val_ < 0)
		{
			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y1][x1];

			if (val1 == 29 || val1 == 30)
			{
				map_data.tile[y1][x2] = 0;
			}
			else if (val2 == 29 || val2 == 30)
			{
				map_data.tile[y2][x2] = 0;
			}
			else if (val1 != BLANK_TILE || val2 != BLANK_TILE )
			{
				x_pos_ = (x1 + 1) * TILE_SIZE;
				x_val_ = 0;
			}
		}
	}

	//vertical

	int width_min = 15;
	x1 = (x_pos_ ) / TILE_SIZE;
	x2 = (x_pos_ + addition) / TILE_SIZE;

	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + y_val_+ height_frame_-1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (y_val_ > 0)
		{
			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];

			if (val1 == 29 || val1 == 30)
			{
				map_data.tile[y1][x2] = 0;
			}
			else if (val2 == 29 || val2 == 30)
			{
				map_data.tile[y2][x2] = 0;
			}

			else if (val1 != BLANK_TILE || val2 != BLANK_TILE )
			{
				y_pos_ = y2 * TILE_SIZE;
				y_pos_ -= (height_frame_ + 1);
				y_val_ = 0;
			}
		}
		else if (y_val_ < 0)
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];

			if (val1 == 29 || val1 == 30)
			{
				map_data.tile[y1][x2] = 0;
			}
			else if (val2 == 29 || val2 == 30)
			{
				map_data.tile[y2][x2] = 0;
			}
			else if (val1 != BLANK_TILE || val2 != BLANK_TILE )
			{
				y_pos_ = (y1 + 1) * TILE_SIZE;
				y_val_ = 0;

			}
		}
	}


	 x_pos_ = x_pos_ + x_val_;
	 y_pos_ = y_pos_ + y_val_;

	if (x_pos_ < 0)
	{
		x_pos_ = 0;
	}
	else if (x_pos_ + width_frame_ > map_data.max_x_)
	{
		x_pos_ = map_data.max_x_ - width_frame_ - 1;
	}
}

int Slime :: CheckPos()
{
	if (x_pos_ >= 900 && x_pos_ <= 915 && y_pos_ >= 225 && y_pos_ <= 255)
		return 1;
	return 0;
}

void Slime::GenerateWalkSkin()
{
	move_sound = Mix_LoadWAV("gamesound//202403312253.wav");
	if (move_sound == NULL)
	{
		cout<<"Failed to load move sound SDL_mixer Error: %s\n"<< Mix_GetError();
	}

	WalkSkin[0][0] = "";
	WalkSkin[0][1] = "";
	WalkSkin[0][2] = "";
	WalkSkin[0][3] = "";

	WalkSkin[1][0] = "movement//B_left.png";
	WalkSkin[1][1] = "movement//B_right.png";
	WalkSkin[1][2] = "movement//B_up.png";
	WalkSkin[1][3] = "movement//B_down.png";

	WalkSkin[2][0] = "movement//G_left.png";
	WalkSkin[2][1] = "movement//G_right.png";
	WalkSkin[2][2] = "movement//G_up.png";
	WalkSkin[2][3] = "movement//G_down.png";

	WalkSkin[3][0] = "movement//R_left.png";
	WalkSkin[3][1] = "movement//R_right.png";
	WalkSkin[3][2] = "movement//R_up.png";
	WalkSkin[3][3] = "movement//R_down.png";
}
