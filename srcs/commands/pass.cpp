/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:58:29 by ndiamant          #+#    #+#             */
/*   Updated: 2024/01/12 15:11:03 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Users.hpp"
#include "../../includes/Server.hpp"
#include "../../includes/Channels.hpp"

void handlePassCommand(const char* message, Users *sender, Server *server)
{
	// Extract the password from the message
	std::string password = std::string(message).substr(5); // Assuming "PASS " is 5 characters

	// Check if the user is already registered
	if (sender->isRegistered() == 0)
	{
		// Send error message for already registered users
		std::string errMsg = "ERROR :You are already registered\r\n";
		send(sender->getSocket(), errMsg.c_str(), errMsg.size(), 0);
		return;
	}

	// Verify the password
	if (password != server->getPassword()) {
		// Handle incorrect password case, maybe by closing the connection or sending an error message
		std::string errMsg = "ERROR :Incorrect password\r\n";
		send(sender->getSocket(), errMsg.c_str(), errMsg.size(), 0);
		return;
	}

	// If the password is correct, set the user as registered
	sender->setRegistered(true);
}
