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

	if (_staticPlayers.count(key) == 0)
	{
		std::cout << "this should not be happening" << std::endl;
		return;
	}
	else
	{
		std::list<Player*> &l = _staticPlayers[key];
		auto iter = std::find(l.begin(), l.end(), this);
		assert(iter != l.end());
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

Player::Player(glm::vec2 pos, glm::vec2 dir, const std::string& name, int ID, int level, glm::vec2 mapSize) :
_pos(pos),
_dir(dir),
_ritual(false),
_level(level),
_teamName(name),
_ID(ID),
_mapSize(mapSize)
{
	_resources.resize(7);
	_modelPos = _pos;
	_modelDir = _dir;
	_moveTime = 0;
	_modelDirChange = glm::vec2(0, 0);
	stopMoving();
	_model = new Model("assets/player.model");
}

Player::~Player(void)
{
	delete _model;

	uint64_t key = keyHash(_modelPos);
	if (_staticPlayers.count(key) == 0)
		return;
	std::list<Player*> &l = _staticPlayers[key];
	auto iter = std::find(l.begin(), l.end(), this);
	if (iter != l.end())
		l.erase(iter);
	if (l.empty())
		_staticPlayers.erase(key);
	spaceOutPlayers(key);
}

void	Player::MoveTo(glm::vec2 pos)
{
	if (pos != _pos)
	{
		assert(pos == glm::mod(_pos + _dir, _mapSize));
		
		_pos = pos;
		_moveTime = 1;
		_moveDir = _dir;
		startMoving();
	}
}

void	Player::SetDir(glm::vec2 dir)
{
	if (dir != _dir)
	{
		assert(glm::dot(dir, _dir) == 0);
		
		_dir = dir;
		_modelDirChange = _dir - _modelDir;
	}
}

void	Player::PickUp(std::vector<int> resources)
{
	assert(resources.size() == 7);
	for (int i = 0; i < 7; i++)
	{
		assert(resources[i] >= 0);
		_resources[i] += resources[i];
		assert(_resources[i] >= 0);
	}
}

void	Player::PutDown(std::vector<int> resources)
{
	assert(resources.size() == 7);
	for (int i = 0; i < 7; i++)
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

glm::vec2	Player::GetPosition(void)
{
	return _pos;
}

void	Player::Update(double dt)
{

	if (_moveTime > 0)
	{
		glm::vec2 newpos = _modelPos + _modelDir * dt;
		newpos = glm::mod(newpos, _mapSize);
		_modelPos = newpos;
		_moveTime -= dt;
		if (_moveTime < 0)
		{
			_moveTime = 0;
			_modelPos = _pos;
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
	float angle = acos(glm::dot(_modelDir, glm::vec2(1, 0)));
	
	if (glm::dot(_modelDir, glm::vec2(0, 1)) < 0)
	{
		angle = 2 * M_PI - angle;
	}

	glm::mat4 rot = glm::rotate(angle, glm::vec3(0, 1, 0));
	_model->Render(perspective, rot, glm::vec3(_modelPos.x, _height * 0.5, -_modelPos.y));

	Character3D c;
	c.Render(perspective,
		 glm::vec3(_modelPos.x ,
			   _height * 0.5 + 0.6,
			   -_modelPos.y),
		 glm::vec3(1, 0, 0),
		 0.02,
		 _level + '0');
}
