include_directories ("${PROJECT_SOURCE_DIR}/Dubbel Virtual Machine")
include_directories(${GMP_INCLUDES})

add_executable(dubar 
	${CMAKE_CURRENT_SOURCE_DIR}/Archiver.cpp
)

target_link_libraries(dubar DubbelVM ${GMP_LIBRARIES})

install(TARGETS dubar RUNTIME DESTINATION bin)
