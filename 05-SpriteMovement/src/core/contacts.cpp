#include "core/contacts.h"

#include "core/userData.h"
#include "game.h"

namespace
{

// Le fil de retour : une forme -> son corps -> l'etiquette de son proprietaire.
UserData* DonneesDe(const b2ShapeId forme)
{
	if (!b2Shape_IsValid(forme)) return nullptr;
	return static_cast<UserData*>(b2Body_GetUserData(b2Shape_GetBody(forme)));
}

}  // namespace

void TraiterLesEvenements(const b2WorldId world, Game& game)
{
	// --- les contacts : le vaisseau contre un asteroide --------------------
	const b2ContactEvents contacts = b2World_GetContactEvents(world);

	for (int i = 0; i < contacts.beginCount; ++i)
	{
		const b2ContactBeginTouchEvent& e = contacts.beginEvents[i];
		const UserData* a = DonneesDe(e.shapeIdA);
		const UserData* b = DonneesDe(e.shapeIdB);
		if (!a || !b) continue;

		const bool choc = (a->Type() == UserDataType::Ship && b->Type() == UserDataType::Asteroid) ||
		                  (b->Type() == UserDataType::Ship && a->Type() == UserDataType::Asteroid);

		// Les degats au CHOC, pas a la separation. L'original les donnait dans
		// EndContact, donc le vaisseau encaissait en s'eloignant.
		if (choc) game.SetDamagesToShip(5.0f);
	}

	// --- les capteurs : le missile qui traverse un asteroide ---------------
	const b2SensorEvents capteurs = b2World_GetSensorEvents(world);

	for (int i = 0; i < capteurs.beginCount; ++i)
	{
		const b2SensorBeginTouchEvent& e = capteurs.beginEvents[i];

		const UserData* missile = DonneesDe(e.sensorShapeId);
		const UserData* cible = DonneesDe(e.visitorShapeId);
		if (!missile || !cible) continue;

		if (missile->Type() == UserDataType::Missile &&
		    cible->Type() == UserDataType::Asteroid)
		{
			game.PutAsteroidToDeath(cible->LocalId());
			game.PutMissileToDeath(missile->LocalId());
		}
	}
}
