#pragma once

#include <list>

#include <SFML/Audio.hpp>

// Un `sf::Sound` ne joue qu'un son a la fois : en rejouer un deja en cours coupe
// le precedent. Pour que deux tirs se superposent, il faut donc un `sf::Sound`
// par son en vol — d'ou la liste, purgee de ceux qui ont fini.
class SoundManager
{
public:
	static SoundManager& Instance();

	SoundManager(const SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;

	void PlayPiou();
	void PlayBrr();
	void PlayBoum();

	// A appeler une fois par image : retire les sons termines.
	void CleanSounds();

private:
	SoundManager();

	void Play(const sf::SoundBuffer& buffer);

	sf::SoundBuffer piou_;
	sf::SoundBuffer brr_;
	sf::SoundBuffer boum_;

	// Une liste, pas un vector : `sf::Sound` n'est pas deplacable sans risque
	// et une liste ne deplace jamais ses elements.
	std::list<sf::Sound> en_cours_;
};
