include_directories ("${PROJECT_SOURCE_DIR}/Dubbel Virtual Machine")
include_directories ("${PROJECT_SOURCE_DIR}/Dubbel Builder")
include_directories ("${PROJECT_SOURCE_DIR}/Stout Compiler Library")
include_directories (${GMP_INCLUDES})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(Readline)

if(READLINE_FOUND)
    include_directories(${Readline_INCLUDE_DIR})
    add_definitions(-DUSE_READLINE)
endif(READLINE_FOUND)

add_executable(stout
	${CMAKE_CURRENT_SOURCE_DIR}/Stout.cpp
)

if(READLINE_FOUND)
    target_link_libraries(stout StoutCompiler DubbelBuilder DubbelVM ${GMP_LIBRARIES} ${GMPXX_LIBRARIES} ${Readline_LIBRARY})
else(READLINE_FOUND)
    target_link_libraries(stout StoutCompiler DubbelBuilder DubbelVM ${GMP_LIBRARIES} ${GMPXX_LIBRARIES})
endif(READLINE_FOUND)

install(TARGETS stout RUNTIME DESTINATION bin)

