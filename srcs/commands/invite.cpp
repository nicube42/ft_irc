/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:11:21 by ndiamant          #+#    #+#             */
/*   Updated: 2024/01/08 18:58:07 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Users.hpp"
#include "../../includes/Server.hpp"
#include "../../includes/Channels.hpp"

void handleInviteCommand(const char* message, Users *sender, Server *server)
{
	(void) server;
	(void) sender;
	(void) message;
	// std::string inviteMessage(message);
	// std::istringstream iss(inviteMessage);
	// std::string command, nickname, channel;
	// iss >> command >> nickname >> channel;

	// // Check if the sender is a member of the channel
	// if (sender->getCurrentChannel()->getUserByName(sender->getNickname()))
	// {
	// 	// Check if the channel is invite-only and the sender is a channel operator
	// 	if (/*!server->isChannelInviteOnly(channel) || */sender->isOperator(sender))
	// 	{
	// 		// Invite the nickname to the channel
	// 		server->inviteUserToChannel(nickname, channel);
	// 	}
	// 	else
	// 	{
	// 		// Sender is not a channel operator, cannot invite other clients
	// 		// Handle error or send error message to the sender
	// 	}
	// }
	// else
	// {
	// 	// Sender is not a member of the channel, cannot invite other clients
	// 	// Handle error or send error message to the sender
	// }
}
