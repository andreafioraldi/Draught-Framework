include_directories ("${PROJECT_SOURCE_DIR}/Dubbel Builder")
include_directories ("${PROJECT_SOURCE_DIR}/Stout Compiler Library")
include_directories(${GMP_INCLUDES})

add_executable(stoutc 
	${CMAKE_CURRENT_SOURCE_DIR}/StoutC.cpp
)

target_link_libraries(stoutc StoutCompiler DubbelBuilder ${GMP_LIBRARIES})

install(TARGETS stoutc RUNTIME DESTINATION bin)
