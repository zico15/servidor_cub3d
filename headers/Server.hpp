/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edos-san <edos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 20:37:00 by ezequeil          #+#    #+#             */
/*   Updated: 2023/04/17 20:51:52 by edos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <time.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <vector>
#include "Socket.hpp"

class Map;

class Server: public Socket {

	private:
		std::map<std::string, Map *> 	_channels;
		std::string						_password;

	public:
		Server();
		Server(std::string name, int port, std::string password);
		~Server();
		void send(Client *client, std::string data);
		void sendAll(Client *clientIgnore, std::string data);
		void execute(Client *client, std::string event, std::string data = "");
		void connect();
		std::string &getPassword();
		std::map<std::string, Map *> &getMaps();
		Map *getMap(std::string name);
	
		static void	acceptNewConnection(Server *server, Client *client);
		static void errorcommand(Server *server, Client *client, std::string data);
		static void help(Server *server, Client *client, std::string data);
		
		static void quit(Server *server, Client *client, std::string data);
		static void	fd(Server *server, Client *client, std::string data);
		static void	notice(Server *server, Client *client, std::string data);
		static void position(Server *server, Client *client, std::string data);
		static void newplayer(Server *server, Client *client, std::string data);
		
		Map 	*addMap(std::string const name);
};

#endif
