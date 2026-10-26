#pragma once

#include <SFML/Graphics.hpp>

class Brick : public sf::Drawable
{
public:
	Brick(sf::Vector2f position, sf::Vector2f size, sf::Color fill, sf::Color outline);

	sf::FloatRect GetBounds() const { return shape_.getGlobalBounds(); }

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::RectangleShape shape_;
};
