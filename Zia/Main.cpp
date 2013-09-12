#include <iostream>
#include "Server.h"

int				main(void)
{
	Server		*serv = new Server(8080);

	serv->launch();
	delete serv;
	return (0);
}