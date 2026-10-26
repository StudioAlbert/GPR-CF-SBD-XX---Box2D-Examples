add_executable(01-Gravity src/main.cpp src/game.cpp src/ball.cpp)
target_include_directories(01-Gravity PRIVATE include)
target_link_libraries(01-Gravity PRIVATE SFML::Graphics box2d::box2d)
