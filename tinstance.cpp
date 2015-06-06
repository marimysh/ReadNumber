#include "tinstance.h"

void TInstance::SplittoInt2(std::string input, std::vector<int>* out,
								  std::string separator)
{
	size_t pos = 0;
	std::string token;
	while ((pos = input.find(separator)) != std::string::npos) {
		token = input.substr(0, pos);
		out->push_back (atoi(token.c_str ()));
		input.erase(0, pos + separator.length());
	}
	out->push_back (atof(token.c_str ()));
	return;
}

void TInstance::SplittoDouble(std::string input, std::vector<double>* out,
								  std::string separator)
{
	size_t pos = 0;
	std::string token;
	while ((pos = input.find(separator)) != std::string::npos) {
		token = input.substr(0, pos);
		out->push_back (atof(token.c_str ()));
		input.erase(0, pos + separator.length());
	}
	out->push_back (atof(token.c_str ()));
	return;
}

void TInstance::FromString(std::string st)
{
	goal = -1;
	this->SplittoDouble (st, &this->features, ",");
}

int TInstance::getGoal() const
{
	return goal;
}

void TInstance::FromString(int number, const std::string st)
{
	this->goal = number;
	this->SplittoDouble (st, &features, ",");
}

std::string TInstance::ToString()
{
	std::string res;
	res = std::to_string(this->goal);
	for (size_t i = 0; i < this->features.size(); ++i)
		res += std::to_string(this->features.at(i)) + ",";
	return res;
}

TInstance::TInstance()
{
}

TInstance::~TInstance()
{

}

