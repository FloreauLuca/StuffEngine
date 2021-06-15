#pragma once
#include <vector>

//https://solarianprogrammer.com/2012/07/18/perlin-noise-cpp-11/

namespace stuff::algo
{
constexpr unsigned X_NOISE_GEN = 31;
constexpr unsigned Y_NOISE_GEN = 211;
constexpr unsigned Z_NOISE_GEN = 409;
constexpr unsigned W_NOISE_GEN = 601;
constexpr unsigned SEED_NOISE_GEN = 1009;
class PerlinNoise
{
public:
	PerlinNoise() = default;
	explicit PerlinNoise(unsigned int seed);
	float CalculateNoise(float x, float y = 0, float z = 0, float w = 0);
	
	float InterpolationNoise(float x, float y);
	float InterpolationNoise(float x, float y, float z);
	float InterpolationNoise(float x, float y, float z, float w);
	
	float SmoothNoise(float x, float y);
	float SmoothNoise(float x, float y, float z);
	float SmoothNoise(float x, float y, float z, float w);
	
	float Lerp(float a, float b, float t);
	//Random beetween -1 and 1
	float IntNoise(int x);
	float IntNoise(int x, int y, int z = 0, int w = 0);

	void SetPersistance(float persistance) { persistance_ = persistance; }
	void SetOctaves(unsigned octaves) { octaves_ = octaves; }
private:
	unsigned seed_ = 0;
	float persistance_ = 0.0f;
	float octaves_ = 0.0f;
};
}
