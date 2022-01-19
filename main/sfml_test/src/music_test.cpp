#include "music_test.h"
#include <iostream>

#include "engine/system.h"
#include "math/color.h"
#include "utility/data_location.h"

namespace stuff
{
void MusicTest::Init()
{
	if(!drumSoundBuffer_.loadFromFile(dataPath + "sounds/drum.wav"))
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

	bigCircle_.setRadius(bigCirRad_);
	bigCircle_.setOrigin(bigCirRad_, bigCirRad_);
	sf::Vector2f center = sf::Vector2f(windowSize_.x / 2.0f, windowSize_.y / 2.0f);
	bigCircle_.setPosition(center);

	smallCircle_.setRadius(10.0f);
	smallCircle_.setOrigin(10.0f, 10.0f);
	smallCircle_.setPosition(center + sf::Vector2f(bigCirRad_, 0.0f));
	smallCircle_.setFillColor(sf::Color::Red);

	timer_ = 0.0f;
}

void MusicTest::Update(float dt)
{
	graphics_.Draw(bigCircle_);
	sf::Vector2f center = sf::Vector2f(windowSize_.x / 2.0f, windowSize_.y / 2.0f);
	
	timer_ += dt;
	for (int i = 0; i < COUNT; ++i)
	{
		float speed = (i+1.0f) / (COUNT);

		float timer = timer_ * speed;
		
		if (std::fmod(timer, rythm_) < speed * dt)
		{
			pianoSounds_[i].setPitch(speed * 4.0f);
			pianoSounds_[i].play();
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
		graphics_.Draw(smallCircle_);
		
	}
	if (std::fmod(timer_ + rythm_/2.0f, rythm_) < dt)
	{
		//kickSound_.play();
	}
	if (std::fmod(timer_, rythm_/4.0f) < dt)
	{
		//pianoSound_.setPitch(std::fmod(timer_, rythm_) / 4.0f + 1.0f);
		//pianoSound_.play();
	}
	//std::cout << timer_ << " " << timer2_ << std::endl;
}

void MusicTest::Destroy()
{
	drumSound_.stop();
	kickSound_.stop();
}
}
