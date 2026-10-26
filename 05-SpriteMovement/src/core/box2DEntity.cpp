#include "core/box2DEntity.h"

#include "core/SFML_Utilities.h"

Box2DEntity::Box2DEntity(const b2WorldId world) : world_(world)
{
	b2BodyDef body_def = b2DefaultBodyDef();
	body_def.type = b2_dynamicBody;
	body_def.angularDamping = 0.01f;
	body_def.linearDamping = 0.01f;
	body_def.userData = &user_data_;

	body_ = b2CreateBody(world_, &body_def);
}

Box2DEntity::~Box2DEntity()
{
	// Le monde peut avoir ete detruit avant l'entite : on verifie.
	if (b2World_IsValid(world_) && b2Body_IsValid(body_)) b2DestroyBody(body_);
}

void Box2DEntity::Update()
{
	setPosition(MetersToPixels(b2Body_GetPosition(body_)));

	// Le signe moins : Y descend a l'ecran, donc la rotation s'y lit a l'envers.
	setRotation(sf::radians(-b2Rot_GetAngle(b2Body_GetRotation(body_))));
}
