#include "brickManager.h"

void BrickManager::InitiateBricks(const sf::Vector2u window_size)
{
	constexpr sf::Vector2f taille{40.0f, 25.0f};
	constexpr float kEcart = 1.1f;

	for (float x = 30.0f; x < static_cast<float>(window_size.x); x += taille.x * kEcart)
	{
		for (float y = 30.0f; y < 200.0f; y += taille.y * kEcart)
		{
			bricks_.emplace_back(sf::Vector2f(x, y), taille, sf::Color::White, sf::Color::Blue);
		}
	}
}

void BrickManager::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	for (const Brick& brick : bricks_) target.draw(brick, states);
}
