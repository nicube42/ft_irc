/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 19:02:18 by ndiamant          #+#    #+#             */
/*   Updated: 2024/01/12 14:11:42 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Users.hpp"
#include "../../includes/Server.hpp"
#include "../../includes/Channels.hpp"

void handlePingCommand(const char* message, Users *sender, Server *server)
{
	(void)	server;
	std::string fullMessage(message);

	std::size_t spacePos = fullMessage.find(' ');
	if (spacePos != std::string::npos)
	{
		std::string serverIdentifier = fullMessage.substr(spacePos + 1);

		std::string pongResponse = "PONG " + serverIdentifier + "\r\n";

		send(sender->getSocket(), pongResponse.c_str(), pongResponse.size(), 0);
	}
}
