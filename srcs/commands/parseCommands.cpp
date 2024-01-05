/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseCommands.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:00:56 by ndiamant          #+#    #+#             */
/*   Updated: 2024/01/05 15:16:29 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <cstring>
#include "../../includes/Server.hpp"
#include "../../includes/Users.hpp"

void handleJoinCommand(const char* message, Users *sender, Server *server);
void handleNickCommand(const char* message, Users *sender, Server *server);
void handleOperCommand(const char* message, Users *sender, Server *server);
void handleKickCommand(const char* message, Users *sender, Server *server);
void handleInviteCommand(const char* message, Users *sender, Server *server);


enum CommandType
{
	UNKNOWN,
	KICK,
	INVITE,
	TOPIC,
	MODE,
	JOIN,
	NICK,
	OPER,
	QUIT
};

CommandType checkIrcCommand(const char* message)
{
	if (std::strncmp(message, "KICK", 4) == 0) return KICK;
	else if (std::strncmp(message, "JOIN", 4) == 0) return JOIN;
	else if (std::strncmp(message, "INVITE", 6) == 0) return INVITE;
	else if (std::strncmp(message, "TOPIC", 5) == 0) return TOPIC;
	else if (std::strncmp(message, "MODE", 4) == 0) return MODE;
	else if (std::strncmp(message, "NICK", 4) == 0) return NICK;
	else if (std::strncmp(message, "OPER", 4) == 0) return OPER;
	else if (std::strncmp(message, "QUIT", 4) == 0) return QUIT;

	return UNKNOWN;
}

int parseCommands(const char* message, Users *sender, Server *server)
{
	CommandType cmdType = checkIrcCommand(message);

	switch(cmdType)
	{
		case JOIN:
			handleJoinCommand(message, sender, server);
			break;
		case NICK:
			handleNickCommand(message, sender, server);
			break;
		case OPER:
			handleOperCommand(message, sender, server);
			break;
		case QUIT:
			
			break;
		case KICK:
			handleKickCommand(message, sender, server);
			break;
		case INVITE:
			handleInviteCommand(message, sender, server);
			break;
		case TOPIC:

			break;
		case MODE:

			break;

		default:
			return (0);
	}
	return (1);
}
