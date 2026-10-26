#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

// La raquette. Elle est un corps Box2D dynamique : c'est le seul element du
// squelette qui passe par le moteur physique, la balle fait ses collisions a la
// main.
class Player : public sf::Drawable
{
public:
	void Init(sf::Vector2u window_size, b2WorldId world);

	void MoveLeft();
	void MoveRight();
	void Stop();

	void Update();
	sf::FloatRect GetBounds() const { return shape_.getGlobalBounds(); }
	sf::Vector2f GetVelocity() const;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Vector2f window_size_;
	sf::RectangleShape shape_;
	b2BodyId body_ = b2_nullBodyId;
};
