#ifndef		__SERVER_H__
#define		__SERVER_H__

#ifdef		_WIN32
#include	"SocketWin.h"
#define		socklen_t int
#else
#include	"SocketUnix.h"
#define		closesocket close
#endif

#include <iostream>
#include "Client.h"

#define	FD_FREE		0
#define	FD_SERVER	1
#define	FD_CLIENT	2
#define	LIMIT		256
#define	BUFF_SIZE	1024

class					Server
{
	typedef int (Server::*fct)(int);
private:
	ISocketAbstract		*socket;
	Client		       	*clientList;
	int			   		port;
	int  				listenSocket;
	bool				status;
	char				fd_type[LIMIT];
	fct	       			fct_write[LIMIT];
	fct	       			fct_read[LIMIT];
	fd_set       		fd_read;
	fd_set       		fd_write;
public:
	Server(int);
	~Server();
public:
	int	       			launch();
	int	       			get_fdmax();
	void				check_fd();
	int  				server_recv(int);
	int  				server_send(int);
	int  				client_recv(int);
	int  				client_send(int);
};

#endif