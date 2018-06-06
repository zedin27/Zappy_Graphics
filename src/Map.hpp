#pragma once

#include "zappy.hpp"
#include "Player.hpp"
#include "Egg.hpp"
#include "Sound.hpp"
#include "Time.hpp"

class	Map
{
	std::map<std::string, std::function<void(std::string)>> _events;
	std::vector<Player*> _players;
	std::vector<Egg*> _eggs;
	std::vector<Sound*> _sounds;
	glm::vec2 _size;
	std::vector<std::vector<std::vector<int>>> _resources;
	double _timeUnit;
	
	static const glm::vec2 _directions[4];
	
	Player	*getPlayer(int ID);
	Egg	*getEgg(int ID);
	
public:
	Map(void);
	~Map(void);

	void	Update(double dt);
};
