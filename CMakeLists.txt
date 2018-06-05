cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(ParticleTest VERSION 0.1.0 LANGUAGES CXX)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX /usr/ CACHE PATH "Default install prefix" FORCE)
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

if(CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
endif()

set(CMAKE_CXX_STANDARD 17)


add_library(particletest SHARED particletest.cpp)

add_executable(sample-test-bin sample-test.cpp)
target_link_libraries(sample-test-bin particletest)

enable_testing()
add_test(sample-test sample-test-bin)

configure_file(${CMAKE_SOURCE_DIR}/particletest.pc.in ${CMAKE_BINARY_DIR}/particletest.pc)
install(FILES ${CMAKE_BINARY_DIR}/particletest.pc DESTINATION lib/pkgconfig)


install(
  TARGETS particletest
  LIBRARY DESTINATION lib
)

install(FILES particletest.hpp DESTINATION include)
