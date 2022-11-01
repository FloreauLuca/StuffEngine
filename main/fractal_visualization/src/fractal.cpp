#include "fractal_visualization.h"

#include "compute_shader.h"
#include "utility/data_location.h"

#include <iostream>
#include <numeric>
#include <iomanip>

namespace stuff
{
	void Fractal::Init()
	{
		//Init text
		if (!font_.loadFromFile(dataPath + "kepler.otf"))
		{
			std::cout << "Error font not loaded" << std::endl;
		}
		text_.setFont(font_);
		text_.setFillColor(sf::Color::White);
		text_.setCharacterSize(textSize_);
		text_.setPosition(5, 15);
	}
	
	void Fractal::Update(float dt)
	{
		text_.setString(formulaText_);
		graphics_.Draw(text_);
	}
}
