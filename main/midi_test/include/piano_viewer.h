#pragma once
#include <iostream>
#include <array>
#include <SFML/Audio.hpp>


#include "midi_info.h"
#include "engine/engine.h"
#include "engine/system.h"
#include "math/const.h"

namespace stuff
{
	class PianoViewer : public SystemInterface
	{
	public:
		PianoViewer(Engine& engine, MidiInfo midiInfo, std::vector<std::pair<int, int>> channels = std::vector<std::pair<int, int>>()) : engine_(engine), graphics_(engine.GetGraphics()), midiInfo_(midiInfo), channels_(channels)
		{
		}

		void Init() override;
		void Update(float dt) override;
		void Destroy() override;
		void SpawnNote(int noteIndex, float length, int channel);
		void DrawPiano();

	private:
		float GetKeyPosition(int noteIndex);
		bool IsKeyBlack(int noteIndex);
		Engine& engine_;
		Graphics& graphics_;

		sf::Vector2u windowSize_ = sf::Vector2u(450, 800);
		
		float timer_ = 0.0f;
		
		MidiInfo midiInfo_ = MidiInfo(0, 0);
		
		std::vector<sf::RectangleShape> keyboards_;
		std::vector<sf::RectangleShape> notes_;

		int gammeCount_ = 4;
		const sf::Vector2f offset_ = sf::Vector2f(5, 5);
		sf::Vector2f rectSize_;
		sf::RectangleShape noteRect_ = sf::RectangleShape();

		const std::array<sf::Color, 6> lgbtColors_ = {
			sf::Color(5, 98, 1),
			sf::Color(153, 183, 24),
			sf::Color(122, 56, 9),
		};
		
		bool play = false;
		bool isPressed_ = false;
		int speed_ = 0;

		std::vector<int> currentIndex_;
		std::vector<int> cumulateTime_;
		std::vector<int> trackList_;
		std::vector<std::pair<int, int>> channels_;
	};
}
