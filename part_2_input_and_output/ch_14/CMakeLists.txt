add_executable(p2ch14drill drill.cpp)

add_executable(p2ch14pr1_6 problem_1_to_6.cpp)
target_link_libraries(p2ch14pr1_6 graphics)

add_executable(p2ch14pr7 problem_7.cpp "Stripped_closed_polyline.cpp")
target_link_libraries(p2ch14pr7 graphics)

add_executable(p2ch14pr8 problem_8.cpp)
target_link_libraries(p2ch14pr8 graphics)

add_executable(p2ch14pr9 problem_9.cpp)
target_link_libraries(p2ch14pr9 graphics)

add_executable(p2ch14pr10 problem_10.cpp Pseudo_window.cpp)
target_link_libraries(p2ch14pr10 graphics)

add_executable(p2ch14pr11 problem_11.cpp Binary_tree.cpp)
target_link_libraries(p2ch14pr11 graphics)

add_executable(p2ch14pr12 problem_12.cpp Binary_tree.cpp)
target_link_libraries(p2ch14pr12 graphics)

add_executable(p2ch14pr13 problem_13.cpp Binary_tree.cpp)
target_link_libraries(p2ch14pr13 graphics)

add_executable(p2ch14pr14 problem_14.cpp Binary_tree.cpp)
target_link_libraries(p2ch14pr14 graphics)

add_executable(p2ch14pr15 problem_15.cpp)
add_executable(p2ch14pr16 problem_16.cpp)
target_link_libraries(p2ch14pr16 graphics)