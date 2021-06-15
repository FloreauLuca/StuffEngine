#include <algo/noise/perlin_noise.h>

#include <numeric>
#include <random>

//http://freespace.virgin.net/hugo.elias/models/m_perlin.htm

namespace stuff::algo
{

PerlinNoise::PerlinNoise(unsigned seed) : seed_(seed)
{
}

float PerlinNoise::CalculateNoise(float x, float y, float z, float w)
{
	float total = 0;

	for (int i = 0; i < octaves_; ++i)
	{
		float frequency = pow(2, i);
		float amplitude = pow(persistance_, i);
		if (w == 0)
		{
			if (z == 0)
			{
				total += InterpolationNoise(x * frequency, y * frequency) * amplitude;
			} else
			{
				total += InterpolationNoise(x * frequency, y * frequency, z * frequency) * amplitude;
			}
		} else
		{
			total += InterpolationNoise(x * frequency, y * frequency, z * frequency, w * frequency) * amplitude;
		}
	}

	return total;
}

float PerlinNoise::InterpolationNoise(float x, float y)
{
	int intX = floor(x);
	float fracX = x - intX;

	int intY = floor(y);
	float fracY = y - intY;

	float x0y0 = SmoothNoise(intX, intY);
	float x1y0 = SmoothNoise(intX + 1, intY);
	float x0y1 = SmoothNoise(intX, intY + 1);
	float x1y1 = SmoothNoise(intX + 1, intY + 1);

	float y0 = Lerp(x0y0, x1y0, fracX);
	float y1 = Lerp(x0y1, x1y1, fracX);
	return Lerp(y0, y1, fracY);
}

float PerlinNoise::InterpolationNoise(float x, float y, float z)
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
	float x0y0z1 = SmoothNoise(intX, intY, intZ + 1);
	float x1y0z1 = SmoothNoise(intX + 1, intY, intZ + 1);
	float x0y1z1 = SmoothNoise(intX, intY + 1, intZ + 1);
	float x1y1z1 = SmoothNoise(intX + 1, intY + 1, intZ + 1);

	float y0z0 = Lerp(x0y0z0, x1y0z0, fracX);
	float y1z0 = Lerp(x0y1z0, x1y1z0, fracX);
	float y0z1 = Lerp(x0y0z1, x1y0z1, fracX);
	float y1z1 = Lerp(x0y1z1, x1y1z1, fracX);

	float z0 = Lerp(y0z0, y1z0, fracY);
	float z1 = Lerp(y0z1, y1z1, fracY);
	return Lerp(z0, z1, fracZ);
}

float PerlinNoise::InterpolationNoise(float x, float y, float z, float w)
{
	int intX = floor(x);
	float fracX = x - intX;

	int intY = floor(y);
	float fracY = y - intY;

	int intZ = floor(z);
	float fracZ = z - intZ;

	int intW = floor(w);
	float fracW = w - intW;

	float x0y0z0w0 = SmoothNoise(intX, intY, intZ, intW);
	float x1y0z0w0 = SmoothNoise(intX + 1, intY, intZ, intW);
	float x0y1z0w0 = SmoothNoise(intX, intY + 1, intZ, intW);
	float x1y1z0w0 = SmoothNoise(intX + 1, intY + 1, intZ, intW);
	float x0y0z1w0 = SmoothNoise(intX, intY, intZ + 1, intW);
	float x1y0z1w0 = SmoothNoise(intX + 1, intY, intZ + 1, intW);
	float x0y1z1w0 = SmoothNoise(intX, intY + 1, intZ + 1, intW);
	float x1y1z1w0 = SmoothNoise(intX + 1, intY + 1, intZ + 1, intW);
	float x0y0z0w1 = SmoothNoise(intX, intY, intZ, intW + 1);
	float x1y0z0w1 = SmoothNoise(intX + 1, intY, intZ, intW + 1);
	float x0y1z0w1 = SmoothNoise(intX, intY + 1, intZ, intW + 1);
	float x1y1z0w1 = SmoothNoise(intX + 1, intY + 1, intZ, intW + 1);
	float x0y0z1w1 = SmoothNoise(intX, intY, intZ + 1, intW + 1);
	float x1y0z1w1 = SmoothNoise(intX + 1, intY, intZ + 1, intW + 1);
	float x0y1z1w1 = SmoothNoise(intX, intY + 1, intZ + 1, intW + 1);
	float x1y1z1w1 = SmoothNoise(intX + 1, intY + 1, intZ + 1, intW + 1);

	float y0z0w0 = Lerp(x0y0z0w0, x1y0z0w0, fracX);
	float y1z0w0 = Lerp(x0y1z0w0, x1y1z0w0, fracX);
	float y0z1w0 = Lerp(x0y0z1w0, x1y0z1w0, fracX);
	float y1z1w0 = Lerp(x0y1z1w0, x1y1z1w0, fracX);
	float y0z0w1 = Lerp(x0y0z0w1, x1y0z0w1, fracX);
	float y1z0w1 = Lerp(x0y1z0w1, x1y1z0w1, fracX);
	float y0z1w1 = Lerp(x0y0z1w1, x1y0z1w1, fracX);
	float y1z1w1 = Lerp(x0y1z1w1, x1y1z1w1, fracX);

	float z0w0 = Lerp(y0z0w0, y1z0w0, fracY);
	float z1w0 = Lerp(y0z1w0, y1z1w0, fracY);
	float z0w1 = Lerp(y0z0w1, y1z0w1, fracY);
	float z1w1 = Lerp(y0z1w1, y1z1w1, fracY);

	float w0 = Lerp(z0w0, z1w0, fracZ);
	float w1 = Lerp(z0w1, z1w1, fracZ);
	return Lerp(w0, w1, fracW);
}

