#include "game.h"

#include "core/SFML_Utilities.h"
#include "core/contacts.h"
#include "managers/soundManager.h"
#include "managers/textureManager.h"

namespace
{
constexpr float kPas = 1.0f / 60.0f;
constexpr int kSousPas = 4;
constexpr float kDelaiAsteroide = 1.0f;   // s
}  // namespace

Game::Game() = default;

Game::~Game()
{
	// Les entites tiennent des corps de ce monde : on les detruit d'abord.
	window_limits_.clear();
	missile_manager_.reset();
	asteroid_manager_.reset();
	ship_.reset();

	if (b2World_IsValid(world_)) b2DestroyWorld(world_);
}

void Game::Init()
{
	window_.create(sf::VideoMode({1280, 720}), "Asteroid Spaceship");
	window_.setVerticalSyncEnabled(true);
	window_.setFramerateLimit(60);

	// Apesanteur : vu de dessus.
	b2WorldDef world_def = b2DefaultWorldDef();
	world_def.gravity = {0.0f, 0.0f};
	world_ = b2CreateWorld(&world_def);

	ship_.emplace(world_);
	ship_->Init(window_.getSize());

	asteroid_manager_.emplace(world_);
	missile_manager_.emplace(world_);

	const sf::Texture& fin = TextureManager::Instance().GameOver();
	game_over_title_.emplace(fin);
	game_over_title_->setOrigin(sf::Vector2f(fin.getSize()) * 0.5f);
	game_over_title_->setPosition(sf::Vector2f(window_.getSize()) * 0.5f);

	// Les quatre bords.
	const sf::Vector2f taille(window_.getSize());
	constexpr float kEpaisseur = 10.0f;

	window_limits_.push_back(std::make_unique<Bouncer>(
	    world_, sf::Vector2f(taille.x * 0.5f, 0.0f), sf::Vector2f(taille.x, kEpaisseur)));
	window_limits_.push_back(std::make_unique<Bouncer>(
	    world_, sf::Vector2f(taille.x * 0.5f, taille.y), sf::Vector2f(taille.x, kEpaisseur)));
	window_limits_.push_back(std::make_unique<Bouncer>(
	    world_, sf::Vector2f(0.0f, taille.y * 0.5f), sf::Vector2f(kEpaisseur, taille.y)));
	window_limits_.push_back(std::make_unique<Bouncer>(
	    world_, sf::Vector2f(taille.x, taille.y * 0.5f), sf::Vector2f(kEpaisseur, taille.y)));
}

void Game::Loop()
{
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
			if (const auto* relache = event->getIf<sf::Event::KeyReleased>())
			{
				if (relache->scancode == sf::Keyboard::Scancode::D)
				{
					debug_mode_ = !debug_mode_;
				}
				if (relache->scancode == sf::Keyboard::Scancode::Space && !game_over_)
				{
					missile_manager_->AddMissile(*ship_);
					SoundManager::Instance().PlayPiou();
				}
				if (relache->scancode == sf::Keyboard::Scancode::Left ||
				    relache->scancode == sf::Keyboard::Scancode::Right)
				{
					ship_->SetAngularDamping(10.0f);
				}
			}
		}

		// L'etat du clavier, lu hors de la file : une touche maintenue pousse
		// a chaque image, elle ne produit pas un evenement par image.
		if (!game_over_)
		{
			using sf::Keyboard::Scancode;
			if (sf::Keyboard::isKeyPressed(Scancode::Up)) ship_->SpeedUp(1.0f);
			if (sf::Keyboard::isKeyPressed(Scancode::Down)) ship_->SpeedDown(10.0f);
			if (sf::Keyboard::isKeyPressed(Scancode::Left)) ship_->RotateLeft(1.0f);
			if (sf::Keyboard::isKeyPressed(Scancode::Right)) ship_->RotateRight(1.0f);
		}

		if (!game_over_) Update();
		Draw();

		SoundManager::Instance().CleanSounds();
	}
}

void Game::Update()
{
	const float ecoule = clock_.restart().asSeconds();

	// Un pas FIXE, rattrape par un accumulateur.
	accumulateur_ += ecoule;
	while (accumulateur_ >= kPas)
	{
		b2World_Step(world_, kPas, kSousPas);
		accumulateur_ -= kPas;
	}

	// Les evenements se lisent APRES le pas : la simulation est finie, on peut
	// detruire des corps sans risque.
	TraiterLesEvenements(world_, *this);

	ship_->Update();
	asteroid_manager_->Update();
	missile_manager_->Update();

	life_bar_.SetLife(ship_->Life());
	life_bar_.Update();

	if (ship_->Life() <= 0.0f)
	{
		game_over_ = true;
		SoundManager::Instance().PlayBoum();
		return;
	}

	// Un asteroide par seconde.
	depuis_asteroide_ += ecoule;
	if (depuis_asteroide_ >= kDelaiAsteroide)
	{
		asteroid_manager_->AddAsteroid(sf::Vector2f(window_.getSize()));
		depuis_asteroide_ = 0.0f;
	}
}

void Game::Draw()
{
	window_.clear();

	if (!game_over_) window_.draw(*ship_);

	window_.draw(*asteroid_manager_);
	window_.draw(*missile_manager_);

	if (debug_mode_)
	{
		for (const auto& b : window_limits_) window_.draw(*b);
	}

	window_.draw(life_bar_);

	if (game_over_ && game_over_title_) window_.draw(*game_over_title_);

	window_.display();
}

void Game::SetDamagesToShip(const float damages)
{
	ship_->SetDamages(damages);
	SoundManager::Instance().PlayBoum();
}

void Game::PutAsteroidToDeath(const long id)
{
	asteroid_manager_->PutAsteroidToDeath(id);
}

void Game::PutMissileToDeath(const long id)
{
	missile_manager_->PutMissileToDeath(id);
}
