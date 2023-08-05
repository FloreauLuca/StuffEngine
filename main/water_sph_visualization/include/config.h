#pragma once
namespace stuff
{
	class Config
	{
	public:
		static const float PARTICLE_SIZE;
		static const unsigned PARTICLE_COUNT;
		static const float MIN_X;
		static const float MAX_X;
		static const float MAX_Y;

		static const float GRAVITY;
		static const float MAX_SPEED;
		static const float SPACING;
		static const float K;
		static const float K_NEAR;
		static const float REST_DENSITY;
		static const float R;
		static const float SIGMA;
		static const float WALL_DAMP;
		static const float VEL_DAMP;
	};
}
