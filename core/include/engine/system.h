#pragma once
#include <SFML/Window/Event.hpp>

namespace stuff
{
class SystemInterface
{
public:
	virtual ~SystemInterface() = default;
	virtual void Init() = 0;

	virtual void Update(float dt) = 0;

	virtual void Destroy() = 0;

	virtual void OnEvent(sf::Event event) {};
private:
};
}