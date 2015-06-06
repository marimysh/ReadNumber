#ifndef LEARN_H
#define LEARN_H


class Learn
{
public:
	int number;
	std::vector <float> features;
	static TInstance FromTestString(const string& s);
	static TInstance FromLearnString(const string& s);
	string ToString() const;
	Learn();
	~Learn();
};

#endif // LEARN_H
