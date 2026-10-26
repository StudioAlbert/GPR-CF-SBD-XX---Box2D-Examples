#pragma once

// Le fil qui ramene d'une forme physique a l'objet de jeu.
//
// Box2D ne sait rien de vos classes : `userData` est un `void*`. Pour savoir ce
// qu'on a touche, il faut donc que tous les objets du jeu partagent une base
// commune et portent une etiquette. Sans ca, on ne peut que deviner — et deviner
// juste par chance, comme la version d'origine de cet exemple, qui lisait un
// `ContactEvent<Ball>` la ou il y avait parfois un `ContactEvent<Bouncer>`.
enum class TypeObjet
{
	Balle,
	Mur
};

class Objet
{
public:
	explicit Objet(const TypeObjet type) : type_(type) {}
	virtual ~Objet() = default;

	TypeObjet Type() const { return type_; }

	// Appele une fois par contact, pour chacun des deux objets.
	virtual void Touche(const Objet& autre) = 0;

private:
	TypeObjet type_;
};
