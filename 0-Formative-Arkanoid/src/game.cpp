#include "game.h"

Game::Game()
{
	window_.create(sf::VideoMode({700, 860}), "The Game");
	window_.setVerticalSyncEnabled(true);
	window_.setFramerateLimit(60);
	window_.setKeyRepeatEnabled(false);

	// La balle fait ses collisions a la main ; seule la raquette est un corps.
	b2WorldDef world_def = b2DefaultWorldDef();
	world_def.gravity = {0.0f, 0.0f};
	world_ = b2CreateWorld(&world_def);

	ball_.emplace(window_.getSize());
	player_.Init(window_.getSize(), world_);
	brick_manager_.InitiateBricks(window_.getSize());

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
			ball_.emplace(window_.getSize());
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
	constexpr float kPas = 1.0f / 60.0f;
	constexpr int kSousPas = 4;

	const float ecoule = clock_.restart().asSeconds();

	b2World_Step(world_, kPas, kSousPas);
	player_.Update();

	// TO DO : la balle ne bouge pas. Decommenter, puis regler ce qui suit.
	// ball_->Update(ecoule);
	(void)ecoule;

	ball_->CollideBounds();

	if (ball_->Collide(player_.GetBounds()))
	{
		// La raquette communique son elan a la balle.
		ball_->AddForce(player_.GetVelocity() * 0.0005f);
	}

	for (const Brick& brick : brick_manager_.GetBricks())
	{
		ball_->Collide(brick.GetBounds());
	}

	game_over_ = ball_->IsOut();
}

void Game::Draw()
{
	window_.clear(sf::Color::Black);

	window_.draw(*ball_);
	window_.draw(player_);
	window_.draw(brick_manager_);

	if (game_over_ && text_)
	{
		text_->setString("GAME OVER !");
		window_.draw(*text_);
	}

	window_.display();
}
