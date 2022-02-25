add_library(simpleutf simpleutf.c)

target_include_directories(simpleutf
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:include>)

install(FILES simpleutf.h DESTINATION include)
