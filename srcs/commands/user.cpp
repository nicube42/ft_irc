/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:57:28 by ndiamant          #+#    #+#             */
/*   Updated: 2024/01/12 14:58:42 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Users.hpp"
#include "../../includes/Server.hpp"
#include "../../includes/Channels.hpp"

void handleUserCommand(const char* message, Users *sender, Server *server)
{
	(void) server;
	// Check if the user is already registered
	if (sender->isRegistered())
	{
		// Send error message for already registered users
		std::string errMsg = "ERROR :You are already registered\r\n";
		send(sender->getSocket(), errMsg.c_str(), errMsg.size(), 0);
		return;
	}

	std::string msg(message);

	// Expected format: USER <username> <hostname> <servername> :<realname>
	std::istringstream iss(msg.substr(5)); // Skip "USER "
	std::string username, hostname, servername, realname;
	iss >> username >> hostname >> servername;
	
	// Extract realname (which may contain spaces and starts with a colon)
	std::size_t colonPos = msg.find(" :", iss.tellg());
	if (colonPos != std::string::npos) {
		realname = msg.substr(colonPos + 2); // Skip " :"
	}

	// Check if all required parameters were provided
	if (username.empty() || hostname.empty() || servername.empty() || realname.empty()) {
		std::string errMsg = "ERROR :Not enough parameters\r\n";
		send(sender->getSocket(), errMsg.c_str(), errMsg.size(), 0);
		return;
	}

	// Set user details
	sender->setUsername(username);
	sender->setRealname(realname);
	if (sender->getNickname() != "default")
		sender->setRegistered(true);
}
