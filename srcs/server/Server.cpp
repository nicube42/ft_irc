/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:28:30 by ndiamant          #+#    #+#             */
/*   Updated: 2024/01/03 14:35:46 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/server/Server.hpp"

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
	//prepare poll and stock fds
	struct pollfd server_fd_struct;
	server_fd_struct.fd = _server_fd;
	server_fd_struct.events = POLLIN;
	_fds.push_back(server_fd_struct);
	return (true);
}

void Server::broadcastMessage(const char* message, int except_fd = -1)
{
	std::string init = "Message received: ";
	std::string msg = init + message + "\n";
	message = msg.c_str();
	for (size_t i = 1; i < _fds.size(); ++i)
	{
		if (_fds[i].fd != except_fd)
			send(_fds[i].fd, message, strlen(message), 0);
	}
}

void Server::run()
{
	std::cout << GREEN << "Server is running on port " << _port << RESET << std::endl;
	_addrlen = sizeof(struct sockaddr_in);

	while (true)
	{
		int ret = poll(_fds.data(), _fds.size(), TIMEOUT);

		if (ret < 0)
		{
			std::cerr << RED << "Poll error!" << RESET << std::endl;
			break;
		}
		else
		{
			if (_fds[0].revents & POLLIN)
			{
				//stock new client connection
				int client_socket = accept(_server_fd, (struct sockaddr *)&_address, (socklen_t*)&_addrlen);
				if (client_socket >= 0)
				{
					fcntl(client_socket, F_SETFL, O_NONBLOCK);
					
					std::cout << GREEN << "New client connected" << RESET << std::endl;
					struct pollfd new_client_fd;
					new_client_fd.fd = client_socket;
					new_client_fd.events = POLLIN;
					_fds.push_back(new_client_fd);
				}
			}
			for (size_t i = 1; i < _fds.size(); i++)
			{
				//handle messages from clients
				if (_fds[i].revents & POLLIN)
				{
					char buffer[1024] = {0};
					int valread = recv(_fds[i].fd, buffer, sizeof(buffer), 0);
					if (valread > 0)
					{
						buffer[valread] = '\0';
						std::cout << "Message Received: " << buffer << std::endl;
						broadcastMessage(buffer, _fds[i].fd);
					}
					else
					{
						std::cout << RED << "Client disconnected or error" << RESET << std::endl;
						close(_fds[i].fd);
						_fds.erase(_fds.begin() + i);
						i--;
					}
				}
			}
		}
	}
}

Server::~Server()
{
	for (size_t i = 0; i < _fds.size(); ++i)
	{
		if (_fds[i].fd != -1)
			close(_fds[i].fd);
	}
}
