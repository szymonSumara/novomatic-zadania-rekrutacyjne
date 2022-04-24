#Add the google test subdirectory
add_subdirectory(googletest)

#include googletest/include dir
include_directories(googletest/include)

#include the googlemock/include dir
include_directories(googletest/googlemock/include)

include_directories(../src/Ex.1)

#Define your executable
add_executable(ALL_TESTS main.cpp)

#Link with GoogleTest
target_link_libraries(ALL_TESTS gtest gtest_main)
target_link_libraries(ALL_TESTS Collision)

#Link with GoogleMock
target_link_libraries(ALL_TESTS gmock gmock_main)

