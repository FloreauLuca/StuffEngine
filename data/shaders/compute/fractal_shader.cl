#pragma OPENCL EXTENSION cl_khr_fp64 : enable
#define DOUBLE_SUPPORT_AVAILABLE

#if defined(DOUBLE_SUPPORT_AVAILABLE)

// double
typedef double real;
typedef double2 real2;
typedef double3 real3;
typedef double4 real4;
typedef double8 real8;
typedef double16 real16;

#else

// float
typedef float real;
typedef float2 real2;
typedef float3 real3;
typedef float4 real4;
typedef float8 real8;
typedef float16 real16;

#endif

static constant uchar4 black = (uchar4)(0, 0, 0, 255);
static constant uchar4 white = (uchar4)(255, 255, 255, 255);
static constant uchar4 red = (uchar4)(255, 0, 0, 255);
static constant uchar4 green = (uchar4)(0, 255, 0, 255);
static constant uchar4 blue = (uchar4)(0, 0, 255, 255);

float noise(const size_t x, const float time)
{
	return (sin((x * (x * x * 15731 + 789221)) * time) * (real)0.5 + (real)1.0);
}

float sqr_length(const real2 z)
{
	return z.x * z.x + z.y * z.y;
}

float sqr_distance(const real2 z1, const real2 z2)
{
	return sqr_length(z1 - z2);
}

uchar4 evaluate_gradient(__global const uchar4* colors, const real value)
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

uchar4 HSLtoRGB(const real H, const real S, const real L, const real A) 
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

real2 complex_multiply(const real2 z1, const real2 z2)
{
	return (real2)(z1.x * z2.x - z1.y * z2.y, z1.y * z2.x + z1.x * z2.y);
}

real2 complex_divide(const real2 z1, const real2 z2)
{
	return (real2)((z1.x * z2.x + z1.y * z2.y)/(z2.x*z2.x + z2.y * z2.y),
	(z1.y * z2.x - z1.x * z2.y)/(z2.x*z2.x + z2.y * z2.y));
}

real2 get_coord(const real2 center, const real2 screen, const real zoom)
{
	real2 coord = (real2)(((real)get_global_id(0) / get_global_size(0)), ((real)get_global_id(1) / get_global_size(1)));
	coord -= (real2)(0.5f, 0.5f);
	coord *= screen / min(screen.x, screen.y);
	coord *= zoom;
	coord += center;
	return coord;
}

__kernel void color(__global uchar4* pixels, float time)
{
	size_t index = (get_global_id(1) * get_global_size(0)) + get_global_id(0);
	uchar4 color;
	real2 coord = get_coord((real2)(0.0f, 0.0f), (real2)(1.0f, 1.0f), (real)1.0f);
	color.x = (uchar)((coord.x) * 255 * (cos(time) * 0.5f + 1.0f));
	color.y = (uchar)((coord.y) * 255 * (sin(time) * 0.5f + 1.0f));
	color.z = (uchar)((1 - coord.x + coord.y) * 255) % 255;
	color.w = 255;
	pixels[index] = color;
}

__kernel void julia(
	__global uchar4* pixels, __global const uchar4* colors, const double2 center, const double2 screen, const double zoom,
	int max_iterations, double2 coeff
	)
{
	const real2 coord = get_coord((real2)(center.x, center.y), (real2)(screen.x, screen.y), (real)zoom);
	uchar4 color = black;

	int i = 0;
	real2 number = coord;
	while(sqr_length(number) < (real)100.0 && i < max_iterations)
	{
		real2 temp = number;
		number.x = temp.x * temp.x - temp.y * temp.y;
		number.y = 2 * temp.x * temp.y;
		number.x += (real)coeff.x;
		number.y += (real)coeff.y;
		i++;
	}

	if (i >= max_iterations || i < 3)
	{
		color = black;
	}
	else
	{
		color = evaluate_gradient(colors, i/(real)5.0);
	}

	size_t index = (get_global_id(1) * get_global_size(0)) + get_global_id(0);
	pixels[index] = color;
}

