#ifndef BUFFERABLE_H_
#define BUFFERABLE_H_

#include"Package_Buffer.h"

class ConstBufferable{	//This is constant operator interface...

public:

	virtual void operator<<( AeternalBuffer& buffer) const noexcept = 0;
};


class Bufferable{	//This is non-constant operator interface...

public:

	virtual void operator<<( AeternalBuffer& buffer) noexcept = 0;
};

#endif /* BUFFERABLE_H_ */
