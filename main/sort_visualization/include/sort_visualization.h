#pragma once
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
private:
	Engine& engine_;
	Graphics& graphics_;

	const sf::Vector2u windowSize_ = sf::Vector2u(1400, 900);
	const sf::Vector2u offset = sf::Vector2u(5, 5);

	std::vector<int> list_;
	
	sf::RectangleShape standardRect;
	const unsigned int listSize = 100;
	algo::BubbleSort bubble_sort_;
};
}
