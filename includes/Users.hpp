/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:18:30 by ndiamant          #+#    #+#             */
/*   Updated: 2024/01/05 15:10:08 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USERS_HPP

# define USERS_HPP

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <poll.h>
#include "Channels.hpp"

#pragma once

class Channels;

class Users
{
	private:
		std::string 		_nickname;
		int					_socket;
		struct pollfd		_fd;
		Channels*			_currentChannel;
		bool				_isOperator;
	
	public:
		Users(const int &socket);
		~Users(void);

		int	getSocket() const;
		std::string		getNickname() const;
		struct pollfd	getFd() const;
		Channels*		getCurrentChannel() const;

		void			setFd(struct pollfd fd);
		void			setNickname(const std::string &nickname);
		void			setCurrentChannel(Channels* channel);

		bool			isOperator() const;
		void			setOperator(bool isOperator);

};

#endif