float PerlinNoise::SmoothNoise(float x, float y)
{
	//Beetween -1/4 1/4
	float corners = (
		IntNoise(x - 1, y - 1) + IntNoise(x + 1, y - 1) + IntNoise(x - 1, y + 1) + IntNoise(x + 1, y + 1)
		) / 16;
	//Beetween -1/2 1/2
	float sides = (
		IntNoise(x - 1, y) + IntNoise(x + 1, y) + IntNoise(x, y - 1) + IntNoise(x, y + 1)
		) / 8;
	//Beetween -1/4 1/4
	float center = IntNoise(x, y) / 4;
	return corners + sides + center;
}

float PerlinNoise::SmoothNoise(float x, float y, float z)
{
	//Beetween -1/4 1/4
	float corners = (
		IntNoise(x - 1, y - 1, z - 1) + IntNoise(x + 1, y - 1, z - 1) + IntNoise(x - 1, y + 1, z - 1) + IntNoise(x + 1, y + 1, z - 1) +
		IntNoise(x - 1, y - 1, z + 1) + IntNoise(x + 1, y - 1, z + 1) + IntNoise(x - 1, y + 1, z + 1) + IntNoise(x + 1, y + 1, z + 1)
		) / 64;
	//Beetween -1/2 1/2
	float sides = (
		IntNoise(x - 1, y, z - 1) + IntNoise(x + 1, y, z - 1) + IntNoise(x, y - 1, z - 1) + IntNoise(x, y + 1, z - 1) +
		IntNoise(x - 1, y, z + 1) + IntNoise(x + 1, y, z + 1) + IntNoise(x, y - 1, z + 1) + IntNoise(x, y + 1, z + 1)
		) / 32;
	//Beetween -1/4 1/4
	float center = IntNoise(x, y, z) / 4;
	return corners + sides + center;
}

float PerlinNoise::SmoothNoise(float x, float y, float z, float w)
{
	//Beetween -1/4 1/4
	float corners = (
		IntNoise(x - 1, y - 1, z - 1, w - 1) + IntNoise(x + 1, y - 1, z - 1, w - 1) + IntNoise(x - 1, y + 1, z - 1, w - 1) + IntNoise(x + 1, y + 1, z - 1, w - 1) +
		IntNoise(x - 1, y - 1, z + 1, w - 1) + IntNoise(x + 1, y - 1, z + 1, w - 1) + IntNoise(x - 1, y + 1, z + 1, w - 1) + IntNoise(x + 1, y + 1, z + 1, w - 1) +
		IntNoise(x - 1, y - 1, z - 1, w + 1) + IntNoise(x + 1, y - 1, z - 1, w + 1) + IntNoise(x - 1, y + 1, z - 1, w + 1) + IntNoise(x + 1, y + 1, z - 1, w + 1) +
		IntNoise(x - 1, y - 1, z + 1, w + 1) + IntNoise(x + 1, y - 1, z + 1, w + 1) + IntNoise(x - 1, y + 1, z + 1, w + 1) + IntNoise(x + 1, y + 1, z + 1, w + 1)
		) / 64;
	//Beetween -1/2 1/2
	float sides = (
		IntNoise(x - 1, y, z - 1, w - 1) + IntNoise(x + 1, y, z - 1, w - 1) + IntNoise(x, y - 1, z - 1, w - 1) + IntNoise(x, y + 1, z - 1, w - 1) +
		IntNoise(x - 1, y, z + 1, w - 1) + IntNoise(x + 1, y, z + 1, w - 1) + IntNoise(x, y - 1, z + 1, w - 1) + IntNoise(x, y + 1, z + 1, w - 1) +
		IntNoise(x - 1, y, z - 1, w + 1) + IntNoise(x + 1, y, z - 1, w + 1) + IntNoise(x, y - 1, z - 1, w + 1) + IntNoise(x, y + 1, z - 1, w + 1) +
		IntNoise(x - 1, y, z + 1, w + 1) + IntNoise(x + 1, y, z + 1, w + 1) + IntNoise(x, y - 1, z + 1, w + 1) + IntNoise(x, y + 1, z + 1, w + 1)
		) / 32;
	//Beetween -1/4 1/4
	float center = IntNoise(x, y, z, w) / 4;
	return corners + sides + center;
}

float PerlinNoise::Lerp(float a, float b, float t)
{
	return (1.0f - t) * a + t * b;
}
//Random beetween -1 and 1
float PerlinNoise::IntNoise(int x)
{
	x = (x << 13) ^ x;
	return (1.0f - ((x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
}
float PerlinNoise::IntNoise(int x, int y, int z, int w)
{
	int n = (
		X_NOISE_GEN * x
		+ Y_NOISE_GEN * y
		+ Z_NOISE_GEN * z
		+ W_NOISE_GEN * w
		+ SEED_NOISE_GEN * seed_)
		& 0x7fffffff;
	return IntNoise(n);
}
}
