#include "lifeBar.h"

#include <algorithm>

namespace
{
constexpr sf::Vector2f kTaille{200.0f, 16.0f};
constexpr sf::Vector2f kCoin{20.0f, 20.0f};
}  // namespace

LifeBar::LifeBar(const float life_max) : life_max_(life_max), life_(life_max)
{
	contour_.setSize(kTaille);
	contour_.setPosition(kCoin);
	contour_.setFillColor(sf::Color::Transparent);
	contour_.setOutlineColor(sf::Color::White);
	contour_.setOutlineThickness(1.0f);

	fill_.setSize(kTaille);
	fill_.setPosition(kCoin);
	fill_.setFillColor(sf::Color(60, 200, 90));
}

void LifeBar::SetLife(const float life)
{
	life_ = std::clamp(life, 0.0f, life_max_);
}

void LifeBar::Update()
{
	const float part = life_max_ > 0.0f ? life_ / life_max_ : 0.0f;
	fill_.setSize({kTaille.x * part, kTaille.y});

	// Du vert au rouge a mesure qu'elle descend.
	fill_.setFillColor(sf::Color(static_cast<std::uint8_t>(230 * (1.0f - part)),
	                             static_cast<std::uint8_t>(60 + 140 * part), 90));
}

void LifeBar::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(fill_, states);
	target.draw(contour_, states);
}
