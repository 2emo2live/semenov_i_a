find_package(Matplot++ REQUIRED)
find_package(unofficial-libharu CONFIG REQUIRED)

add_executable(comparing comparing.cpp)

target_link_libraries(comparing Matplot++::matplot unofficial::libharu::hpdf)