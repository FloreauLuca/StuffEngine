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