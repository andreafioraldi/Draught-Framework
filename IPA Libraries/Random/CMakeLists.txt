include_directories("${PROJECT_SOURCE_DIR}/Dubbel Virtual Machine")
include_directories(${GMP_INCLUDES})

add_library(Random SHARED 
	${CMAKE_CURRENT_SOURCE_DIR}/Random.cpp
)
set_target_properties(Random PROPERTIES SUFFIX ".dubsl")
set_target_properties(Random PROPERTIES PREFIX "")

target_link_libraries(Random DubbelVM ${GMP_LIBRARIES})

if(WIN32)
install(TARGETS Random RUNTIME DESTINATION lib)
else()
install(TARGETS Random LIBRARY DESTINATION lib)
endif()