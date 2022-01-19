#pragma once
#include <SFML/Graphics.hpp>

#include "engine/engine.h"
#include "engine/system.h"

namespace stuff
{
class Graphics;
class Engine;

//https://necessarydisorder.wordpress.com/2017/11/15/drawing-from-noise-and-then-making-animated-loopy-gifs-from-there/

class RotatingLine : public SystemInterface
{
public:
	RotatingLine(Engine& engine) : engine_(engine), graphics_(engine.GetGraphics())
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
};
}
