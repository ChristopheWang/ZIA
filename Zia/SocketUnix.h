#ifndef		__SOCKETUNIX_H__
#define		__SOCKETUNIX_H__

#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include "ISocketAbstract.h"

#define SOCKADDR_IN	struct sockaddr_in
#define SOCKADDR	struct sockaddr

class					SocketUnix : public ISocketAbstract
{
private:
  int   				port;
  int					listenSocket;
  SOCKADDR_IN			serverAddr;
public:
  SocketUnix(int);
  virtual ~SocketUnix() {}

  virtual int			init();
  virtual void			quit();
};

#endif