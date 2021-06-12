#include "sound_test.h"

#include <iostream>

#include "engine/system.h"
#include "utility/data_location.h"

namespace stuff
{
void SoundTest::Init()
{
	timer_ = 0;
	if(!waveSoundBuffer_.loadFromFile(dataPath + "wave.wav"))
	{
		std::cout << "Sound fail to load" << std::endl;
	}
	waveSound_.setBuffer(waveSoundBuffer_);
	waveSound_.setLoop(true);
	waveSound_.play();
}

void SoundTest::Update(float dt)
{
	timer_ += dt;
	waveSound_.setPitch(timer_);
	std::cout << timer_ << std::endl;
}

void SoundTest::Destroy()
{
	waveSound_.stop();
}
}
