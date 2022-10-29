#pragma OPENCL EXTENSION cl_khr_fp64 : enable

float noise(size_t x, float time)
{
	return (sin((x * (x * x * 15731 + 789221)) * time) * 0.5f + 1.0f);
}

float sqr_length(double2 z)
{
	return z.x * z.x + z.y * z.y;
}

float sqr_distance(double2 z1, double2 z2)
{
	return sqr_length(z1 - z2);
}

uchar4 evaluate_gradient(__global uchar4* colors, double value)
{       
	// float count = (colors.size()-1) * t;
	// int prev = floor(count);
	// int next = ceil(count);
	// return (uchar4)(
	// 	lerp(colors[prev].r, colors[next].r, count - prev),
	// 	lerp(colors[prev].g, colors[next].g, count - prev),
	// 	lerp(colors[prev].b, colors[next].b, count - prev),
	// 	lerp(colors[prev].w, colors[next].w, count - prev)
	// 	);
	return colors[(uint)value % 6];
}

uchar4 HSLtoRGB(double H, double S, double L, double A) 
{
    float s = clamp((float)S, 0.0f, 100.0f) / 100;
    float l = clamp((float)L, 0.0f, 100.0f) / 100;
	
    float C = (1 - fabs((float)(2*l - 1))) * s;
    float X = C * (1 - fabs((float)fmod(clamp((float)H, 0.0f, 360.0f) / 60.0f, 2) - 1));
    float m = l - C/2.0f;
    float r, g, b;
    if (H < 60) {
        r = C;
        g = X;
    	b = 0;
    }
    else if (H >= 60 && H < 120) {
        r = X;
        g = C;
    	b = 0;
    }
    else if (H >= 120 && H < 180) {
        r = 0;
        g = C;
    	b = X;
    }
    else if (H >= 180 && H < 240) {
        r = 0;
        g = X;
        b = C;
    }
    else if (H >= 240 && H < 300) {
        r = X;
        g = 0;
        b = C;
    }
    else {
        r = C;
        g = 0;
    	b = X;
    }
    uchar R = (r + m) * 255;
    uchar G = (g + m) * 255;
    uchar B = (b + m) * 255;
    return (uchar4)(R, G, B, A);
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

double2 get_coord(double2 center, double2 screen, double zoom)
{
	double2 coord = (double2)(((double)get_global_id(0) / get_global_size(0)), ((double)get_global_id(1) / get_global_size(1)));
	coord -= (double2)(0.5f, 0.5f);
	coord *= screen / min(screen.x, screen.y);
	coord *= zoom;
	coord += center;
	return coord;
}

__kernel void color(__global uchar4* pixels, float time)
{
	size_t index = (get_global_id(1) * get_global_size(0)) + get_global_id(0);
	uchar4 color;
	double2 coord = get_coord((double2)(0.0, 0.0), (double2)(1.0, 1.0), 1.0);
	color.x = (uchar)((coord.x) * 255 * (cos(time) * 0.5f + 1.0f));
	color.y = (uchar)((coord.y) * 255 * (sin(time) * 0.5f + 1.0f));
	color.z = (uchar)((1 - coord.x + coord.y) * 255) % 255;
	color.w = 255;
	pixels[index] = color;
}

__kernel void julia(
	__global uchar4* pixels, __global uchar4* colors, double2 center, double2 screen, double zoom,
	int max_iterations, double2 coeff
	)
{
	uchar4 black = (uchar4)(0, 0, 0, 255);
	uchar4 white = (uchar4)(255, 255, 255, 255);
	uchar4 red = (uchar4)(255, 0, 0, 255);
	uchar4 green = (uchar4)(0, 255, 0, 255);
	uchar4 blue = (uchar4)(0, 0, 255, 255);

	double2 coord = get_coord(center, screen, zoom);
	uchar4 color = black;

	int i = 0;
	double2 number = coord;
	while(length(number) < 10 && i < max_iterations)
	{
		double2 temp = number;
		number.x = temp.x * temp.x - temp.y * temp.y;
		number.y = 2 * temp.x * temp.y;
		number.x += coeff.x;
		number.y += coeff.y;
		i++;
	}

	if (i >= max_iterations || i < 3)
	{
		color = black;
	}
	else
	{
		color = evaluate_gradient(colors, i/5.0);
	}

	size_t index = (get_global_id(1) * get_global_size(0)) + get_global_id(0);
	pixels[index] = color;
}

__kernel void mandelbrot(
	__global uchar4* pixels, __global uchar4* colors, double2 center, double2 screen, double zoom,
	int max_iterations
	)
{
	uchar4 black = (uchar4)(0, 0, 0, 255);
	uchar4 white = (uchar4)(255, 255, 255, 255);
	uchar4 red = (uchar4)(255, 0, 0, 255);
	uchar4 green = (uchar4)(0, 255, 0, 255);
	uchar4 blue = (uchar4)(0, 0, 255, 255);

	double2 coord = get_coord(center, screen, zoom);
	uchar4 color = black;

	int i = 0;
	double2 c;
	double2 number = (double2)(0.0, 0.0);
	while(sqr_length(number) < 10 && i < max_iterations)
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
		color = evaluate_gradient(colors, log2((double)i+60) * 10);
	}

	size_t index = (get_global_id(1) * get_global_size(0)) + get_global_id(0);
	pixels[index] = color;
}

