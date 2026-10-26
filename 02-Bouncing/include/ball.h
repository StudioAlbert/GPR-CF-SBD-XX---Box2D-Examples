#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class Game;

// La bille dynamique. Elle porte un `userData` : c'est par la qu'on la retrouve
// depuis un evenement de contact.
class Ball
{
public:
	Ball(Game& game, sf::RenderWindow& window);

	void Init();
	void Update();
	void Render() const;
	void SetPixelsPosition(sf::Vector2f pixels_position) const;

	void SetNewColor();

private:
	Game& game_;
	sf::RenderWindow& window_;

	sf::CircleShape shape_;
	b2BodyId body_ = b2_nullBodyId;
};
