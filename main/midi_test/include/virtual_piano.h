#pragma once
#include <SFML/Audio.hpp>

#include "engine/engine.h"
#include "engine/system.h"
#include "math/const.h"

namespace stuff
{
	class VirtualPiano : public SystemInterface
	{
	public:
		VirtualPiano(Engine& engine) : engine_(engine), graphics_(engine.GetGraphics())
		{
		}

		void Init() override;
		void Update(float dt) override;
		void PlayNote(int noteIndex);
		void StopNote(int noteIndex);
		void Destroy() override;

	private:
		std::string ConvertIndexToNote(int noteIndex) const;
		
		Engine& engine_;
		Graphics& graphics_;

		float timer_ = 0.0f;
		
		const size_t NOTE_COUNT = 48;
		
		std::vector<sf::SoundBuffer> soundBuffer_;
		std::vector<sf::Sound> keyboardSounds_;

		std::string samplePath_ = "RecordedPiano/";
	};
}
