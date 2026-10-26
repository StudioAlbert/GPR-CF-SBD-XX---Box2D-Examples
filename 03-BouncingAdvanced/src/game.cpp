#include "game.h"

#include "SFML-Utilities.h"

Game::~Game()
{
	if (b2World_IsValid(world_)) b2DestroyWorld(world_);
}

void Game::Init()
{
	window_.create(sf::VideoMode({1280, 720}), "SAE Bouncing Advanced");
	window_.setVerticalSyncEnabled(true);
	window_.setFramerateLimit(60);

	b2WorldDef world_def = b2DefaultWorldDef();
	world_def.gravity = {0.0f, -9.81f};
	world_ = b2CreateWorld(&world_def);

	the_ball_.Init(world_, window_.getSize());
}

void Game::Loop()
{
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
				if (presse->button == sf::Mouse::Button::Left)
					mouse_pressed_bouncer_ = sf::Vector2f(presse->position);
				if (presse->button == sf::Mouse::Button::Right)
					mouse_pressed_ball_ = sf::Vector2f(presse->position);
			}
			if (const auto* relache = event->getIf<sf::Event::MouseButtonReleased>())
			{
				const sf::Vector2f fin(relache->position);

				if (relache->button == sf::Mouse::Button::Left)
				{
					// Le trait donne la longueur ET l'inclinaison.
					if (VecLength(fin - mouse_pressed_bouncer_) > 5.0f)
						bouncers_.push_back(
						    std::make_unique<Bouncer>(world_, mouse_pressed_bouncer_, fin));
				}
				if (relache->button == sf::Mouse::Button::Right)
				{
					the_ball_.SetPixelsPosition(fin, fin - mouse_pressed_ball_);
				}
			}
			if (const auto* touche = event->getIf<sf::Event::KeyReleased>())
			{
				if (touche->scancode == sf::Keyboard::Scancode::Space) ClearBouncers();
			}
		}

		// --- la physique ---------------------------------------------------
		b2World_Step(world_, kPas, kSousPas);
		the_ball_.Update();

		// --- le graphique --------------------------------------------------
		window_.clear();
		for (const auto& b : bouncers_) window_.draw(*b);
		window_.draw(the_ball_);
		window_.display();
	}
}

void Game::ClearBouncers()
{
	for (const auto& b : bouncers_) b2DestroyBody(b->GetBody());
	bouncers_.clear();
}
