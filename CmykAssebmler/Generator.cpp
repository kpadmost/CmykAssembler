#include "Generator.h"


const char Generator::variables[4] = { 'C', 'M', 'Y', 'K' };

vector<char> Generator::getBlocks(int length, int probability)
{
	if (probability < 0 || probability > 100)
	{
		throw exception("niemozliwe!");
	}
	srand(time(0));
	vector<char>& result = vector<char>(length);
	int rn;
	result[0] = variables[rand() % 4];
	for (int i = 1; i < length; ++i)
	{
		rn = rand() % 100;
		switch (result[i - 1])
		{
			case 'C':
				result[i] = rn < probability ? 'M' : variables[rand() % 4];
				break;
			case 'M':
				result[i] = rn < probability ? 'Y' : variables[rand() % 4];
				break;
			case 'Y':
				result[i] = rn < probability ? 'K' : variables[rand() % 4];
				break;
			case 'K':
				result[i] = rn < probability ? 'C' : variables[rand() % 4];
				break;
		default:
			break;
		}
	}
	return result;
}