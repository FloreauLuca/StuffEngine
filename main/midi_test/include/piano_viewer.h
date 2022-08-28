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
		PianoViewer(Engine& engine, MidiInfo midiInfo, int channel = -1) : engine_(engine), graphics_(engine.GetGraphics()), midiInfo_(midiInfo), channel_(channel)
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
		void Next()
		{
			timer_ = 0;
			currentIndex = 0;
			cumulateTime_ = 0;
			channel_++;
		}
		Engine& engine_;
		Graphics& graphics_;

		sf::Vector2u windowSize_ = sf::Vector2u(450, 800);
		
		float timer_ = 0.0f;
		
		MidiInfo midiInfo_ = MidiInfo(0, 0);
		
		std::vector<sf::RectangleShape> keyboards_;
		std::vector<sf::RectangleShape> notes_;

		int gammeCount_ = 6;
		const sf::Vector2f offset_ = sf::Vector2f(5, 5);
		sf::Vector2f rectSize_;
		sf::RectangleShape noteRect_ = sf::RectangleShape();

		const std::array<sf::Color, 6> lgbtColors_ = {
			sf::Color(255, 0, 24),
			sf::Color(255, 165, 44),
			sf::Color(255, 255, 65),
			sf::Color(0, 128, 24),
			sf::Color(0, 0, 249),
			sf::Color(134, 0, 125)
		};
		
		bool play = false;
		bool isPressed_ = false;

		int cumulateTime_ = 0;
		int currentIndex = 0;
		int trackIndex = 0;
		int speed_ = 0;
		int channel_ = 0;
	};
}
