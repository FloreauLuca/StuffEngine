#pragma once
#include <SFML/Graphics.hpp>

#include "engine/engine.h"
#include "engine/system.h"

namespace stuff
{
	const float PI = static_cast<float>(3.14159265358979323846);

	class SteeringShip final
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

		void Draw(Graphics& graphics);

		void LookAt(sf::Vector2f pos);
	private:
		
		float timer_ = 0.0f;
		
		sf::CircleShape triangle_;
		
		sf::Color color_;

		float size_ = 25.0f;

		sf::Vector2f pos_;

		float rot_ = 0.0f;

	};
}
