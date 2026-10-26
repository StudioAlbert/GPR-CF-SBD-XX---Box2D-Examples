// Le « hello world » de Box2D : une caisse qui tombe sur un sol, et sa position
// affichee en console. Aucun graphique — c'est l'atelier de SBD-04, ou l'on
// verifie que la physique tourne avant d'avoir quoi que ce soit a l'ecran.

#include <cstdlib>
#include <iostream>

#include <box2d/box2d.h>

int main()
{
	std::cout << "Hello Box2D 3\n";

	// --- le monde ----------------------------------------------------------
	b2WorldDef world_def = b2DefaultWorldDef();
	world_def.gravity = {0.0f, -10.0f};
	const b2WorldId world = b2CreateWorld(&world_def);

	// --- le sol, statique --------------------------------------------------
	b2BodyDef ground_def = b2DefaultBodyDef();
	ground_def.position = {0.0f, -10.0f};
	const b2BodyId ground = b2CreateBody(world, &ground_def);

	// b2MakeBox prend des DEMI-dimensions : 100 m de large, 20 m de haut.
	const b2Polygon ground_box = b2MakeBox(50.0f, 10.0f);
	b2ShapeDef ground_shape = b2DefaultShapeDef();
	b2CreatePolygonShape(ground, &ground_shape, &ground_box);

	// --- la caisse, dynamique ----------------------------------------------
	b2BodyDef body_def = b2DefaultBodyDef();
	body_def.type = b2_dynamicBody;
	body_def.position = {0.0f, 4.0f};
	const b2BodyId body = b2CreateBody(world, &body_def);

	const b2Polygon box = b2MakeBox(1.0f, 1.0f);
	b2ShapeDef shape_def = b2DefaultShapeDef();
	shape_def.density = 1.0f;
	shape_def.material.friction = 0.3f;
	b2CreatePolygonShape(body, &shape_def, &box);

	// --- la simulation ------------------------------------------------------
	// Un pas FIXE de 1/60 s, quatre-vingt-dix fois : une seconde et demie. La
	// caisse part de 4 m, tombe, et se pose a 1 m — la moitie de sa hauteur.
	constexpr float kPas = 1.0f / 60.0f;
	constexpr int kSousPas = 4;

	for (int i = 0; i < 90; ++i)
	{
		b2World_Step(world, kPas, kSousPas);

		const b2Vec2 position = b2Body_GetPosition(body);
		const float angle = b2Rot_GetAngle(b2Body_GetRotation(body));

		std::cout << "x = " << position.x << "  y = " << position.y
		          << "  angle = " << angle << '\n';
	}

	// Emporte les corps et les formes : rien d'autre a liberer.
	b2DestroyWorld(world);
	return EXIT_SUCCESS;
}
