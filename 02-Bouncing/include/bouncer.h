#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class Game;

// La plateforme. Statique : elle ne bouge pas quand on lui tombe dessus.
class Bouncer
{
public:
	Bouncer(Game& game, sf::RenderWindow& window);

	void Init();
	void Update();
	void Render() const;

private:
	Game& game_;
	sf::RenderWindow& window_;

	sf::RectangleShape shape_;
	b2BodyId body_ = b2_nullBodyId;
};
