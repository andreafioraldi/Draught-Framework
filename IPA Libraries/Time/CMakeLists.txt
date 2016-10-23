include_directories("${PROJECT_SOURCE_DIR}/Dubbel Virtual Machine")
include_directories(${GMP_INCLUDES})

add_library(Time SHARED 
	${CMAKE_CURRENT_SOURCE_DIR}/Time.cpp
)
set_target_properties(Time PROPERTIES SUFFIX ".dubsl")
set_target_properties(Time PROPERTIES PREFIX "")

target_link_libraries(Time DubbelVM ${GMP_LIBRARIES})

if(WIN32)
install(TARGETS Time RUNTIME DESTINATION lib)
else()
install(TARGETS Time LIBRARY DESTINATION lib)
endif()

