add_executable(p2ch13drill drill.cpp)
target_link_libraries(p2ch13drill graphics)

add_executable(p2ch13pr1 problem_1.cpp "Arc.cpp" "Arc.hpp")
target_link_libraries(p2ch13pr1 graphics)

add_executable(p2ch13pr2 problem_2.cpp "Box.cpp" "Box.hpp")
target_link_libraries(p2ch13pr2 graphics)

add_executable(p2ch13pr3 problem_3.cpp "Arrow.cpp" "Arrow.hpp")
target_link_libraries(p2ch13pr3 graphics)

add_executable(p2ch13pr4 problem_4.cpp connection_points.hpp)
target_link_libraries(p2ch13pr4 graphics)

add_executable(p2ch13pr5 problem_5.cpp connection_points.hpp)
target_link_libraries(p2ch13pr5 graphics)

add_executable(p2ch13pr7 problem_7.cpp)
target_link_libraries(p2ch13pr7 graphics)

add_executable(p2ch13pr8 problem_8.cpp "Regular_hexagon.cpp" "Regular_polygon.cpp")
target_link_libraries(p2ch13pr8 graphics)

add_executable(p2ch13pr9 problem_9.cpp "Regular_hexagon.cpp" "Regular_polygon.cpp")
target_link_libraries(p2ch13pr9 graphics)

add_executable(p2ch13pr11 problem_11.cpp)
target_link_libraries(p2ch13pr11 graphics)

add_executable(p2ch13pr12 problem_12.cpp)
target_link_libraries(p2ch13pr12 graphics)

add_executable(p2ch13pr13 problem_13.cpp)
target_link_libraries(p2ch13pr13 graphics)