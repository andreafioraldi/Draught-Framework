include_directories("${PROJECT_SOURCE_DIR}/Dubbel Virtual Machine")
include_directories(${GMP_INCLUDES})

add_library(IO SHARED 
	${CMAKE_CURRENT_SOURCE_DIR}/IO.cpp
)
set_target_properties(IO PROPERTIES SUFFIX ".dubsl")
set_target_properties(IO PROPERTIES PREFIX "")

target_link_libraries(IO DubbelVM ${GMP_LIBRARIES})

if(WIN32)
install(TARGETS IO RUNTIME DESTINATION lib)
else()
install(TARGETS IO LIBRARY DESTINATION lib)
endif()