add_executable(p2ch12drill drill.cpp)
target_include_directories(p2ch12drill PRIVATE ${FLTK_INCLUDE_DIRS})
 target_link_libraries(p2ch12drill fltk)