#include "day18_snailfish.h"

#include <iostream>

namespace stuff::advent
{
std::string Day18Snailfish::FindAnswer()
{
	Pair* basePair = nullptr;
	std::vector<Pair*> readPair;
	while (!myFile_.eof())
	{
		myFile_ >> readLine;
		readPair.push_back(FillPair());
		DisplayPair(readPair[readPair.size()-1], true);
		std::cout << std::endl;
	}
	std::cout << std::endl;
	int maxCount = 0;
	for (int i = 0; i < readPair.size(); ++i)
	{
		for (int j = 0; j < readPair.size(); ++j)
		{
			if (i == j)
				continue;
			//std::cout << std::endl;
			//DisplayPair(readPair[i], true);
			//std::cout << std::endl;
			//DisplayPair(readPair[j], true);
			//std::cout << std::endl;
			//std::cout << std::endl << "Addition" << std::endl;
			Pair* pair = AdditionPairs(readPair[i], readPair[j]);
			//DisplayPair(pair, true);
			//std::cout << std::endl << "Reduced" << std::endl;
			pair = ReducePairs(pair);
			//DisplayPair(pair, true);
			//std::cout << std::endl;
			//std::cout << Magnitude(pair) << std::endl;
			maxCount = std::max(Magnitude(pair), maxCount);
			myFile_.seekg(0, myFile_.beg);
			readPair = std::vector<Pair*>(); //Full memory leak MDR
			while (!myFile_.eof())
			{
				myFile_ >> readLine;
				readPair.push_back(FillPair());
				//DisplayPair(readPair[readPair.size() - 1], true);
				//std::cout << std::endl;
			}
		}
		std::cout << i << "/" << readPair.size() << std::endl;
		std::cout << maxCount << std::endl;
	}
	return std::to_string(maxCount);
}

void Day18Snailfish::DisplayAnswer()
{
}

Pair* Day18Snailfish::FillPair()
{
	Pair* pair = new Pair();
	readLine.erase(readLine.begin());
	if (readLine[0] == '[')
	{
		pair->left = FillPair();
		pair->left->parent = pair;
		pair->left->isLeft = true;
	}
	else
	{
		std::string::size_type pos;
		int left = std::stoi(readLine, &pos);
		pair->leftValue = left;
		readLine.erase(readLine.begin(), readLine.begin() + pos);
	}
	readLine.erase(readLine.begin());
	if (readLine[0] == '[')
	{
		pair->right = FillPair();
		pair->right->parent = pair;
		pair->right->isLeft = false;
	}
	else
	{
		std::string::size_type pos;
		int right = std::stoi(readLine, &pos);
		pair->rightValue = right;
		readLine.erase(readLine.begin(), readLine.begin() + pos);
	}
	readLine.erase(readLine.begin());
	return pair;
}

Pair* Day18Snailfish::AdditionPairs(Pair* base, Pair* read)
{
	if (!base)
		return read;
	Pair* pair = new Pair();
	base->parent = pair;
	base->isLeft = true;
	read->parent = pair;
	read->isLeft = false;
	pair->left = base;
	pair->right = read;
	return pair;
}

bool Day18Snailfish::CheckPairSplit(Pair* pair, int depth)
{
	Pair* currentPair = pair;
	if (currentPair->left != nullptr)
	{
		if (CheckPairSplit(currentPair->left, depth + 1))
			return true;
	}
	if (currentPair->leftValue >= 10)
	{
		Pair* newPair = new Pair();
		newPair->parent = currentPair;
		newPair->isLeft = true;
		newPair->leftValue = std::floor(currentPair->leftValue / 2.0f);
		newPair->rightValue = std::ceil(currentPair->leftValue / 2.0f);
		currentPair->leftValue = -1;
		currentPair->left = newPair;
		//std::cout << "Split" << std::endl;
		return true;
	}
	if (currentPair->right != nullptr)
	{
		if (CheckPairSplit(currentPair->right, depth + 1))
			return true;
	}
	if (currentPair->rightValue >= 10)
	{
		Pair* newPair = new Pair();
		newPair->parent = currentPair;
		newPair->isLeft = false;
		newPair->leftValue = std::floor(currentPair->rightValue / 2.0f);
		newPair->rightValue = std::ceil(currentPair->rightValue / 2.0f);
		currentPair->rightValue = -1;
		currentPair->right = newPair;
		//std::cout << "Split" << std::endl;
		return true;
	}
	return false;
}

bool Day18Snailfish::CheckPairExplode(Pair* pair, int depth)
{
	Pair* currentPair = pair;
	if (depth >= 4 && currentPair->leftValue != -1 && currentPair->rightValue != -1)
	{
		int* leftValue = FindNearest(currentPair, true);
		if (leftValue)
			*leftValue += currentPair->leftValue;
		int* rightValue = FindNearest(currentPair, false);
		if (rightValue)
			*rightValue += currentPair->rightValue;
		if (currentPair->isLeft)
		{
			currentPair->parent->left = nullptr;
			currentPair->parent->leftValue = 0;
		}
		else
		{
			currentPair->parent->right = nullptr;
			currentPair->parent->rightValue = 0;
		}
		//std::cout << "Explode : ";
		//DisplayPair(currentPair, true);
		//std::cout << std::endl;
		delete currentPair;
		return true;
	}
	if (currentPair->left != nullptr)
	{
		if (CheckPairExplode(currentPair->left, depth + 1))
			return true;
	}
	if (currentPair->right != nullptr)
	{
		if (CheckPairExplode(currentPair->right, depth + 1))
			return true;
	}
	return false;
}

int* Day18Snailfish::FindNearest(Pair* pair, bool left)
{
	if (pair->parent == nullptr)
		return nullptr;
	Pair* leftPair = pair;
	if (leftPair->isLeft == left)
	{
		return FindNearest(leftPair->parent, left);
	}
	else
	{
		leftPair = leftPair->parent;
		if (left)
		{
			if (leftPair->left)
			{
				leftPair = leftPair->left;
				while (leftPair->right)
				{
					leftPair = leftPair->right;
				}
				return &leftPair->rightValue;
			}
			else
			{
				return &leftPair->leftValue;
			}
		}
		else
		{
			if (leftPair->right)
			{
				leftPair = leftPair->right;
				while (leftPair->left)
				{
					leftPair = leftPair->left;
				}
				return &leftPair->leftValue;
			} else
			{
				return &leftPair->rightValue;
			}
		}
	}
	return nullptr;
}

Pair* Day18Snailfish::ReducePairs(Pair* pair)
{
	bool ended = false;
	while (!ended)
	{
		//DisplayPair(pair, true);
		//std::cout << std::endl;
		ended = true;
		if (CheckPairExplode(pair, 0))
		{
			ended = false;
			continue;
		}
		if (CheckPairSplit(pair, 0))
		{
			ended = false;
			continue;
		}
	}
	return pair;
}

void Day18Snailfish::DisplayPair(Pair* pair, bool child)
{
	std::cout << "[";
	if (pair->left && child)
	{
		DisplayPair(pair->left, child);
	} else
	{
		std::cout << pair->leftValue;;
	}
	std::cout << ",";
	if (pair->right && child)
	{
		DisplayPair(pair->right, child);
	}
	else
	{
		std::cout << pair->rightValue;
	}
	std::cout << "]";
}

int Day18Snailfish::Magnitude(Pair* pair)
{
	int left = 0;
	if (pair->left)
		left = Magnitude(pair->left);
	else
		left = pair->leftValue;
	int right = 0;
	if (pair->right)
		right = Magnitude(pair->right);
	else
		right = pair->rightValue;
	return 3*left + 2*right;
}
}
