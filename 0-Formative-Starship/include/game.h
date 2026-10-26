#pragma once

#include <optional>

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "player.h"

// Formative : le squelette d'un shoot'em up. Le vaisseau se deplace, le reste
// est a vous — missiles, asteroides, score, fin de partie.
class Game
{
public:
	Game();
	~Game();

	int Loop();

private:
	void CheckEvents();
	void Update();
	void Draw();

	sf::RenderWindow window_;
	b2WorldId world_ = b2_nullWorldId;

	Player player_;

	sf::Font font_;
	std::optional<sf::Text> text_;

	bool game_over_ = false;
};
