set(CMAKE_BUILD_TYPE Release)
set(SFML_LIBS sfml-window sfml-graphics sfml-system)

FILE(GLOB EngineObj src/EngineBase/*.cpp)
FILE(GLOB EngineComponentsObj src/EngineBase/Components/*.cpp)
add_library(Engine OBJECT ${EngineObj} ${EngineComponentsObj})

FILE(GLOB InterfaceObj src/GraphInterface/*.cpp)
add_library(Interface OBJECT ${InterfaceObj})

#FILE(GLOB CoreObj src/GameCore/*.cpp)

add_executable(test $<TARGET_OBJECTS:Engine> $<TARGET_OBJECTS:Interface> src/main.cpp)

target_link_libraries(test ${SFML_LIBS})
