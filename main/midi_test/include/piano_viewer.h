#pragma once
#include <iostream>
#include <array>
#include <SFML/Audio.hpp>


#include "midi_info.h"
#include "midi_reader.h"
#include "engine/engine.h"
#include "engine/system.h"
#include "math/const.h"

namespace stuff
{
	class PianoViewer : public MidiReader
	{
	public:
		PianoViewer(Engine& engine, MidiInfo midiInfo, float speed = 1.0f, std::vector<std::pair<int, int>> channels = std::vector<std::pair<int, int>>()) : MidiReader(midiInfo, channels), engine_(engine), noteSpeed_(speed), graphics_(engine.GetGraphics())
		{
		}

		void Init() override;
		void Update(float dt) override;
		void Destroy() override;
		void OnPlayEvent(int noteIndex, float length, int channel) override;
	private:
		float GetKeyPosition(int noteIndex);
		bool IsKeyBlack(int noteIndex);
	private:
		Engine& engine_;
		Graphics& graphics_;

		sf::Vector2u windowSize_ = sf::Vector2u(450, 800);
		
		float timer_ = 0.0f;
		
		MidiInfo midiInfo_ = MidiInfo(0, 0);
		
		std::vector<sf::RectangleShape> keyboards_;
		std::vector<sf::RectangleShape> notes_;

		int gammeCount_ = 6;
		int firstNote_ = 24;
		
		const sf::Vector2f offset_ = sf::Vector2f(5, 5);
		sf::Vector2f rectSize_;
		sf::RectangleShape noteRect_ = sf::RectangleShape();

		const std::array<sf::Color, 3> colors_ = {
			sf::Color(5, 98, 1),
			sf::Color(153, 183, 24),
			sf::Color(122, 56, 9),
		};
		float noteSpeed_ = 0;
	};
}
