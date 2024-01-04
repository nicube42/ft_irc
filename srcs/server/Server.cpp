/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:28:30 by ndiamant          #+#    #+#             */
/*   Updated: 2024/01/04 19:34:52 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"
#include "../../includes/Users.hpp"
#include "../../includes/Channels.hpp"

Server::Server(int port, std::string password) : _port(port), _password(password)
{
	_server_fd = -1;
	_fds.clear();
}

bool Server::setup()
{
	//create socket
	_server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_server_fd == -1)
	{
		std::cerr << RED << "Could not create socket" << RESET << std::endl;
		return (false);
	}

	memset(&_address, 0, sizeof(_address));
	_address.sin_family = AF_INET;
	_address.sin_addr.s_addr = INADDR_ANY;
	_address.sin_port = htons(_port);

	if (bind(_server_fd, (struct sockaddr *)&_address, sizeof(_address)) < 0)
	{
		std::cerr << RED << "Bind failed" << RESET << std::endl;
		return (false);
	}

	listen(_server_fd, 3);
	if (fcntl(_server_fd, F_SETFL, O_NONBLOCK) < 0)
	{
			std::cerr << RED << "Failed to set non-blocking mode" << RESET << std::endl;
			return (false);
	}
	//prepare poll and stock fd server
	struct pollfd server_fd_struct;
	server_fd_struct.fd = _server_fd;
	server_fd_struct.events = POLLIN;
	_fds.push_back(server_fd_struct);
	return (true);
}

void Server::ensureChannelExists(const std::string& channelName)
{
	for (size_t i = 0; i < _channels.size(); ++i)
	{
		if (_channels[i].getName() == channelName) {
			return;
		}
	}
	Channels newChannel(channelName);
	_channels.push_back(newChannel);
}


void Server::handleNewConnection(int client_socket)
{
	Users newUser(client_socket);

	_users.push_back(newUser);

	struct pollfd user_fd;
	user_fd.fd = client_socket;
	user_fd.events = POLLIN;
	_users.back().setFd(user_fd);

	srand(time(NULL));
	std::stringstream nickname;
	nickname << "User" << rand();
	_users.back().setNickname(nickname.str());

	ensureChannelExists("Welcome");
	_channels[0].addUser(&_users.back());
}

void Server::handleMessage(int userIndex, const char* message)
{
	std::list<Users>::iterator it = _users.begin();
	std::advance(it, userIndex);

	if (it != _users.end())
		_channels[0].broadcastMessage(message, *it);
}


void Server::run()
{
	std::cout << GREEN << "Server is running on port " << _port << RESET << std::endl;
	_addrlen = sizeof(struct sockaddr_in);

	while (true)
	{
		std::list<struct pollfd> fds;
		fds.push_back(_fds.front());
		for (std::list<Users>::iterator it = _users.begin(); it != _users.end(); ++it)
			fds.push_back(it->getFd());

		std::vector<struct pollfd> fds_vector(fds.begin(), fds.end());

		int ret = poll(&fds_vector[0], fds_vector.size(), TIMEOUT);

		if (ret < 0)
		{
			std::cerr << RED << "Poll error!" << RESET << std::endl;
			break;
		}
		else if (ret > 0)
		{
			// Accept new connection and handle it
			if (fds_vector[0].revents & POLLIN)
			{
				int client_socket = accept(_server_fd, (struct sockaddr *)&_address, (socklen_t*)&_addrlen);
				if (client_socket >= 0)
				{
					fcntl(client_socket, F_SETFL, O_NONBLOCK);
					std::cout << GREEN << "New client connected" << RESET << std::endl;
					handleNewConnection(client_socket);
				}
			}

			// Handle events for each user
			for (size_t i = 1; i < fds.size(); i++)
			{
				if (fds_vector[i].revents & POLLIN)
				{
					char buffer[1024] = {0};
					int valread = recv(fds_vector[i].fd, buffer, sizeof(buffer), 0);
					if (valread > 0)
					{
						buffer[valread] = '\0';
						std::cout << "Message Received: " << buffer << std::endl;
						handleMessage(i - 1, buffer);
					}
					else if (valread == 0)
					{
						std::cout << RED << "Client disconnected" << RESET << std::endl;
						close(fds_vector[i].fd);

						std::list<Users>::iterator it = _users.begin();
						std::advance(it, i - 1);

						if (it != _users.end())
							_users.erase(it);
						i--;
					}
				}
			}
		}
	}
}


Server::~Server()
{
	for (std::list<struct pollfd>::iterator it = _fds.begin(); it != _fds.end(); ++it)
	{
		if (it->fd != -1)
			close(it->fd);
	}
}
