#include <iostream>
#include <string>
#include "Server.h"

Server::Server(int _port)
  : port(_port), status(false)
{
  socket = NULL;
#ifdef	_WIN32
  socket = new SocketWin(port);
#else
  socket = new SocketUnix(port);
#endif
}

Server::~Server()
{
  delete socket;
}

int				Server::launch()
{
  if ((listenSocket = socket->init()) == -1)
    {
		std::cerr << "Echec de l'initialisation du serveur !" << std::endl;
		return (-1);
    }
  clientList = new Client[LIMIT];
  memset(fd_type, FD_FREE, LIMIT);
  fd_type[listenSocket] = FD_SERVER;
  fct_write[listenSocket] = &Server::server_send;
  fct_read[listenSocket] = &Server::server_recv;
  status = true;
  std::cout << "Serveur demarre sur le port: " << port << std::endl;
  while (status)
    {
      FD_ZERO(&fd_read);
      FD_ZERO(&fd_write);
      if (select(get_fdmax() + 1, &fd_read, &fd_write, NULL, NULL) == -1)
		{
			std::cerr << "Select error" << std::endl;
			return (-1);
		}
      check_fd();
    }
  socket->quit();
  delete [] clientList;
  return (0);
}

int  	      	Server::get_fdmax()
{
  int			i;
  int	      	fd_max;

  i = 0;
  fd_max = 0;
  while (i < LIMIT)
    {
      if (fd_type[i] != FD_FREE)
		{
			FD_SET(i, &fd_read);
			fd_max = i;
		}
      i++;
    }
  return (fd_max);
}

void	     	Server::check_fd()
{
  int	       	i;
  int	       	cs;

  i = 0;
  while (i < LIMIT)
    {
      if (FD_ISSET(i, &fd_read))
		{
			if ((cs = (this->*fct_read[i])(i)) < LIMIT)
				FD_SET(i, &fd_write);
		}
      if (FD_ISSET(i, &fd_write))
		(this->*fct_write[i])(cs);
      i++;
    }
}

int	       		Server::server_send(int cs)
{
  if (cs < LIMIT)
    {
      fct_write[cs] = &Server::client_send;
      send(cs, "Bienvenue, vous etes connecte au serveur ZIA\n", strlen("Bienvenue, vous etes connecte au serveur ZIA\n"), 0);
    }
  return (0);
}

int    			Server::server_recv(int s)
{
  SOCKADDR_IN	clientAddr;
  socklen_t		clientAddrLen;
  int			cs;

  clientAddrLen = sizeof(clientAddr);
  if ((cs = accept(s, (SOCKADDR *)&clientAddr, &clientAddrLen)) == -1)
    {
      std::cerr  << "Accept error" << std::endl;
      return (-1);
    }
  if (cs < LIMIT)
    {
      clientList[cs].setCs(cs);
      std::cout << "Connection client " << cs << ": " << inet_ntoa(clientAddr.sin_addr) << std::endl;
      fd_type[cs] = FD_CLIENT;
      fct_read[cs] = &Server::client_recv;
    }
  else
    {
      send(cs, "<Server>: Clients max atteints", strlen("<Server>: Clients max atteints"), 0);
      closesocket(cs);
    }
  return (cs);
}

int	       		Server::client_recv(int cs)
{
	memset(&clientList[cs].buffer, 0, BUFF_SIZE);
	clientList[cs].nb_read = recv(cs, clientList[cs].buffer, BUFF_SIZE, 0);
	if (clientList[cs].nb_read > 0)
		std::cout << "Client[" << cs << "]: " << clientList[cs].buffer;
	return (cs);
}

int		Server::client_send(int cs)
{
  if (clientList[cs].nb_read <= 0)
    {
      std::cout << "Deconnection client:" << cs << std::endl;
      closesocket(cs);
      fd_type[cs] = FD_FREE;
    }
  else
  {
	  std::cout << "Envoie de reponse HTTP: " << std::endl;
	  send(cs, "HTTP/1.1 200 OK\r\nDate: Thu, 11 Jan 2007 14:00:36 GMT\r\nServer: Apache/2.0.54 (Debian GNU/Linux) DAV/2 SVN/1.1.4\r\nConnection: close\r\nTransfer-Encoding: chunked\r\nContent-Type: text/html; charset=ISO-8859-1\r\n\r\n178a1\r\n\r\n", strlen("HTTP/1.1 200 OK\r\nDate: Thu, 11 Jan 2007 14:00:36 GMT\r\nServer: Apache/2.0.54 (Debian GNU/Linux) DAV/2 SVN/1.1.4\r\nConnection: close\r\nTransfer-Encoding: chunked\r\nContent-Type: text/html; charset=ISO-8859-1\r\n\r\n178a1\r\n\r\n"), 0);
  }
  return (0);
}