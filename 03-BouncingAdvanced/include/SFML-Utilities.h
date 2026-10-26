#pragma once

#include <cmath>

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

// Le seul endroit de ce programme qui connait le facteur.
constexpr float kPixelsMetersRatio = 100.0f;

// Y monte chez Box2D, il descend chez SFML : les deux conversions vivent ici.
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

inline float VecLength(const sf::Vector2f v)
{
	return std::sqrt(v.x * v.x + v.y * v.y);
}

// L'angle oriente de vec1 vers vec2, dans le repere de l'ECRAN (Y vers le bas).
inline float VecAngle(const sf::Vector2f v1, const sf::Vector2f v2)
{
	const float determinant = v1.x * v2.y - v1.y * v2.x;
	const float produit_scalaire = v1.x * v2.x + v1.y * v2.y;
	return std::atan2(determinant, produit_scalaire);
}
