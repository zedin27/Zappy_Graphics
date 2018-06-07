#include "ServerMonitor.hpp"

ServerMonitor::ServerMonitor(int fd) : _fd(fd)
{
	FD_ZERO(&_rfds);
	FD_SET(_fd, &_rfds);

	_tv.tv_sec = 0;
	_tv.tv_usec = 0;
}

void	ServerMonitor::Update(void)
{
	//clear the previous frames commands + data
	_commands.clear();
	_data.clear();

	//read the server fd, taking care to not get blocked
	char buf[10000];	
	if (FD_ISSET(_fd, &_rfds))
	{
		int bytes_read = read(_fd, buf, 9999); //shhh, no one needs to know
		assert(bytes_read < 9999);
		buf[bytes_read] = '\0';

		std::stringstream ss((std::string(buf)));

		for (std::string line; std::getline(ss, line);)
		{
			size_t delim = line.find(' ');
			_commands.push_back(line.substr(0, delim));
			_data.push_back(line.substr(delim + 1));
		}
	}
}

const std::vector<const std::string>&	ServerMonitor::Commands(void)
{
	return _commands;
}

const std::vector<const std::string>&	ServerMonitor::Data(void)
{
	return _data;
}
