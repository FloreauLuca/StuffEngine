#include "recursive_music.h"

#include <iostream>

#include "math/color.h"
#include "math/const.h"
#include "utility/data_location.h"

namespace stuff
{
MusicCircles::MusicCircles(const sf::SoundBuffer& soundBuffer)
{
	sound_.setBuffer(soundBuffer);
	sound_.setLoop(false);

	bigCircle_.setFillColor(sf::Color::Transparent);
	bigCircle_.setOutlineColor(sf::Color::White);

	smallCircle_.setFillColor(sf::Color::Red);
}

sf::Vector2f MusicCircles::DrawCircle(Graphics& graphics, float timer)
{
	graphics.Draw(bigCircle_);

	float angle = (timer * speed_) * PI * 2.0f;
	float circleRatio = fmod(angle / (PI * 2.0f), 1.0f);
	sf::Vector2f pos = center_ + sf::Vector2f(cos(angle) * bigRadius_, sin(angle) * bigRadius_);
	float radiusInc = 1.0f - circleRatio;
	float radius = smallRadius_ + radiusInc*0.0f;
	smallCircle_.setRadius(radius);
	smallCircle_.setOrigin(radius, radius);
	smallCircle_.setPosition(pos);
	graphics.Draw(smallCircle_);
	return pos;
}

bool MusicCircles::TryPlaySound(float timer)
{
	float angleOffset = ((timer + soundOffset_) * speed_) * PI * 2.0f;
	if (fmod(angleOffset / (PI * 2.0f), 1.0f) < 0.1f)
	{
		if (!played_)
		{
			//std::cout << fmod(angleOffset / (PI * 2.0f), 1.0f) << std::endl;
			sound_.play();
			played_ = true;
			return true;
		}
	}
	else
	{
		played_ = false;
	}
	return false;
}

void MusicCircles::SetSpeed(float speed)
{
	speed_ = speed;
}

void MusicCircles::SetRadius(float radius, float thickness)
{
	bigRadius_ = radius;
	smallRadius_ = radius / radiusRatio_;
	thickness_ = thickness;
	bigCircle_.setOutlineThickness(thickness_);
	bigCircle_.setRadius(bigRadius_ - thickness_ / 2);
	bigCircle_.setOrigin(bigRadius_ - thickness_ / 2, bigRadius_ - thickness_ / 2);
	smallCircle_.setRadius(smallRadius_);
	smallCircle_.setOrigin(smallRadius_, smallRadius_);
}

void MusicCircles::SetColor(sf::Color color)
{
	color_ = color;
	smallCircle_.setFillColor(color_);
}

void MusicCircles::SetPitch(float pitch)
{
	pitch_ = pitch;
	sound_.setPitch(pitch_);
}

void MusicCircles::SetPosition(sf::Vector2f pos)
{
	center_ = pos;
	bigCircle_.setPosition(center_);
}

void RecursiveMusic::Init()
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

	windowSize_ = graphics_.GetWindowSize();

	musicCircles_ = std::vector<MusicCircles>(COUNT);
	for (int i = 0; i < COUNT; ++i)
	{
		musicCircles_[i] = MusicCircles(pianoSoundBuffer_);

		const float circleRatio = static_cast<float>(i) / COUNT;
		const float circleRatio2 = std::lerp(1.0f, 0.5f, circleRatio);

		sf::Vector2f center = sf::Vector2f(windowSize_.x / 2.0f, windowSize_.y / 2.0f);

		musicCircles_[i].SetColor(HSLtoRGB(circleRatio * 360.0f, 100.0f, 50.0f));
		musicCircles_[i].SetRadius(bigCirRad_ * circleRatio2, thickness_ * circleRatio2);
		musicCircles_[i].SetPosition(center);
		musicCircles_[i].SetPitch(3.0f * circleRatio2);
		musicCircles_[i].SetSpeed(circleRatio2);
	}


	backGroundCircle_.setRadius(backCirSize_);
	backGroundCircle_.setOrigin(backCirSize_, backCirSize_);
	backGroundCircle_.setFillColor(sf::Color::White);
	
	rect_.setSize({ bigCirRad_ * 0.7f, 5 });
	rect_.setPosition({ windowSize_.x / 2.0f + bigCirRad_ * 0.4f, windowSize_.y / 2.0f });

	timer_ = 0.0f;
	perlinNoise_ = algo::PerlinNoise(0);
}

void RecursiveMusic::DrawBackground(float dt)
{
	std::ranges::for_each(colorTimer_, [dt](auto& color) { color.second += dt * 10.0f; });
	float interval = 30.0f;
	for (int x = 0; x < windowSize_.x; x += interval)
	{
		for (int y = 0; y < windowSize_.y; y += interval)
		{
			sf::Vector2f pos;
			int colorIndex = std::round((perlinNoise_.IntNoise(y, x) * 0.5f + 0.5f) * COUNT);
			sf::Color color = HSLtoRGB(((float)colorIndex / COUNT) * 360.0f, 100.0f, 50.0f);
			backGroundCircle_.setFillColor(color);
			
			float translation = std::max(0.0f, sin(std::clamp(colorTimer_[colorIndex] - y / 100.0f, 0.0f, PI)));
			backGroundCircle_.setRadius(backCirSize_ + perlinNoise_.IntNoise(x, y) + translation * COUNT);

			pos += sf::Vector2f(x + perlinNoise_.IntNoise(x, y) * interval * 0.2f,
			                    y + perlinNoise_.IntNoise(y, x) * interval * 0.2f);
			backGroundCircle_.setPosition(pos);
			graphics_.Draw(backGroundCircle_);
		}
	}
}

void RecursiveMusic::Update(float dt)
{
	DrawBackground(dt);
	timer_ += dt;
	for (int i = 0; i < COUNT; ++i)
	{
		musicCircles_[i].DrawCircle(graphics_, timer_);
		if (musicCircles_[i].TryPlaySound(timer_))
		{
			colorTimer_[i] = 0.0f;
		}
	}
	graphics_.Draw(rect_);
}

void RecursiveMusic::Destroy()
{
	drumSound_.stop();
	kickSound_.stop();
	pianoSound_.stop();
}
}
