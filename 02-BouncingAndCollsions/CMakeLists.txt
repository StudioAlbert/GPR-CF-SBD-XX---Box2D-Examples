add_executable(02-BouncingAndCollsions
        src/main.cpp
        src/game.cpp
        src/ball.cpp
        src/bouncer.cpp
        src/contacts.cpp)
target_include_directories(02-BouncingAndCollsions PRIVATE include ../_Utilities/include)
target_link_libraries(02-BouncingAndCollsions PRIVATE SFML::Graphics box2d::box2d)
