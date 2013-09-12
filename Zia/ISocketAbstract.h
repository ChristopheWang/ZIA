#ifndef		__ISOCKETABSTRACT_H__
#define		__ISOCKETABSTRACT_H__

class		ISocketAbstract
{
public:
	virtual ~ISocketAbstract() {}

	virtual int			init() = 0;
	virtual void		quit() = 0;
};

#endif