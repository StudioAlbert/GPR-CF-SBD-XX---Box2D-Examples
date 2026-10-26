add_executable(04-ZeroGravity
        src/main.cpp
        src/game.cpp
        src/ball.cpp
        src/bouncer.cpp
        src/sensor.cpp
        src/contacts.cpp)
target_include_directories(04-ZeroGravity PRIVATE include)
target_link_libraries(04-ZeroGravity PRIVATE SFML::Graphics box2d::box2d)
