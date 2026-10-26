#include "brick.h"

Brick::Brick(const sf::Vector2f position, const sf::Vector2f size, const sf::Color fill,
             const sf::Color outline)
    : shape_(size)
{
	shape_.setOrigin(size * 0.5f);
	shape_.setPosition(position);
	shape_.setFillColor(fill);
	shape_.setOutlineColor(outline);
	shape_.setOutlineThickness(1.0f);
}

void Brick::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(shape_, states);
}
