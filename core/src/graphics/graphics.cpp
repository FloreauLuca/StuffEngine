#include "graphics/graphics.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include "engine/engine.h"
#include "utility/data_location.h"

namespace stuff
{
Graphics::Graphics(Engine& engine) : engine_(engine)
{
}

void Graphics::Init()
{
    window_ = std::make_unique<sf::RenderWindow>(sf::VideoMode(1000, 1000), "StuffEngine");
    if (!font_.loadFromFile(dataPath + "sansation.ttf"))
    {
        std::cout << "Error file not loaded" << std::endl;
    }
}

void Graphics::Update(float dt)
{
    sf::Event event;
    while (window_->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            engine_.StopEngine();
        }
    	
        engine_.GetInputSystem().OnEvent(event);
    }
	
    window_->clear();
    for (auto& rectangle_shape : rectangleShapes_)
    {
        window_->draw(rectangle_shape);
    }
    for (auto& circle_shape : circleShapes_)
    {
        window_->draw(circle_shape);
    }
    for (auto& sprite : sprites_)
    {
        window_->draw(sprite);
    }
    for (auto& text : texts_)
    {
        text.setFont(font_);
        window_->draw(text);
    }
    window_->display();
    circleShapes_.clear();
    rectangleShapes_.clear();
    texts_.clear();
    sprites_.clear();
}

void Graphics::Draw(sf::CircleShape& circleShape)
{
    circleShapes_.push_back(circleShape);
}

void Graphics::Draw(sf::RectangleShape& rectangleShape)
{
    rectangleShapes_.push_back(rectangleShape);
}
void Graphics::Draw(sf::Text& text)
{
    texts_.push_back(text);
}

void Graphics::Draw(sf::Sprite& sprite)
{
    sprites_.push_back(sprite);
}

void Graphics::Destroy()
{
    window_->close();
}
}
