#
# Author: Jin Yuqi (Ricky)
# Email: jinyq@new-rt.com
# Date: 2019.03.15
#

cmake_minimum_required(VERSION 3.0)

find_package(GTest REQUIRED)
add_executable(app main.cpp)

add_library(GMock::GMock STATIC IMPORTED)
set_target_properties(GMock::GMock PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/gmock/lib/libgmock.a")

add_library(GMock::Main STATIC IMPORTED)
set_target_properties(GMock::Main PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/gmock/lib/libgmock_main.a")
set_target_properties(GMock::Main PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/gmock/include")
set_target_properties(GMock::Main PROPERTIES INTERFACE_LINK_LIBRARIES GMock::GMock)
set_property(TARGET GMock::Main APPEND PROPERTY INTERFACE_LINK_LIBRARIES GTest::GTest)


target_link_libraries(app GMock::Main pthread)
