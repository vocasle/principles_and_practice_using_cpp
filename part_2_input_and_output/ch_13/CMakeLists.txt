add_executable(p2ch13drill drill.cpp)
target_link_libraries(p2ch13drill graphics)

add_executable(p2ch13pr1 problem_1.cpp "Arc.cpp" "Arc.hpp")
target_link_libraries(p2ch13pr1 graphics)

add_executable(p2ch13pr2 problem_2.cpp "Box.cpp" "Box.hpp" "Arc.cpp" "Arc.hpp")
target_link_libraries(p2ch13pr2 graphics)