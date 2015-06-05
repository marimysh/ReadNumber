#ifndef TPOOL_H
#define TPOOL_H

#include <iostream>
#include <vector>
#include "tinstance.h"

class TPool
{
public:
	std::vector <TInstance> Pool;
	static TPool ReadLearn (const std::string &path);
	TPool();
	~TPool();
};

#endif // TPOOL_H
