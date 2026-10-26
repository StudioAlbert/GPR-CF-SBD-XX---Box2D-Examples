#include "managers/textureManager.h"

#include <iostream>

namespace
{

// Une texture de secours visible plutot qu'un plantage : si le fichier manque,
// on voit un carre et on sait quoi chercher dans la console.
void Charger(sf::Texture& texture, const std::string& chemin)
{
	if (!texture.loadFromFile(chemin))
	{
		std::cerr << "texture introuvable : " << chemin << '\n';
		texture = sf::Texture(sf::Vector2u(32, 32));
	}
}

}  // namespace

TextureManager::TextureManager()
{
	// Attention a la casse : le fichier s'appelle `asteroid.png` en minuscules.
	// Windows s'en moque, Linux non.
	Charger(asteroid_, "data/asteroid.png");
	Charger(ship_, "data/Ship.png");
	Charger(game_over_, "data/GameOver.png");
	Charger(missile_, "data/missile.png");
}

TextureManager& TextureManager::Instance()
{
	// Construite au premier appel, detruite a la fin du programme. Pas de `new`,
	// donc rien a liberer.
	static TextureManager instance;
	return instance;
}
