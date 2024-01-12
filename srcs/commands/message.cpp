/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:59:42 by ndiamant          #+#    #+#             */
/*   Updated: 2024/01/12 14:06:35 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Users.hpp"
#include "../../includes/Server.hpp"
#include "../../includes/Channels.hpp"

void handleMessageCommand(const char* message, Users *sender, Server *server)
{
	(void) message;
	(void) sender;
	(void) server;

	std::string privmsg = message;
	std::istringstream iss(privmsg);
	std::string command, destination, content;
	int isUser = 1;
	int isChannel = 1;
	
	if (!(iss >> command >> destination >> content))
	{
		// Invalid format
		return;
	}
	Channels* channel = server->getChannelByName(destination);
	if (!channel)
	{
		isChannel = 0;
		// Invalid channel
	}
	Users* user = server->getUserByNickname(destination);
	if (user == NULL)
	{
		isUser = 0;
		// Invalid user
	}
	if (isUser)
	{
		std::string formattedMessage = CYN + sender->getNickname() + " messaged you" + RESET + ": " + content + "\n";
		send(user->getSocket(), formattedMessage.c_str(), formattedMessage.size() + 1, 0);
	}
	if (isChannel)
	{
		std::string formattedMessage = CYN "messaged the channel" RESET ": " + content + "\n";
		channel->broadcastMessage(formattedMessage, *sender);
	}
}
