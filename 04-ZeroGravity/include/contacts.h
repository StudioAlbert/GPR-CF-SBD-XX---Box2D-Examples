#pragma once

#include <box2d/box2d.h>

// Box2D 3 n'a plus d'ecouteur. Le monde range les evenements pendant le pas, et
// on les lit APRES. Les capteurs ont leur propre file, separee des contacts.
//
// A appeler apres b2World_Step, une fois par image.
void TraiterLesCapteurs(b2WorldId world);
