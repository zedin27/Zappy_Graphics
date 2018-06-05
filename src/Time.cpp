#include "Time.hpp"

Time::Time(void)
{
	running = false;
	resetted = true;
	paused = false;
	begin = 0.0;
	end = 0.0;
	_oldTime = glfwGetTime();
	_deltaTime = 0.0;
}

void	Time::Step(void)
{
	double time = glfwGetTime();
	_deltaTime = time - _oldTime;
	_oldTime = time;
}

void	Time::Reset(void)
{
	glfwSetTime(0.0);
	_oldTime = 0.0;
}

double	Time::Total(void)
{
	return glfwGetTime();
}

double	Time::Delta(void)
{
	return _deltaTime;
}

double	Time::Start(void) //Test needed
{
	if (!running)
	{
		if (resetted)
			begin = clock();
		else
			begin -= end - clock();
		running = true;
		resetted = false;
	}
}

double	Time::Stop(void) //Test needed
{
	if (running)
	{
		end = clock();
		running = false;
	}
}

bool	Time::isRunning() //Test needed
{
	return (running);
}

clock_t	Time::Ticks() //Test needed
{
	if (!running)
		return 0;
	if (paused)
		return (end - begin);
	return (clock() - begin);
}
