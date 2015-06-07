#include "tpool.h"

void TPool::ReadLearn(const std::string &path, int count)
{
	std::ifstream inputFile;
	inputFile.open (path);

	std::string st;

	while (std::getline(inputFile, st) && (count-- >= 0))
	{
		TInstance simple;
		simple.FromString(std::atoi(st.substr(0,1).c_str()), st.substr(2));
		this->Pool.push_back(simple);
	}
	inputFile.close();
	return;
}

void TPool::ReadTest(const std::string &path, int countBegin, int count = 0)
{
	std::ifstream inputFile;
	inputFile.open (path);

	std::string st;
	while (std::getline(inputFile, st) && (countBegin >= 0))
		countBegin--;

	while (std::getline(inputFile, st) && (count-- > 0))
	{
		TInstance simple;
		simple.FromString(std::atoi(st.substr(0,1).c_str()), st.substr(2));
		this->Pool.push_back(simple);
	}
	inputFile.close();
	return;
}

TPool::TPool()
{

}

TPool::~TPool()
{

}