__kernel void newton_N(
	__global uchar4* pixels, __global uchar4* colors, double2 center, double2 screen, double zoom,
	int max_iterations, __global double2* roots, int nb_roots, int display_grid
	)
{
	uchar4 black = (uchar4)(0, 0, 0, 255);
	uchar4 white = (uchar4)(255, 255, 255, 255);

	double2 coord = get_coord(center, screen, zoom);
	uchar4 color = black;

	int i = 0;
	double2 number = coord;
	double2 r_1 = roots[0];
	double2 r_2 = roots[1];
	double2 r_3 = roots[2];
	double2 r_4 = roots[3];
	double d_min = DBL_MAX;
	for (int i = 0; i < nb_roots; i++)
	{
		double d_N = (double)(sqr_distance(number, roots[i]));
		d_min = (double)(min(d_min, d_N));
	}
	double threshold = 0.001;
	while(d_min > threshold && i < max_iterations)
	{
		double2 num = number - roots[0];
		for (int i = 1; i < nb_roots; i++)
		{
			num = complex_multiply(num, number - roots[i]);
		}
		//double2 num = complex_multiply(complex_multiply(complex_multiply(number - r_1, number - r_2), number - r_3), number - r_4);
		double2 denom = 0;
		for (int i = 0; i < nb_roots; i++)
		{
			double2 denom_j = 0;
			for (int j = 0; j < nb_roots; j++)
			{
				if(j != i)
				{
					if (denom_j.x == 0.0 && denom_j.y == 0.0)
					{
						denom_j = number - roots[j];
					}
					else
					{
						denom_j = complex_multiply(denom_j, number - roots[j]);
					}
				}
			}
			denom += denom_j;
		}
		number = number - complex_divide(num, denom);
		for (int i = 0; i < nb_roots; i++)
		{
			double d_N = (double)(sqr_distance(number, roots[i]));
			d_min = (double)(min(d_min, d_N));
		}
		i++;
	}

	for (int i = 0; i < nb_roots; i++)
	{
		double d_N = (double)(sqr_distance(number, roots[i]));
		if (d_N <= d_min)
		{
			color = colors[i % 6];
		}
	}

	if (display_grid == 1)
	{
		if (fabs(fmod(coord.x, 0.5)) < 0.005 || fabs(fmod(coord.y, 0.5)) < 0.005)
		{
			color.w -= 100;
		}
	}
	
	for (int i = 0; i < nb_roots; i++)
	{
		if (sqr_distance(coord, roots[i]) < 0.0005)
		{
			color = white;
			break;
		}
	}

	size_t index = (get_global_id(1) * get_global_size(0)) + get_global_id(0);
	pixels[index] = color;
}