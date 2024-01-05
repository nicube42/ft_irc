/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:08:40 by ndiamant          #+#    #+#             */
/*   Updated: 2024/01/05 15:02:22 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Users.hpp"
#include "../../includes/Server.hpp"
#include "../../includes/Channels.hpp"

void handleOperCommand(const char* message, Users *sender, Server *server)
{
	std::string operMessage = message;
	std::istringstream iss(operMessage);
	std::string command, username, password;
	
	if (!(iss >> command >> username >> password))
	{
		// Invalid format
		return;
	}
	if (password != server->getPassword())
	{
		// Invalid password
		return;
	}
	send(sender->getSocket(), GREEN "New operator\n" RESET, 23, 0);
	server->getUserByNickname(username)->setOperator(true);
}
