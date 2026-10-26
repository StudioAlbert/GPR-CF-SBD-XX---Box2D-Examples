#pragma once

#include <SFML/Graphics.hpp>

class LifeBar : public sf::Drawable
{
public:
	explicit LifeBar(float life_max);

	void SetLife(float life);
	void Update();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::RectangleShape fill_;
	sf::RectangleShape contour_;
	float life_max_;
	float life_;
};
