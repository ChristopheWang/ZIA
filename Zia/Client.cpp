#include <iostream>
#include "Client.h"

Client::Client()
  : nb_read(0)
{
}

Client::~Client()
{
}

void			Client::setCs(int _cs)
{
  this->cs = _cs;
}

void			Client::setLogin(std::string _login)
{
  this->login = _login;
}

int    			Client::getCs()
{
  return (this->cs);
}

std::string		Client::getLogin()
{
  return (this->login);
}