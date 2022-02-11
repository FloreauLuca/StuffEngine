#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics/Color.hpp>

struct Gradient
{
    std::vector<sf::Color> Colors = std::vector<sf::Color>();
	
	sf::Color Evaluate(float t)
	{
        float count = (Colors.size()-1) * t;
        int prev = std::floor(count);
        int next = std::ceil(count);
        return sf::Color(
            std::lerp(Colors[prev].r, Colors[next].r, count - prev),
            std::lerp(Colors[prev].g, Colors[next].g, count - prev),
            std::lerp(Colors[prev].b, Colors[next].b, count - prev)
            );
	}
};

inline sf::Color HSLtoRGB(const float H, const float S, const float L) {
	
    float s = std::clamp(S, 0.0f, 100.0f) / 100;
    float l = std::clamp(L, 0.0f, 100.0f) / 100;
	
    float C = (1 - abs(2*l - 1)) * s;
    float X = C * (1 - abs(fmod(std::clamp(H, 0.0f, 360.0f) / 60.0f, 2) - 1));
    float m = l - C/2.0f;
    float r, g, b;
    if (H < 60) {
        r = C;
        g = X;
    	b = 0;
    }
    else if (H >= 60 && H < 120) {
        r = X;
        g = C;
    	b = 0;
    }
    else if (H >= 120 && H < 180) {
        r = 0;
        g = C;
    	b = X;
    }
    else if (H >= 180 && H < 240) {
        r = 0;
        g = X;
        b = C;
    }
    else if (H >= 240 && H < 300) {
        r = X;
        g = 0;
        b = C;
    }
    else {
        r = C;
        g = 0;
    	b = X;
    }
    int R = (r + m) * 255;
    int G = (g + m) * 255;
    int B = (b + m) * 255;
    return sf::Color(R, G, B);
}
