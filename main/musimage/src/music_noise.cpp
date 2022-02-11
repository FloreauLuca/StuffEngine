#include "music_noise.h"
#include <iostream>

#include "engine/system.h"
#include "math/color.h"
#include "utility/data_location.h"

namespace stuff
{
	void MusicNoise::Init()
	{
		if (!drumSoundBuffer_.loadFromFile(dataPath + "sounds/drum.wav"))
		{
			std::cout << "Sound fail to load" << std::endl;
		}
		drumSound_.setBuffer(drumSoundBuffer_);
		drumSound_.setLoop(false);

		if (!kickSoundBuffer_.loadFromFile(dataPath + "sounds/kick.wav"))
		{
			std::cout << "Sound fail to load" << std::endl;
		}
		kickSound_.setBuffer(kickSoundBuffer_);
		kickSound_.setLoop(false);

		if (!pianoSoundBuffer_.loadFromFile(dataPath + "sounds/piano.wav"))
		{
			std::cout << "Sound fail to load" << std::endl;
		}
		pianoSound_.setBuffer(pianoSoundBuffer_);
		pianoSound_.setLoop(false);
		pianoSounds_.resize(COUNT, sf::Sound(pianoSoundBuffer_));

		windowSize_ = graphics_.GetWindowSize();

		float thickness_ = 10.0f;
		bigCircle_.setRadius(bigCirRad_ - thickness_ / 2);
		bigCircle_.setOrigin(bigCirRad_ - thickness_ / 2, bigCirRad_ - thickness_ / 2);
		sf::Vector2f center = sf::Vector2f(windowSize_.x / 2.0f, windowSize_.y / 2.0f);
		bigCircle_.setPosition(center);
		bigCircle_.setOutlineThickness(thickness_);
		bigCircle_.setFillColor(sf::Color::Transparent);
		bigCircle_.setOutlineColor(sf::Color::White);

		smallCircle_.setRadius(smallCirRad_);
		smallCircle_.setOrigin(smallCirRad_, smallCirRad_);
		smallCircle_.setPosition(center + sf::Vector2f(bigCirRad_, 0.0f));
		smallCircle_.setFillColor(sf::Color::Red);

		backGroundCircle_.setRadius(backCirSize_);
		backGroundCircle_.setOrigin(backCirSize_, backCirSize_);
		backGroundCircle_.setFillColor(sf::Color::White);
		
		timer_ = 0.0f;
		perlinNoise_ = algo::PerlinNoise(0);
	}

	void MusicNoise::DrawBackground(float dt)
	{
		std::ranges::for_each(colorTimer_, [dt](auto& color) { color.second += dt * 10.0f; });
		float interval = 20.0f;
		for (int x = 0; x < windowSize_.x; x+= interval)
		{
			for (int y = 0; y < windowSize_.y; y += interval)
			{
				sf::Vector2f pos;
				int colorIndex = std::round((perlinNoise_.IntNoise(y, x) * 0.5f + 0.5f) * 5.0f);
				sf::Color color = HSLtoRGB(((float)colorIndex / COUNT) * 360.0f, 100.0f, 50.0f);
				backGroundCircle_.setFillColor(color);
				for (auto color_timer : colorTimer_)
				{
				}
				float translation = std::max(0.0f, sin(std::clamp(colorTimer_[colorIndex] - y / 100.0f, 0.0f, PI)));
				backGroundCircle_.setRadius(backCirSize_ + perlinNoise_.IntNoise(x, y) + translation * COUNT);
				
				pos += sf::Vector2f(x + perlinNoise_.IntNoise(x, y) * interval * 0.2f, y + perlinNoise_.IntNoise(y, x) * interval * 0.2f);
				backGroundCircle_.setPosition(pos);
				graphics_.Draw(backGroundCircle_);
			}
		}
	}

	void MusicNoise::Update(float dt)
	{
		DrawBackground(dt);
		graphics_.Draw(bigCircle_);
		sf::Vector2f center = sf::Vector2f(windowSize_.x / 2.0f, windowSize_.y / 2.0f);

		timer_ += dt;
		for (int i = 0; i < COUNT; ++i)
		{
			float speed = (i + 1.0f) / (COUNT);

			float timer = timer_ * speed;

			if (std::fmod(timer, rythm_) < speed * dt)
			{
				pianoSounds_[i].setPitch(speed * 4.0f);
				pianoSounds_[i].play();
				sf::Color color = HSLtoRGB(((float)i / COUNT) * 360.0f, 100.0f, 50.0f);
				colorTimer_[i] = 0.0f;
				//switch (i)
				//{
				//case 0:
				//	drumSound_.play();
				//	break;
				//case 1:
				//	kickSound_.play();
				//	break;
				//case 2:
				//	pianoSound_.play();
				//	break;
				//}
			}
			smallCircle_.setPosition(center + sf::Vector2f(cos((timer - speed * 0.5f) * PI * 2.0f) * bigCirRad_, sin((timer - speed * 0.5f) * PI * 2.0f) * bigCirRad_));
			smallCircle_.setFillColor(HSLtoRGB(((float)i / COUNT) * 360.0f, 100.0f, 50.0f));
			float radius = smallCirRad_ + (0.1f - std::clamp(std::fmod(timer - speed * 0.4f, rythm_), 0.0f, 0.1f)) * 100.0f;
			smallCircle_.setRadius(radius);
			graphics_.Draw(smallCircle_);

		}
		if (std::fmod(timer_ + rythm_ / 2.0f, rythm_) < dt)
		{
			//kickSound_.play();
		}
		if (std::fmod(timer_, rythm_ / 4.0f) < dt)
		{
			//pianoSound_.setPitch(std::fmod(timer_, rythm_) / 4.0f + 1.0f);
			//pianoSound_.play();
		}
		//std::cout << timer_ << " " << timer2_ << std::endl;
	}

	void MusicNoise::Destroy()
	{
		drumSound_.stop();
		kickSound_.stop();
	}
}
