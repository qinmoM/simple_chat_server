cmake_minimum_required(VERSION 3.10)
project(chat)



add_subdirectory(
    external/qinmo_net
)



add_executable(${PROJECT_NAME}
    ./main.cpp
    ./src/ChatServer.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ./include/db
        ./include/model
        ./include/model/entity
        ./include/service
        ./external/nlohmann_json
)



target_link_libraries(${PROJECT_NAME}
    PRIVATE
        mysqlclient
        qinmo_net
)