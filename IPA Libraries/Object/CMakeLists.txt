include_directories("${PROJECT_SOURCE_DIR}/Dubbel Virtual Machine")
include_directories(${GMP_INCLUDES})

add_library(Object SHARED 
	${CMAKE_CURRENT_SOURCE_DIR}/Object.cpp
)
set_target_properties(Object PROPERTIES SUFFIX ".dubsl")
set_target_properties(Object PROPERTIES PREFIX "")

target_link_libraries(Object DubbelVM ${GMP_LIBRARIES})

if(WIN32)
install(TARGETS Object RUNTIME DESTINATION lib)
else()
install(TARGETS Object LIBRARY DESTINATION lib)
endif()

