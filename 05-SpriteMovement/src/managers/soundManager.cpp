#include "managers/soundManager.h"

#include <iostream>

namespace
{

void Charger(sf::SoundBuffer& buffer, const std::string& chemin)
{
	if (!buffer.loadFromFile(chemin)) std::cerr << "son introuvable : " << chemin << '\n';
}

}  // namespace

SoundManager::SoundManager()
{
	Charger(piou_, "data/sounds/Piou.wav");
	Charger(brr_, "data/sounds/Brr.wav");
	Charger(boum_, "data/sounds/Boum.wav");
}

SoundManager& SoundManager::Instance()
{
	static SoundManager instance;
	return instance;
}

void SoundManager::Play(const sf::SoundBuffer& buffer)
{
	// En SFML 3, un `sf::Sound` recoit son tampon a la construction.
	en_cours_.emplace_back(buffer).play();
}

void SoundManager::PlayPiou() { Play(piou_); }
void SoundManager::PlayBrr() { Play(brr_); }
void SoundManager::PlayBoum() { Play(boum_); }

void SoundManager::CleanSounds()
{
	en_cours_.remove_if(
	    [](const sf::Sound& s) { return s.getStatus() == sf::SoundSource::Status::Stopped; });
}
