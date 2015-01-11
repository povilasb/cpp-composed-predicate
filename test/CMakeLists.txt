cmake_minimum_required(VERSION 2.6)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}.")

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS "-std=c++98 -Wall -Wextra")

set(test_src_dir "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(test_src_files
	${test_src_dir}/composed_predicate_test.cpp
	${test_src_dir}/cpp11_composed_predicate_test.cpp
	${test_src_dir}/boost_composed_predicate_test.cpp
)


set_source_files_properties(${test_src_dir}/cpp11_composed_predicate_test.cpp
	PROPERTIES COMPILE_FLAGS -std=c++11)


find_package(Boost REQUIRED)
if (Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
endif()


set(gmock_dir "${CMAKE_CURRENT_SOURCE_DIR}/lib/gmock")
set(gtest_dir "${gmock_dir}/gtest")
add_subdirectory("${gmock_dir}" "${CMAKE_CURRENT_BINARY_DIR}/lib/gmock")
include_directories("${gtest_dir}/include")
include_directories("${gmock_dir}/include")


set(all_libraries gmock_main gmock gtest)


add_custom_target(run-tests COMMAND "")
set(test_bin_dir "${CMAKE_CURRENT_BINARY_DIR}/test-bin")

foreach(test_src_file ${test_src_files})
	get_filename_component(test_name "${test_src_file}" NAME_WE)
	add_executable("${test_name}" "${test_src_file}")
	add_dependencies("${test_name}" ${all_libraries})
	target_link_libraries("${test_name}" ${all_libraries})

	add_custom_command(TARGET run-tests
		COMMAND "${test_bin_dir}/${test_name}")
	add_dependencies(run-tests "${test_name}")

	set_target_properties("${test_name}" PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${test_bin_dir}")
endforeach()
