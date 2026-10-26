add_executable(0-Formative-Starship src/main.cpp src/game.cpp src/player.cpp)
target_include_directories(0-Formative-Starship PRIVATE include ../_Utilities/include)
target_link_libraries(0-Formative-Starship PRIVATE SFML::Graphics box2d::box2d)
copy_data(0-Formative-Starship)
