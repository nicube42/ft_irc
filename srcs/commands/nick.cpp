/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:53:30 by ndiamant          #+#    #+#             */
/*   Updated: 2024/01/05 13:56:38 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Users.hpp"
#include "../../includes/Server.hpp"
#include "../../includes/Channels.hpp"

void handleNickCommand(const char* message, Users *sender, Server *server)
{
	(void) server;
	std::string nickname = message + 5;
	if (!nickname.empty() && nickname[nickname.length() - 1] == '\n')
		nickname.erase(nickname.length() - 1);
	sender->setNickname(nickname);
}
