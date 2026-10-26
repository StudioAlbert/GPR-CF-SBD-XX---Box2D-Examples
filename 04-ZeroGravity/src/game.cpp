#include "game.h"

#include <iostream>

#include "SFML_Utilities.h"
#include "contacts.h"

Game::Game() : the_ball_(this->window_)
{
}

Game::~Game()
{
	if (b2World_IsValid(world_)) b2DestroyWorld(world_);
}

void Game::Init()
{
	window_.create(sf::VideoMode({1280, 720}), "SAE Zero Gravity");
	window_.setVerticalSyncEnabled(true);
	window_.setFramerateLimit(60);

	// Apesanteur : la balle garde sa vitesse jusqu'a ce qu'elle tape un bord.
	b2WorldDef world_def = b2DefaultWorldDef();
	world_def.gravity = {0.0f, 0.0f};
	world_ = b2CreateWorld(&world_def);

	the_ball_.Init(world_);

	const sf::Vector2f taille(window_.getSize());

	// Les quatre bords de la fenetre.
	window_limits_.emplace_back(world_, sf::Vector2f(0.5f * taille.x, 0.0f),
	                            sf::Vector2f(taille.x, 10.0f));
	window_limits_.emplace_back(world_, sf::Vector2f(0.5f * taille.x, taille.y),
	                            sf::Vector2f(taille.x, 10.0f));
	window_limits_.emplace_back(world_, sf::Vector2f(0.0f, 0.5f * taille.y),
	                            sf::Vector2f(10.0f, taille.y));
	window_limits_.emplace_back(world_, sf::Vector2f(taille.x, 0.5f * taille.y),
	                            sf::Vector2f(10.0f, taille.y));
}

void Game::Loop()
{
	// Un pas FIXE. Le pas variable de la version d'origine donnait des
	// resultats differents a chaque execution, et des bugs injouables.
	constexpr float kPas = 1.0f / 60.0f;
	constexpr int kSousPas = 4;

	while (window_.isOpen())
	{
		// --- les evenements ------------------------------------------------
		while (const std::optional event = window_.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window_.close();
				return;
			}
			if (const auto* resized = event->getIf<sf::Event::Resized>())
			{
				sf::View view = window_.getView();
				view.setSize(sf::Vector2f(resized->size));
				window_.setView(view);
			}
			if (const auto* presse = event->getIf<sf::Event::MouseButtonPressed>())
			{
				if (presse->button == sf::Mouse::Button::Right)
					mouse_pressed_pos_sensor_ = sf::Vector2f(presse->position);
				if (presse->button == sf::Mouse::Button::Left)
					mouse_pressed_pos_ball_ = sf::Vector2f(presse->position);
			}
			if (const auto* relache = event->getIf<sf::Event::MouseButtonReleased>())
			{
				const sf::Vector2f fin(relache->position);

				if (relache->button == sf::Mouse::Button::Right)
				{
					// Le glisser donne le centre et le rayon du capteur.
					const sf::Vector2f centre = 0.5f * (fin + mouse_pressed_pos_sensor_);
					const float rayon = 0.5f * VecDistance(mouse_pressed_pos_sensor_, fin);
					if (rayon > 1.0f)
						sensors_.push_back(std::make_unique<Sensor>(world_, centre, rayon));
				}
				if (relache->button == sf::Mouse::Button::Left)
				{
					// Le glisser donne la vitesse de depart.
					the_ball_.SetPixelsPosition(fin, fin - mouse_pressed_pos_ball_);
					const b2Vec2 v = the_ball_.GetLinearVelocity();
					std::cout << "vitesse de la balle : " << v.x << " ; " << v.y << " m/s\n";
				}
			}
			if (const auto* touche = event->getIf<sf::Event::KeyReleased>())
			{
				if (touche->scancode == sf::Keyboard::Scancode::Space) ClearSensors();
			}
			if (const auto* touche = event->getIf<sf::Event::KeyPressed>())
			{
				switch (touche->scancode)
				{
					case sf::Keyboard::Scancode::Left:  the_ball_.Move(-1.0f, 0.0f); break;
					case sf::Keyboard::Scancode::Right: the_ball_.Move(1.0f, 0.0f);  break;
					case sf::Keyboard::Scancode::Up:    the_ball_.Move(0.0f, 1.0f);  break;
					case sf::Keyboard::Scancode::Down:  the_ball_.Move(0.0f, -1.0f); break;
					default: break;
				}
			}
		}

		// --- la physique ---------------------------------------------------
		accumulateur_ += clock_.restart().asSeconds();
		while (accumulateur_ >= kPas)
		{
			b2World_Step(world_, kPas, kSousPas);
			accumulateur_ -= kPas;
		}

		// Les capteurs se lisent APRES le pas.
		TraiterLesCapteurs(world_);

		the_ball_.Update();

		// --- le graphique --------------------------------------------------
		window_.clear();
		for (const auto& b : window_limits_) window_.draw(b);
		for (const auto& s : sensors_) window_.draw(*s);
		window_.draw(the_ball_);
		window_.display();
	}
}

void Game::ClearSensors()
{
	// Detruire le corps emporte sa forme. On vide ensuite le vecteur, qui
	// possede les objets.
	for (const auto& s : sensors_) b2DestroyBody(s->GetBody());
	sensors_.clear();
}
