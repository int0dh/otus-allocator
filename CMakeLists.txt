cmake_minimum_required(VERSION 3.2)

project(otus_allocator_container)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_NAME "otus_allocator_container")

add_executable(${PROJECT_NAME} main.cxx)

set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_STANDARD 20 
	CXX_STANDARD_REQUIRED ON)
target_compile_definitions(${PROJECT_NAME} PRIVATE BUILD_VERSION=$ENV{BUILD_VERSION})

target_compile_options(${PROJECT_NAME} PRIVATE
	-Wall -Wextra -pedantic -Werror -fconcepts)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH $ENV{BUILD_VERSION})
set(CPACK_PACKAGE_CONTACT hit@me.com)
include(CPack)
