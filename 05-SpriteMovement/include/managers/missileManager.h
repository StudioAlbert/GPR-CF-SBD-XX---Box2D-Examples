#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "missile.h"
#include "ship.h"

class MissileManager : public sf::Drawable
{
public:
	explicit MissileManager(b2WorldId world) : world_(world) {}

	void Update();
	void AddMissile(const Ship& ship);
	void PutMissileToDeath(long id);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::vector<std::unique_ptr<Missile>> missiles_;
	b2WorldId world_;
};
