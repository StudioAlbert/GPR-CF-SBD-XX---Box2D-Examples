#include "managers/asteroidManager.h"

#include <algorithm>

void AsteroidManager::Update()
{
	// On enleve les morts AVANT de mettre a jour : detruire leur corps pendant
	// la lecture des evenements serait trop tot, le pas est fini ici.
	std::erase_if(asteroids_, [](const std::unique_ptr<Asteroid>& a) { return a->IsDead(); });

	for (const auto& a : asteroids_) a->Update();
}

void AsteroidManager::AddAsteroid(const sf::Vector2f window_size)
{
	asteroids_.push_back(std::make_unique<Asteroid>(world_, window_size));
}

void AsteroidManager::PutAsteroidToDeath(const long id)
{
	const auto trouve = std::find_if(asteroids_.begin(), asteroids_.end(),
	                                 [id](const auto& a) { return a->LocalId() == id; });

	if (trouve != asteroids_.end()) (*trouve)->SetIsDead();
}

void AsteroidManager::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	for (const auto& a : asteroids_) target.draw(*a, states);
}
