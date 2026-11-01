cmake_minimum_required(VERSION 3.10)
project(chat)



add_subdirectory(
    external/qinmo_tool
)



add_executable(${PROJECT_NAME}
    ./main.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ./include
        ./include/db
)



target_link_libraries(${PROJECT_NAME}
    PRIVATE
        mysqlclient
        qinmo_tool
)