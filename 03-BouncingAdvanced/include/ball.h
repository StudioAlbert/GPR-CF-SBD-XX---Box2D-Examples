#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class Ball : public sf::Drawable
{
public:
	void Init(b2WorldId world, sf::Vector2u window_size);
	void Update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void SetPixelsPosition(sf::Vector2f pixels_position, sf::Vector2f velocity) const;

private:
	sf::CircleShape shape_;
	b2BodyId body_ = b2_nullBodyId;
};
