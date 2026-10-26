#pragma once

#include <optional>

#include <SFML/Graphics.hpp>

#include "core/box2DEntity.h"

// Un missile est un CAPTEUR : il traverse ce qu'il touche et le signale, au lieu
// de rebondir dessus. Il passe donc par `b2World_GetSensorEvents`, pas par les
// contacts.
class Missile : public Box2DEntity
{
public:
	Missile(b2WorldId world, sf::Vector2f start_pixels, sf::Angle angle);

	void SetIsDead() { is_dead_ = true; }
	bool IsDead() const { return is_dead_; }
	long LocalId() const { return user_data_.LocalId(); }

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	static long NextId();

	std::optional<sf::Sprite> sprite_;
	bool is_dead_ = false;
};
