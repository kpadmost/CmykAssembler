#include "AlgImplementation.h"

const vector<string> AlgImplementation::templatesFirstHalf = vector<string>({ ".CMY", "..CM", "...C" });
const vector<string> AlgImplementation::templatesSecondHalf = vector<string>({ "K...", "YK..", "MYK." });



const string AlgImplementation::paragon = "CMYK";

int AlgImplementation::firstAlg()
{	

	vector<int> paragonIndices = vector<int>();
	vector<int> templateLeftIndices[3];
	vector<int> templateRightIndices[3];
	for (int i = 0; i < 3; ++i)
	{
		templateLeftIndices[i] = vector<int>();
		templateRightIndices[i] = vector<int>();
	}
	string piece;
	bool movesAreAvailable = true;
	int leftIndex, rightIndex;
	vector<int>::iterator it;
	while (movesAreAvailable)
	{
		//look for appropriate indices
		for (auto i = 0; i < paragonIndexBeginning - 4; ++i) {
			piece = createBlock(i);
			int match;

			if (piece == paragon)
				paragonIndices.push_back(i);
			else
			{
				match = templateIndexMatch(piece, templatesFirstHalf);
				if (match != -1)
					templateLeftIndices[match].push_back(i);
				else
				{
					match = templateIndexMatch(piece, templatesSecondHalf);
					if (match != -1)
						templateRightIndices[match].push_back(i);
				}

			}
			//construction is not working!
			/*else if (match = templateIndexMatch(piece, templatesFirstHalf) != -1)
				templateLeftIndices[match].push_back(i);
			else if (match = templateIndexMatch(piece, templatesSecondHalf) != -1)
				templateRightIndices[match].push_back(i);*/

		}
		//paragons are our priority, move them all
		while (paragonIndices.size() > 0)
		{
			int ind = paragonIndices.back();
			paragonIndices.pop_back();
			for (int i = 0; i < 3; ++i)
			{
				adjustIndicesVector(templateLeftIndices[i], ind);
				adjustIndicesVector(templateRightIndices[i], ind);
			}
			paragonIndexBeginning -= 4;
			robotStep(ind);
		}

		//check, if any moves are available
		bool wordsCanBeCreated = false;
		for (int i = 0; i < 3; ++i)
		{
			if (templateLeftIndices[i].size() != 0 && templateRightIndices[i].size() != 0)
			{
				wordsCanBeCreated = true;
				break;
			}
		}

		//if not, return
		if (!wordsCanBeCreated)
		{
			movesAreAvailable = false;
			continue;
		}

		//check halfs
		for (int i = 0; i < 3; ++i)
		{
			//while are apropriate pieces available
			while (templateLeftIndices[i].size() > 0 && templateRightIndices[i].size() > 0)
			{
				leftIndex = templateLeftIndices[i].back();
				rightIndex = -1;
				//for left, find right
				for (it = templateRightIndices[i].begin(); it != templateRightIndices[i].end(); ++it)
					if (abs(*it - leftIndex) > 4)
					{
						rightIndex = *it;
						break;
					}
				
				//remove this from vec
				templateLeftIndices[i].pop_back();
				if (rightIndex == -1)	
					continue;
				
				for (int j = 0; j < 3; ++j)
				{
					adjustIndicesVector(templateLeftIndices[j], leftIndex, rightIndex);
					adjustIndicesVector(templateRightIndices[j], leftIndex, rightIndex);
				}
				createWord(leftIndex, rightIndex);
				cutWord(i);
				paragonIndexBeginning -= 4;
				paragonsMove();
			}
		}
		for (int i = 0; i < 3; ++i)
		{
			templateLeftIndices[i].clear();
			templateRightIndices[i].clear();
		}
	}
	
	//move words to end
	int temp = paragonIndexBeginning >> 2;
	while (temp-- > 0)
		robotStep(0);
	//printList();
	return (size - paragonIndexBeginning) >> 2;
		
}

