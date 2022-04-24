add_executable(Ex.1 Ex.1/main.cpp)
add_executable(Ex.2 Ex.2/main.cpp)
add_executable(Ex.3 Ex.3/main.cpp)


target_link_libraries(Ex.2 -lsfml-graphics -lsfml-window -lsfml-system)
target_link_libraries(Ex.2 Collision)
target_link_libraries(Ex.1 Collision)

