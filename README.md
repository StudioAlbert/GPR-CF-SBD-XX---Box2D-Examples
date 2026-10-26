# GPR-CF-SBD — Exemples Box2D

Le code des séances SBD qui touchent à la physique : Box2D **3.2** et SFML **3.1**, un
programme par idée, chacun dans son répertoire avec sa cible CMake.

## Compiler

```bash
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
cmake --build build
```

SFML et Box2D viennent de **vcpkg** : `vcpkg.json` dit ce qu'il faut, vcpkg l'installe à la
configuration, et les DLL sont recopiées à côté des exécutables.

Sous CLion, le panneau **Vcpkg** met la toolchain en place et la ligne
`-DCMAKE_TOOLCHAIN_FILE` devient inutile.

> [!] Box2D 3.2 est récent
> vcpkg ne le connaît que depuis le **22 octobre 2026**. Si la configuration échoue sur
> `no version database entry for box2d at 3.2.0`, votre checkout vcpkg est trop ancien :
> `git pull` dedans, puis reconfigurez.
>
> La version compte : entre 3.1 et 3.2, `fixedRotation` est devenu `motionLocks`, et le
> rappel pre-solve a changé de signature.

## Les cibles

| Séance | Cible | Ce qu'elle montre | État |
|---|---|---|---|
| SBD-04 | `01-Gravity` | le monde, le pas fixe, un corps dynamique qui tombe ; le clic le téléporte | **portée** |
| SBD-05 | `02-Bouncing` | les contacts : la bille change de couleur à chaque choc | **portée** |
| SBD-05 | `02-BouncingAndCollsions` | les contacts, avec les événements | à porter |
| SBD-05 | `03-BouncingAdvanced` | le même, rangé | à porter |
| SBD-06 | `04-ZeroGravity` | un vrai capteur : la bille le traverse et il s'allume | **portée** |
| SBD-05 | `05-SpriteMovement` | un petit jeu complet : vaisseau, missiles, astéroïdes | à porter |
| — | `00-Starter` | le squelette vide | à porter |
| — | `0-Formative-Arkanoid`, `0-Formative-Starship` | deux formatives | à porter |

## L'état du portage

Ce dépôt était en **Box2D 2 et SFML 2**, en projets Visual Studio. Le portage se fait cible
par cible : seules celles listées comme *portée* ci-dessus entrent dans le `CMakeLists.txt`
racine. Les autres restent en l'état, avec leurs `.vcxproj`, jusqu'à leur tour.

Ce qui change, d'une version à l'autre :

| Box2D 2 | Box2D 3.2 |
|---|---|
| `b2World monde(gravite)` | `b2DefaultWorldDef()` puis `b2CreateWorld(&def)` |
| `b2Body*`, `b2Fixture*` | `b2BodyId`, `b2ShapeId` — des identifiants |
| `b2FixtureDef` + `CreateFixture` | `b2ShapeDef` + `b2CreateCircleShape` — la fixture a disparu |
| `bodyDef.fixedRotation` | `bodyDef.motionLocks.angularZ` |
| `monde.Step(dt, 6, 2)` | `b2World_Step(monde, dt, 4)` — un seul compte de sous-pas |
| `b2ContactListener` | `b2World_GetContactEvents(monde)`, lu **après** le pas |

Et côté SFML :

| SFML 2 | SFML 3.1 |
|---|---|
| `sf::VideoMode(1280, 720)` | `sf::VideoMode({1280, 720})` |
| `sf::Event e; while (pollEvent(e))` | `while (const std::optional e = pollEvent())` |
| `e.type == sf::Event::Closed` | `e->is<sf::Event::Closed>()` |
| `e.size.width` | `e->getIf<sf::Event::Resized>()->size.x` |

## Le facteur mètres / pixels

**100 px/m**, dans `Game::pixels_meters_ratio_`. Un mètre vaut cent pixels, donc la
conversion se vérifie de tête. Il n'apparaît qu'à un seul endroit du projet.