int AlgImplementation::secondAlg()
{
	string piece;
	int matchIndex;
	int iter = 0;
	int secIter = 0;
	bool wordCreated;
	while (iter < paragonIndexBeginning - 4)
	{
		wordCreated = false;
		secIter = iter + 4;
		piece = createBlock(iter);
		if (piece == paragon)
		{
			robotStep(iter);
			paragonIndexBeginning -= 4;
			wordCreated = true;
		}
		else 
		{
			matchIndex = templateIndexMatch(piece, templatesFirstHalf);
			if (matchIndex != -1)
			{
				while (secIter < paragonIndexBeginning - 4)
				{
					piece = createBlock(secIter);
					if (templateIndexMatch(piece, templatesSecondHalf) == matchIndex)
					{
						cout << " first: " << iter << " second: " << secIter << endl;

						createWord(iter, secIter);
						cutWord(matchIndex);
						paragonIndexBeginning -= 4;
						paragonsMove();
						printList();
						wordCreated = true;
						break;
					}
					++secIter;
				}
			}
			else 
			{
				matchIndex = templateIndexMatch(piece, templatesSecondHalf);
				if (matchIndex != -1)
					while (secIter < paragonIndexBeginning - 4)
					{
						piece = createBlock(secIter);
						if (templateIndexMatch(piece, templatesFirstHalf) == matchIndex)
						{
							cout << " first: " << secIter << " second: " << iter << endl;
							createWord(secIter, iter);
							cutWord(matchIndex);
							paragonIndexBeginning -= 4;
							paragonsMove();
							
							printList();
							wordCreated = true;
							break;
						}
						++secIter;
					}
			}
				
		}
		if (!wordCreated) ++iter;
	}

	int temp = paragonIndexBeginning >> 2;
	while (temp-- > 0)
		robotStep(0);
	return (size - paragonIndexBeginning) >> 2;
}

void AlgImplementation::setData(vector<char>& _vec)
{
	blocks = _vec;
	paragonIndexBeginning = size = _vec.size();
	robotStepCalledCount = 0;
}

void AlgImplementation::printList() const
{
	cout << endl;
	for_each(blocks.begin(), blocks.end(), [](char x) {cout << x; });
}

inline string AlgImplementation::createBlock(int index)
{
	char arr[4];
	for (int i = 0; i < 4; ++i)
		arr[i] = blocks[index + i];
	return string(arr, arr + 4);
}


void AlgImplementation::cutWord(int type)
{
	int firstCut = 7 - type;
	robotStep(size - firstCut);

	//cut the spare
	robotStep(size - 8);
}

void AlgImplementation::robotStep(int index)
{
	++robotStepCalledCount;
	vector<char>::iterator wordIteratorBegin = blocks.begin() + index;
	//to avoid reallocation, let's create temp array
	char vals[4];
	for (int i = 0; i < 4; ++i)
		vals[i] = blocks[index + i];
	blocks.erase(wordIteratorBegin, wordIteratorBegin + 4);
	for (char c : vals)
		blocks.emplace_back(c);
}

void AlgImplementation::createWord(int leftIndex, int rightIndex)
{
	robotStep(leftIndex);
	if (rightIndex > leftIndex)
		rightIndex -= 4;
	robotStep(rightIndex);
}

void AlgImplementation::paragonsMove()
{
	int paragonNumber = (size - paragonIndexBeginning) >> 2;
	int cutIndex = size - 8;
	while (paragonNumber-- > 0)
	{
		robotStep(cutIndex);
		cutIndex -= 4;
	}
}

void AlgImplementation::adjustIndicesVector(vector<int>& vec, const int leftIndex, const int rightIndex)
{
	auto it = remove_if(vec.begin(), vec.end(), [=](int _x)
	{
		return abs(_x - leftIndex) < 4 || abs(_x - rightIndex < 4);
	});
	vec.erase(it, vec.end());
	transform(vec.begin(), vec.end(), vec.begin(), [=](int _x) 
	{ 
		if (_x > leftIndex && _x > rightIndex)
			return _x - 8;

		//if index between two indexes
		if (_x - leftIndex > 0 != _x - rightIndex > 0)
			return _x - 4;

		return _x;
	});
}

void AlgImplementation::adjustIndicesVector(vector<int>& vec, const int index)
{
	auto it = remove_if(vec.begin(), vec.end(), [=](int _x) { return abs(_x - index) < 4; });
	vec.erase(it, vec.end());
	transform(vec.begin(), vec.end(), vec.begin(), [=](int _x)
	{
		if (_x > index)
			return _x - 4;
		return _x;
	});
}

int AlgImplementation::templateIndexMatch(const string& word, const vector<string>& templateVec) const
{
	for (int i = 0; i < 3; ++i)
		if (regex_match(word, regex(templateVec[i]))) return i;

	return -1;
}

