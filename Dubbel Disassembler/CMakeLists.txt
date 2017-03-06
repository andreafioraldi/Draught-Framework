include_directories ("${PROJECT_SOURCE_DIR}/Dubbel Disassembler Library")
include_directories(${GMP_INCLUDES})

add_executable(ddis 
	${CMAKE_CURRENT_SOURCE_DIR}/DDis.cpp
)

target_link_libraries(ddis DubbelDisassembler ${GMP_LIBRARIES} ${GMPXX_LIBRARIES})

install(TARGETS ddis RUNTIME DESTINATION bin)
