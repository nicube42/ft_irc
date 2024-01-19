/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:59:42 by ndiamant          #+#    #+#             */
/*   Updated: 2024/01/16 12:47:34 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Users.hpp"
#include "../../includes/Server.hpp"
#include "../../includes/Channels.hpp"


/*
      Command: PRIVMSG
   Parameters: <receiver>{,<receiver>} <text to be sent>

   PRIVMSG is used to send private messages between users.  <receiver>
   is the nickname of the receiver of the message.  <receiver> can also
   be a list of names or channels separated with commas.

   The <receiver> parameter may also me a host mask  (#mask)  or  server
   mask  ($mask).   In  both cases the server will only send the PRIVMSG
   to those who have a server or host matching the mask.  The mask  must
   have at  least  1  (one)  "."  in it and no wildcards following the
   last ".".  This requirement exists to prevent people sending messages
   to  "#*"  or "$*",  which  would  broadcast  to  all  users; from
   experience, this is abused more than used responsibly and properly.
   Wildcards are  the  '*' and  '?'   characters.   This  extension  to
   the PRIVMSG command is only available to Operators.

   Numeric Replies:

           ERR_NORECIPIENT                 ERR_NOTEXTTOSEND
           ERR_CANNOTSENDTOCHAN            ERR_NOTOPLEVEL
           ERR_WILDTOPLEVEL                ERR_TOOMANYTARGETS
           ERR_NOSUCHNICK
           RPL_AWAY
*/

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
