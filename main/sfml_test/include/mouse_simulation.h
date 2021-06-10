#pragma once
#include <SFML/Graphics.hpp>

#include "engine/engine.h"
#include "engine/system.h"

namespace stuff
{
class Graphics;
class Engine;

class MouseSim : public SystemInterface
{
public:
	MouseSim(Engine& engine) : engine_(engine), graphics_(engine.GetGraphics())
	{
	}

	void Init() override;
	void Update(float dt) override;
	void Destroy() override;
private:
	Engine& engine_;
	Graphics& graphics_;

	float timer_ = 0.0f;
	float reduceSpeed = 0.95f;
	float radiusMouse = 2.0f;
	float mousePower = 1.0f;

	const sf::Vector2u squareCount_ = sf::Vector2u(20, 20);
	sf::Vector2u windowSize_ = sf::Vector2u(1, 1);
	std::vector <std::pair<sf::Vector2f, float>> pixelToDraw_;
};
}
