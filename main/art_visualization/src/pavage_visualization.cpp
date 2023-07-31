#include "pavage_visualization.h"

#include <iostream>
#include <numeric>


#include "math/color.h"
#include "math/const.h"
#include "math/vector.h"
#include <imgui.h>


namespace stuff
{
	void PavageVisualization::Init()
	{
		timer_ = 0;
		windowSize_ = graphics_.GetWindowSize();
	}

	void PavageVisualization::Update(float dt)
	{
		timer_ += dt;
		sf::Vector2f center = sf::Vector2f(windowSize_.x / 2.0f, windowSize_.y / 2.0f);
		sf::Vector2i squareCount = sf::Vector2i(windowSize_.x / size_, windowSize_.y / size_);
		for (size_t x = 0; x < squareCount.x; x++)
		{
			for (size_t y = 0; y < squareCount.y; y++)
			{
				sf::Vector2f center = sf::Vector2f(x * 2.0f * size_ - size_*2, y * 2.0f * size_);
				sf::Color color = (x + y) % 2 == 0 ? sf::Color::Cyan : sf::Color::Red;
				if (y % 2 == 0)
				{
					center.x += tilling_ * size_;
					DrawPavage(center, color, tilling_);
				}
				else
				{
					DrawPavage(center, color, 0.0f);
				}
			}
		}
		DrawPavage(center + sf::Vector2f(0.0f, 200.0f), sf::Color::White, tilling_);

		if (true)
		{
			ImGui::Begin("Parameters");
			ImGui::DragFloat("Size", &size_, 0.5f, 5.0f, 200.0f);
			ImGui::DragFloat("Resolution", &resolution_, 1.0f, 5.0f, 100.0f);
			ImGui::DragFloat2("Speed", speed_, 0.1f, -20.0f, 20.0f);
			ImGui::DragFloat2("Amplitude", amplitude_, 0.1f, -5.0f, 5.0f);
			ImGui::DragFloat2("Frequency", frenquency_, 1.0f, -5.0f, 5.0f);
			ImGui::DragFloat("Tiling", &tilling_, 0.01f, -2.0f, 2.0f);
			ImGui::End();
		}
	}

	void PavageVisualization::DrawPavage(sf::Vector2f position, sf::Color color, float tilling)
	{
		sf::VertexArray base_vertices(sf::TriangleFan);
		base_vertices.append(sf::Vertex(sf::Vector2f(0.0f, 0.0f) * size_, sf::Color::White));
		AddHorizontalLine(&base_vertices, corners_[0] * size_, corners_[1] * size_, true, tilling);
		AddVerticalLine(&base_vertices, base_vertices[base_vertices.getVertexCount()-1].position, corners_[2] * size_, true, tilling);
		AddHorizontalLine(&base_vertices, base_vertices[base_vertices.getVertexCount()-1].position, corners_[3] * size_, false, tilling);
		AddVerticalLine(&base_vertices, base_vertices[base_vertices.getVertexCount()-1].position, corners_[0] * size_, false, tilling);

		for (size_t i = 0; i < base_vertices.getVertexCount(); i++)
		{
			base_vertices[i].position += position;
			base_vertices[i].color = color;
		}
		graphics_.Draw(base_vertices);
	}

	void PavageVisualization::AddHorizontalLine(sf::VertexArray* vertices, sf::Vector2f start, sf::Vector2f end, bool reverse, float tilling)
	{
		sf::Vector2f normalVec = normalize(start - end);
		sf::Vector2f normal = start - end;
		if (reverse)
		{
			normal = normalize(sf::Vector2f(-normal.y, normal.x));
		}
		else
		{
			normal = normalize(sf::Vector2f(normal.y, -normal.x));
		}
		
		for (size_t i = 0; i <= resolution_; i++)
		{
			float lerpValue = i / resolution_;
			if (reverse)
			{
				lerpValue = 1 - lerpValue;
			}
			sf::Color color = HSLtoRGB(lerpValue * 360.0f, 100.0f, 50.0f);
			sf::Vector2f vec = lerp(start, end, i / resolution_);
			float timer = speed_[0] * timer_;
			float curve = sin(frenquency_[0] * lerpValue * 2 * PI + timer - tilling * PI) - sin(timer - tilling * PI);
			curve *= amplitude_[0];
			vec += normal * curve * 0.1f * size_;
			vec += normalVec * sin(timer + tilling * PI) * 0.1f * size_;
			vertices->append(sf::Vertex(vec, color));
		}
	}

	void PavageVisualization::AddVerticalLine(sf::VertexArray* vertices, sf::Vector2f start, sf::Vector2f end, bool reverse, float tilling)
	{
		sf::Vector2f normalVec = normalize(start - end);
		sf::Vector2f normal = start - end;
		if (reverse)
		{
			normal = normalize(sf::Vector2f(-normal.y, normal.x));
		}
		else
		{
			normal = normalize(sf::Vector2f(normal.y, -normal.x));
		}

		for (size_t i = 0; i <= resolution_; i++)
		{
			float lerpValue = i / resolution_;
			if (reverse)
			{
				lerpValue = 1 - lerpValue;
			}
			sf::Color color = HSLtoRGB(lerpValue * 360.0f, 100.0f, 50.0f);
			sf::Vector2f vec = lerp(start, end, i / resolution_);
			float timer = speed_[1] * timer_;
			float curve = sin(frenquency_[1] * lerpValue * 2 * PI + timer) - sin(timer);
			curve *= amplitude_[1];
			vec += normal * curve * 0.1f * size_;
			vec += normalVec * sin(timer + tilling * PI) * 0.1f * size_;
			vertices->append(sf::Vertex(vec, color));
		}
	}

	void PavageVisualization::Destroy()
	{
	}
}
