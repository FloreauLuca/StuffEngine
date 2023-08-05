#include "water_simulation.h"

#include "config.h"
#include <water_physics.h>

namespace stuff
{
	WaterSimulation::WaterSimulation()
	{
		// Initialize spatial partitioning grid
		grid_ = std::vector<std::vector<std::vector<WaterParticle*>>>(grid_size_x_);
		for (int i = 0; i < grid_size_x_; i++)
		{
			grid_[i] = std::vector<std::vector<WaterParticle*>>(grid_size_y_);
			for (int j = 0; j < grid_size_y_; j++)
			{
				grid_[i][j] = std::vector<WaterParticle*>();
			}
		}
		particles_ = std::vector<WaterParticle*>();
	}

	void WaterSimulation::AddParticle(WaterParticle* particle)
	{
		particles_.push_back(particle);
	}

	void WaterSimulation::CalculateDensity()
	{
		// For each particle
		for (WaterParticle* particle : particles_)
		{
			float density = 0.0f;
			float density_near = 0.0f;

			// for each particle in the 9 neighboring cells in the spatial partitioning grid
			for (int i = particle->grid_x_ - 1; i <= particle->grid_x_ + 1; i++)
			{
				for (int j = particle->grid_y_ - 1; j <= particle->grid_y_ + 1; j++)
				{
					// If the cell is in the grid
					if (i >= 0 && i < grid_size_x_ && j >= 0 && j < grid_size_y_)
					{
						// For each particle in the cell
						for (WaterParticle* neighbor : grid_[i][j])
						{
							if (neighbor == particle)
							{
								continue;
							}
							// Calculate distance between particles
							float dist = Magnitude(particle->position_ - neighbor->position_);

							if (dist < Config::R)
							{
								float normal_distance = 1 - dist / Config::R;
								particle->rho_ += normal_distance * normal_distance;
								particle->rho_near_ += normal_distance * normal_distance * normal_distance;
								neighbor->rho_ += normal_distance * normal_distance;
								neighbor->rho_near_ += normal_distance * normal_distance * normal_distance;

								// Add n to p's neighbors for later use
								particle->neighbor_.push_back(neighbor);
							}
						}
					}
				}
			}
			particle->rho_ += density;
			particle->rho_near_ += density_near;
		}
	}

	void WaterSimulation::CreatePressure()
	{
		for (WaterParticle* particle : particles_)
		{
			sf::Vector2f pressure_force = sf::Vector2f(0,0);

			for (WaterParticle* neighbor : particle->neighbor_)
			{
				sf::Vector2f particule_to_neighbor = neighbor->position_ - particle->position_;
				float distance = Magnitude(particle->position_ - neighbor->position_);

				float normal_distance = 1 - distance / Config::R;
				float total_pressure = (particle->press_ + neighbor->press_) * normal_distance * normal_distance + (particle->press_near_ + neighbor->press_near_) * normal_distance * normal_distance * normal_distance;
				sf::Vector2f pressure_vector = total_pressure * (particule_to_neighbor / Magnitude(particule_to_neighbor));
				neighbor->force_ += pressure_vector;
				pressure_force += pressure_vector;
			}
			particle->force_ -= pressure_force;
		}
	}

	void WaterSimulation::CalculateViscosity()
	{
		for (WaterParticle* particle : particles_)
		{
			for (WaterParticle* neighbor : particle->neighbor_)
			{
				sf::Vector2f particule_to_neighbor = neighbor->position_ - particle->position_;
				float distance = Magnitude(particle->position_ - neighbor->position_);
				sf::Vector2f normal_p_to_n = (particule_to_neighbor / Magnitude(particule_to_neighbor));
				float relative_distance = distance / Config::R;
				float velocity_difference = Dot(particle->velocity_ - neighbor->velocity_, normal_p_to_n);
				if (velocity_difference > 0.0f)
				{
					sf::Vector2f viscosity_force = (1 - relative_distance) * velocity_difference * Config::SIGMA * normal_p_to_n;
					particle->velocity_ -= viscosity_force * 0.5f;
					neighbor->velocity_ += viscosity_force * 0.5f;
				}
			}
		}
	}

	void WaterSimulation::Update(float dt)
	{
		// Assign particles to spatial partitioning grid
		for (int i = 0; i < grid_size_x_; i++)
		{
			for (int j = 0; j < grid_size_y_; j++)
			{
				grid_[i][j].clear();
			}
		}

		for(WaterParticle* particle : particles_)
		{
			// Assign grid_x and grid_y using x_min y_min x_max y_max
			particle->grid_x_ = (int)((particle->position_.x - x_min_) / (x_max_ - x_min_) * grid_size_x_);
			particle->grid_y_ = (int)((particle->position_.y - y_min_) / (y_max_ - y_min_) * grid_size_y_);

            // Add particle to grid if it is within bounds
            if (particle->grid_x_ >= 0 && particle->grid_x_ < grid_size_x_ && particle->grid_y_ >= 0 && particle->grid_y_ < grid_size_y_)
            {
                grid_[particle->grid_x_][particle->grid_y_].push_back(particle);
            }
        }

		for (WaterParticle* particle : particles_)
		{
			particle->Update(dt);
        }

        CalculateDensity();

		for (WaterParticle* particle : particles_)
		{
			particle->CalculatePressure();
        }

        CreatePressure();

		CalculateViscosity();
	}

	void WaterSimulation::Draw(Graphics& graphics)
	{
	}
}