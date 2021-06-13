#pragma once
#include <vector>

//https://solarianprogrammer.com/2012/07/18/perlin-noise-cpp-11/

namespace stuff::algo
{/*
	static float IntNoise(int x)
	{
		x = (x << 13) ^ x;
		return (1.0f - ((x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
	}

	static float IntNoise(int x, int y)
	{
		int n = x + y * 57;
		n = (n << 13) ^ n;
		return (1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
	}

	static float IntNoise(int x, int y, int z)
	{
		int n = x + y * 57 + z * 57 * 57;
		n = (n << 13) ^ n;
		return (1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
	}

	static float LinearInterpolation(float a, float b, float t)
	{
		return (1.0f - t) * a + t * b;
	}

	static float CubicInterpolation(float a0, float a, float b, float b1, float t)
	{
		float P = (b1 - b) - (a0 - a);
		float	Q = (a0 - a) - P;
		float	R = b - a0;
		float	S = a;

		return pow(P * t, 3) + pow(Q * t, 2) + R * t + S;
	}


	static float CosineInterpolation(float a, float b, float t)
	{
		float ft = t * 3.1415927f;
		float f = (1 - cos(ft)) * .5f;
		return  a * (1 - f) + b * f;
	}

	static float SmoothNoise(float x, float y)
	{
		float corners = (IntNoise(x - 1, y - 1) + IntNoise(x + 1, y - 1) + IntNoise(x - 1, y + 1) + IntNoise(x + 1, y + 1)) / 16;
		float sides = (IntNoise(x - 1, y ) + IntNoise(x + 1, y ) + IntNoise(x , y - 1) + IntNoise(x , y + 1)) / 8;
		float center = IntNoise(x, y) / 4;
		return corners + sides + center;
	}

	static float InterpolationNoise(float x, float y)
	{
		int intX = floor(x);
		float fracX = x - intX;

		int intY = floor(y);
		float fracY = y - intY;

		float v1 = SmoothNoise(intX, intY);
		float v2 = SmoothNoise(intX+1, intY);
		float v3 = SmoothNoise(intX, intY+1);
		float v4 = SmoothNoise(intX+1, intY+1);

		float i1 = LinearInterpolation(v1, v2, fracX);
		float i2 = LinearInterpolation(v3, v4, fracX);
		return LinearInterpolation(i1, i2, fracY);
	}

	static float PerlinNoiseFunc(float x, float y, float persistance, float octaves = 5)
	{
		float total = 0;

		for (int i = 0; i < octaves; ++i)
		{
			float frequency = pow(2, i);
			float amplitude = pow(persistance, i);

			total += InterpolationNoise(x * frequency, y * frequency) * amplitude;
		}

		return total;
	}

	static float SmoothNoise(float x, float y, float z)
	{
		float corners = (IntNoise(x - 1, y - 1, z - 1) + IntNoise(x + 1, y - 1, z - 1) + IntNoise(x - 1, y + 1, z - 1) + IntNoise(x + 1, y + 1, z - 1) +
						 IntNoise(x - 1, y - 1, z + 1) + IntNoise(x + 1, y - 1, z + 1) + IntNoise(x - 1, y + 1, z + 1) + IntNoise(x + 1, y + 1, z + 1)) / 32;
		float sides = (IntNoise(x - 1, y, z - 1) + IntNoise(x + 1, y, z - 1) + IntNoise(x, y - 1, z - 1) + IntNoise(x, y + 1, z - 1)+
					   IntNoise(x - 1, y, z + 1) + IntNoise(x + 1, y, z + 1) + IntNoise(x, y - 1, z + 1) + IntNoise(x, y + 1, z + 1)) / 16;
		float center = IntNoise(x, y, z) / 4;
		return corners + sides + center;
	}

	static float InterpolationNoise(float x, float y, float z)
	{
		int intX = floor(x);
		float fracX = x - intX;

		int intY = floor(y);
		float fracY = y - intY;

		int intZ = floor(z);
		float fracZ = z - intZ;

		float x0y0z0 = SmoothNoise(intX, intY, intZ);
		float x1y0z0 = SmoothNoise(intX + 1, intY, intZ);
		float x0y1z0 = SmoothNoise(intX, intY + 1, intZ);
		float x1y1z0 = SmoothNoise(intX + 1, intY + 1, intZ);
		float x0y0z1 = SmoothNoise(intX, intY, intZ+1);
		float x1y0z1 = SmoothNoise(intX + 1, intY, intZ + 1);
		float x0y1z1 = SmoothNoise(intX, intY + 1, intZ + 1);
		float x1y1z1 = SmoothNoise(intX + 1, intY + 1, intZ + 1);

		float y0z0 = LinearInterpolation(x0y0z0, x1y0z0, fracX);
		float y1z0 = LinearInterpolation(x0y1z0, x1y1z0, fracX);
		float y0z1 = LinearInterpolation(x0y0z1, x1y0z1, fracX);
		float y1z1 = LinearInterpolation(x0y1z1, x1y1z1, fracX);

		float z0 = LinearInterpolation(y0z0, y1z0, fracY);
		float z1 = LinearInterpolation(y0z1, y1z1, fracY);
		return LinearInterpolation(z0, z1, fracZ);
	}

	static float PerlinNoiseFunc3D(float x, float y, float z, float persistance, float octaves = 5)
	{
		float total = 0;

		for (int i = 0; i < octaves; ++i)
		{
			float frequency = pow(2, i);
			float amplitude = pow(persistance, i);

			total += InterpolationNoise(x * frequency, y * frequency, z * frequency) * amplitude;
		}

		return total;
	}*/

constexpr unsigned X_NOISE_GEN = 31;
constexpr unsigned Y_NOISE_GEN = 211;
constexpr unsigned Z_NOISE_GEN = 409;
constexpr unsigned SEED_NOISE_GEN = 1009;
class PerlinNoise
{
public:
	PerlinNoise() = default;
	explicit PerlinNoise(unsigned int seed);
	float CalculateNoise(float x, float y, float z, float persistance, float octaves);
	float InterpolationNoise(float x, float y, float z);
	float SmoothNoise(float x, float y, float z);
	float Lerp(float a, float b, float t);
	//Random beetween -1 and 1
	float IntNoise(int x);
	float IntNoise(int x, int y, int z);
private:
	unsigned seed_ = 0;
};
}
