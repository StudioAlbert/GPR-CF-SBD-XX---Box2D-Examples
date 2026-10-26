#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "brick.h"

class BrickManager : public sf::Drawable
{
public:
	void InitiateBricks(sf::Vector2u window_size);

	std::vector<Brick>& GetBricks() { return bricks_; }

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::vector<Brick> bricks_;
};
