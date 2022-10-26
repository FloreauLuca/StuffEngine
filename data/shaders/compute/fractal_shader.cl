#if defined(cl_khr_fp64)
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
#define DOUBLE_SUPPORT_AVAILABLE
#elif defined(cl_amd_fp64)
#pragma OPENCL EXTENSION cl_amd_fp64 : enable
#define DOUBLE_SUPPORT_AVAILABLE
#endif

#if defined(DOUBLE_SUPPORT_AVAILABLE)

// double
typedef double real_t;
typedef double2 real2_t;
typedef double3 real3_t;
typedef double4 real4_t;
typedef double8 real8_t;
typedef double16 real16_t;
#define PI 3.14159265358979323846

#else

// float
typedef float real_t;
typedef float2 real2_t;
typedef float3 real3_t;
typedef float4 real4_t;
typedef float8 real8_t;
typedef float16 real16_t;
#define PI 3.14159265359f
#endif

float noise(size_t x, float time)
{
	return (sin((x * (x * x * 15731 + 789221)) * time) * 0.5f + 1.0f);
}

double magnitude(double2 vector)
{
	return vector.x * vector.x + vector.y * vector.y;
}

uchar4 evaluate_gradient(__global uchar4* colors, double value)
{
	return colors[(uint)value % 6];
}

__kernel void color(__global uchar4* pixels, float time)
{
	size_t index = (get_global_id(1) * get_global_size(0)) + get_global_id(0);
	uchar4 color;
	color.x = (uchar)(((float)get_global_id(0) / get_global_size(0)) * 255 * (cos(time) * 0.5f + 1.0f));
	color.y = (uchar)(((float)get_global_id(1) / get_global_size(1)) * 255 * (sin(time) * 0.5f + 1.0f));
	color.z = (uchar)((1 - (float)get_global_id(0) / get_global_size(0) + get_global_id(1) / get_global_size(1)) * 255) % 255;
	color.w = 255;
	pixels[index] = color;
}

__kernel void julia(__global uchar4* pixels, __global uchar4* colors, double pos_x, double pos_y, double width, double height, int max_iterations, double coeff_x, double coeff_y)
{
	uchar4 black = (uchar4)(0, 0, 0, 255);
	uchar4 white = (uchar4)(255, 255, 255, 255);
	uchar4 red = (uchar4)(255, 0, 0, 255);
	uchar4 green = (uchar4)(0, 255, 0, 255);
	uchar4 blue = (uchar4)(0, 0, 255, 255);

	double2 coord = (double2)(((double)get_global_id(0) / get_global_size(0)), ((double)get_global_id(1) / get_global_size(1)));
	coord -= (double2)(0.5f, 0.5f);
	coord *= (double2)(width, height);
	coord += (double2)(pos_x, pos_y);
	uchar4 color = black;

	int i = 0;
	double2 number = coord;
	while(magnitude(number) < 10 && i < max_iterations)
	{
		double2 temp = number;
		number.x = temp.x * temp.x - temp.y * temp.y;
		number.y = 2 * temp.x * temp.y;
		number.x += coeff_x;
		number.y += coeff_y;
		i++;
	}

	if (i >= max_iterations)
	{
		color = black;
	}
	else
	{
		// color = (uchar4)(i * 15, i * 15, i * 15, 255);
		color = evaluate_gradient(colors, i/5.0);
	}

	size_t index = (get_global_id(1) * get_global_size(0)) + get_global_id(0);
	pixels[index] = color;
}

__kernel void mandelbrot(__global uchar4* pixels, __global uchar4* colors, double pos_x, double pos_y, double width, double height, int max_iterations)
{
	uchar4 black = (uchar4)(0, 0, 0, 255);
	uchar4 white = (uchar4)(255, 255, 255, 255);
	uchar4 red = (uchar4)(255, 0, 0, 255);
	uchar4 green = (uchar4)(0, 255, 0, 255);
	uchar4 blue = (uchar4)(0, 0, 255, 255);

	double2 coord = (double2)(((double)get_global_id(0) / get_global_size(0)), ((double)get_global_id(1) / get_global_size(1)));
	coord -= (double2)(0.5f, 0.5f);
	coord *= (double2)(width, height);
	coord += (double2)(pos_x, pos_y);
	uchar4 color = black;

	int i = 0;
	double2 c;
	double2 number = (double2)(0.0, 0.0);
	while(magnitude(number) < 10 && i < max_iterations)
	{
		double2 temp = number;
		number.x = temp.x * temp.x - temp.y * temp.y;
		number.y = 2 * temp.x * temp.y;
		number += coord;
		i++;
	}

	if (i >= max_iterations)
	{
		color = black;
	}
	else
	{
		// color = (uchar4)(i * 15, i * 15, i * 15, 255);
		color = evaluate_gradient(colors, i/5.0);
	}

	size_t index = (get_global_id(1) * get_global_size(0)) + get_global_id(0);
	pixels[index] = color;
}