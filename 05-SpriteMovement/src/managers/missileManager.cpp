#include "managers/missileManager.h"

#include <algorithm>

void MissileManager::Update()
{
	std::erase_if(missiles_, [](const std::unique_ptr<Missile>& m) { return m->IsDead(); });

	for (const auto& m : missiles_) m->Update();
}

void MissileManager::AddMissile(const Ship& ship)
{
	missiles_.push_back(
	    std::make_unique<Missile>(world_, ship.getPosition(), ship.getRotation()));
}

void MissileManager::PutMissileToDeath(const long id)
{
	const auto trouve = std::find_if(missiles_.begin(), missiles_.end(),
	                                 [id](const auto& m) { return m->LocalId() == id; });

	if (trouve != missiles_.end()) (*trouve)->SetIsDead();
}

void MissileManager::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	for (const auto& m : missiles_) target.draw(*m, states);
}
