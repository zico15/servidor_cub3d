/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 21:32:55 by edos-san          #+#    #+#             */
/*   Updated: 2023/04/11 17:03:56 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Map_HPP
# define Map_HPP

#include <iostream>
#include <map>
#include <vector>

typedef struct pollfd t_socket;

class Client;
class Server;

class Map {

	private:
		std::string							_channel;
		std::string							_pass;
		std::vector<Client *>				_clients;
		std::vector<std::string>			_msg;
		std::string							_topic;
		std::vector<Client *>				_op;

	public:	
		Map(std::string	channel);
		Map(std::string	channel, std::string channelpass);
		~Map();
		void 				   add(Client *client, Server *server);
		void 				  remove(Server *server, Client *client);
		std::string 		  getName();
		std::vector<Client *> &getClients();
		size_t 					getSize();
		std::string 			getpass();
		std::string				getTopic() const;
		void					setTopic(std::string topic);

		bool 		isInTheMap(Client *client);
		bool		isOp(Client * client);
		void 		send(Server *server, Client *client, std::string message);
		void		rmOp(Server *server, Client *client);
		std::string nicksOnMap(void);
		
		void 		who(Server *server, Client *client);

		static void join(Server *server, Client *client, std::string data);
		static void leave(Server *server, Client *client, std::string data);
		static void list(Server *server, Client *client, std::string data);
		static void mode(Server *server, Client *client, std::string data);
		static void kick(Server *server, Client *client, std::string data);
		static void	topic(Server *server, Client *client, std::string data);

};



std::ostream& operator<<(std::ostream& os, Map *channel);


#endif
