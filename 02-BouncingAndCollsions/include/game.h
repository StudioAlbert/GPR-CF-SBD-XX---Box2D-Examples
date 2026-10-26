#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "ball.h"
#include "bouncer.h"

// Apesanteur, quatre murs. Maintenir le clic gauche lache des balles ; chacune
// palit a mesure qu'elle tape les murs, et le mur touche s'allume.
//
// C'est la demonstration de « qui a touche qui » : chaque forme porte son objet
// de jeu, et chaque objet porte son etiquette de type.
class Game
{
public:
	Game() = default;
	~Game();

	void Init();
	void Loop();

private:
	sf::RenderWindow window_;
	b2WorldId world_ = b2_nullWorldId;

	// Des pointeurs : Box2D garde l'adresse de chaque balle dans `userData`, et
	// un vector qui grandit deplace ses elements.
	std::vector<std::unique_ptr<Ball>> balls_;
	std::vector<std::unique_ptr<Bouncer>> murs_;
};
