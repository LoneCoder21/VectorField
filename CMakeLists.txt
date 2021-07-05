cmake_minimum_required(VERSION 3.10)

add_subdirectory(vendor/SFML)
add_subdirectory(vendor/glm)

project(VectorField)

set(CMAKE_CXX_STANDARD 17)

link_directories("vendor/SFML/lib")

file(GLOB VectorFieldsrc "*.h" "*.cpp")
add_executable(VectorField ${VectorFieldsrc})

target_link_libraries(VectorField debug sfml-graphics-d.lib optimized sfml-graphics.lib)
target_link_libraries(VectorField debug sfml-window-d.lib optimized sfml-window.lib)
target_link_libraries(VectorField debug sfml-system-d.lib optimized sfml-system.lib)

target_include_directories(VectorField PRIVATE "vendor/SFML/include")
target_include_directories(VectorField PRIVATE "vendor/glm")

file(COPY vendor/SFML/lib/Debug/sfml-graphics-d-2.dll DESTINATION Debug/)
file(COPY vendor/SFML/lib/Debug/sfml-window-d-2.dll DESTINATION Debug/)
file(COPY vendor/SFML/lib/Debug/sfml-system-d-2.dll DESTINATION Debug/)

file(COPY vendor/SFML/lib/Release/sfml-graphics-2.dll DESTINATION Release)
file(COPY vendor/SFML/lib/Release/sfml-window-2.dll DESTINATION Release)
file(COPY vendor/SFML/lib/Release/sfml-system-2.dll DESTINATION Release)