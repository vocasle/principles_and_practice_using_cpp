file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${Graphics_lib_SOURCE_DIR}/include/graphics/*.h")

add_library(graphics 
	Graph.cpp  
	GUI.cpp
	Simple_window.cpp
	Window.cpp
	"${HEADER_LIST}"
)

target_include_directories(graphics PUBLIC ../include)
target_link_libraries(graphics fltk fltk_images)
target_include_directories(graphics PUBLIC ${FLTK_INCLUDE_DIRS})