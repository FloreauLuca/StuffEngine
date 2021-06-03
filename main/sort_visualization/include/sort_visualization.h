#pragma once
#include <array>

#include <SFML/Graphics.hpp>

#include "bubble_sort.h"
#include "engine/engine.h"
#include "engine/system.h"

namespace stuff
{
class Graphics;
class Engine;

class SortVisualization : public SystemInterface
{
public:
	SortVisualization(Engine& engine) : engine_(engine), graphics_(engine.GetGraphics())
	{
	}

	void Init() override;
	void Update(float dt) override;
	void Destroy() override;
	virtual void SortList();
protected:
	std::vector<int> list_;
	std::vector <std::pair<size_t, size_t>> swap_pairs;
private:
	Engine& engine_;
	Graphics& graphics_;

	const sf::Vector2u windowSize_ = sf::Vector2u(1400, 900);
	const sf::Vector2u offset = sf::Vector2u(5, 5);

	size_t pairIndex_ = 0;
	sf::RectangleShape standardRect;
	const unsigned int listSize = 100;
	const std::array<sf::Color, 6> lgbtColors_ = {
		sf::Color(255, 0, 24),
		sf::Color(255, 165, 44),
		sf::Color(255, 255, 65),
		sf::Color(0, 128, 24),
		sf::Color(0, 0, 249),
		sf::Color(134, 0, 125)
	};
};
}
