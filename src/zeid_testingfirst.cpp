#include <iostream>
#include <time.h>
#include <ctime>

using namespace std;

class Time
{
	bool running;
	bool resetted;
	bool paused;
	double begin;
	double end;
	double _oldTime;

public:
	Time(void);

	//! Time since the last call to Time.Step
	double Delta(void);

	//Begin countdown of time
	double Start(void);

	void Reset();

	//Stop countdown of time
	double Stop(void);

	bool isRunning();

	//Ticks
	clock_t Ticks();
};

Time::Time(void)
{
	running = false;
	resetted = true;
	paused = false;
	begin = 0.0;
	end = 0.0;
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

void	Time::Reset()
{
	paused = false;
	begin = clock();
}

int main() //Testing Time class for lambda
{
	Time testing;

	testing.Start();
	for (int i = 0; i < 10; i++)
	{
		cout << i << endl;
		while (testing.Ticks() < 1000)
		{
			testing.Reset();
			cout << "\n";
		}
	}
	cout << "iT WORKs\n";
}
