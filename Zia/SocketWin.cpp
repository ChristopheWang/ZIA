#include <iostream>
#include "SocketWin.h"

SocketWin::SocketWin(int _port)
  : port(_port)
{
  std::cout << "Systeme d'exploitation detecte: Windows" << std::endl;
}

int					SocketWin::init()
{
  WSADATA			wsaData;
  int				on = 1;

  if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
      std::cerr << "WSAStartup error: "<< WSAGetLastError() << std::endl;
      return (-1);
    }
  if ((listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    {
      std::cerr << "Socket error: " << WSAGetLastError() << std::endl;
      WSACleanup();
      return (-1);
    }
  setsockopt(this->listenSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(port);
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  if (bind(listenSocket, (SOCKADDR *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
      std::cerr << "Bind error: " << WSAGetLastError() << std::endl;
      WSACleanup();
      return (-1);
    }
  if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
    {
      std::cerr << "Listen: " << WSAGetLastError() << std::endl;
      WSACleanup();
      return (-1);
    }
  std::cout << "Windows Socket Init Complete" << std::endl;
  return (listenSocket);
}

void				SocketWin::quit()
{
  shutdown(listenSocket, SD_BOTH);
  closesocket(listenSocket);
  WSACleanup();
}
