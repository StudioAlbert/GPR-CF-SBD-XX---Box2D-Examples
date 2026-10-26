#pragma once

#include <optional>

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class Player : public sf::Drawable
{
public:
	void Init(sf::Vector2u window_size, b2WorldId world);

	void MoveLeft();
	void MoveRight();
	void Stop();

	void Update();
	sf::Vector2f GetVelocity() const;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Vector2f window_size_;

	// La texture est un MEMBRE, pas une locale du constructeur. Un sprite ne
	// copie pas son image : il pointe dessus. Une texture locale meurt a la fin
	// du constructeur et le sprite s'affiche en blanc — c'est le piege de
	// SBD-01, et il etait dans ce squelette.
	sf::Texture texture_;
	std::optional<sf::Sprite> shape_;

	b2BodyId body_ = b2_nullBodyId;
};
