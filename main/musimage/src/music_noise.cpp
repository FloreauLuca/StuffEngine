#include "music_noise.h"

#include <iostream>
#include <numeric>

#include "math/const.h"
#include "math/vector.h"
#include "utility/data_location.h"


namespace stuff
{
void MusicNoise::Init()
{
	timer_ = 0;
	windowSize_ = graphics_.GetWindowSize();
	perlinNoise_ = algo::PerlinNoise(0);
	squareCount_ = sf::Vector2u(sf::Vector2f(windowSize_) / squareSize_);
	texture_.create(squareCount_.x, squareCount_.y);
	image_.create(squareCount_.x, squareCount_.y, sf::Color::Black);
	sprite_.setScale(static_cast<float>(windowSize_.x) / squareCount_.x, static_cast<float>(windowSize_.y) / squareCount_.y);
	sprite_.setTexture(texture_);
	text_.setFillColor(sf::Color::White);
	text_.setCharacterSize(20);
	text_.setOutlineColor(sf::Color::Black);
	text_.setOutlineThickness(5.0f);
	text_.setStyle(sf::Text::Bold);
	//perlinNoise_.SetPersistance(0.75f);
	//perlinNoise_.SetOctaves(5);
	//perlinNoise_.SetPersistance(0.8f);
	//perlinNoise_.SetOctaves(10);
	perlinNoise_.SetPersistance(0.8f);
	perlinNoise_.SetOctaves(3);

	if (!waveSoundBuffer_.loadFromFile(dataPath + "wave.wav"))
	{
		std::cout << "Sound fail to load" << std::endl;
	}
	waveSound_.setBuffer(waveSoundBuffer_);
	//waveSound_.setLoop(true);
	CreateTexture();
}

void MusicNoise::Update(float dt)
{
	timer_ += dt * 0.4f;

	float result = perlinNoise_.CalculateNoise(pos_.x / ZOOM, pos_.y / ZOOM) * 0.5f + 0.5f;
	image_.setPixel(pos_.x, pos_.y, sf::Color(result * 255, result * 255, result * 255));
	
	pos_.x = cos(timer_) * (squareCount_.x / 3.0f) + squareCount_.x / 2.0f;
	pos_.y = sin(timer_) * (squareCount_.x / 3.0f) + squareCount_.y / 2.0f;
	
	image_.setPixel(pos_.x, pos_.y, sf::Color(0, 0, 255));
	float sound = perlinNoise_.CalculateNoise(pos_.x / ZOOM, pos_.y / ZOOM) * 0.5f + 0.5f;
	sound = std::clamp(sound, 0.0f, 1.0f);
	
	texture_.update(image_);
	graphics_.Draw(sprite_);
	if (waveSound_.getPitch() != fmod(sound * 2.0f, 2.0f))
	{
		waveSound_.setPitch(fmod(sound * 2.0f, 2.0f));
		waveSound_.play();
	}
}

void MusicNoise::Destroy()
{
}

void MusicNoise::CreateTexture()
{
	for (unsigned i = 0; i < squareCount_.x; i++)
	{
		for (unsigned j = 0; j < squareCount_.y; j++)
		{
			float result = 0;
			float x = i / ZOOM;
			float y = j / ZOOM;
			result = perlinNoise_.CalculateNoise(x, y) * 0.5f + 0.5f;
			result = std::clamp(result, 0.0f, 1.0f);
			result *= 255;
			image_.setPixel(i, j, sf::Color(result, result, result));
		}
	}
}
}
