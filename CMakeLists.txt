cmake_minimum_required(VERSION 3.21)

project(SimpleUTF VERSION 0.1)

add_subdirectory(src)

install(TARGETS simpleutf
	EXPORT SimpleUTFTargets
	DESTINATION lib)
install(EXPORT SimpleUTFTargets
	FILE SimpleUTFTargets.cmake
	DESTINATION lib/cmake/SimpleUTF)
include(CMakePackageConfigHelpers)
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
	"${CMAKE_CURRENT_BINARY_DIR}/SimpleUTFConfig.cmake"
	INSTALL_DESTINATION "lib/cmake/SimpleUTF"
	NO_SET_AND_CHECK_MACRO
	NO_CHECK_REQUIRED_COMPONENTS_MACRO)
write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/SimpleUTFConfigVersion.cmake"
	VERSION "${SimpleUTF_VERSION_MAJOR}.${SimpleUTF_VERSION_MINOR}"
	COMPATIBILITY AnyNewerVersion)
install(FILES
	"${CMAKE_CURRENT_BINARY_DIR}/SimpleUTFConfigVersion.cmake"
	"${CMAKE_CURRENT_BINARY_DIR}/SimpleUTFConfig.cmake"
	DESTINATION lib/cmake/SimpleUTF)
export(EXPORT SimpleUTFTargets
	FILE "${CMAKE_CURRENT_BINARY_DIR}/SimpleUTFTargets.cmake")

if(BUILD_TESTING)
	enable_testing()
	add_subdirectory(tests)
endif(BUILD_TESTING)
