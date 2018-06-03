#include "Player.hpp"

Player::Player(glm::vec2 pos, glm::vec2 dir, const std::string& name, int ID, int level) :
_pos(pos),
_dir(dir),
_ritual(false),
_level(level),
_teamName(name),
_ID(ID)
{
	_resources.resize(6);	
}

Player::~Player(void)
{
}

void	Player::MoveTo(glm::vec2 pos)
{
	_pos = pos;
}

void	Player::SetDir(glm::vec2 dir)
{
	_dir = dir;
}

void	Player::PickUp(std::vector<int> resources)
{
	assert(resources.size() == 6);
	for (int i = 0; i < 6; i++)
	{
		assert(resources[i] >= 0);
		_resources[i] += resources[i];
		assert(_resources[i] >= 0);
	}
}

void	Player::PutDown(std::vector<int> resources)
{
	assert(resources.size() == 6);
	for (int i = 0; i < 6; i++)
	{
		assert(resources[i] >= 0);
		_resources[i] -= resources[i];
		assert(_resources[i] >= 0);
	}
}

void	Player::PartyMode(bool mode)
{
	_ritual = mode;
}

void	Player::LevelUp(void)
{
	if (_level < 8)
		_level += 1;
}

const std::string&	Player::Name(void)
{
	return _teamName;
}

int	Player::ID(void)
{
	return _ID;
}
