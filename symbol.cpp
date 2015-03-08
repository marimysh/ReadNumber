#include "symbol.h"

Symbol::Symbol()
{
}

Symbol::Symbol(std::vector<int>::iterator itListImg, int width, int height)
{
	this->width = width;
	this->height = height;
	for (size_t i = 0; i < height; ++i)
	{
		std::vector<int> temp;
		for (size_t j = 0; j < width; ++j)
			temp.push_back (*itListImg);
		this->Map.push_back (temp);
	}
}

Symbol::~Symbol()
{

}

int Symbol::getwidth ()
{
	return this->width;
}
