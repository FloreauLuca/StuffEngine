
#include "algo/noise/polar_noise.h"

namespace stuff::algo
{

	PolarNoise::PolarNoise(float diameter, unsigned seed) : diameter_(diameter)
	{
		perlinNoise_ = algo::PerlinNoise(seed);
		deltaX_ = rand()%1024;
		deltaY_ = rand()%1024;
	}

	float PolarNoise::CalculateNoise(float x)
	{
		float xOff = (cosf(x) + 1) / 2 * diameter_ + deltaX_;
		float yOff = (sinf(x) + 1) / 2 * diameter_ + deltaY_;
		float r = perlinNoise_.CalculateNoise(xOff, yOff);
		return r;
	}

	float PolarNoise::CalculateNoise(float x, float y, float z)
	{
		float xOff = (cosf(z) + 1) / 2 * diameter_ + deltaX_;
		float yOff = (sinf(z) + 1) / 2 * diameter_ + deltaY_;
		float r = perlinNoise_.CalculateNoise(x, y, xOff, yOff);
		return r;
	}
}
