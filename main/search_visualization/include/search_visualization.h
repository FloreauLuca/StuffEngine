#pragma once
#include <array>
#include <chrono>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


#include "engine/engine.h"
#include "engine/system.h"

namespace stuff
{
class Graphics;
class Engine;

class SearchVisualization : public SystemInterface
{
public:
	explicit SearchVisualization(Engine& engine) : engine_(engine), graphics_(engine.GetGraphics())
	{
	}

	void Init() override;
	void Update(float dt) override;
	void Destroy() override;
	void SetListSize(unsigned listSize) { listSize_ = listSize; }
	virtual void SortList();
protected:
	std::vector<int> list_;
	std::vector<std::pair<size_t, size_t>> swap_pairs;
	std::vector<std::vector<size_t>> coloredList_;
	std::string sortName_ = "";
	std::chrono::microseconds sortTime_ = std::chrono::microseconds();
private:
	Engine& engine_;
	Graphics& graphics_;

	sf::Vector2u windowSize_ = sf::Vector2u(1400, 900);
	const sf::Vector2u offset = sf::Vector2u(5, 5);
	const sf::Vector2f fillSize_ = sf::Vector2f(0, 300);

	size_t pairIndex_ = 0;
	sf::RectangleShape standardRect;
	unsigned int listSize_ = 100;
	const std::array<sf::Color, 6> lgbtColors_ = {
		sf::Color(255, 0, 24),
		sf::Color(255, 165, 44),
		sf::Color(255, 255, 65),
		sf::Color(0, 128, 24),
		sf::Color(0, 0, 249),
		sf::Color(134, 0, 125)
	};
	sf::SoundBuffer waveSoundBuffer_;
	sf::Sound waveSound_;
	sf::Font font_;
	sf::Text text_;

	int sortSpeed = 100;
};
}
