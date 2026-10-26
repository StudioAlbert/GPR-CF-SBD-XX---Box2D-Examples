#pragma once

#include <SFML/Graphics.hpp>

class Ball : public sf::Drawable
{
public:
	explicit Ball(sf::Vector2u window_size);

	void Update(float time_elapsed);
	void CollideBounds();
	bool Collide(const sf::FloatRect& bounds);
	bool IsOut() const;
	void AddForce(sf::Vector2f force);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	void Bounce(sf::Vector2f direction);
	static sf::Vector2f ContactNormal(const sf::FloatRect& bounds, sf::Vector2f direction);

	sf::Vector2f window_size_;
	sf::Vector2f direction_;
	sf::Vector2f velocity_;

	sf::CircleShape shape_;
};
