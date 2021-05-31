
#include "engine/engine.h"

#include <chrono>
#include <iostream>

#include "engine/system.h"
#include "utility/data_location.h"

namespace stuff
{
void Engine::StartEngine()
{
	RegisterSystem(*this);
	RegisterSystem(graphics_);
	RegisterSystem(window_);
	initAction_.Execute();
	EngineLoop();
}

static std::chrono::time_point<std::chrono::system_clock> clock;

void Engine::EngineLoop()
{

    isRunning_ = true;
    std::chrono::system_clock::time_point clock = std::chrono::system_clock::now();

    while (isRunning_)
    {
        const auto end = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsed_seconds = end - clock;
        const float dt = elapsed_seconds.count();
        clock = end;
        updateAction_.Execute(dt);
    }
	DestroyEngine();
}

void Engine::DestroyEngine()
{
	destroyAction_.Execute();
	
}

void Engine::StopEngine()
{
	isRunning_ = false;
}

void stuff::Engine::RegisterSystem(SystemInterface& system)
{
    initAction_.RegisterCallback([&system] { system.Init(); });
    updateAction_.RegisterCallback([&system](float dt) { system.Update(dt); });
    destroyAction_.RegisterCallback([&system] {
        system.Destroy();
        });
}

void Engine::Init()
{
	
}
void Engine::Update(float dt)
{

    sf::Text text;
    text.setString(std::to_string(1.0f/dt));
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(14);
    graphics_.Draw(text);
    //std::cout << 1.0f / dt << " FPS" << std::endl;
	
}
void Engine::Destroy()
{
	
}
}
