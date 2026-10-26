#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "ball.h"
#include "bouncer.h"

// Clic gauche : on trace une plateforme inclinee. Clic droit : on relance la
// bille, le glisser donne la vitesse. Espace efface les plateformes.
class Game
{
public:
	Game() = default;
	~Game();

	void Init();
	void Loop();

private:
	void ClearBouncers();

	sf::RenderWindow window_;
	b2WorldId world_ = b2_nullWorldId;

	Ball the_ball_;
	// Des pointeurs : un vector qui grandit deplace ses elements.
	std::vector<std::unique_ptr<Bouncer>> bouncers_;

	sf::Vector2f mouse_pressed_bouncer_, mouse_pressed_ball_;
};
