cmake_minimum_required(VERSION 3.2)
# set (CMAKE_CXX_STANDARD 11)

project(ndbox)

# Specify at least C++11
add_definitions("-std=c++11")

# Enable strict handling of warnings
add_definitions("-Wall -Wextra")

# In case /usr/local/include is not in your default includes
# include_directories(/usr/local/include)

# In case /usr/local/lib is not in your default linker path
# link_directories(/usr/local/lib)

find_package(MAVSDK REQUIRED)

# creare variabili d'ambiente per liberie esterne es: BOOST_ROOT_DIR
file(GLOB SOURCE_FILES
    "src/*.h"
    "src/*.cc")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES
    PREFIX ""
    SUFFIX ".node")
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/node_modules/node-addon-api
    ${CMAKE_SOURCE_DIR}/node_modules/node-addon-api/src
    ${CMAKE_JS_INC})

execute_process(COMMAND node -p "require('node-addon-api').include"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_API_DIR
        )
string(REPLACE "\n" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
string(REPLACE "\"" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_ADDON_API_DIR}) #per boost BOOST_INCLUDE_DIRS

# target_include_directories(${PROJECT_NAME} PUBLIC mavsdk)
target_link_libraries(${PROJECT_NAME}
    MAVSDK::mavsdk_telemetry
    MAVSDK::mavsdk_info
    MAVSDK::mavsdk_action
    MAVSDK::mavsdk
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_JS_LIB})
