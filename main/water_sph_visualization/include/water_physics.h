#pragma once
namespace stuff
{
	class WaterPhysics
	{
	public:
	};
    // friends defined inside class body are inline and are hidden from non-ADL lookup
    sf::Vector2f operator*(const sf::Vector2f& lhs,        // passing lhs by value helps optimize chained a+b+c
        const sf::Vector2f& rhs) // otherwise, both parameters may be const references
    {
        return sf::Vector2f(lhs.x * rhs.x, lhs.y * rhs.y);
    };
    // friends defined inside class body are inline and are hidden from non-ADL lookup
    sf::Vector2f operator*(const sf::Vector2f& lhs,        // passing lhs by value helps optimize chained a+b+c
        const sf::Vector2u& rhs) // otherwise, both parameters may be const references
    {
        return sf::Vector2f(lhs.x * rhs.x, lhs.y * rhs.y);
    };

    // friends defined inside class body are inline and are hidden from non-ADL lookup
    sf::Vector2f operator*(const sf::Vector2u& lhs,        // passing lhs by value helps optimize chained a+b+c
        const sf::Vector2f& rhs) // otherwise, both parameters may be const references
    {
        return sf::Vector2f(lhs.x * rhs.x, lhs.y * rhs.y);
    };

    // friends defined inside class body are inline and are hidden from non-ADL lookup
    float Dot(const sf::Vector2f& lhs,        // passing lhs by value helps optimize chained a+b+c
        const sf::Vector2f& rhs) // otherwise, both parameters may be const references
    {
        return lhs.x * rhs.x + lhs.y * rhs.y;
    };

    // friends defined inside class body are inline and are hidden from non-ADL lookup
    float Magnitude(const sf::Vector2f& lhs) // otherwise, both parameters may be const references
    {
        return sqrt(lhs.x * lhs.x + lhs.y * lhs.y);
    };
}
