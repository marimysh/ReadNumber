#include "tpool.h"

void TPool::ReadLearn(const std::string &path)
{
	std::ifstream inputFile;
	inputFile.open (path);

	std::string st;
	std::getline(inputFile, st);

	while (std::getline(inputFile, st))
	{
		TInstance simple;
		simple.FromString(std::atoi(st.substr(0,1).c_str()), st.substr(2));
		this->Pool.push_back(simple);
	}
	return;
}

void TPool::ReadTest(const std::string &path)
{
	std::ifstream inputFile;
	inputFile.open (path);

	std::string st;
	std::getline(inputFile, st);

	while (std::getline(inputFile, st))
	{
		TInstance simple;
		simple.FromString(st);
		this->Pool.push_back(simple);
	}
	return;
}

TPool::TPool()
{

}

TPool::~TPool()
{

}

