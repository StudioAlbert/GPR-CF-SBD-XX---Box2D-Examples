#include "contacts.h"

#include "objet.h"

void TraiterLesContacts(const b2WorldId world)
{
	const b2ContactEvents contacts = b2World_GetContactEvents(world);

	for (int i = 0; i < contacts.beginCount; ++i)
	{
		const b2ContactBeginTouchEvent& e = contacts.beginEvents[i];

		// Les deux formes portent un `Objet*` : le cast est sur, et chacune
		// sait ce qu'elle a touche grace a l'etiquette de l'autre.
		auto* a = static_cast<Objet*>(b2Shape_GetUserData(e.shapeIdA));
		auto* b = static_cast<Objet*>(b2Shape_GetUserData(e.shapeIdB));

		if (a && b)
		{
			a->Touche(*b);
			b->Touche(*a);
		}
	}
}
