#pragma once
#include "action.h"
#include "system.h"
#include "graphics/graphics.h"
#include "graphics/window.h"
#include "utility/input.h"

#include <SFML\Graphics.hpp>


namespace stuff
{
class Engine : public SystemInterface
{
public:
	Engine()
		: graphics_(*this)
	{
	}

	void StartEngine();
	void EngineLoop();
	void DestroyEngine();
	void StopEngine();
	void RegisterSystem(SystemInterface& system);
	void Init() override;
	void Update(float dt) override;
	void Destroy() override;
	void OnEvent(sf::Event event) override;
	InputSystem& GetInputSystem() { return inputSystem_; };
	Graphics& GetGraphics() { return graphics_; };
	Action<sf::Event> EventAction;
private:
	Action<> initAction_;
	Action<float> updateAction_;
	Action<> drawImGuiAction_;
	Action<> destroyAction_;

	Graphics graphics_;
	InputSystem inputSystem_;
	bool isRunning_ = true;
	sf::Texture penguinLogo_;
	sf::Font font_;

	bool showFPS_ = true;
	bool showDebugImgui_ = false;
};
}
