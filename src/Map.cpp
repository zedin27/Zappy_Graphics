#include "Map.hpp"

Map::Map(void)
{
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
		
		/*	pseudo for now
		**	Player is created
		**	New player arrives with ID, level, and name of the team
		**	Spawns in a position
		**	Starts in a direction of... (N, S, W, or E)
		*/

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

		/*	pseudo for now
		**	Resource of the tiles in the map (?)
		*/
	};
	_events["sgt"] = [this](std::string data) //get time unit (check Time.cpp/hpp)
	{
		double time;

		std::stringstream ss;
		ss << data;

		ss >> time;
	};
	_events["msz"] = [this](std::string data) //map size or dimensions (check Map.cpp/hpp)
	{
		size_t x, y;

		std::stringstream ss;
		ss << data;

		ss >> x >> y;
		/* Making the size of the map
		for (size_t i = 0; i < x; i++)
		{
			for (size_t j = 0; j < y; j++)
			{
				//map[i][j] with you x and y values
			}
		}
		*/
	};
	_events["enw"] = [this](std::string data) //add an egg from the player
	{
		int egg;
		int id;
		glm::vec2 pos;

		std::stringstream ss;
		ss << data;

		ss >> egg >> id >> pos.x >> pos.y;
		//_eggs.push_back()

	};
	_events["pgt"] = [this](std::string data) //player picks resource
	{
		int id;
		int resource;

		std::stringstream ss;
		ss << data;

		ss >> id >> resource;
	};
	_events["pin"] = [this](std::string data)
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
	_events["pbc"] = [this](std::string data) //a player makes a sound
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
		/*
		** if player # dies, remove player object from map.(?)
		*/
		if (p)
			delete p;
	};
	_events["seg"] = [this](std::string data) //game is over (true/false of the map)
	{
		std::string team_name

		std::stringstream ss;
		ss << data;

		ss >> team_name
		/*
		** if game status team_name finishes, then update the game and announce winner 
		*/
	};
}

Map::~Map(void)
{
}

void	Map::Update(double dt)
{
	//get server info...

	
}
