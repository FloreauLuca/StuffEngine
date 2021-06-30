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

/**
 * \brief Parent class of a sorting algorithm visualization
 */
class SortVisualization : public SystemInterface
{
public:
	explicit SortVisualization(Engine& engine) : engine_(engine), graphics_(engine.GetGraphics())
	{
	}

	void Init() override;
	void Update(float dt) override;
	void Destroy() override;
	void SetListSize(unsigned listSize) { listSize_ = listSize; }
	/**
	 * \brief Sort the list using a sorting algorithm, set the swapPairs_ and the coloredList_
	 */
	virtual void SortList();

protected:
	// List of elements
	std::vector<int> list_;
	// List of pairs to swap
	std::vector<std::pair<size_t, size_t>> swapPairs_;
	// List of elements to color
	std::vector<std::vector<size_t>> coloredList_;
	std::string sortName_ = "Unknown Sort";
	std::chrono::microseconds sortTime_ = std::chrono::microseconds();

private:
	Engine& engine_;
	Graphics& graphics_;

	sf::Vector2u windowSize_ = sf::Vector2u(1400, 900);
	const sf::Vector2f offset = sf::Vector2f(5, 5);
	const sf::Vector2f fillSize_ = sf::Vector2f(0, 300);

	size_t pairIndex_ = 0;
	unsigned int listSize_ = 100;

	sf::RectangleShape standardRect_;
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
	const sf::Vector2f nameTextPos_ = sf::Vector2f(0, 30);
	const sf::Vector2f elementTextPos_ = sf::Vector2f(0, 60);
	const sf::Vector2f timeTextPos_ = sf::Vector2f(0, 90);
	const unsigned textSize_ = 30;

	float sortSpeed_ = 100.0f;
	const float endSortSpeed_ = 50.0f;
	const float increaseSortSpeed_ = 5.0f;
	// Multiplier apply to size to obtain start speed
	const float speedSizeMultiplier_ = 0.2f;
};
}
