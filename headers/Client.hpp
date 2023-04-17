/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edos-san <edos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 21:32:55 by edos-san          #+#    #+#             */
/*   Updated: 2023/04/17 13:32:40 by edos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "Map.hpp"

typedef struct pollfd t_socket;

class Server;

class Client {

	private:
		int					  _fd;
		int					  _index_fd;
		std::string 		  _hostname;
		std::string 		  _nickname;
		std::string			  _position;
		bool 				  _isConnect;
		Map 				  *_map;
		Client();

	public:
		Client(int fd, int index, std::string hostname);
		~Client();
		void receiver();
		bool run();
		void setNickname(const std::string& nickname);
		void	setMap(Map *map);
		std::string getPrefix() const;

		void setConnect(bool status){
			_isConnect = status;
		};

		std::string &getHostname()
		{
			return _hostname;
		};

		Map *getMap();

		std::string &getNickname(){
			return _nickname;
		};

	
		std::string &getPosition(){
			return _position;
		};

		void setPosition(const std::string& data){
			_position = data;
		};

		int getFd(){
			return _fd;
		};

		int getIndexFd(){
			return _index_fd;
		};

		bool isConnect(){
			return _isConnect;
		};

		static bool isNickname(std::map<int, Client *> clients, Client *client);
		
};	


#endif
