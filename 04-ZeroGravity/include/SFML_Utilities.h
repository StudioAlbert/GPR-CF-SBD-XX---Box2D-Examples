#pragma once

#include <cmath>

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

// Le seul endroit de ce programme qui connait le facteur. Un metre vaut cent
// pixels : la conversion se verifie de tete.
constexpr float kPixelsMetersRatio = 100.0f;

// Y monte chez Box2D, il descend chez SFML. Les deux conversions vivent ici,
// ensemble, parce que les oublier separement donne deux bugs differents.
inline b2Vec2 PixelsToMeters(const sf::Vector2f pixels)
{
	return {pixels.x / kPixelsMetersRatio, -1.0f * pixels.y / kPixelsMetersRatio};
}

inline b2Vec2 PixelsToMeters(const sf::Vector2u pixels)
{
	return PixelsToMeters(sf::Vector2f(pixels));
}

inline float PixelsToMeters(const float pixels)
{
	return pixels / kPixelsMetersRatio;
}

inline sf::Vector2f MetersToPixels(const b2Vec2 meters)
{
	return {meters.x * kPixelsMetersRatio, -1.0f * meters.y * kPixelsMetersRatio};
}

inline float MetersToPixels(const float meters)
{
	return meters * kPixelsMetersRatio;
}

inline float VecDistance(const sf::Vector2f p1, const sf::Vector2f p2)
{
	const sf::Vector2f d = p2 - p1;
	return std::sqrt(d.x * d.x + d.y * d.y);
}
