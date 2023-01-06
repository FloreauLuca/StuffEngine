#pragma once
#include <array>
#include <day.h>

namespace stuff::advent
{
class Day9 : public Day
{
public:
	Day9(stuff::Engine& engine) : Day(engine), engine_(engine), graphics_(engine.GetGraphics())
	{
	}

	void Init() override;
	void Update(float dt) override;
	void Destroy() override;

	std::string FindAnswer() override;
	void DisplayAnswer() override;
private:
	Engine& engine_;
	Graphics& graphics_;

	float timer_ = 0.0f;

	sf::Vector2i headPos;
	sf::Vector2i tailPos;

	const sf::Vector2u squareCount_ = sf::Vector2u(100, 100);
	sf::Vector2u windowSize_ = sf::Vector2u(1, 1);

	sf::Texture texture_;
	sf::Image image_;
	sf::Sprite sprite_;
};
}
