#include "game.h"

#include "contacts.h"

Game::~Game()
{
	if (b2World_IsValid(world_)) b2DestroyWorld(world_);
}

void Game::Init()
{
	window_.create(sf::VideoMode({1280, 720}), "SAE Bouncing and Collisions");
	window_.setVerticalSyncEnabled(true);
	window_.setFramerateLimit(60);

	b2WorldDef world_def = b2DefaultWorldDef();
	world_def.gravity = {0.0f, 0.0f};
	world_ = b2CreateWorld(&world_def);

	const sf::Vector2f taille(window_.getSize());
	constexpr float kEpaisseur = 20.0f;

	murs_.push_back(std::make_unique<Bouncer>(world_, sf::Vector2f(taille.x * 0.5f, 0.0f),
	                                          sf::Vector2f(taille.x, kEpaisseur)));
	murs_.push_back(std::make_unique<Bouncer>(world_, sf::Vector2f(taille.x * 0.5f, taille.y),
	                                          sf::Vector2f(taille.x, kEpaisseur)));
	murs_.push_back(std::make_unique<Bouncer>(world_, sf::Vector2f(0.0f, taille.y * 0.5f),
	                                          sf::Vector2f(kEpaisseur, taille.y)));
	murs_.push_back(std::make_unique<Bouncer>(world_, sf::Vector2f(taille.x, taille.y * 0.5f),
	                                          sf::Vector2f(kEpaisseur, taille.y)));
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
		}

		// Maintenir le clic lache des balles, une par image.
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && balls_.size() < 300)
		{
			const sf::Vector2f ou(sf::Mouse::getPosition(window_));
			balls_.push_back(std::make_unique<Ball>(world_, ou));
		}

		// --- la physique ---------------------------------------------------
		b2World_Step(world_, kPas, kSousPas);
		TraiterLesContacts(world_);

		for (const auto& b : balls_) b->Update();
		for (const auto& m : murs_) m->Update(kPas);

		// --- le graphique --------------------------------------------------
		window_.clear();
		for (const auto& m : murs_) window_.draw(*m);
		for (const auto& b : balls_) window_.draw(*b);
		window_.display();
	}
}
