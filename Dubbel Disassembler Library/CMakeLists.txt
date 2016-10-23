include_directories (${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${GMP_INCLUDES})

add_library(DubbelDisassembler SHARED 
	${CMAKE_CURRENT_SOURCE_DIR}/Disassembler.cpp
)

target_link_libraries(DubbelDisassembler ${GMP_LIBRARIES})

if(WIN32)
install(TARGETS DubbelDisassembler RUNTIME DESTINATION lib)
else()
install(TARGETS DubbelDisassembler LIBRARY DESTINATION lib)
endif()
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/DubbelDisassembler.h DESTINATION include)


