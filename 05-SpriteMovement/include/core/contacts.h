#pragma once

#include <box2d/box2d.h>

class Game;

// Box2D 3 n'a plus d'ecouteur : le monde range les evenements pendant le pas et
// on les lit apres. Deux files separees :
//
//   - les CONTACTS, pour le vaisseau qui percute un asteroide ;
//   - les CAPTEURS, pour le missile — il est declare `isSensor`, donc il ne
//     produit pas de contact, il produit un evenement de capteur.
//
// A appeler apres b2World_Step, une fois par image.
void TraiterLesEvenements(b2WorldId world, Game& game);
