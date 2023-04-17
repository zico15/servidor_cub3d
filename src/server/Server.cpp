/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edos-san <edos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 21:36:54 by edos-san          #+#    #+#             */
/*   Updated: 2023/04/17 22:19:55 by edos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/poll.h>
#include "Server.hpp"
#include "Client.hpp"
#include "Msg.hpp"
#include "Util.hpp"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <string.h>

Server::Server(){
    
}

Server::Server(std::string hostname, int port, std::string password): _password(password)
{
    std::cout << "\x1B[2J\x1B[HServer has been created: " << port << " password: " << password << "\n";
    init(SERVER, hostname, port, 200);

    //Server
    on("FD", &Server::fd);
    on("PS", &Server::position);
    on("QUIT", &Server::quit);
    on("NOTICE", &Server::notice);
    on("NEW", &Server::newplayer);
    on("RT", &Server::notice);
    addMap("Test");
    //Client

    //Map
}

/*
*/
void Server::newplayer(Server *server, Client *client, std::string data)
{
    data = "NEW " + data;

    client->setPosition("PS" + data.substr(3));
    if (client->getMap())
    {    
        client->getMap()->send(server, client, data);
        client->getMap()->newPlayer(server, client);
    }
}

/*
*/
void Server::position(Server *server, Client *client, std::string data)
{
    data = "PS " + data;
    client->setPosition(data);
    if (client->getMap()) 
        client->getMap()->send(server, client, data);   
}


/*
/quit               quit irc
*/
void Server::quit(Server *server, Client *client, std::string data)
{
    server->deleteClient(client);
}


//The function in bellow will send the message: "PONG :data" read for information here: 4.6.3 Pong message
void Server::fd(Server *server, Client *client, std::string data)
{
    data = "FD: " +  ft_itoa(client->getFd());
    std::cout <<  data<< "\n";
    server->send(client, data);

}


void Server::notice(Server *server, Client *client, std::string data)
{
    // (void)client;

	std::cout << "notice: " << data << std::endl;
    // std::string target = data.substr(0, (data.find(" ")));
    // std::string message = ":test NOTICE " + target;
    // message += data.substr(data.find(" "), data.size());
    // //std::cout << "O valor-------->" << message << "\n";
    // if (server->getMaps()[target])
    //     server->getMaps()[target]->send(server, NULL, message);
    // else if (server->getClient(target))
    //     server->send(server->getClient(target), message);
}

void Server::connect()
{
    struct sockaddr_in clientAddr;
	socklen_t clientAddrLen = sizeof(clientAddr);
	
	int fd_client = accept(_fd,  (struct sockaddr *) &clientAddr, &clientAddrLen);
    if (fd_client < 0)
		return ;
	std::string hostname = inet_ntoa(clientAddr.sin_addr);
    
	std::cout << "IP: " << hostname << std::endl;
	
	for (int i = 1; i < getMaxConnecting(); i++)
    {
        if (getSocket(i).fd == -1)
		{
			setEvent(i, fd_client, POLLIN | POLLHUP);
            Client *client =  new Client(getSocket(i).fd, i, hostname);
            addClient(i, client);
            getMap("Test")->add(client, this);
			break;
		}
    }
    setEvent(0, getFd(), POLLIN | POLLOUT | POLLHUP);
}

void Server::execute(Client *client, std::string event, std::string data)
{

	function fun = _events[event];
	if (!fun)  
        send(client, ERR_UNKNOWNERROR(data));
    else
        (fun)(this, client, data);
}

void Server::sendAll(Client *client,  std::string data)
{
    std::map<int, Client *>::iterator it;

    for (it = _clients.begin(); it != _clients.end(); it++)
    {
        if ((*it).second != client)
            send((*it).second, data);
    }
}

void Server::send(Client *client, std::string data)
{
    if (!client)
        return ;
   emit(client->getIndexFd(), data + "\r\n");
}

std::string &Server::getPassword(){
	return _password;
}

Map *Server::addMap(std::string const name)
{
    Map *channel = getMap(name);
    if (!channel)
        channel = new Map(name);
    _channels[name] = channel;
    return channel;
}

std::map<std::string, Map *> &Server::getMaps(){
    return _channels;
}

Map *Server::getMap(std::string name){

    std::map<std::string, Map *>::iterator it = _channels.find(name);

    return (*it).second;
}

void Server::acceptNewConnection(Server *server, Client *client)
{
    server->send(client, RPL_WELCOME(client->getNickname()));
};

Server::~Server()
{
    _is_run = false;
    { 
        std::map<int, Client *>::iterator it;
        for (it = _clients.begin(); it != _clients.end(); it++){
            close((*it).second->getFd());
            setEvent((*it).second->getIndexFd(), -1, 0, 0);
            delete (*it).second;
        }
    }
    {
        std::map<std::string, Map *>::iterator it;
        for (it = _channels.begin(); it != _channels.end(); it++){
            delete (*it).second;
        }
    }
    std::cout << "~Server\n";
}
