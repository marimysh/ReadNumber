#ifndef TLEANER_H
#define TLEANER_H

#include "tlinermodel.h"
#include "tpool.h"

class TLeaner
{
public:
	TLeaner();
	~TLeaner();
	virtual TLinerModel Learn (const TPool &pool, int number = -1);
};

#endif // TLEANER_H
