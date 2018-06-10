#pragma once

#include "zappy.hpp"
#include "Model.hpp"

class	Player
{
	glm::vec2 _pos;
	glm::vec2 _dir;
	std::vector<int> _resources;
	bool _ritual;
	int _level;
	std::string _teamName;
	int _ID;
	glm::vec2 _mapSize;
	
//rendering stuff:
	
	glm::vec2 _modelPos;
	float _moveTime;
	glm::vec2 _moveDir;
	glm::vec2 _modelDir;
	glm::vec2 _modelDirChange;
	float _height;
	bool _moving;
	Model *_model;

	static std::map<uint64_t, std::list<Player*>> _staticPlayers;

	void	stopMoving(void);
	void	startMoving(void);
	void	spaceOutPlayers(uint64_t key);
	
public:
	Player(glm::vec2 pos, glm::vec2 dir, const std::string& name, int ID, int level, glm::vec2 mapSize);
	~Player(void);

	void	MoveTo(glm::vec2 pos);
	void	SetDir(glm::vec2 dir);
	void	PickUp(std::vector<int> resources);
	void	PutDown(std::vector<int> resources);

	void	PartyMode(bool);
	void	LevelUp(void);
	const std::string&	Name(void);
	int	ID(void);

	glm::vec2	GetPosition(void);
	void	Update(double dt);
	void	Render(std::pair<glm::mat4, glm::mat4> perspective);
};
