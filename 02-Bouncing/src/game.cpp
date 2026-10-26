#include "game.h"

#include "contacts.h"

Game::Game() : the_ball_(*this, this->window_), bouncer_(*this, this->window_)
{
}

Game::~Game()
{
	if (b2World_IsValid(world_)) b2DestroyWorld(world_);
}

void Game::Init()
{
	window_.create(sf::VideoMode({1280, 720}), "SAE Bouncing");
	window_.setVerticalSyncEnabled(true);
	window_.setFramerateLimit(60);

	b2WorldDef world_def = b2DefaultWorldDef();
	world_def.gravity = {0.0f, -9.81f};
	world_ = b2CreateWorld(&world_def);

	bouncer_.Init();
	the_ball_.Init();
}

void Game::Loop()
{
	constexpr float time_step = 1.0f / 60.0f;
	constexpr int sub_step_count = 4;

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
			if (const auto* clic = event->getIf<sf::Event::MouseButtonReleased>())
			{
				the_ball_.SetPixelsPosition(sf::Vector2f(clic->position));
			}
		}

		// --- la physique ---------------------------------------------------
		b2World_Step(world_, time_step, sub_step_count);

		// Les contacts se lisent APRES le pas : la simulation est finie, on peut
		// creer, detruire et modifier sans risque.
		TraiterLesContacts(world_);

		the_ball_.Update();
		bouncer_.Update();

		// --- le graphique --------------------------------------------------
		window_.clear();
		bouncer_.Render();
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
