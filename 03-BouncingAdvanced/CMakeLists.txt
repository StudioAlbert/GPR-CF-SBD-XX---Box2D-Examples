add_executable(03-BouncingAdvanced src/main.cpp src/game.cpp src/ball.cpp src/bouncer.cpp)
target_include_directories(03-BouncingAdvanced PRIVATE include)
target_link_libraries(03-BouncingAdvanced PRIVATE SFML::Graphics box2d::box2d)
