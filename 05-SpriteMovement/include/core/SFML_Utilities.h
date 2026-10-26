#pragma once

#include <cmath>

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

// Le seul endroit du programme qui connait le facteur.
constexpr float kPixelsMetersRatio = 100.0f;
constexpr float kEpsilon = 0.0001f;

// Y monte chez Box2D, il descend chez SFML.
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

inline float VecLength(const b2Vec2 v)
{
	return std::sqrt(v.x * v.x + v.y * v.y);
}
