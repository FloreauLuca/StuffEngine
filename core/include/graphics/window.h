#pragma once
#include <SFML/Graphics.hpp>


#include "engine/system.h"

namespace stuff
{
class Window : public SystemInterface
{
public:
	void Init() override;
	void Update(float dt) override;
	void Destroy() override;
private:
};
}
