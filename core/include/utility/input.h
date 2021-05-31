#pragma once
#include <SFML/Graphics.hpp>


#include "engine/system.h"

namespace stuff
{
class InputSystem : public SystemInterface
{
public:
	void Init() override;
	void Update(float dt) override;
	void OnEvent(sf::Event event);
	void Destroy() override;
private:
};

}
