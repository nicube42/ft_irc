/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:30:08 by ndiamant          #+#    #+#             */
/*   Updated: 2024/01/05 14:43:25 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Users.hpp"
#include "../../includes/Server.hpp"
#include "../../includes/Channels.hpp"

void handleKickCommand(const char* message, Users *sender, Server *server)
{
	if (!sender->isOperator())
	{
		send(sender->getSocket(), RED "You are not an operator\n" RESET, 34, 0);
		return;
	}
	else
	{
		std::string kickMessage = message;
		std::istringstream iss(kickMessage);
		std::string command, username, channelName;
		
		if (!(iss >> command >> username >> channelName))
		{
			// Invalid format
			return;
		}
		Channels* channel = server->getChannelByName(channelName);
		if (!channel)
		{
			// Invalid channel
			return;
		}
		Users* user = channel->getUserByName(username);
		if (user == NULL)
		{
			// Invalid user
			return;
		}
		channel->removeUser(user);
		user->setCurrentChannel(nullptr);
	}
}
