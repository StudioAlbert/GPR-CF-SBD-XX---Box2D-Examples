add_executable(02-Bouncing src/main.cpp src/game.cpp src/ball.cpp src/bouncer.cpp src/contacts.cpp)
target_include_directories(02-Bouncing PRIVATE include)
target_link_libraries(02-Bouncing PRIVATE SFML::Graphics box2d::box2d)
