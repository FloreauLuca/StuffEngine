#include "flocking_visualization.h"

#include <iostream>
#include <numeric>

#include "math/const.h"
#include "utility/data_location.h"


namespace stuff
{
	void FlockingVisualization::Init()
	{
		if (!waveSoundBuffer_.loadFromFile(dataPath + "wave.wav"))
		{
			std::cout << "Sound fail to load" << std::endl;
		}
		waveSound_.setBuffer(waveSoundBuffer_);
		waveSound_.setLoop(true);
		//waveSound_.play();
		waveSound_.setPitch(1.0);
		
		timer_ = 0;
		windowSize_ = graphics_.GetWindowSize();
		float radius = windowSize_.x / 4.0f;
		for (int i = 0; i < boidNb_; ++i)
		{
			boids_.push_back(Boid(sf::Vector2f(rand() % windowSize_.x, rand()%windowSize_.y),shipSize_));
		}
	}
	
	void FlockingVisualization::Update(float dt)
	{
		timer_ += dt * 2.0f;
		float radius = /*(sinf(timer_) + 1)/2 **/ (windowSize_.x / 2.0f);

		sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*graphics_.GetWindow()));
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) align_force_ -= 0.1f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) align_force_ += 0.1f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) cohesion_force_ -= 0.1f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) cohesion_force_ += 0.1f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) seperation_force_ -= 0.1f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) seperation_force_ += 0.1f;
		sf::Text text;
		text.setString("Align : " + std::to_string(align_force_));
		text.setPosition(10, 10);
		graphics_.Draw(text);
		text.setString("Cohesion : " + std::to_string(cohesion_force_));
		text.setPosition(10, 30);
		graphics_.Draw(text);
		text.setString("Seperation : " + std::to_string(seperation_force_));
		text.setPosition(10, 50);
		graphics_.Draw(text);
		sf::Vector2f sum = boids_[(static_cast<int>(timer_ * 5.0f)) % boidNb_].GetPosition();
		std::vector<algo::SteeringBehavior> steers;
		for (auto& boid : boids_)
		{
			steers.push_back(boid);
		}
		for (unsigned i = 0; i < boidNb_; ++i)
		{
			boids_[i].Edge(windowSize_);
			boids_[i].Update(dt, steers, windowSize_, align_force_, cohesion_force_, seperation_force_);
			boids_[i].Draw(graphics_, windowSize_);
		}
		sum = normalize(sum) * 1.0f;
		waveSound_.setPitch(sum.x);
		waveSound_.setVolume(sum.y * 50.0f);
	}

	void FlockingVisualization::Destroy()
	{
		waveSound_.stop();
	}
}
