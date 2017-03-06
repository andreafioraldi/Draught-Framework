include_directories ("${PROJECT_SOURCE_DIR}/Dubbel Builder")
include_directories ("${PROJECT_SOURCE_DIR}/Dubbel Assembler Library")
include_directories(${GMP_INCLUDES})

add_executable(dasm 
	${CMAKE_CURRENT_SOURCE_DIR}/Dasm.cpp
)

target_link_libraries(dasm DubbelAssembler DubbelBuilder ${GMP_LIBRARIES} ${GMPXX_LIBRARIES})

install(TARGETS dasm RUNTIME DESTINATION bin)
