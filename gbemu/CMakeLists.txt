set(MAIN_SOURCES
	main.c
)

add_executable(gbemu ${MAIN_SOURCES})
target_link_libraries(gbemu PUBLIC)
