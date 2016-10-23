include_directories ("${PROJECT_SOURCE_DIR}/Dubbel Virtual Machine")
include_directories ("${PROJECT_SOURCE_DIR}/Dubbel Builder")
include_directories ("${PROJECT_SOURCE_DIR}/Stout Compiler Library")
include_directories(${GMP_INCLUDES})

add_executable(stout
	${CMAKE_CURRENT_SOURCE_DIR}/Stout.cpp
)

target_link_libraries(stout StoutCompiler DubbelBuilder DubbelVM ${GMP_LIBRARIES})

install(TARGETS stout RUNTIME DESTINATION bin)

