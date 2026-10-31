cmake_minimum_required(VERSION 3.30)
project(jeu_de_la_vie LANGUAGES CXX)
find_package(SFML COMPONENTS graphics window system)
include(FetchContent)
FetchContent_Declare(Catch2 URL https://github.com/catchorg/Catch2/archive/refs/tags/v3.7.1.zip )
FetchContent_MakeAvailable(Catch2)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
enable_testing()

# Pour faire les premières questions.
add_executable(jeu_de_la_vie_test grille.cc main.cc)
target_compile_features(jeu_de_la_vie_test PUBLIC cxx_std_17)
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(jeu_de_la_vie_test PRIVATE -Wall -Wpedantic)
endif()
target_link_libraries(jeu_de_la_vie_test PRIVATE Catch2::Catch2WithMain)
include(Catch)
catch_discover_tests(jeu_de_la_vie_test)

# Pour faire la question 6
#add_executable(jeu_de_la_vie_texte grille.cpp main_texte.cpp)
#target_compile_features(jeu_de_la_vie_texte PUBLIC cxx_std_17)
#if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
#	target_compile_options(jeu_de_la_vie_texte PRIVATE -Wall -Wpedantic)
#endif()

# Pour faire la question 7
#add_executable(jeu_de_la_vie_sfml grille.cpp affichage_sfml.cc main_sfml.cc)
#target_link_libraries(jeu_de_la_vie_sfml PRIVATE sfml-graphics sfml-window sfml-system)
#target_compile_features(jeu_de_la_vie_sfml PRIVATE cxx_std_17)
#if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
#	target_compile_options(jeu_de_la_vie_sfml PRIVATE -Wall -Wpedantic)
#endif()
