include_directories("${PROJECT_SOURCE_DIR}/Dubbel Virtual Machine")
include_directories(${GMP_INCLUDES})

add_library(Ptr SHARED 
	${CMAKE_CURRENT_SOURCE_DIR}/Ptr.cpp
)
set_target_properties(Ptr PROPERTIES SUFFIX ".dubsl")
set_target_properties(Ptr PROPERTIES PREFIX "")

target_link_libraries(Ptr DubbelVM ${GMP_LIBRARIES})

if(WIN32)
install(TARGETS Ptr RUNTIME DESTINATION lib)
else()
install(TARGETS Ptr LIBRARY DESTINATION lib)
endif()

