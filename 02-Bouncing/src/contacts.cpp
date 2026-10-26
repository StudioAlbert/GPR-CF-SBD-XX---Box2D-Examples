#include "contacts.h"

#include <iostream>

#include "ball.h"

void TraiterLesContacts(b2WorldId world)
{
	const b2ContactEvents contacts = b2World_GetContactEvents(world);

	for (int i = 0; i < contacts.beginCount; ++i)
	{
		const b2ContactBeginTouchEvent& e = contacts.beginEvents[i];
		std::cout << "debut de contact\n";

		// `userData` est le fil qui ramene de la forme physique a l'objet de jeu.
		// Ici seule la bille en pose un, donc un pointeur non nul est une bille.
		for (const b2ShapeId forme : {e.shapeIdA, e.shapeIdB})
		{
			if (auto* ball = static_cast<Ball*>(b2Shape_GetUserData(forme)))
			{
				ball->SetNewColor();
			}
		}
	}

	for (int i = 0; i < contacts.endCount; ++i)
	{
		std::cout << "fin de contact\n";
	}
}
