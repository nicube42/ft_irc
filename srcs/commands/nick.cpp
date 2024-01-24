/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:53:30 by ndiamant          #+#    #+#             */
/*   Updated: 2024/01/24 15:09:03 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Users.hpp"
#include "../../includes/Server.hpp"
#include "../../includes/Channels.hpp"
#include "../../includes/replies.hpp"
#include <regex>

/*
4.1.2 Nick message

      Command: NICK
   Parameters: <nickname> [ <hopcount> ]

   NICK message is used to give user a nickname or change the previous
   one.  The <hopcount> parameter is only used by servers to indicate
   how far away a nick is from its home server.  A local connection has
   a hopcount of 0.  If supplied by a client, it must be ignored.

   If a NICK message arrives at a server which already knows about an
   identical nickname for another client, a nickname collision occurs.
   As a result of a nickname collision, all instances of the nickname
   are removed from the server's database, and a KILL command is issued
   to remove the nickname from all other server's database. If the NICK
   message causing the collision was a nickname change, then the
   original (old) nick must be removed as well.

   If the server recieves an identical NICK from a client which is
   directly connected, it may issue an ERR_NICKCOLLISION to the local
   client, drop the NICK command, and not generate any kills.

   Numeric Replies:

           ERR_NONICKNAMEGIVEN             ERR_ERRONEUSNICKNAME
           ERR_NICKNAMEINUSE               ERR_NICKCOLLISION

   Example:

   NICK Wiz                        ; Introducing new nick "Wiz".

   :WiZ NICK Kilroy                ; WiZ changed his nickname to Kilroy.
*/

void handleNickCommand(const char* message, Users *sender, Server *server)
{
	(void) server;
	std::string nickMessage(message);
	if (nickMessage.length() <= 6)
	{
		send(sender->getSocket(), ERR_NONICKNAMEGIVEN(std::to_string(sender->getSocket())).c_str(), 
			ERR_NONICKNAMEGIVEN(std::to_string(sender->getSocket())).length(), 0);
		return;
	}
	std::string nickname = nickMessage.substr(5);
	nickname.erase(std::remove(nickname.begin(), nickname.end(), '\r'), nickname.end());
	nickname.erase(std::remove(nickname.begin(), nickname.end(), '\n'), nickname.end());

	std::regex nicknameRegex("^[a-zA-Z][a-zA-Z0-9\\[\\]\\-\\\\\\^\\{\\}\\|]*$");

	if (!std::regex_match(nickname, nicknameRegex))
	{
		send(sender->getSocket(), ERR_ERRONEUSNICKNAME(std::to_string(sender->getSocket()), sender->getNickname()).c_str(),
		ERR_ERRONEUSNICKNAME(std::to_string(sender->getSocket()), sender->getNickname()).length(), 0);
		return;
	}

	if (server->getUserByNickname(nickname))
	{
		send(sender->getSocket(), ERR_NICKNAMEINUSE(std::to_string(sender->getSocket()), sender->getNickname()).c_str(),
				ERR_NICKNAMEINUSE(std::to_string(sender->getSocket()), sender->getNickname()).length(), 0);
		return;
	}
	
	sender->setNickname(nickname);
	// if (sender->getUsername() != "default")
	// {
	// 	sender->setRegistered(true);
	// 	std::cout << "User registered" << std::endl;
	// }
}
