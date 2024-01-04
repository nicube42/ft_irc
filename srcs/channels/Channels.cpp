/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channels.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:19:14 by ndiamant          #+#    #+#             */
/*   Updated: 2024/01/04 19:23:35 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Channels.hpp"

Channels::Channels(const std::string &name) : _name(name)
{
}

void Channels::addUser(Users *user)
{
	if (!user) return;

	for (std::list<Users*>::iterator it = _users.begin(); it != _users.end(); ++it)
	{
		if (*it == user)
		return;
	}
	_users.push_back(user);
}

void Channels::removeUser(Users *user)
{
    _users.remove(user);
}

void Channels::broadcastMessage(const std::string &message, Users &sender)
{
	std::string formattedMessage = sender.getNickname() + ": " + message;
	for (std::list<Users*>::iterator it = _users.begin(); it != _users.end(); ++it)
	{
		Users* user = *it;
		if (user != &sender)
		{
			int fd = user->getFd().fd;
			send(fd, formattedMessage.c_str(), formattedMessage.size() + 1, 0);
		}
	}
}

const std::string &Channels::getName() const
{
	return (_name);
}
