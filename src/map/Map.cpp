/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:46:22 by edos-san          #+#    #+#             */
/*   Updated: 2023/04/11 19:28:54 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include "Map.hpp"
#include "Server.hpp"
#include "Msg.hpp"
#include "Client.hpp"
#include "Util.hpp"

Map::Map(std::string	name): _name(name)
{
    std::cout << "\033[35mNew Map: " << name << "\033[0m" << std::endl;
}


Map::~Map()
{
    
}

void Map::add(Client *client, Server *server) {
    (void) client;
    (void) server;
}


void Map::remove(Server *server, Client *client){
    std::vector<Client *>::iterator it;

    (void) server;
    for (it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (client == *it)
        {
        
            break ;
        }
    }

}

std::string Map::getName()
{
  return (_name);
}

std::vector<Client *> &Map::getClients()
{
    return _clients;
}

size_t Map::getSize()
{
    return (_clients.size());
}

void Map::send(Server *server, Client *client, std::string message)
{
    std::vector<Client *>::iterator it;
    
    for (it = _clients.begin(); it < _clients.end(); ++it)
    {
        if (!*it || client == (*it))
            continue ;
        server->send((*it), message);
    }
}

