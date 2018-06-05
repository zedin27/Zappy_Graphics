#pragma once

#include "zappy.hpp"

//! Time utility class
class Time
{
	bool running;
	bool resetted;
	bool paused;
	double begin;
	double end;
	double _oldTime;
	double _deltaTime;

public:
	Time(void);

	//! Reset the total time to zero, see Time.Total
	void Reset(void);

	//! Step time forward, measure delta time
	void Step(void);

	//! Time since the creation of the Time object or the last call to Time.Reset
	double Total(void);

	//! Time since the last call to Time.Step
	double Delta(void);

	//Begin countdown of time
	double Start(void);

	//Stop countdown of time
	double Stop(void);

	bool isRunning();

	//Ticks
	clock_t Ticks();
};
