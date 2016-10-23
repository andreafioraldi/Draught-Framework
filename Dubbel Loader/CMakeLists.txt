include_directories ("${PROJECT_SOURCE_DIR}/Dubbel Virtual Machine")
include_directories(${GMP_INCLUDES})

add_executable(dubbel 
	${CMAKE_CURRENT_SOURCE_DIR}/Loader.cpp
)

target_link_libraries(dubbel DubbelVM ${GMP_LIBRARIES})

install(TARGETS dubbel RUNTIME DESTINATION bin)
