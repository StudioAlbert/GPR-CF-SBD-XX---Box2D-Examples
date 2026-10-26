#pragma once

#include <memory>
#include <optional>
#include <vector>

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "bouncer.h"
#include "lifeBar.h"
#include "ship.h"
#include "managers/asteroidManager.h"
#include "managers/missileManager.h"

// Un vaisseau en apesanteur, des asteroides qui tombent une fois par seconde, et
// des missiles qui les traversent. C'est le seul exemple du depot qui ressemble
// a un vrai jeu : plusieurs types d'entites, chacune reconnaissable au contact.
//
//   fleches     tourner et pousser
//   espace      tirer
//   D           afficher les bords de la fenetre
class Game
{
public:
	Game();
	~Game();

	void Init();
	void Loop();

	void SetDamagesToShip(float damages);
	void PutAsteroidToDeath(long id);
	void PutMissileToDeath(long id);

private:
	void Update();
	void Draw();

	sf::RenderWindow window_;
	b2WorldId world_ = b2_nullWorldId;

	std::vector<std::unique_ptr<Bouncer>> window_limits_;

	std::optional<Ship> ship_;
	std::optional<AsteroidManager> asteroid_manager_;
	std::optional<MissileManager> missile_manager_;

	LifeBar life_bar_{Ship::LifeMax()};
	std::optional<sf::Sprite> game_over_title_;

	sf::Clock clock_;
	float accumulateur_ = 0.0f;
	float depuis_asteroide_ = 0.0f;

	bool debug_mode_ = false;
	bool game_over_ = false;
};
