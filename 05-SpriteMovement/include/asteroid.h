#pragma once

#include <optional>

#include <SFML/Graphics.hpp>

#include "core/box2DEntity.h"

class Asteroid : public Box2DEntity
{
public:
	Asteroid(b2WorldId world, sf::Vector2f window_size);

	void SetIsDead() { is_dead_ = true; }
	bool IsDead() const { return is_dead_; }
	long LocalId() const { return user_data_.LocalId(); }

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	static long NextId();

	std::optional<sf::Sprite> sprite_;
	bool is_dead_ = false;
};
