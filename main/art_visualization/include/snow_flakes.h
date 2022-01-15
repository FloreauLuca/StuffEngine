#pragma once
#include <array>

#include <SFML/Graphics.hpp>

#include "engine/engine.h"
#include "engine/system.h"

namespace stuff
{
class Graphics;
class Engine;

class SnowFlakes : public SystemInterface
{
public:
	SnowFlakes(Engine& engine) : engine_(engine), graphics_(engine.GetGraphics())
	{
	}

	void Init() override;
	void Update(float dt) override;
	void Destroy() override;
private:
	Engine& engine_;
	Graphics& graphics_;
	
	float timer_ = 0.0f;
	sf::Vector2u windowSize_ = sf::Vector2u(1, 1);
	std::vector<std::array<sf::Color, 4>> colors_ =
	{
		//Bi
		std::array<sf::Color, 4>{sf::Color(225, 0, 175), sf::Color(150, 50, 225), sf::Color::Blue, sf::Color::Blue},
		//Lesbian
		std::array<sf::Color, 4>{sf::Color(200, 50, 0),sf::Color::White,  sf::Color(150, 0, 100), sf::Color(150, 0, 100)},
		//Trans
		std::array<sf::Color, 4>{sf::Color(255, 150, 150),sf::Color::White,sf::Color(100, 200, 255),sf::Color(100, 200, 255)},
		//Asexual
		std::array<sf::Color, 4>{sf::Color(125, 0, 125), sf::Color::White, sf::Color::Black, sf::Color::Black},
		//NonBinary
		std::array<sf::Color, 4>{sf::Color::Yellow, sf::Color::White,sf::Color(125, 0, 125),sf::Color::Black},
		//Pan
		std::array<sf::Color, 4>{sf::Color(250, 50, 125), sf::Color::Yellow,sf::Color(50, 175, 250),sf::Color(50, 175, 250)},
		//LGBT
		std::array<sf::Color, 4>{sf::Color::Red, sf::Color::Blue,sf::Color::Yellow,sf::Color::Green},
	};
};
}
