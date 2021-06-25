#pragma once
#include <SFML/Graphics.hpp>

#include "engine/engine.h"
#include "engine/system.h"
#include "math/vector.h"

namespace stuff
{
	class Graphics;
	class Engine;

	class Boid
	{
	public:
		Boid(sf::Vector2f pos = sf::Vector2f(0, 0), float size = 25.0f, float rot = 0.0f, sf::Color color = sf::Color::Red)
		{
			triangle_ = sf::CircleShape(size, 3);
			triangle_.setOrigin(size, size);
			triangle_.setPosition(pos);
			triangle_.setRotation(rot);
			triangle_.setFillColor(color);
			pos_ = pos;
			velocity_ = normalize(sf::Vector2f((rand() % 100) - 50, (rand() % 100) - 50)) * max_speed_;
		}

		sf::Vector2f Align(std::vector<Boid>& boids)
		{
			sf::Vector2f steering;
			float total = 0;
			for (int i = 0; i < boids.size(); ++i)
			{
				float dist = magnitude(pos_ - boids[i].pos_);
				if (&boids[i] != this && dist < perception)
				{
					steering += boids[i].velocity_;
					total++;
				}
			}
			if (total > 0)
			{
				steering /= total;
				steering = normalize(steering) * max_speed_;
				steering -= velocity_;

				steering = truncate(steering, max_force_);
			}
			return steering;
		}


		sf::Vector2f Cohesion(std::vector<Boid>& boids)
		{
			sf::Vector2f steering;
			float total = 0;
			for (int i = 0; i < boids.size(); ++i)
			{
				float dist = magnitude(pos_ - boids[i].pos_);
				if (&boids[i] != this && dist < perception)
				{
					steering += boids[i].pos_;
					total++;
				}
			}
			if (total > 0)
			{
				steering /= total;
				steering -= pos_;
				steering = normalize(steering) * max_speed_;
				steering -= velocity_;
				steering = normalize(steering) * max_force_;
			}
			return steering;
		}

		sf::Vector2f Seperation(std::vector<Boid>& boids)
		{
			sf::Vector2f steering;
			float total = 0;
			for (int i = 0; i < boids.size(); ++i)
			{
				float dist = magnitude(pos_ - boids[i].pos_);
				if (&boids[i] != this && dist < perception)
				{
					sf::Vector2f diff = pos_ - boids[i].pos_;
					diff /= dist;
					steering += diff;
					total++;
				}
			}
			if (total > 0)
			{
				steering /= total;
				steering = normalize(steering) * max_speed_;
				steering -= velocity_;
				steering = normalize(steering) * max_force_;
			}
			return steering;
		}

		void Edge(sf::Vector2u windowSize)
		{
			if (pos_.x > windowSize.x) pos_ = { 0, pos_.y };
			if (pos_.y > windowSize.y) pos_ = { pos_.x, 0 };
			if (pos_.x < 0) pos_ = { static_cast<float>(windowSize.x), pos_.y };
			if (pos_.y < 0) pos_ = { pos_.x , static_cast<float>(windowSize.y) };
		}
		
		void Flock(std::vector<Boid>& boids,
			float align_force_ = 0.5f,
			float cohesion_force_ = 0.5f,
			float seperation_force_ = 0.5f)
		{
			sf::Vector2f alignement = Align(boids);
			alignement *= align_force_;
			acc_ = alignement;
			sf::Vector2f cohesion = Cohesion(boids);
			cohesion *= cohesion_force_;
			acc_ += cohesion;
			sf::Vector2f seperation = Seperation(boids);
			seperation *= seperation_force_;
			acc_ += seperation;
		}

		void Update(float dt)
		{
			velocity_ += acc_ * dt;
			velocity_ = truncate(velocity_, max_speed_);
			pos_ += velocity_ * dt;

		}

		void Draw(Graphics& graphics, sf::Vector2u windowSize)
		{
			triangle_.setPosition(pos_);
			triangle_.setFillColor(sf::Color(pos_.x / windowSize.x * 255, pos_.y / windowSize.y * 255, (1 - (pos_.x + pos_.y) / (windowSize.x + windowSize.y)) * 255));
			graphics.Draw(triangle_);
		}

		sf::Vector2f pos_;
		sf::Vector2f velocity_;
	private:
		float max_speed_ = 400.0f;
		float max_force_ = 500.0;
		float perception = 100;
		sf::Vector2f acc_;

		sf::CircleShape triangle_;


	};

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
		
		const float shipSize_ = 25.0f;
		const unsigned boidNb_ = 50;
		std::vector<Boid> boids_;

		float align_force_ = 0.5f;
		float cohesion_force_ = 0.5f;
		float seperation_force_ = 0.5f;
	};
}
