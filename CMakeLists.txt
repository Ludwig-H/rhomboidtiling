# CMake for order-k Delaunay triangulations using CGAL.
# Includes a commandline tool (main) and tests (test).

cmake_minimum_required(VERSION 3.16)
project(rhomboid CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(CGAL REQUIRED COMPONENTS)
include(${CGAL_USE_FILE})

set(DEPENDENCIES src/rhomboid.cpp src/utils.cpp)

add_executable(main src/main.cpp ${DEPENDENCIES})
add_executable(VerticesKOrderDelaunay src/vertices_korder_delaunay.cpp ${DEPENDENCIES})
add_executable(tests_2d src/tests_2d.cpp ${DEPENDENCIES})
add_executable(tests_3d src/tests_3d.cpp ${DEPENDENCIES})

target_link_libraries(main ${CGAL_LIBRARIES} ${CGAL_3RD_PARTY_LIBRARIES})
target_link_libraries(VerticesKOrderDelaunay ${CGAL_LIBRARIES} ${CGAL_3RD_PARTY_LIBRARIES})
target_link_libraries(tests_2d ${CGAL_LIBRARIES} ${CGAL_3RD_PARTY_LIBRARIES})
target_link_libraries(tests_3d ${CGAL_LIBRARIES} ${CGAL_3RD_PARTY_LIBRARIES})
target_include_directories(tests_2d PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(tests_3d PRIVATE ${CMAKE_SOURCE_DIR})
