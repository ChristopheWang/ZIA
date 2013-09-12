#include <iostream>
#include <string.h>
#include "SocketUnix.h"

SocketUnix::SocketUnix(int _port)
  : port(_port)
{
  std::cout << "Systeme d'exploitation detecte: Unix" << std::endl;
}

int			SocketUnix::init()
{
  struct protoent	*pe = getprotobyname("TCP");
  int				on = 1;

  if ((this->listenSocket = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    {
      std::cerr << "Socket error" << std::endl;
      return (-1);
    }
  setsockopt(this->listenSocket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
  memset(&this->serverAddr, 0, sizeof(this->serverAddr));
  this->serverAddr.sin_family = AF_INET;
  this->serverAddr.sin_port = htons(this->port);
  this->serverAddr.sin_addr.s_addr = INADDR_ANY;
  if (bind(this->listenSocket, (struct sockaddr *)&this->serverAddr, sizeof(this->serverAddr)) == -1)
    {
      std::cerr << "Bind error" << std::endl;
      return (-1);
    }
  if (listen(this->listenSocket, SOMAXCONN) == -1)
    {
      std::cerr << "Listen error" << std::endl;
      return (-1);
    }
  std::cout << "Unix Socket Init Complete" << std::endl;
  return (this->listenSocket);
}

void			SocketUnix::quit()
{
  shutdown(this->listenSocket, SHUT_RDWR);
  close(this->listenSocket);
}
