#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <iostream>
#define	BUFF_SIZE	1024

class				Client
{
 private:
	int		      	cs;
	std::string		login;
 public:
	Client();
	~Client();
public:
	int				nb_read;
	char			buffer[BUFF_SIZE];
	void			setCs(int);
	void			setLogin(std::string);
	int  			getCs();
	std::string		getLogin();
};

#endif