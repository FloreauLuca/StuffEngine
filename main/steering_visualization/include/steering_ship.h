#pragma once
#include <SFML/Graphics.hpp>

#include "algo/steering/flee_behavior.h"
#include "algo/steering/seek_behavior.h"
#include "engine/engine.h"
#include "engine/system.h"

//https://gamedevelopment.tutsplus.com/series/understanding-steering-behaviors--gamedev-12732

namespace stuff
{
	class SteeringShip final : FleeBehavior, SeekBehavior
	{
	public:
		SteeringShip(float size = 25.0f, float rot = 0.0f, sf::Color color = sf::Color::Red,
		             sf::Vector2f pos = sf::Vector2f(0, 0));

		void Init();
		void Update(float dt);
		void Destroy();

		void SetSize(float size);
		void SetPosition(sf::Vector2f pos);
		void SetColor(sf::Color color);
		void SetRotation(float rot);
		
		float GetSize() const;
		sf::Vector2f GetPosition() const;
		sf::Color GetColor() const;
		float GetRotation() const;

		void Draw(Graphics& graphics);

		void LookAt(sf::Vector2f pos);

		void SetTarget(sf::Vector2f target);
	
	private:
		
		float timer_ = 0.0f;
		
		sf::CircleShape triangle_;

		sf::Vector2f target_;

		sf::Vector2f velocity_;
		float max_velocity_ = 300.0f;
		float force_percent_ = 0.1f;

	};
}
