#include "camera.h"
#include <math\vector.h>
#include <math\const.h>

namespace stuff
{
	void Camera::Update(float dt)
	{
		timer_ += dt * speed_;
		currentZoom_ = std::exp(lerp(std::log(startZoom_), std::log(endZoom_), (double)cos(timer_ + PI) * 0.5f + 0.5f));
		for (size_t i = 0; i < cameraParameters_.size(); i++)
		{
			if (i < cameraParameters_.size() - 1)
			{
				if (cameraParameters_[i].zoom > currentZoom_ && cameraParameters_[i + 1].zoom < currentZoom_)
				{
					double value = smoothstep(cameraParameters_[i].zoom, cameraParameters_[i + 1].zoom, currentZoom_);
					currentPosition_.x = lerp(cameraParameters_[i].position.x, cameraParameters_[i + 1].position.x, value);
					currentPosition_.y = lerp(cameraParameters_[i].position.y, cameraParameters_[i + 1].position.y, value);
					break;
				}
				else if (cameraParameters_[i].zoom < currentZoom_)
				{
					currentPosition_ = cameraParameters_[i].position;
					break;
				}
			}
			else 
			{
				if (cameraParameters_[i].zoom > currentZoom_)
				{
					currentPosition_ = cameraParameters_[i].position;
					break;
				}
			}
		}
	}
}
