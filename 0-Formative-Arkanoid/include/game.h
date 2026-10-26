#pragma once

#include <optional>

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "ball.h"
#include "brickManager.h"
#include "player.h"

// Formative : le squelette d'un casse-briques. La raquette marche, les briques
// sont posees. Le reste est a vous — voir les deux TO DO de `ball.cpp`.
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

	std::optional<Ball> ball_;
	Player player_;
	BrickManager brick_manager_;

	sf::Font font_;
	std::optional<sf::Text> text_;

	sf::Clock clock_;
	bool game_over_ = false;
};
