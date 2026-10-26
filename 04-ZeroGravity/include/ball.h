#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class Ball : public sf::Drawable
{
public:
	explicit Ball(sf::RenderWindow& window);

	void Init(b2WorldId world);
	void Update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void SetPixelsPosition(sf::Vector2f pixels_position, sf::Vector2f velocity) const;
	void Move(float x, float y) const;

	b2Vec2 GetLinearVelocity() const { return b2Body_GetLinearVelocity(body_); }

private:
	sf::RenderWindow& window_;

	sf::CircleShape shape_;
	b2BodyId body_ = b2_nullBodyId;
};
