#include "Map.hpp"

const glm::vec2 Map::_directions[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

//FIXME: Lambda expressions that has the Player class will be changed. Check before testing

Player	*Map::getPlayer(int ID)
{
	for (size_t i = 0; i < _players.size(); i++)
	{
		if (ID == _players[i]->ID())
			return _players[i];
	}
	assert(1);
	return nullptr;
}

Egg	*Map::getEgg(int ID)
{
	for (size_t i = 0; i < _players.size(); i++)
	{
		if (ID == _eggs[i]->ID())
			return _eggs[i];
	}
	assert(1);
	return nullptr;
}

Map::Map(void)
{
	_grid = nullptr;
	
	// [this] is basically calling every member from the class Map
	_events["ppo"] = [this](std::string data)
	{
		int playerID;
		glm::vec2 pos;
		int orientation;

		std::stringstream ss;
		ss << data; //Putting in my data string

		ss >> playerID >> pos.x >> pos.y >> orientation; //Taking out my data string (Hint: whitespaces are important!)

		//change player position
		Player *p = getPlayer(playerID);
		p->MoveTo(pos);
		p->SetDir(_directions[orientation - 1]);

	};
	_events["pnw"] = [this](std::string data) //add new player
	{
		int playerID;
		glm::vec2 pos;
		int orientation;
		int level;
		std::string team_name;

		std::stringstream ss;
		ss << data;
		ss >> playerID >> pos.x >> pos.y >> orientation >> level >> team_name;

		_players.push_back(new Player(pos, _directions[orientation - 1], team_name, playerID, level, _size));
	};
	_events["ebo"] = [this](std::string data)
	{
		//ignore
	};
	_events["tna"] = [this](std::string data)
	{
		//ignore
	};
	_events["bct"] = [this](std::string data) //content of map block
	{
		size_t x, y;
		int quantity[7];

		std::stringstream ss;
		ss << data;
		ss >> x >> y;
		for (auto& q : quantity)
			ss >> q;
		for (int i = 0; i < _resources[x][y].size(); i++)
			_resources[x][y][i] += quantity[i];
	};

	_events["sgt"] = [this](std::string data) //get time unit (check Time.cpp/hpp)
	{
		std::stringstream ss;
		ss << data;

		ss >> _timeUnit;
	};

	_events["msz"] = [this](std::string data) //map size or dimensions (check Map.cpp/hpp)
	{
		size_t x, y;
		std::vector<std::vector<size_t>> some_matrix;

		std::stringstream ss;
		ss << data;

		ss >> x >> y;
		_size.x = x;
		_size.y = y;
		_grid = new Grid(x, y);
	};
	
	_events["enw"] = [this](std::string data) //add an egg from the player
	{
		int egg;
		int playerID;
		glm::vec2 pos;

		std::stringstream ss;
		ss << data;

		ss >> egg >> playerID >> pos.x >> pos.y;

		_eggs.push_back(new Egg(pos, playerID));

	};

	_events["pgt"] = [this](std::string data) //player picks resource
	{
		int playerID;
		int resource;

		std::stringstream ss;
		ss << data;

		ss >> playerID >> resource;

		std::vector<int> resources;
		resources.resize(7);
		resources[resource] += 1;
		
		Player *p = getPlayer(playerID);
		p->PickUp(resources);
	};

	_events["pin"] = [this](std::string data) //ignore
	{
		//ignore
	};

	_events["pex"] = [this](std::string data) //a player kick out
	{
		int playerID;

		std::stringstream ss;
		ss << data;

		ss >> playerID;
		
	};
	
	_events["pbc"] = [this](std::string data) //IGNORE: a player makes a sound
	{
		int playerID;
		std::string message;

		std::stringstream ss;
		ss << data;

		ss >> playerID >> message;
	};

	_events["pic"] = [this](std::string data) // IGNORE: a ritual happens on square (with the force idea?)
	{
		glm::vec2 pos;
		int level;
		int playerID;

		std::stringstream ss;
		ss << data;

		ss >> pos.x >> pos.y >> level; // can ignore these because of previous given information(?)

		Player *p = getPlayer(playerID);
		p->PartyMode(true);
	};

	_events["plv"] = [this](std::string data) //IGNORE
	{
		//ignore
	};

	_events["pfk"] = [this](std::string data) //IGNORE
	{
		//ignore
	};

	_events["eht"] = [this](std::string data) //egg hatches - remove it
	{
		int eggID;

		std::stringstream ss;
		ss << data;

		ss >> eggID;

		for (size_t i = 0; i < _eggs.size(); i++)
		{
			if (_eggs[i]->ID() == eggID)
			{
				delete _eggs[i];
				_eggs.erase(_eggs.begin() + i);
				break;
			}
		}
	};

	_events["edi"] = [this](std::string data) //egg is bad - remove it
	{
		int eggID;

		std::stringstream ss;
		ss << data;

		ss >> eggID;
		
		for (size_t i = 0; i < _eggs.size(); i++)
		{
			if (_eggs[i]->ID() == eggID)
			{
				delete _eggs[i];
				_eggs.erase(_eggs.begin() + i);
				break ;
			}
		}
	};

	_events["pdi"] = [this](std::string data) //player dies - remove it
	{
		int playerID;

		std::stringstream ss;
		ss << data;

		ss >> playerID;
		
		for (size_t i = 0; i < _players.size(); i++)
		{
			if (_players[i]->ID() == playerID)
			{
				delete _players[i];
				_players.erase(_players.begin() + i);
				break ;
			}
		}
	};

	//CURRENT
	_events["seg"] = [this](std::string data) //IGNORE: game is over (true/false of the map)
	{
		std::string team_name;

		std::stringstream ss;
		ss << data;

		ss >> team_name;
	};
}

Map::~Map(void)
{
}

void	Map::Render(std::pair<glm::mat4, glm::mat4> perspective, double dt)
{
	std::vector<std::string> commands;
	std::vector<std::string> data;
	
	for (size_t i = 0; i < commands.size(); i++)
	{
		if (_events.count(commands[i]) != 0)
			_events[commands[i]](data[i]);
	}
	
	for (Player *p : _players)
	{
		p->Update(dt);
		p->Render(perspective);
	}

	for (Egg *e : _eggs)
	{
		e->Render(perspective);
	}

	if (_grid)
	{
		_grid->Render(perspective);
	}
}

