cmake_minimum_required(VERSION 3.28) # plancher impose par SFML 3.1
project(GPR_CF_SBD_XX_Box2D_Examples CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Les sources sont en UTF-8, MSVC ne le devine pas.
if(MSVC)
    add_compile_options(/utf-8)
endif()

# SFML et Box2D viennent de vcpkg, comme dans les projets des etudiants :
# `vcpkg.json` dit ce qu'il faut, vcpkg l'installe a la configuration, et les DLL
# sont recopiees a cote des executables.
#
#   cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
find_package(SFML 3 COMPONENTS Graphics Audio System REQUIRED)
find_package(box2d CONFIG REQUIRED)

# Copie le dossier data/ de la cible a cote de son executable.
# Sans ca, les chemins relatifs du code ne trouvent rien a l'execution.
function(copy_data target)
    add_custom_command(TARGET ${target} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/data" "$<TARGET_FILE_DIR:${target}>/data")
endfunction()

add_subdirectory(01-Gravity)
add_subdirectory(02-Bouncing)
add_subdirectory(04-ZeroGravity)
