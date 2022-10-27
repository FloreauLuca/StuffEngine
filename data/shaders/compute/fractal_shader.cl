#pragma OPENCL EXTENSION cl_khr_fp64 : enable

float noise(size_t x, float time)
{
	return (sin((x * (x * x * 15731 + 789221)) * time) * 0.5f + 1.0f);
}

uchar4 evaluate_gradient(__global uchar4* colors, double value)
{
	return colors[(uint)value % 6];
}

double2 complex_multiply(double2 z1, double2 z2)
{
	return (double2)(z1.x * z2.x - z1.y * z2.y, z1.y * z2.x + z1.x * z2.y);
}

double2 complex_divide(double2 z1, double2 z2)
{
	return (double2)((z1.x * z2.x + z1.y * z2.y)/(z2.x*z2.x + z2.y * z2.y),
	(z1.y * z2.x - z1.x * z2.y)/(z2.x*z2.x + z2.y * z2.y));
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
	while(length(number) < 10 && i < max_iterations)
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
	while(length(number) < 10 && i < max_iterations)
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

__kernel void newton_3(__global uchar4* pixels, __global uchar4* colors, double pos_x, double pos_y, double width, double height, int max_iterations, double2 r_1, double2 r_2, double2 r_3)
{
	uchar4 black = (uchar4)(0, 0, 0, 255);
	uchar4 white = (uchar4)(255, 255, 255, 255);

	double2 coord = (double2)(((double)get_global_id(0) / get_global_size(0)), ((double)get_global_id(1) / get_global_size(1)));
	coord -= (double2)(0.5f, 0.5f);
	coord *= (double2)(width, height);
	coord += (double2)(pos_x, pos_y);
	uchar4 color = black;

	int i = 0;
	double2 number = coord;
	double d_1 = (double)(length(number - r_1));
	double d_2 = (double)(length(number - r_2));
	double d_3 = (double)(length(number - r_3));
	double d_min = (double)(min(min(d_1, d_2), d_3));
	double threshold = 0.001;
	while(d_min > threshold && i < max_iterations)
	{
		double2 num = complex_multiply(complex_multiply(number - r_1, number - r_2), number - r_3);
		double2 denom = complex_multiply(number - r_1, number - r_2) + complex_multiply(number - r_1, number - r_3) + complex_multiply(number - r_2, number - r_3);
		number = number - complex_divide(num, denom);
		d_1 = (double)(length(number - r_1));
		d_2 = (double)(length(number - r_2));
		d_3 = (double)(length(number - r_3));
		d_min = (double)(min(min(d_1, d_2), d_3));
		i++;
	}

	// if (i >= max_iterations)
	// {
	// 	color = black;
	// }
	// else
	if (d_1 < d_2 && d_1 < d_3)
	{
		color = colors[1];
	}
	else if (d_2 < d_1 && d_2 < d_3)
	{
		color = colors[3];
	}
	else
	{
		color = colors[5];
	}

	if (fabs(fmod(coord.x, 0.5)) < 0.005 || fabs(fmod(coord.y, 0.5)) < 0.005)
	{
		color.a -= 100;
	}
	
	if (length(coord - r_1) < 0.01 || length(coord - r_2) < 0.01 || length(coord - r_3) < 0.01)
	{
		color = white;
	}

	size_t index = (get_global_id(1) * get_global_size(0)) + get_global_id(0);
	pixels[index] = color;
}


__kernel void newton_4(__global uchar4* pixels, __global uchar4* colors, double pos_x, double pos_y, double width, double height, int max_iterations, double2 r_1, double2 r_2, double2 r_3, double2 r_4)
{
	uchar4 black = (uchar4)(0, 0, 0, 255);
	uchar4 white = (uchar4)(255, 255, 255, 255);

	double2 coord = (double2)(((double)get_global_id(0) / get_global_size(0)), ((double)get_global_id(1) / get_global_size(1)));
	coord -= (double2)(0.5f, 0.5f);
	coord *= (double2)(width, height);
	coord += (double2)(pos_x, pos_y);
	uchar4 color = black;

	int i = 0;
	double2 number = coord;
	double d_1 = (double)(length(number - r_1));
	double d_2 = (double)(length(number - r_2));
	double d_3 = (double)(length(number - r_3));
	double d_4 = (double)(length(number - r_4));
	double d_min = (double)(min(min(d_1, d_2), min(d_3, d_4)));
	double threshold = 0.001;
	while(d_min > threshold && i < max_iterations)
	{
		double2 num = complex_multiply(complex_multiply(complex_multiply(number - r_1, number - r_2), number - r_3), number - r_4);
		double2 denom = 
			complex_multiply(complex_multiply(number - r_1, number - r_2), number - r_3) +
			complex_multiply(complex_multiply(number - r_1, number - r_2), number - r_4) +
			complex_multiply(complex_multiply(number - r_1, number - r_3), number - r_4) +
			complex_multiply(complex_multiply(number - r_2, number - r_3), number - r_4);
		number = number - complex_divide(num, denom);
		d_1 = (double)(length(number - r_1));
		d_2 = (double)(length(number - r_2));
		d_3 = (double)(length(number - r_3));
		d_4 = (double)(length(number - r_4));
		d_min = (double)(min(min(d_1, d_2), min(d_3, d_4)));
		i++;
	}

	if (d_1 < d_2 && d_1 < d_3 && d_1 < d_4)
	{
		color = colors[1];
	}
	else if (d_2 < d_1 && d_2 < d_3 && d_2 < d_4)
	{
		color = colors[3];
	}
	else if (d_3 < d_1 && d_3 < d_2 && d_3 < d_4)
	{
		color = colors[4];
	}
	else
	{
		color = colors[5];
	}

	if (fabs(fmod(coord.x, 0.5)) < 0.005 || fabs(fmod(coord.y, 0.5)) < 0.005)
	{
		color.a -= 100;
	}
	
	if (length(coord - r_1) < 0.01 || length(coord - r_2) < 0.01 || length(coord - r_3) < 0.01 || length(coord - r_4) < 0.01)
	{
		color = white;
	}

	size_t index = (get_global_id(1) * get_global_size(0)) + get_global_id(0);
	pixels[index] = color;
}