/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channels.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:16:43 by ndiamant          #+#    #+#             */
/*   Updated: 2024/01/04 19:08:41 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNELS_HPP

# define CHANNELS_HPP

#pragma once

#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <sys/socket.h>
#include "Users.hpp"

class Users;

class Channels
{
private:
    std::string _name;
    std::list<Users *> _users; // Changed from vector to list

public:
    Channels(const std::string &name);

    void addUser(Users *user);
    void removeUser(Users *user);
    void broadcastMessage(const std::string &message, Users &sender);

    const std::string& getName() const;
};

#endif
