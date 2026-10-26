#pragma once

#include <box2d/box2d.h>

// Box2D 3 n'a plus d'ecouteur de contacts. Le monde range les evenements pendant
// le pas, et on les lit APRES, quand la simulation est finie. Plus de rappel au
// milieu, donc plus de mise en garde sur ce qu'on a le droit d'y faire.
//
// A appeler apres b2World_Step, une fois par image.
void TraiterLesContacts(b2WorldId world);
