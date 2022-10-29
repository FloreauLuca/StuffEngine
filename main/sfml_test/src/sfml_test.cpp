#include "sfml_test.h"

#include <iostream>

#include "engine/system.h"
#include "utility/data_location.h"

namespace stuff
{
void SfmlTest::Init()
{
	timer_ = 0;
	if(!penguinHead_.loadFromFile(dataPath + "penguin_head.png"))
	{
		std::cout << "Sprite fail to load" << std::endl;
	}
	if (!penguinLogo_.loadFromFile(dataPath + "penguin.png"))
	{
		std::cout << "Sprite fail to load" << std::endl;
	}
	if (!font_.loadFromFile(dataPath + "Insanibu.ttf"))
	{
		std::cout << "Error font not loaded" << std::endl;
	}
	std::cout << font_.getInfo().family << " " << font_.getLineSpacing(30) << " " << font_.getUnderlineThickness(30) << std::endl;
	std::cout << font_.getGlyph('1', 30, false).advance << std::endl;
}

void SfmlTest::Update(float dt)
{
	//Init text
	sf::Text text;
	text.setFillColor(sf::Color::White);
	text.setPosition(5, 15);
	text.setStyle(sf::Text::Bold);
	text.setString(L"F = z² + 1.23 - 0.67i");
	text.setFont(font_);
	graphics_.Draw(text);

	sf::Vector2f center(sf::Vector2f(graphics_.GetWindowSize()) / 2.0f);
	timer_ += dt*2;
	sf::CircleShape circle1(300.0f);
	sf::Color color;
	color.r = abs(sin(timer_ + 0.5f)) * 255;
	color.g = abs(cos(timer_)) * 255;
	color.b = 255;
	color.a = 255;
	circle1.setFillColor(color);
	circle1.setPosition(center.x - circle1.getRadius(),center.y - circle1.getRadius());
	graphics_.Draw(circle1);
	
	sf::CircleShape circle2(50.0f);
	circle2.setFillColor(sf::Color::Black);
	sf::Vector2f pos(center.x - circle2.getRadius(), center.y - circle2.getRadius());
	pos.x += sin(timer_) * 250;
	pos.y += cos(timer_) * 250;
	circle2.setPosition(pos);
	graphics_.Draw(circle2);
	
	sf::Sprite spriteHead(penguinHead_);
	spriteHead.setPosition(pos);
	spriteHead.setScale(100.0f /penguinHead_.getSize().x, 100.0f /penguinHead_.getSize().y);
	graphics_.Draw(spriteHead);
	
	sf::Sprite spriteLogo(penguinLogo_);
	spriteLogo.setPosition(graphics_.GetWindowSize().x - 100,graphics_.GetWindowSize().y - 100);
	spriteLogo.setScale(100.0f/ penguinLogo_.getSize().x, 100.0f / penguinLogo_.getSize().y);
	graphics_.Draw(spriteLogo);
}

void SfmlTest::Destroy()
{
}
}
