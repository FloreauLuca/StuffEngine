#include "water_particle.h"

#include "water_physics.h"
#include "config.h"

namespace stuff
{
	WaterParticle::WaterParticle(sf::Vector2f position, float size)
	{
		size_ = size;
		position_ = position;
	}

	void WaterParticle::Update(float dt)
	{
		if (position_.y + size_ > Config::MAX_Y)
		{
			sf::Vector2f normal = sf::Vector2f(0, -1);
			SurfaceBounce(normal, sf::Vector2f(position_.x, Config::MAX_Y - size_));
		}
		
		if (position_.x - size_ < Config::MIN_X)
		{
			sf::Vector2f normal = sf::Vector2f(1, 0);
			SurfaceBounce(normal, sf::Vector2f(Config::MIN_X + size_, position_.y));
		}

		if (position_.x + size_ > Config::MAX_X)
		{
			sf::Vector2f normal = sf::Vector2f(-1, 0);
			SurfaceBounce(normal, sf::Vector2f(Config::MAX_X - size_, position_.y));
		}

		prev_position_ = position_;

		velocity_ += force_ * dt;

		position_ += velocity_ * dt;

		force_ = sf::Vector2f(0, -Config::GRAVITY);

		velocity_ = (position_ - prev_position_) / dt;
		
		speed_ = Magnitude(velocity_);

		// Set to MAX_VEL if velocity is greater than MAX_VEL
		if (speed_ > Config::MAX_SPEED)
		{
			velocity_ = velocity_ / speed_ * Config::MAX_SPEED;
		}

		// Reset density
		rho_ = 0.0f;
		rho_near_ = 0.0f;

		// Reset neighbors
		neighbor_.clear();
	}

	void WaterParticle::CalculatePressure()
	{
		press_ = Config::K * (rho_ - Config::REST_DENSITY);
		press_near_ = Config::K_NEAR * rho_near_;
	}
	
	void WaterParticle::SurfaceBounce(sf::Vector2f normal, sf::Vector2f wallPos)
	{
		float vel_normal = Dot(velocity_, normal);
		if (vel_normal > 0)
		{
			return;
		}

		sf::Vector2f vel_tangent = velocity_ - normal * vel_normal;
		velocity_ = vel_tangent - normal * vel_normal * Config::WALL_DAMP;
		position_ = wallPos + normal * 0.0008f;
	}

	void WaterParticle::Draw(Graphics& graphics)
	{
		sf::Vector2u windowSize = graphics.GetWindowSize();
		sf::CircleShape circle(size_ * windowSize.x);
		circle.setOrigin(size_ * windowSize.x, size_ * windowSize.y);
		circle.setPosition(position_ * windowSize);
		circle.setFillColor(sf::Color(200 * (1.0f-position_.y), 200 * (1.0f - position_.y), 255, 255));
		graphics.Draw(circle);

		for (WaterParticle* neighbor : neighbor_)
		{
			sf::VertexArray line;
			line.setPrimitiveType(sf::Lines);
			line.append(sf::Vertex(position_ * windowSize, sf::Color(255, 255, 255, 5)));
			line.append(sf::Vertex(neighbor->position_ * windowSize, sf::Color(255, 255, 255, 5)));
			graphics.Draw(line);
		}
	}
}