#pragma once
#include <SFML/Graphics.hpp>

#include "engine/engine.h"
#include "engine/system.h"

namespace stuff
{
class Graphics;
class Engine;

class SfmlTest : public SystemInterface
{
public:
	SfmlTest(Engine& engine) : engine_(engine), graphics_(engine.GetGraphics())
	{
	}

	void Init() override;
	void Update(float dt) override;
	void Destroy() override;
private:
	Engine& engine_;
	Graphics& graphics_;

	float timer_ = 0.0f;
	sf::Texture penguinHead_;
	sf::Texture penguinLogo_;
};
}
