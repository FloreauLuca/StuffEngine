#include "sound_test.h"

#include <iostream>

#include "engine/system.h"
#include "utility/data_location.h"
#include <imgui.h>
#include <math\vector.h>

namespace stuff
{
void SoundTest::Init()
{
	timer_ = 0;
	if(!waveSoundBuffer_.loadFromFile(dataPath + "long_wave.wav"))
	{
		std::cout << "Sound fail to load" << std::endl;
	}
	waveSound_.setBuffer(waveSoundBuffer_);
	waveSound_.setLoop(true);
	waveSound_.play();
	waveSound2_.setBuffer(waveSoundBuffer_);
	waveSound2_.setLoop(true);
	waveSound2_.play();
	windowSize_ = sf::Vector2f(graphics_.GetWindowSize());
}

void SoundTest::Update(float dt)
{
	timer_ += dt;
	ImGui::Begin("Parameters");
	ImGui::DragFloat("Frequency1", &frequency1_, 0.1f, 0, 10);
	ImGui::DragFloat("Frequency2", &frequency2_, 0.1f, 0, 10);
	ImGui::DragFloat("Ratio", &ratio, 0.01f, 0, 2);
	ImGui::End();
	sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*graphics_.GetWindow()));
	frequency1_ = clamp(mousePos.x / windowSize_.x, 0.0f, 1.0f);
	frequency2_ = clamp(mousePos.y / windowSize_.y, 0.0f, 1.0f);

	waveSound_.setPitch(frequency1_);
	waveSound2_.setPitch(frequency2_);
	waveSound_.setVolume(50);
	waveSound2_.setVolume(ratio * 50);
	sf::CircleShape circle = sf::CircleShape(windowSize_.x * 0.01f);
	sf::Vector2f pos = sf::Vector2f();
	pos.x = frequency1_;
	pos.y = frequency2_;
	pos.x *= windowSize_.x;
	pos.y *= windowSize_.y;
	circle.setPosition(pos);
	graphics_.Draw(circle);
	//std::vector<sf::Int16> samples(2000);
	//int count = waveSoundBuffer_.getSampleCount();
	//std::cout << waveSoundBuffer_.getSampleCount() << std::endl;
	//std::cout << waveSoundBuffer_.getDuration().asSeconds() << std::endl;
	//std::cout << waveSoundBuffer_.getSampleRate() << std::endl;
	//std::cout << waveSoundBuffer_.getChannelCount() << std::endl;
	//std::cout << "=============" << std::endl;
	//std::cin >> count;
	//for (size_t i = 0; i < count; i++)
	//{
	//	std::cout << waveSoundBuffer_.getSamples()[i] << std::endl;
	//}
	//std::cin >> count;
	//std::cout << timer_ << std::endl;
}

void SoundTest::Destroy()
{
	waveSound_.stop();
}
}
