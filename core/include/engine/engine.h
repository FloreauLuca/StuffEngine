#pragma once
#include "action.h"
#include "system.h"
#include "graphics/graphics.h"
#include "graphics/window.h"
#include "utility/input.h"


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
	InputSystem& GetInputSystem() { return inputSystem_; };
	Graphics& GetGraphics() { return graphics_; };
private:
	Action<> initAction_;
	Action<float> updateAction_;
	Action<> drawImGuiAction_;
	Action<> destroyAction_;

	Graphics graphics_;
	Window window_;
	InputSystem inputSystem_;
	bool isRunning_ = true;
	sf::Texture penguinLogo_;
};
}
