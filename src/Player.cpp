#include "Player.hpp"

std::map<uint64_t, std::list<Player*>> Player::_staticPlayers;

static uint64_t	keyHash(glm::vec2 pos)
{
	uint64_t out;

	((float*)&out)[0] = (uint32_t)pos.x;
	((float*)&out)[1] = (uint32_t)pos.y;
	return out;
}

void	Player::stopMoving(void)
{
	//add itself to the list of static players and call spaceOutPlayers()

	uint64_t key = keyHash(_modelPos);

	std::cout << key << " here" << std::endl;
	
	if (_staticPlayers.count(key) == 0)
	{
		std::list<Player*> l = {this};
		_staticPlayers[key] = l;
	}
	else
	{
		std::list<Player*> &l = _staticPlayers[key];
		l.push_back(this);
		std::cout << l.size() << std::endl;
	}
	spaceOutPlayers(key);
	_moving = false;
}

void	Player::startMoving(void)
{
	//remove itself from list of static players and call spaceOutPlayers() and set own height to 0

	uint64_t key = keyHash(_modelPos);

	std::cout << key << " o" << std::endl;
	
	if (_staticPlayers.count(key) == 0)
	{
		std::cout << "this should not be happening" << std::endl;
		return;
	}
	else
	{
		std::list<Player*> &l = _staticPlayers[key];
		auto iter = std::find(l.begin(), l.end(), this);
		l.erase(iter);
		if (l.empty())
			_staticPlayers.erase(key);
	}
	spaceOutPlayers(key);
	_height = 0;
	_moving = true;
}

void	Player::spaceOutPlayers(uint64_t key)
{
	if (_staticPlayers.count(key) == 0)
		return;
	
	std::list<Player*>& list = _staticPlayers[key];
	float i = 0;

	for (auto p : list)
	{
		p->_height = i;
		i++;
	}
}

Player::Player(glm::vec2 pos, glm::vec2 dir, const std::string& name, int ID, int level) :
_pos(pos),
_dir(dir),
_ritual(false),
_level(level),
_teamName(name),
_ID(ID)
{
	_resources.resize(6);
	_modelPos = _pos;
	_modelDir = _dir;
	_modelPosChange = glm::vec2(0, 0);
	_modelDirChange = glm::vec2(0, 0);
	stopMoving();
	_model = new Model("assets/player.model");
}

Player::~Player(void)
{
	delete _model;
}

void	Player::MoveTo(glm::vec2 pos)
{
	if (pos != _pos)
	{
		_pos = pos;
		_modelPosChange = _pos - _modelPos;
		startMoving();
	}
}

void	Player::SetDir(glm::vec2 dir)
{
	if (dir != _dir)
	{
		_dir = dir;
		_modelDirChange = _dir - _modelDir;
	}
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

void	Player::Update(double dt)
{

	if (_modelPosChange.x || _modelPosChange.y)
	{
		_modelPos += _modelPosChange * dt;
		glm::vec2 posError = _pos - _modelPos;
		if (glm::dot(posError, _modelPosChange) < 0)
		{
			_modelPos = _pos;
			_modelPosChange	= glm::vec2(0, 0);
			stopMoving();
		}
	}
	if (_modelDirChange.x || _modelDirChange.y)
	{
		_modelDir += _modelDirChange * dt;
		glm::vec2 dirError = _dir - _modelDir;
		if (glm::dot(dirError, _modelDirChange) < 0)
		{
			_modelDir = _dir;
			_modelDirChange = glm::vec2(0, 0);
		}
	}
}

void	Player::Render(std::pair<glm::mat4, glm::mat4> perspective)
{
	float angle = acos(dot(glm::normalize(_modelDir), glm::vec2(1, 0)));
	glm::mat4 rot = glm::rotate(angle, glm::vec3(0, 1, 0));
	_model->Render(perspective, rot, glm::vec3(_modelPos.x, _height * 0.5, _modelPos.y));
}
