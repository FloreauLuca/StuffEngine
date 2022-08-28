
#include "engine/engine.h"

#include <chrono>
#include <imconfig.h>
#include <imgui.h>
#include <iostream>

#include <Tracy.hpp>

#include "engine/system.h"
#include "utility/data_location.h"

namespace stuff
{
void Engine::StartEngine()
{
	RegisterSystem(*this);
	RegisterSystem(graphics_);
	initAction_.Execute();
	EngineLoop();
}

static std::chrono::time_point<std::chrono::system_clock> clock;

void Engine::EngineLoop()
{

    isRunning_ = true;
    std::chrono::system_clock::time_point clock = std::chrono::system_clock::now();
    sf::Clock update_clock;

    while (isRunning_)
    {
        const auto end = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsed_seconds = end - clock;
        const float dt = elapsed_seconds.count();
        clock = end;
        ImGui::SFML::Update(*graphics_.GetWindow(), update_clock.restart());
        updateAction_.Execute(dt);
        FrameMark
    }
	DestroyEngine();
}

void Engine::DestroyEngine()
{
	destroyAction_.Execute();
    initAction_.ClearAction();
    updateAction_.ClearAction();
    destroyAction_.ClearAction();
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
    if (!penguinLogo_.loadFromFile(dataPath + "penguin.png"))
    {
        std::cout << "Sprite fail to load" << std::endl;
    }
}
void Engine::Update(float dt)
{

    sf::Text text;
    text.setString(std::to_string(dt));
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(14);
    graphics_.Draw(text);
    sf::Sprite spriteLogo(penguinLogo_);
    spriteLogo.setPosition(graphics_.GetWindowSize().x - 60, graphics_.GetWindowSize().y - 60);
    spriteLogo.setScale(50.0f / penguinLogo_.getSize().x, 50.0f / penguinLogo_.getSize().y);
    graphics_.Draw(spriteLogo);
    //std::cout << 1.0f / dt << " FPS" << std::endl;
	
}
void Engine::Destroy()
{
	
}
}
