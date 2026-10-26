add_executable(05-SpriteMovement
        src/main.cpp
        src/game.cpp
        src/ship.cpp
        src/asteroid.cpp
        src/missile.cpp
        src/bouncer.cpp
        src/lifeBar.cpp
        src/core/box2DEntity.cpp
        src/core/userData.cpp
        src/core/contacts.cpp
        src/managers/textureManager.cpp
        src/managers/soundManager.cpp
        src/managers/asteroidManager.cpp
        src/managers/missileManager.cpp)
target_include_directories(05-SpriteMovement PRIVATE include)
target_link_libraries(05-SpriteMovement PRIVATE SFML::Graphics SFML::Audio box2d::box2d)
copy_data(05-SpriteMovement)
