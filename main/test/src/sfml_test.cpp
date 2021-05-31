
#include "sfml_test.h"

#include "engine/system.h"

namespace stuff
{
	void SfmlTest::Init()
	{
	}

	void SfmlTest::Update(float dt)
	{
		sf::CircleShape circle1(100.f);
		circle1.setFillColor(sf::Color::Green);
		graphics_.Draw(circle1);
		sf::CircleShape circle2(50.0f);
		circle2.setFillColor(sf::Color::Red);
		graphics_.Draw(circle2);
	}

	void SfmlTest::Destroy()
	{
	}
}