#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "core/userData.h"

// Tout ce qui existe a la fois dans le monde physique et a l'ecran.
//
// La classe tient le corps, son etiquette, et la recopie du physique vers le
// graphique — dans ce sens-la seulement.
class Box2DEntity : public sf::Drawable, public sf::Transformable
{
public:
	explicit Box2DEntity(b2WorldId world);
	~Box2DEntity() override;

	Box2DEntity(const Box2DEntity&) = delete;
	Box2DEntity& operator=(const Box2DEntity&) = delete;

	void Update();

protected:
	b2BodyId body_ = b2_nullBodyId;

	// Par valeur. Box2D garde son adresse, donc l'entite ne doit jamais etre
	// copiee ni deplacee — d'ou les constructeurs supprimes ci-dessus, et les
	// `unique_ptr` dans les gestionnaires.
	UserData user_data_;

	b2WorldId world_ = b2_nullWorldId;
};
