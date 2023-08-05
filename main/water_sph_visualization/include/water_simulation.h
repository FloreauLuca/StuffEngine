#pragma once
#include "water_particle.h"

namespace stuff
{
	class WaterSimulation
	{
	public:
        WaterSimulation();
        void AddParticle(WaterParticle* particle);
        void CalculateDensity();
        void CreatePressure();
        void CalculateViscosity();
        void Update(float dt);

        void Draw(Graphics& graphics);

		std::vector<WaterParticle*> particles_;

        int grid_size_x_ = 10;
        int grid_size_y_ = 10;
        std::vector<std::vector<std::vector<WaterParticle*>>> grid_;
        float x_min_ = 0.1;
        float x_max_ = 0.9;
        float y_min_ = 0.0f;
        float y_max_ = 0.9f;
	};
}
