#pragma once

#include <box2d/box2d.h>

// Lit les contacts du dernier pas et previent les deux objets concernes.
// A appeler APRES b2World_Step.
void TraiterLesContacts(b2WorldId world);
