add_executable(0-Formative-Arkanoid
        src/main.cpp
        src/game.cpp
        src/ball.cpp
        src/brick.cpp
        src/brickManager.cpp
        src/player.cpp)
target_include_directories(0-Formative-Arkanoid PRIVATE include ../_Utilities/include)
target_link_libraries(0-Formative-Arkanoid PRIVATE SFML::Graphics box2d::box2d)
copy_data(0-Formative-Arkanoid)
