#ifndef ALGIMPLEMENTATION_H
#define ALGIMPLEMENTATION_H

#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <iostream>
#include <regex>
#include <math.h>
using namespace std;

class AlgImplementation
{
private:
	const static vector<string> templatesFirstHalf;
	const static vector<string> templatesSecondHalf;
	const static string paragon;
	int robotStepCalledCount;
	vector<char> blocks;
	int size;

	

	int paragonIndexBeginning;
	//helper functions
	void createWord(int leftIndex, int rightIndex);

	//podstawowy krok robota
	void robotStep(int index);

	//przesuniecie cmykow
	void paragonsMove();
	// stworz slowo z czterech kolejnych klockow
	inline string createBlock(int ind);

	//sprawdza czy slowo jest w jednym z szablonow
	int templateIndexMatch(const string& word, const vector<string>& templateVec) const;
	
	//update struktur pomocnicznych dla alg1
	void adjustIndicesVector(vector<int>& vec, int leftIndex, int rightIndex);
	void adjustIndicesVector(vector<int>& vec, int leftIndex);
	// z osmiu klockow wylap cmyk
	void cutWord(int type);
	int firstAlg();
	int secondAlg();
public:
	void printList() const;
	int getRobotCount() const { return robotStepCalledCount; }
	int runAlg(int type) { if (type == 1) return firstAlg(); return secondAlg(); }
	void setData(vector<char>&);
	AlgImplementation(vector<char>& _blocks) : blocks(_blocks), size(blocks.size()), paragonIndexBeginning(size) { robotStepCalledCount = 0; }
	AlgImplementation() : blocks(vector<char>()) {  }
	~AlgImplementation() { }
};

#endif