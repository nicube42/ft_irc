/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:13:07 by ndiamant          #+#    #+#             */
/*   Updated: 2024/01/08 19:37:08 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Users.hpp"
#include "../../includes/Server.hpp"
#include "../../includes/Channels.hpp"

void handleJoinCommand(const char* message, Users *sender, Server *server)
{
	std::string channelName = message + 5;
	if (channelName[0] != '#')
	{
		// error code
		return;
	}
	if (!channelName.empty() && channelName[channelName.length() - 1] == '\n')
		channelName.erase(channelName.length() - 1);
	Channels* channel = server->getChannelByName(channelName);
	if (!channel)
	{
		server->ensureChannelExists(channelName);
		channel = server->getChannelByName(channelName);
	}
	if (sender->getCurrentChannel())
		sender->getCurrentChannel()->removeUser(sender);
	sender->setCurrentChannel(channel);
	sender->getCurrentChannel()->addUser(sender);
}
