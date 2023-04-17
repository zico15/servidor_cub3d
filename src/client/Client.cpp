/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edos-san <edos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 22:40:38 by edos-san          #+#    #+#             */
/*   Updated: 2023/04/17 21:59:22 by edos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Server.hpp"
#include "Msg.hpp"
#include "Util.hpp"

Client::Client(): _isConnect(false)
{
    return ;
}

Client::Client(int fd, int index, std::string hostname): _hostname(hostname)
{
    _fd = fd;
    _index_fd = index;
    _nickname = "";
    _position = "";
    _isConnect = false;
}

Client::~Client() 
{

    
}


void Client::setNickname(const std::string& nickname){
	_nickname = trim(nickname);
}


bool Client::isNickname(std::map<int, Client *> clients, Client *client)
{
    std::map<int, Client *>::iterator it;

    for (it = clients.begin(); it != clients.end(); it++)
    {
        if (client != it->second && client->getNickname().compare(it->second->getNickname()) == 0)
            return (true);
    }
    return (false);
}

void Client::setMap(Map *map)
{
    _map = map;
}

Map *Client::getMap()
{
	return _map;
}



