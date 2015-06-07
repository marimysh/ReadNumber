#ifndef TPOOL_H
#define TPOOL_H

#include <iostream>
#include <vector>
#include "tinstance.h"
#include <fstream>

class TPool
{
public:
	std::vector <TInstance> Pool;
	void ReadLearn (const std::string &path, int count);
	void ReadTest (const std::string &path, int countBegin, int count);
	TPool();
	~TPool();
};

#endif // TPOOL_H
