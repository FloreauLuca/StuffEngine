#pragma once
#include <SFML/Audio.hpp>

#include "algo/noise/perlin_noise.h"
#include "engine/engine.h"
#include "engine/system.h"

namespace stuff
{
	class MusicCircles
	{
	public:
		MusicCircles() {}
		MusicCircles(const sf::SoundBuffer& soundBuffer);
		sf::Vector2f DrawCircle(Graphics& graphics, float timer);

		bool TryPlaySound(float timer);

		void SetSpeed(float speed);

		void SetRadius(float radius, float thickness);

		void SetColor(sf::Color color);

		void SetPitch(float pitch);

		void SetPosition(sf::Vector2f pos);
	private:

		float speed_ = 1.0f;
		float bigRadius_ = 50.0f;
		float smallRadius_ = 10.0f;
		sf::Color color_ = sf::Color::Red;
		float pitch_ = 2.0f;
		float thickness_ = 5.0f;
		float radiusRatio_ = 8.0f;
		sf::Vector2f center_;

		sf::CircleShape bigCircle_;
		sf::CircleShape smallCircle_;

		float soundOffset_ = 0.25f;
		sf::Sound sound_;

		bool played_ = false;
	};


	class RecursiveMusic : public SystemInterface
	{
	public:
		RecursiveMusic(Engine& engine) : engine_(engine), graphics_(engine.GetGraphics())
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

		sf::Vector2u windowSize_ = sf::Vector2u(1, 1);

		const float bigCirRad_ = 150.0f;
		const float smallCirRad_ = 20.0f;
		const float thickness_ = 5.0f;
		const int COUNT = 8;

		std::vector<MusicCircles> musicCircles_;

		sf::CircleShape backGroundCircle_;
		float backCirSize_ = 2.0f;
		algo::PerlinNoise perlinNoise_;
		std::map<int, float> colorTimer_;


		sf::RectangleShape rect_;
	};
}
