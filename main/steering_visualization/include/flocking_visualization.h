#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "flocking_ship.h"
#include "engine/engine.h"
#include "engine/system.h"
#include "math/vector.h"

namespace stuff
{
class Graphics;
class Engine;

class FlockingVisualization : public SystemInterface
{
public:
	FlockingVisualization(Engine& engine) : engine_(engine), graphics_(engine.GetGraphics())
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

	const float shipSize_ = 10.0f;
	const unsigned boidNb_ = 75;
	std::vector<Boid> boids_;

	float align_force_ = 5.0f;
	float cohesion_force_ = 0.5f;
	float seperation_force_ = 5.0f;

	sf::SoundBuffer waveSoundBuffer_;
	sf::Sound waveSound_;
};
}
