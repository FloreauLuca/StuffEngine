#pragma once
#include <SFML/Audio.hpp>

#include "algo/noise/perlin_noise.h"
#include "engine/engine.h"
#include "engine/system.h"

namespace stuff
{
class Circles
{
public:
	Circles();
	sf::Vector2f DrawCircle(Graphics& graphics, float timer);

	void SetSpeed(float speed);

	void SetRadius(float radius, float thickness);

	void SetColor(sf::Color color);
	
	void SetPosition(sf::Vector2f pos);
private:

	float speed_ = 1.0f;
	float bigRadius_ = 50.0f;
	float smallRadius_ = 10.0f;
	sf::Color color_ = sf::Color::Red;
	float pitch_ = 2.0f;
	float thickness_ = 5.0f;
	float radiusRatio_ = 7.0f;
	sf::Vector2f center_;
	
	sf::CircleShape bigCircle_;
	sf::CircleShape smallCircle_;
};


class FourierCircles : public SystemInterface
{
public:
	FourierCircles(Engine& engine) : engine_(engine), graphics_(engine.GetGraphics())
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
	
	const float bigCirRad_ = 50.0f;
	const float smallCirRad_ = 20.0f;
	const float thickness_ = 5.0f;
	const int COUNT = 5;

	std::vector<Circles> circles_;

	sf::VertexArray line_;

	float speed_ = 0.0f;
};
}
