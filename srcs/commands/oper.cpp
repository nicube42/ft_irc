/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:08:40 by ndiamant          #+#    #+#             */
/*   Updated: 2024/01/16 13:00:40 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Users.hpp"
#include "../../includes/Server.hpp"
#include "../../includes/Channels.hpp"


/*
   The channel operator (also referred to as a "chop" or "chanop") on a
   given channel is considered to 'own' that channel.  In recognition of
   this status, channel operators are endowed with certain powers which
   enable them to keep control and some sort of sanity in their channel.
   As an owner of a channel, a channel operator is not required to have
   reasons for their actions, although if their actions are generally
   antisocial or otherwise abusive, it might be reasonable to ask an IRC
   operator to intervene, or for the usersjust leave and go elsewhere
   and form their own channel.

   The commands which may only be used by channel operators are:

        KICK    - Eject a client from the channel
        MODE    - Change the channel's mode
        INVITE  - Invite a client to an invite-only channel (mode +i)
        TOPIC   - Change the channel topic in a mode +t channel




Oikarinen & Reed                                                [Page 6]

RFC 1459              Internet Relay Chat Protocol              May 1993


   A channel operator is identified by the '@' symbol next to their
   nickname whenever it is associated with a channel (ie replies to the
   NAMES, WHO and WHOIS commands).



         Command: OPER
   Parameters: <user> <password>

   OPER message is used by a normal user to obtain operator privileges.
   The combination of <user> and <password> are required to gain
   Operator privileges.

   If the client sending the OPER command supplies the correct password
   for the given user, the server then informs the rest of the network
   of the new operator by issuing a "MODE +o" for the clients nickname.

   The OPER message is client-server only.

   Numeric Replies:

           ERR_NEEDMOREPARAMS              RPL_YOUREOPER
           ERR_NOOPERHOST                  ERR_PASSWDMISMATCH

   Example:

   OPER foo bar                    ; Attempt to register as an operator
                                   using a username of "foo" and "bar" as
                                   the password.
*/

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
