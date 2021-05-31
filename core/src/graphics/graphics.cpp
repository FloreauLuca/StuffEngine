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
    if (!penguinLogo_.loadFromFile(dataPath + "penguin.png"))
    {
        std::cout << "Sprite fail to load" << std::endl;
    }
    window_ = std::make_unique<sf::RenderWindow>(sf::VideoMode(windowSize_.x, windowSize_.y), "StuffEngine");
    window_->setIcon(penguinLogo_.getSize().x, penguinLogo_.getSize().y, penguinLogo_.copyToImage().getPixelsPtr());
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
    	if (event.type == sf::Event::Resized)
    	{
            windowSize_.x = event.size.width;
            windowSize_.y = event.size.height;
            std::cout << "Window resized : " << windowSize_.x << ", " << windowSize_.y << std::endl;
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
