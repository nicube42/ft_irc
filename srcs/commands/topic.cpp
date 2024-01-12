/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:54:54 by ndiamant          #+#    #+#             */
/*   Updated: 2024/01/08 19:52:28 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Users.hpp"
#include "../../includes/Server.hpp"
#include "../../includes/Channels.hpp"

void handleTopicCommand(const char* message, Users *sender, Server *server)
{
    std::string channel;
    std::string topic;

    std::istringstream iss(message);
    iss >> channel >> topic;
	if (!channel.empty() && channel[channel.length() - 1] == '\n')
		channel.erase(channel.length() - 1);
	if (!topic.empty() && topic[topic.length() - 1] == '\n')
		topic.erase(topic.length() - 1);
    if (topic.empty())
    {
		std::string toSend = server->getChannelByName(channel)->getTopic() + "\n";
		send(sender->getSocket(), toSend.c_str(), toSend.size() + 1, 0);
		std::cout << server->getChannelByName(channel)->getTopic() << std::endl;
    }
	else if (topic == "-")
	{
		server->getChannelByName(channel)->setTopic("");
    }
	else
	{
		server->getChannelByName(channel)->setTopic(topic);
    }
}
