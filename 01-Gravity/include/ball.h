#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class Game;

// Une bille dynamique qui tombe. Le clic la teleporte sous la souris.
class Ball
{
public:
	Ball(Game& game, sf::RenderWindow& window);

	void Init();
	void Update();
	void Render();
	void SetPixelsPosition(sf::Vector2f pixels_position);

private:
	Game& game_;
	sf::RenderWindow& window_;

	sf::CircleShape shape_;

	// Un identifiant, pas un pointeur : le monde possede le corps.
	b2BodyId body_ = b2_nullBodyId;
};
