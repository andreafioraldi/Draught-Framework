include_directories (${CMAKE_CURRENT_SOURCE_DIR})
include_directories ("${PROJECT_SOURCE_DIR}/Dubbel Builder")
include_directories(${GMP_INCLUDES})

add_library(DubbelAssembler SHARED 
	${CMAKE_CURRENT_SOURCE_DIR}/Compiler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Conversion.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ScanLines.cpp
)

target_link_libraries(DubbelAssembler DubbelBuilder ${GMP_LIBRARIES} ${GMPXX_LIBRARIES})

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
install(TARGETS DubbelAssembler RUNTIME DESTINATION lib)
else()
install(TARGETS DubbelAssembler LIBRARY DESTINATION lib)
endif()
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/DubbelAssembler.h DESTINATION include)


