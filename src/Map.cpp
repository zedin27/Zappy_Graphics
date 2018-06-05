#include "Map.hpp"

Map::Map(void)
{
	// [this] is basically calling every member from the class Map
	_events["ppo"] = [this](std::string data)
	{
		int id;
		glm::vec2 pos;
		int orientation;
		std::stringstream ss;
		ss << data; //Putting in my data string
		ss >> id >> pos.x >> pos.y >> orientation; //Taking out my data string (Hint: whitespaces are important!)

		//change player position
		Player *p = getPlayer(id);
		p->MoveTo(pos);
		p->SetDir(_directions[orientation - 1]);

	};
	_events["pnw"] = [this](std::string data) //add new player
	{
		int id;
		glm::vec2 pos;
		int orientation;
		int level;
		std::string team_name;

		std::stringstream ss;
		ss << data;
		ss >> id >> pos.x >> pos.y >> orientation >> level >> team_name;

		_player.push_back(new Player(pos, orientation, team_name, id, level));

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
		for (int i = 0; i < _resourses[x][y].size(); i++)
			_resources[x][y][i] += quantity[i];
	};

	_events["sgt"] = [this](std::string data) //get time unit (check Time.cpp/hpp)
	{
		double timer;
		Time countdown;

		std::stringstream ss;
		ss << data;

		ss >> timer;
		timer.Step();
	};

	_events["msz"] = [this](std::string data) //map size or dimensions (check Map.cpp/hpp)
	{
		size_t x, y;
		std::vector<vector<size_t>>some_matrix;

		std::stringstream ss;
		ss << data;

		ss >> x >> y;
		_size.x = x;
		_size.y = y;
	};
	
	_events["enw"] = [this](std::string data) //add an egg from the player
	{
		int egg;
		int id;
		glm::vec2 pos;

		std::stringstream ss;
		ss << data;

		ss >> egg >> id >> pos.x >> pos.y;

		_eggs.push_back(new Egg(pos, id));

	};

	_events["pgt"] = [this](std::string data) //player picks resource
	{
		int id;
		int resource;

		std::stringstream ss;
		ss << data;

		ss >> id >> resource;
	};
	_events["pin"] = [this](std::string data) //ignore
	{
		//ignore
	};
	_events["pex"] = [this](std::string data) //a player uses kick
	{
		int id;

		std::stringstream ss;
		ss << data;

		ss >> id;
	};
	_events["pbc"] = [this](std::string data) //(Ignore for now)a player makes a sound
	{
		int id;
		std::string message;

		std::stringstream ss;
		ss << data;

		ss >> id >> message;
	};
	_events["pic"] = [this](std::string data) //a ritual happens on square (with the force idea?)
	{
		glm::vec2 pos;
		int level;
		int id;

		std::stringstream ss;
		ss << data;

		ss >> pos.x >> pos.y >> level; // can ignore these because of previous given information(?)

		while (!ss.empty())
		{
			ss >> id;
			Player *p = getPlayer(id);
			p->PartyMode(true);
		}
	};
	_events["plv"] = [this](std::string data)
	{
		//ignore
	};
	_events["pfk"] = [this](std::string data)
	{
		//ignore
	};
	_events["eht"] = [this](std::string data) //egg hatches - remove it
	{
		int egg;

		std::stringstream ss;
		ss << data;

		ss >> egg;

		//_eggs.erase(eggs.begin() + i);
		for()
		{
		if (_hatched == true)
			return
		}

		//delete
	};
	_events["edi"] = [this](std::string data) //egg is bad - remove it
	{
		int egg;

		std::stringstream ss;
		ss << data;

		ss >> egg;

		//delete
	};
	_events["pdi"] = [this](std::string data) //player dies - remove it
	{
		int id;

		std::stringstream ss;
		ss << data;

		ss >> id;

		Player *p = getPlayer(id);
		if (_ID.p)
			delete p;
	};
	_events["seg"] = [this](std::string data) //game is over (true/false of the map)
	{
		std::string team_name

		std::stringstream ss;
		ss << data;

		ss >> team_name
	};
}

Map::~Map(void)
{
}

void	Map::Update(double dt)
{
	//get server info...


}
