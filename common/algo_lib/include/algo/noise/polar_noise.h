#pragma once
#include <vector>

#include "perlin_noise.h"

//https://solarianprogrammer.com/2012/07/18/perlin-noise-cpp-11/

namespace stuff::algo
{
	class PolarNoise
	{
	public:
		PolarNoise() = default;
		explicit PolarNoise(float diameter, unsigned seed);
		float CalculateNoise(float x);
		float CalculateNoise(float x, float y, float z);
		void SetPersistance(float persistance) { perlinNoise_.SetPersistance(persistance); }
		void SetOctaves(unsigned octaves) { perlinNoise_.SetOctaves(octaves); }
	private:
		float diameter_ = 0;
		unsigned deltaX_ = 0;
		unsigned deltaY_ = 0;
		algo::PerlinNoise perlinNoise_;
	};
}
