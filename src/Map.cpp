#include "Map.hpp"

Map::Map(void)
{
	_events["ppo"] = [this](std::string data)
	{
		//change player position
	};
	_events["pnw"] = [this](std::string data)
	{
		//add new player
	};
	_events["ebo"] = [this](std::string data)
	{
		//ignore
	};
	_events["tna"] = [this](std::string data)
	{
		//ignore
	};
	_events["bct"] = [this](std::string data)
	{
		//content of map block
	};
	_events["sgt"] = [this](std::string data)
	{
		//get time unit
	};
	_events["msz"] = [this](std::string data)
	{
		//map size
	};
	_events["enw"] = [this](std::string data)
	{
		//add an egg
	};
	_events["pgt"] = [this](std::string data)
	{
		//player picks resource
	};
	_events["pin"] = [this](std::string data)
	{
		//ignore
	};
	_events["pex"] = [this](std::string data)
	{
		//a player uses kick
	};
	_events["pbc"] = [this](std::string data)
	{
		//a player makes a sound
	};
	_events["pic"] = [this](std::string data)
	{
		//a ritual happens on square
	};
	_events["plv"] = [this](std::string data)
	{
		//ignore
	};
	_events["pfk"] = [this](std::string data)
	{
		//ignore
	};
	_events["eht"] = [this](std::string data)
	{
		//egg hatches - remove it
	};
	_events["edi"] = [this](std::string data)
	{
		//egg is bad - remove it
	};
	_events["pdi"] = [this](std::string data)
	{
		//player dies - remove it
	};
	_events["seg"] = [this](std::string data)
	{
		//game is over
	};
}

Map::~Map(void)
{
}

void	Map::Update(double dt)
{
	//get server info...

	
}
