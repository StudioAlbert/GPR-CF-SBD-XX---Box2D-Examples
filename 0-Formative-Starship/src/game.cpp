#include "game.h"

Game::Game()
{
	window_.create(sf::VideoMode({1080, 720}), "The Game");
	window_.setVerticalSyncEnabled(true);
	window_.setFramerateLimit(60);

	// Apesanteur : c'est un shoot'em up vu de dessus.
	b2WorldDef world_def = b2DefaultWorldDef();
	world_def.gravity = {0.0f, 0.0f};
	world_ = b2CreateWorld(&world_def);

	player_.Init(window_.getSize(), world_);

	if (font_.openFromFile("data/arial.ttf"))
	{
		text_.emplace(font_, "", 16);
		text_->setFillColor(sf::Color::White);
		text_->setPosition({50.0f, 250.0f});
	}
}

Game::~Game()
{
	if (b2World_IsValid(world_)) b2DestroyWorld(world_);
}

int Game::Loop()
{
	while (window_.isOpen())
	{
		CheckEvents();
		if (!game_over_) Update();
		Draw();
	}
	return EXIT_SUCCESS;
}

void Game::CheckEvents()
{
	while (const std::optional event = window_.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			window_.close();
			return;
		}
		if (event->is<sf::Event::MouseButtonPressed>())
		{
			game_over_ = false;
		}
		if (const auto* presse = event->getIf<sf::Event::KeyPressed>())
		{
			if (presse->scancode == sf::Keyboard::Scancode::Left) player_.MoveLeft();
			if (presse->scancode == sf::Keyboard::Scancode::Right) player_.MoveRight();
		}
		if (const auto* relache = event->getIf<sf::Event::KeyReleased>())
		{
			if (relache->scancode == sf::Keyboard::Scancode::Left ||
			    relache->scancode == sf::Keyboard::Scancode::Right)
			{
				player_.Stop();
			}
		}
	}
}

void Game::Update()
{
	// Un pas FIXE : l'original passait le temps ecoule, donc la simulation
	// changeait avec le framerate.
	constexpr float kPas = 1.0f / 60.0f;
	constexpr int kSousPas = 4;

	b2World_Step(world_, kPas, kSousPas);
	player_.Update();
}

void Game::Draw()
{
	window_.clear(sf::Color::Black);
	window_.draw(player_);

	if (game_over_ && text_)
	{
		text_->setString("GAME OVER !");
		window_.draw(*text_);
	}

	window_.display();
}
