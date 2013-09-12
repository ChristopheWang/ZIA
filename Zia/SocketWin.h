#ifndef		__SOCKETWIN_H__
#define		__SOCKETWIN_H__

#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include "ISocketAbstract.h"

class				SocketWin : public ISocketAbstract
{
private:
	int				port;
	int				listenSocket;
	SOCKADDR_IN		serverAddr;
public:
	SocketWin(int);
	virtual ~SocketWin() {}
public:
	virtual int		init();
	virtual void	quit();
};

#endif