__kernel void mandelbrot(
	__global uchar4* pixels, __global const uchar4* colors, const double2 center, const double2 screen, const double zoom,
	int max_iterations
	)
{
	const real2 coord = get_coord((real2)(center.x, center.y), (real2)(screen.x, screen.y), (real)zoom);
	uchar4 color = black;

	int i = 0;
	real2 c;
	real2 number = (real2)(0.0, 0.0);
	while(sqr_length(number) < (real)10.0 && i < max_iterations)
	{
		real2 temp = number;
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
		color = evaluate_gradient(colors, log2((real)i+60) * 10);
	}

	size_t index = (get_global_id(1) * get_global_size(0)) + get_global_id(0);
	pixels[index] = color;
}

real2 get_root(__global const double2* roots, int index)
{
	return (real2)(roots[index].x, roots[index].y);
}

__kernel void newton_N(
	__global uchar4* pixels, __global const uchar4* colors, const double2 center, const double2 screen, const double zoom,
	const int max_iterations, __global const double2* roots, const int nb_roots, const int display_grid
	)
{
	const real2 coord = get_coord((real2)(center.x, center.y), (real2)(screen.x, screen.y), (real)zoom);
	uchar4 color = black;

	int i = 0;
	real2 number = coord;
	real d_min = DBL_MAX;
	for (int roots_index = 0; roots_index < nb_roots; roots_index++)
	{
		d_min = (real)(min(d_min, (real)(sqr_distance(number, get_root(roots,roots_index)))));
	}

	real threshold = (real)0.01;
	while(d_min > threshold && i < max_iterations)
	{
		real2 num = number - get_root(roots,0);
		for (int roots_index = 1; roots_index < nb_roots; roots_index++)
		{
			num = complex_multiply(num, number - get_root(roots,roots_index));
		}
		real2 denom = 0;
		for (int roots_index = 0; roots_index < nb_roots; roots_index++)
		{
			real2 denom_add = 0;
			for (int roots_index_add = 0; roots_index_add < nb_roots; roots_index_add++)
			{
				if(roots_index_add != roots_index)
				{
					if (denom_add.x == (real)0.0 && denom_add.y == (real)0.0)
					{
						denom_add = number - get_root(roots,roots_index_add);
					}
					else
					{
						denom_add = complex_multiply(denom_add, number - get_root(roots,roots_index_add));
					}
				}
			}
			denom += denom_add;
		}
		number = number - complex_divide(num, denom);
		d_min = DBL_MAX;
		for (int roots_index = 0; roots_index < nb_roots; roots_index++)
		{
			real d_N = (real)(sqr_distance(number, get_root(roots,roots_index)));
			d_min = (real)(min(d_min, d_N));
		}
		i++;
	}

	//color = colors[(uint)(((real)i/max_iterations) * 5)];
	for (int roots_index = 0; roots_index < nb_roots; roots_index++)
	{
		real d_N = (real)(sqr_distance(number, get_root(roots,roots_index)));
		if (d_N <= d_min)
		{
			color = colors[(int)(roots_index * ((real)6.0/nb_roots)) % 6];
			break;
		}
	}

	if (display_grid == 1)
	{
		if (fabs(fmod(coord.x, (real)0.5)) < (real)0.005 || fabs(fmod(coord.y, (real)0.5)) < (real)0.005)
		{
			color.w -= 100;
		}
	}
	
	for (int roots_index = 0; roots_index < nb_roots; roots_index++)
	{
		if (sqr_distance(coord, get_root(roots,roots_index)) < (real)0.0005)
		{
			color = white;
			break;
		}
	}

	size_t index = (get_global_id(1) * get_global_size(0)) + get_global_id(0);
	pixels[index] = color;
}