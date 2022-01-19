#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "algo/noise/perlin_noise.h"

#include "engine/engine.h"
#include "engine/system.h"

namespace stuff
{
class Graphics;
class Engine;

class MusicNoise : public SystemInterface
{
public:
	MusicNoise(Engine& engine) : engine_(engine), graphics_(engine.GetGraphics())
	{
	}

	void Init() override;
	void Update(float dt) override;
	void Destroy() override;
private:
	void CreateTexture();
	
	Engine& engine_;
	Graphics& graphics_;

	float timer_ = 0.0f;

	const float ZOOM = 10.0f;

	const float squareSize_ = 5.0f;
	sf::Vector2u squareCount_ = sf::Vector2u(1, 1);
	sf::Vector2u windowSize_ = sf::Vector2u(1, 1);
	sf::Vector2i pos_ = sf::Vector2i(1, 1);

	sf::Texture texture_;
	sf::Image image_;
	sf::Sprite sprite_;

	algo::PerlinNoise perlinNoise_;
	sf::Text text_;

	sf::SoundBuffer waveSoundBuffer_;
	sf::Sound waveSound_;
};
}
