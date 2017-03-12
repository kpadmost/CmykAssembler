#include "AlgImplementation.h"
#include "Generator.h"
#include <chrono>

void firstTribe(bool fileInputMode, const char* inf);
void secondTribe(int probability, int number, int algType);
void thirdTribe(int algType, bool approximation, int initialNumber);

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		int init = 100;
		int len = init;
		Generator g = Generator();
		AlgImplementation algor = AlgImplementation();
		algor.setData(g.getBlocks(500));
		algor.printList();
		algor.runAlg(0);
		algor.printList();
		char c;
		cin >> c;
		return 0;
		/*chrono::system_clock::time_point diff;
		int number, cmykNumber, robotStepsNumber;
		bool approximationTests = false;

		long long maxDifference, temp;
		for (int i = 0; i < 9; ++i)
		{
			if (approximationTests)
			{
				maxDifference = 0;
				for (int j = 0; j < 10; ++j)
				{
					vector<char>& vec = g.getBlocks(len);
					algor.setData(vec);
					diff = chrono::high_resolution_clock::now();
					number = algor.runAlg(0);
					temp = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - diff).count();
					if (temp > maxDifference)
					{
						maxDifference = temp;
						cmykNumber = number;
						robotStepsNumber = algor.getRobotCount();
					}

				}
			}
			else
			{
				vector<char>& vec = g.getBlocks(len);
				algor.setData(vec);
				diff = chrono::high_resolution_clock::now();
				number = algor.runAlg(0);
				maxDifference = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - diff).count();
				cmykNumber = number;
				robotStepsNumber = algor.getRobotCount();
			}


			cout << "\nlength: " << len << " czas: "
				<< maxDifference << " Cmyk number: "
				<< cmykNumber << endl << "RobotStep: " << robotStepsNumber << endl;
			len += init;
		}*/
//		char c;
		cin >> c;
		return 0;
	}

	string mode = string(argv[1]);
	if (mode == "-m1")
	{
		firstTribe(mode == "-f", argv[3]);
	}
	else if (mode == "-m2")
	{
		int probability = atoi(argv[2]);
		int number = atoi(argv[3]);
		int algType = atoi(argv[4]);
		secondTribe(probability, number, algType);

	}
	else if (mode == "-m3")
	{
		int mode = atoi(argv[2]);
		int initialNumber = atoi(argv[3]);
		thirdTribe(mode & 1, (mode & 2) > 0, initialNumber);
	}
	else
	{
		cout << "Tryb nierozpoznany!"; return -1;
	}
	return 0;
}

void firstTribe(bool fileInputMode, const char* inf)
{
	if (fileInputMode)
	{

	}
	else
	{
		string test = string(inf);
		if (test.size() < 12)
		{
			cout << "Input error!";
			return;
		}
		char c;
		vector<char>& vec = vector<char>();
		for (int i = 0; i < test.size(); ++i)
		{
			c = test[i];
			if (c != 'C' || c != 'M' || c != 'Y' || c != 'M')
			{
				cout << "Input error!";
				return;
			}
			vec.push_back(c);
		}
		AlgImplementation al = AlgImplementation();
		al.setData(vec);
		al.runAlg(1);
		al.printList();
			
	}
}

void secondTribe(int probability, int number, int algType)
{
	Generator g = Generator();
	AlgImplementation alg = AlgImplementation();
	alg.setData(g.getBlocks(number, probability));
	alg.printList();
	alg.runAlg(algType);
	alg.printList();
}

void thirdTribe(int algType, bool approximation, int initialNumber)
{
	Generator g = Generator();
	AlgImplementation algor = AlgImplementation();
	chrono::system_clock::time_point diff;
	int number, cmykNumber, robotStepsNumber, len = initialNumber;
	bool approximationTests = false;

	long long maxDifference, temp;
	for (int i = 0; i < 9; ++i)
	{
		if (approximationTests)
		{
			maxDifference = 0;
			for (int j = 0; j < 5; ++j)
			{
				vector<char>& vec = g.getBlocks(len);
				algor.setData(vec);
				diff = chrono::high_resolution_clock::now();
				number = algor.runAlg(0);
				temp = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - diff).count();
				if (temp > maxDifference)
				{
					maxDifference = temp;
					cmykNumber = number;
					robotStepsNumber = algor.getRobotCount();
				}

			}
		}
		else
		{
			vector<char>& vec = g.getBlocks(len);
			algor.setData(vec);
			diff = chrono::high_resolution_clock::now();
			number = algor.runAlg(0);
			maxDifference = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - diff).count();
			cmykNumber = number;
			robotStepsNumber = algor.getRobotCount();
		}


		cout << "\nlength: " << len << " czas: "
			<< maxDifference << " Cmyk number: "
			<< cmykNumber << endl << "RobotStep: " << robotStepsNumber << endl;
		len += initialNumber;
	}
}