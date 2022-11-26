find_package(Matplot++ REQUIRED)
add_executable(comparing comparing.cpp)

target_link_libraries(comparing Matplot++::matplot)