#pragma once


namespace stuff
{
class SystemInterface
{
public:
	virtual ~SystemInterface() = default;
	virtual void Init() = 0;

	virtual void Update(float dt) = 0;

	virtual void Destroy() = 0;
private:
};
}