#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "ball.h"
#include "bouncer.h"
#include "sensor.h"

// Apesanteur. Clic gauche tire : on glisse pour donner la vitesse. Clic droit
// trace un capteur, que la balle traverse en l'allumant. Espace efface les
// capteurs, les fleches poussent la balle.
class Game
{
public:
	Game();
	~Game();

	void Init();
	void Loop();

	b2WorldId GetWorld() const { return world_; }

private:
	void ClearSensors();

	sf::RenderWindow window_;
	b2WorldId world_ = b2_nullWorldId;

	Ball the_ball_;
	std::vector<Bouncer> window_limits_;

	// Des pointeurs, et pas des valeurs : la forme physique garde l'adresse de
	// son capteur dans `userData`, et un vecteur qui grandit deplace ses
	// elements. Les adresses pendraient au premier agrandissement.
	std::vector<std::unique_ptr<Sensor>> sensors_;

	sf::Vector2f mouse_pressed_pos_sensor_, mouse_pressed_pos_ball_;

	float accumulateur_ = 0.0f;
	sf::Clock clock_;
};
