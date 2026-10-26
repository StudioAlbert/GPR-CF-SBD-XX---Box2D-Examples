#pragma once

#include <SFML/Graphics.hpp>

// Les textures sont chargees une fois et partagees. Un sprite ne copie pas son
// image : il pointe dessus, et cette image doit vivre aussi longtemps que lui.
// C'est tout l'interet d'un gestionnaire.
class TextureManager
{
public:
	static TextureManager& Instance();

	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;

	const sf::Texture& Asteroid() const { return asteroid_; }
	const sf::Texture& Ship() const { return ship_; }
	const sf::Texture& GameOver() const { return game_over_; }
	const sf::Texture& Missile() const { return missile_; }

private:
	TextureManager();

	sf::Texture asteroid_;
	sf::Texture ship_;
	sf::Texture game_over_;
	sf::Texture missile_;
};
