#include"Time.h"

Time::Time()
{
	start_tick_ = 0;
	pause_tick_ = 0;
	is_started_ = false;
	is_paused_ = false;
}

Time::~Time()
{

}

void Time::start()
{
	is_started_ = true;
	is_paused_ = false;
	start_tick_ = SDL_GetTicks();
}

void Time::stop()
{
	is_paused_ = false;
	is_started_ = false;
}

void Time::paused()
{
	if (is_started_ == true && is_paused_ == false)
	{
		is_paused_ = true;
		pause_tick_ = SDL_GetTicks() - start_tick_;
	}
}

void Time::unpaused()
{
	if (is_paused_ == true)
	{
		is_paused_ = false;
		start_tick_ = SDL_GetTicks() - pause_tick_;
		pause_tick_ = 0;
	}
}

int Time::get_ticks()
{
	if (is_started_ == true)
	{
		if (is_paused_ == true)
		{
			return pause_tick_;
		}
		else
		{
			return SDL_GetTicks() - start_tick_;
		}
	}
	return 0;
}

bool Time::is_started()
{
	return is_started_;
}

bool Time::is_paused()
{
	return is_paused_;
}