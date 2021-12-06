#include "day5_vents.h"

#include <bitset>
#include <iostream>
#include <sstream>

namespace stuff::advent
{
	std::string Day5Vents::FindAnswer()
	{
		grid = std::vector<int>(gridSize* gridSize,0);
		int ventCount = 0;
		while (!myFile_.eof())
		{
			int startVentX = 0;
			int startVentY = 0;
			int endVentX = 0;
			int endVentY = 0;
			char between = 0;
			myFile_ >> startVentX;
			myFile_ >> between;
			myFile_ >> startVentY;
			myFile_ >> between;
			myFile_ >> between;
			myFile_ >> endVentX;
			myFile_ >> between;
			myFile_ >> endVentY;
			//std::cout << startVentX << "-" << endVentX << "," << startVentY << "-" << endVentY << std::endl;

			if (startVentY == endVentY)
			{
				for (int x = std::min(startVentX, endVentX); x <= std::max(startVentX, endVentX); x++)
				{
					grid[x * gridSize + startVentY]++;
				}
			} else if (startVentX == endVentX)
			{
				for (int x = std::min(startVentY, endVentY); x <= std::max(startVentY, endVentY); x++)
				{
					grid[startVentX * gridSize + x]++;
				}
			} else if (startVentY - startVentX == endVentY - endVentX)
			{
				//std::cout << "Diag1" << std::endl;
				for (int x = std::min(startVentX, endVentX); x <= std::max(startVentX, endVentX); x++)
				{
					int y = x - std::min(startVentX, endVentX) + std::min(startVentY, endVentY);
					grid[x * gridSize + y]++;
				}
			}
			else if (startVentX < endVentX)
			{
				//std::cout << "Diag2" << std::endl;
				for (int x = startVentX; x <= endVentX; x++)
				{
					int y = startVentY - (x - startVentX);
					grid[x * gridSize + y]++;
				}
			}
			else
			{
				//std::cout << "Diag3" << std::endl;
				for (int x = endVentX; x <= startVentX; x++)
				{
					int y = endVentY - (x - endVentX);
					grid[x * gridSize + y]++;
				}
			}
			//DisplayGrid();
		}
		int count = 0;
		for (int x = 0; x < gridSize; x++)
		{
			for (int y = 0; y < gridSize; y++)
			{
				if (grid[x * gridSize + y] >= 2)
				{
					count++;
				}
			}
		}
		//DisplayGrid();
		return std::to_string(count);
	}

	void Day5Vents::DisplayGrid()
	{
		for (int x = 0; x < gridSize; x++)
		{
			for (int y = 0; y < gridSize; y++)
			{
				std::cout << grid[y * gridSize + x];
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	void Day5Vents::DisplayAnswer()
	{

	}
	
}

