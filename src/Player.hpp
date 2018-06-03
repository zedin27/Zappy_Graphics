#pragma once

#include "zappy.hpp"

class	Player
{
	glm::vec2 _pos;
	glm::vec2 _dir;
	std::vector<int> _resources;
	bool _ritual;
	int _level;
	std::string _teamName;
	int _ID;
	
public:
	Player(glm::vec2 pos, glm::vec2 dir, const std::string& name, int ID, int level);
	~Player(void);

	void	MoveTo(glm::vec2 pos);
	void	SetDir(glm::vec2 dir);
	void	PickUp(std::vector<int> resources);
	void	PutDown(std::vector<int> resources);

	void	PartyMode(bool);
	void	LevelUp(void);
	const std::string&	Name(void);
	int	ID(void);
};
