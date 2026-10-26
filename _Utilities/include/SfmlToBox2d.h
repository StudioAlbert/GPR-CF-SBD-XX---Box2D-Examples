#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

namespace Utilities
{
namespace SfmlToBox2d
{

// Le seul endroit qui connait le facteur. Un metre vaut cent pixels.
constexpr float PIXELS_METERS_RATIO = 100.0f;

// `inline` : sans lui, inclure cet en-tete depuis deux fichiers donne une erreur
// d'edition de liens — le symbole serait defini deux fois.
//
// Y monte chez Box2D, il descend chez SFML : les deux conversions vivent ici.
inline b2Vec2 PixelsToMeters(const sf::Vector2f pixels)
{
	return {pixels.x / PIXELS_METERS_RATIO, -1.0f * pixels.y / PIXELS_METERS_RATIO};
}

inline b2Vec2 PixelsToMeters(const sf::Vector2u pixels)
{
	return PixelsToMeters(sf::Vector2f(pixels));
}

inline float PixelsToMeters(const float pixels)
{
	return pixels / PIXELS_METERS_RATIO;
}

inline sf::Vector2f MetersToPixels(const b2Vec2 meters)
{
	return {meters.x * PIXELS_METERS_RATIO, -1.0f * meters.y * PIXELS_METERS_RATIO};
}

inline float MetersToPixels(const float meters)
{
	return meters * PIXELS_METERS_RATIO;
}

}  // namespace SfmlToBox2d
}  // namespace Utilities
