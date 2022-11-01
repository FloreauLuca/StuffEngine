#pragma once
#include <SFML\System\Vector2.hpp>
#include <vector>

namespace stuff
{
	struct CameraParameters
	{
	public:
		double zoom;
		sf::Vector2d position;
	};

	class Camera
	{
	public:
		Camera(double speed, double startZoom, double endZoom, std::vector<CameraParameters> cameraParameters = std::vector<CameraParameters>()) : startZoom_(startZoom), endZoom_(endZoom), speed_(speed), cameraParameters_(cameraParameters)
		{
		}

		void Update(float dt);

		sf::Vector2d GetPosition()
		{
			return currentPosition_;
		}

		double GetZoom()
		{
			return currentZoom_;
		}

		void Reset()
		{
			timer_ = 0.0f;
		}

	private:
		float timer_ = 0.0f;
		double startZoom_= 1.0;
		double endZoom_ = 0.0000015;
		float speed_ = 0.1f;
		sf::Vector2d currentPosition_ = sf::Vector2d(0.0, 0.0);
		double currentZoom_ = 1.0f;
		std::vector<CameraParameters> cameraParameters_ = std::vector<CameraParameters>();
	};
}
