include_directories (${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${GMP_INCLUDES})

add_library(DubbelBuilder SHARED 
	${CMAKE_CURRENT_SOURCE_DIR}/Builder.cpp
)

target_link_libraries(DubbelBuilder ${GMP_LIBRARIES} ${GMPXX_LIBRARIES})

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
install(TARGETS DubbelBuilder RUNTIME DESTINATION lib)
else()
install(TARGETS DubbelBuilder LIBRARY DESTINATION lib)
endif()
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/DubbelBuilder.h DESTINATION include)


