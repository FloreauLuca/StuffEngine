#include "snow_flakes.h"

#include <iostream>
#include <numeric>

#include "math/const.h"
#include "math/vector.h"


namespace stuff
{
void SnowFlakes::Init()
{
	timer_ = 0;
	windowSize_ = graphics_.GetWindowSize();
}

void SnowFlakes::Update(float dt)
{
	sf::VertexArray rectangle = sf::VertexArray(sf::TriangleStrip);
	rectangle.append(sf::Vertex(sf::Vector2f( 0, 0 ), sf::Color(0, 0, 50)));
	rectangle.append(sf::Vertex(sf::Vector2f(windowSize_.x, 0), sf::Color(0, 0, 50)));
	rectangle.append(sf::Vertex(sf::Vector2f(0, windowSize_.y), sf::Color(50, 10, 50)));
	rectangle.append(sf::Vertex(sf::Vector2f(windowSize_.x, windowSize_.y), sf::Color(50, 10, 50)));

	graphics_.Draw(rectangle);
	timer_ += dt;
	for (int s = 0; s < 14; s++)
	{
		sf::VertexArray vertices(sf::LineStrip);
		sf::Vector2f center = sf::Vector2f(
			std::fmod(sin(timer_ * (s*0.1f) + s) * (windowSize_.x / 4) + sin(s) * (windowSize_.x / 2) + windowSize_.x / 2 + 100, windowSize_.x+200)-100,
			std::fmod(timer_ * ((s+PI*2) * 3.0f) + s * 125, windowSize_.y+200)-100);
		std::array<sf::Color, 4> color = colors_[s%colors_.size()];
		
		float lerpValue = sin(timer_+s) * 0.5f + 0.5f;
		float startRadius = lerp(25, 0, lerpValue);
		float branchSize = lerp(20, 10, lerpValue);
		float branchLenght = lerp(5, 10, lerpValue);
		float branchCount = lerp(3, 6, lerpValue);
		float endBranchCount = lerp(2, 6, lerpValue);
		float startAngle = timer_ * (s + PI) * 0.2f + s;
		for (float i = startAngle; i < PI * 2 + startAngle; i += PI / 3)
		{
			sf::Vector2f startBranch = center + sf::Vector2f(startRadius * cosf(i), startRadius * sinf(i));
			vertices.append(sf::Vertex(startBranch, color[0]));

			for (int b = 1; b <= branchCount; ++b)
			{
				sf::Vector2f branch = center + sf::Vector2f((startRadius + b * branchLenght) * cosf(i), (startRadius + b * branchLenght) * sinf(i));
				vertices.append(sf::Vertex(branch, color[1]));

				sf::Vector2f vec = branch + sf::Vector2f(branchSize * cosf(i + PI / 3), branchSize * sinf(i + PI / 3));
				vertices.append(sf::Vertex(vec, color[2]));
				vertices.append(sf::Vertex(branch, color[1]));
				vec = branch + sf::Vector2f(branchSize * cosf(i - PI / 3), branchSize * sinf(i - PI / 3));
				vertices.append(sf::Vertex(vec, color[2]));

				vertices.append(sf::Vertex(branch, color[1]));
			}
			sf::Vector2f branch = center + sf::Vector2f((startRadius + branchCount * branchLenght) * cosf(i),
				(startRadius + branchCount * branchLenght) * sinf(i));
			vertices.append(sf::Vertex(branch, color[1]));
			for (int j = 1; j < endBranchCount; ++j)
			{
				float angle = i - PI / 3 + ((float)j / endBranchCount) * 2 * PI / 3;
				sf::Vector2f vec = branch + sf::Vector2f(branchSize * cosf(angle), branchSize * sinf(angle));
				vertices.append(sf::Vertex(vec, color[3]));
				vertices.append(sf::Vertex(branch, color[1]));
			}

			vertices.append(sf::Vertex(startBranch, color[0]));
		}
		vertices.append(vertices[0]);
		graphics_.Draw(vertices);
	}
}

void SnowFlakes::Destroy()
{
}
}
