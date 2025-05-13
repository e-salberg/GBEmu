set(MAIN_SOURCES
	main.c
)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
 
add_executable(gbemu ${HEADERS} ${MAIN_SOURCES})
target_link_libraries(gbemu PUBLIC emu PRIVATE SDL3::SDL3)
