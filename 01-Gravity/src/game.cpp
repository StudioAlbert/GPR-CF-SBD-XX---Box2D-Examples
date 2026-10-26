#include "game.h"

Game::Game() : the_ball_(*this, this->window_)
{
}

Game::~Game()
{
	// Emporte les corps et les formes. Rien d'autre a liberer.
	if (b2World_IsValid(world_)) b2DestroyWorld(world_);
}

void Game::Init()
{
	// SFML 3 : la taille passe en un seul vecteur, plus en deux entiers.
	window_.create(sf::VideoMode({1280, 720}), "SAE Platformer");
	window_.setVerticalSyncEnabled(true);
	window_.setFramerateLimit(60);

	// Box2D 3 : on decrit le monde, puis on le cree. Y monte, d'ou la gravite negative.
	b2WorldDef world_def = b2DefaultWorldDef();
	world_def.gravity = {0.0f, -9.81f};
	world_ = b2CreateWorld(&world_def);

	the_ball_.Init();
}

void Game::Loop()
{
	// Un pas fixe : la simulation ne depend pas du framerate.
	constexpr float time_step = 1.0f / 60.0f;
	constexpr int sub_step_count = 4;

	while (window_.isOpen())
	{
		// --- les evenements ------------------------------------------------
		// SFML 3 : pollEvent rend un optionnel, et les evenements sont des types.
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
			if (const auto* clic = event->getIf<sf::Event::MouseButtonReleased>())
			{
				the_ball_.SetPixelsPosition(sf::Vector2f(clic->position));
			}
		}

		// --- la physique ---------------------------------------------------
		// Box2D 3 : un seul compte de sous-pas, au lieu des deux de la version 2.
		b2World_Step(world_, time_step, sub_step_count);
		the_ball_.Update();

		// --- le graphique --------------------------------------------------
		window_.clear();
		the_ball_.Render();
		window_.display();
	}
}

// Les deux axes Y s'opposent : il monte chez Box2D, il descend chez SFML.
b2Vec2 Game::PixelsToMeters(sf::Vector2f pixels)
{
	return {pixels.x / pixels_meters_ratio_, -1.0f * pixels.y / pixels_meters_ratio_};
}

b2Vec2 Game::PixelsToMeters(sf::Vector2u pixels)
{
	return PixelsToMeters(sf::Vector2f(pixels));
}

float Game::PixelsToMeters(float pixels)
{
	return pixels / pixels_meters_ratio_;
}

float Game::MetersToPixels(float meters)
{
	return meters * pixels_meters_ratio_;
}

sf::Vector2f Game::MetersToPixels(b2Vec2 meters)
{
	return {meters.x * pixels_meters_ratio_, -1.0f * meters.y * pixels_meters_ratio_};
}
