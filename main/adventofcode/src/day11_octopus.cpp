#include "day11_octopus.h"

#include <iostream>

namespace stuff::advent
{
std::string Day11Octopus::FindAnswer()
{
	graphics_.Init();
	windowSize_ = graphics_.GetWindowSize();
	texture_.create(squareCount_.x, squareCount_.y);
	image_.create(squareCount_.x, squareCount_.y, sf::Color::Black);
	sprite_.setScale(static_cast<float>(windowSize_.x) / squareCount_.x, static_cast<float>(windowSize_.y) / squareCount_.y);
	sprite_.setTexture(texture_);
	
	while (!myFile_.eof())
	{
		char digit;
		myFile_ >> digit;
		table.push_back((int)(digit - '0'));
	}
	table.erase(table.end()-1);
	for (int s = 0; s < STEPS; ++s)
	{
		Display();
		std::cout << flashIndex.size() << " " << count << std::endl;
		flashIndex = std::vector<int>();
		for (int i = 0; i < table.size(); ++i)
		{
			table[i]++;
		}
		for (int i = 0; i < table.size(); ++i)
		{
			if (table[i] > 9)
				Flash(i);
		}
		for (int i = 0; i < flashIndex.size(); ++i)
		{
			table[flashIndex[i]] = 0;
		}
		if (flashIndex.size() == table.size())
			return std::to_string(s);
	}
	Display();
	std::cout << flashIndex.size() << " " << count << std::endl;
	return std::to_string(count);
}

void Day11Octopus::DisplayAnswer()
{
}

void Day11Octopus::Flash(int index)
{
	if (std::ranges::find(flashIndex, index) != flashIndex.end())
		return;
	//Display();
	count++;
	flashIndex.push_back(index);
	std::array<int, 8> neighbour = GetNeighbour(index);
	for (int i = 0; i < 8; ++i)
	{
		if (neighbour[i] == -1)
			continue;
		table[neighbour[i]]++;
		if (table[neighbour[i]] > 9)
			Flash(neighbour[i]);
	}
}

std::array<int, 8> Day11Octopus::GetNeighbour(int index)
{
	int i = index - index % RANGE;
	int j = index % RANGE;
	std::array<int, 8> neighbour{};
	neighbour[0] = (i + j - RANGE - 1 >= 0 && i + j - 1 >= i) ? i + j - RANGE - 1 : -1;
	neighbour[1] = (i + j - RANGE >= 0) ? i + j - RANGE : -1;
	neighbour[2] = (i + j - RANGE + 1 >= 0 && i + j + 1 < i + RANGE) ? i + j - RANGE + 1 : -1;
	neighbour[3] = (i + j - 1 >= i) ? i + j - 1 : -1;
	neighbour[4] = (i + j + 1 < i + RANGE && i + j + 1 < table.size()) ? i + j + 1 : -1;
	neighbour[5] = (i + j + RANGE - 1 < table.size() && i + j - 1 >= i) ? i + j + RANGE - 1 : -1;
	neighbour[6] = (i + j + RANGE < table.size()) ? i + j + RANGE : -1;
	neighbour[7] = (i + j + RANGE + 1 < table.size() && i + j + 1 < i + RANGE) ? i + j + RANGE + 1 : -1;
	return neighbour;
}

void Day11Octopus::Display()
{
	for (int i = 0; i < table.size(); ++i)
	{
		int x = i % RANGE;
		int y = (i - x) / RANGE;
		image_.setPixel(x, y, sf::Color(255.0f, (table[i] / 9.0f) * 255, (table[i] / 9.0f) * 255));
		if (i % RANGE == 0)
			std::cout << std::endl;
		std::cout << table[i];
	}
	std::cout << std::endl;
	texture_.update(image_);
	graphics_.Draw(sprite_);
	graphics_.Update(0.1f);
	sf::sleep(sf::seconds(1.0f / sortSpeed_));
}
}
