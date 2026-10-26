#include "contacts.h"

#include <iostream>

#include "sensor.h"

void TraiterLesCapteurs(const b2WorldId world)
{
	const b2SensorEvents capteurs = b2World_GetSensorEvents(world);

	for (int i = 0; i < capteurs.beginCount; ++i)
	{
		const b2SensorBeginTouchEvent& e = capteurs.beginEvents[i];
		// `sensorShapeId` est le capteur, `visitorShapeId` est ce qui le traverse.
		if (auto* s = static_cast<Sensor*>(b2Shape_GetUserData(e.sensorShapeId)))
		{
			s->SetColor(sf::Color::Yellow);
			std::cout << "entree dans un capteur\n";
		}
	}

	for (int i = 0; i < capteurs.endCount; ++i)
	{
		const b2SensorEndTouchEvent& e = capteurs.endEvents[i];
		// Un evenement de fin arrive aussi quand la forme est detruite : on
		// verifie qu'elle est encore valide avant de s'en servir.
		if (!b2Shape_IsValid(e.sensorShapeId)) continue;

		if (auto* s = static_cast<Sensor*>(b2Shape_GetUserData(e.sensorShapeId)))
		{
			s->SetColor(sf::Color::Cyan);
			std::cout << "sortie d'un capteur\n";
		}
	}
}
