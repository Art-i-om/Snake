add_library(Input STATIC
        src/Input.cpp
)

target_include_directories(Input PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Input PUBLIC
        SFML::Window
)