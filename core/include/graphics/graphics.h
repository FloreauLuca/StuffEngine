#pragma once
#include "engine/system.h"
#include <SFML/Graphics.hpp>

namespace stuff
{
class Engine;
class Graphics : public SystemInterface
{
public:
	explicit Graphics(Engine& engine);
	void Init() override;
	void Update(float dt) override;
	void Draw(sf::CircleShape& circleShape);
	void Draw(sf::RectangleShape& rectangleShape);
	void Draw(sf::Text& text);
	void Draw(sf::Sprite& sprite);
	void Destroy() override;
	sf::Vector2u GetWindowSize() const { return windowSize_; }
	sf::RenderWindow* GetWindow() const { return window_.get(); }
private:
	sf::Vector2u windowSize_ = sf::Vector2u(1400, 900);
	sf::Texture penguinLogo_;
	
	sf::Font font_;
	Engine& engine_;
	std::unique_ptr<sf::RenderWindow> window_;
	std::vector<sf::CircleShape> circleShapes_;
	std::vector<sf::RectangleShape> rectangleShapes_;
	std::vector<sf::Text> texts_;
	std::vector<sf::Sprite> sprites_;
};
}
