#pragma once
#include <SFML/Audio.hpp>


#include "algo/noise/perlin_noise.h"
#include "engine/engine.h"
#include "engine/system.h"
#include "math/const.h"

namespace stuff
{
	class MusicNoise : public SystemInterface
	{
	public:
		MusicNoise(Engine& engine) : engine_(engine), graphics_(engine.GetGraphics())
		{
		}

		void Init() override;
		void DrawBackground(float dt);
		void Update(float dt) override;
		void Destroy() override;

	private:
		Engine& engine_;
		Graphics& graphics_;

		float timer_ = 0.0f;
		sf::SoundBuffer drumSoundBuffer_;
		sf::SoundBuffer kickSoundBuffer_;
		sf::Sound drumSound_;
		sf::Sound kickSound_;

		sf::SoundBuffer pianoSoundBuffer_;
		sf::Sound pianoSound_;
		std::vector<sf::Sound> pianoSounds_;

		sf::Vector2u windowSize_ = sf::Vector2u(1, 1);

		sf::CircleShape bigCircle_;
		sf::CircleShape smallCircle_;

		float bigCirRad_ = 100.0f;
		float smallCirRad_ = 20.0f;
		float rythm_ = 1.0f;
		const int COUNT = 5;

		sf::CircleShape backGroundCircle_;
		float backCirSize_ = 2.0f;
		float waveTimer_ = 0.0f;
		algo::PerlinNoise perlinNoise_;
		std::map <int, float> colorTimer_;
	};
}
