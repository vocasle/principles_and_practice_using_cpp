add_executable(p2ch14drill drill.cpp)

add_executable(p2ch14pr1_6 problem_1_to_6.cpp)
target_link_libraries(p2ch14pr1_6 graphics)

add_executable(p2ch14pr7 problem_7.cpp "Stripped_closed_polyline.cpp")
target_link_libraries(p2ch14pr7 graphics)

add_executable(p2ch14pr8 problem_8.cpp)
target_link_libraries(p2ch14pr8 graphics)

add_executable(p2ch14pr9 problem_9.cpp)
target_link_libraries(p2ch14pr9 graphics)