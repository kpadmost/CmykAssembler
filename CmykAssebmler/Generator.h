#ifndef GENERATOR_H
#define GENERATOR_H
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
class Generator
{
private:
	static const char variables[4];
public:
	vector<char> getBlocks(int length, int probability = 25);
	Generator() { }
	~Generator() { }
};


#endif