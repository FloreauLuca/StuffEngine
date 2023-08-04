#include "config.h"

namespace stuff
{
	const float Config::PARTICLE_SIZE = 0.025f;
	const unsigned Config::PARTICLE_COUNT = 10;
	const float Config::MIN_X = 0.1f;
	const float Config::MAX_X = 0.9f;
	const float Config::MAX_Y = 0.9f;

    // Physics parameters
    const float Config::GRAVITY = -0.9f;
    const float Config::MAX_SPEED = 0.25f;
    //const float Config::SPACING = 0.08f;  // Spacing between particles, used to calculate pressure
    //const float Config::K = SPACING / 1000.0f;  // Pressure factor
    //const float Config::K_NEAR = K * 10f;  // Near pressure factor, pressure when particles are close to each other
    //const float Config::REST_DENSITY = 3.0f;  // Default density, will be compared to local density to calculate pressure
    //const float Config::R = SPACING * 1.25f;  // Neighbour radius, if the distance between two particles is less than R, they are neighbours
    //const float Config::SIGMA = 0.2f;  // Viscosity factor
    //const float Config::WALL_DAMP = 0.2f;  // Wall constraints factor, how much the particle is pushed away from the simulation walls
    //const float Config::VEL_DAMP = 0.5f;  // Viscosity factor
}