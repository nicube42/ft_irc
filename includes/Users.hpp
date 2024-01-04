/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:18:30 by ndiamant          #+#    #+#             */
/*   Updated: 2024/01/04 17:26:17 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USERS_HPP

# define USERS_HPP

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <poll.h>

#pragma once

class Users
{
	private:
		std::string _nickname;
		int			_socket;
		struct pollfd	_fd;
	
	public:
		Users(const int &socket);
		~Users(void);

		int	getSocket() const;
		std::string		getNickname() const;
		struct pollfd	getFd() const;

		void			setFd(struct pollfd fd);
		void			setNickname(const std::string &nickname);

};

#endif
