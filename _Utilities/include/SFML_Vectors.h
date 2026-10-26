#pragma once

#include <cmath>

#include <SFML/Graphics.hpp>

namespace Utilities
{
namespace SFML_Vectors
{

// Attention au repere de l'ecran : Y descend, donc UP vaut -1.
inline constexpr sf::Vector2f UP{0.0f, -1.0f};
inline constexpr sf::Vector2f DOWN{0.0f, 1.0f};
inline constexpr sf::Vector2f LEFT{-1.0f, 0.0f};
inline constexpr sf::Vector2f RIGHT{1.0f, 0.0f};

// `inline` : sans lui, inclure cet en-tete depuis deux fichiers donne une erreur
// d'edition de liens.
inline sf::Vector2f Normalize(const sf::Vector2f v)
{
	const float longueur = std::sqrt(v.x * v.x + v.y * v.y);
	if (longueur <= 0.0f) return {0.0f, 0.0f};  // sinon : division par zero
	return v / longueur;
}

inline float Dot(const sf::Vector2f v1, const sf::Vector2f v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

inline sf::Vector2f LeftOrtho(const sf::Vector2f v)
{
	return {-v.y, v.x};
}

inline sf::Vector2f RightOrtho(const sf::Vector2f v)
{
	return {v.y, -v.x};
}

}  // namespace SFML_Vectors
}  // namespace Utilities
