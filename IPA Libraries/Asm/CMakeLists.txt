include_directories("${PROJECT_SOURCE_DIR}/Dubbel Virtual Machine")
include_directories("${PROJECT_SOURCE_DIR}/Dubbel Builder")
include_directories("${PROJECT_SOURCE_DIR}/Dubbel Assembler Library")
include_directories("${PROJECT_SOURCE_DIR}/Dubbel Disassembler Library")
include_directories(${GMP_INCLUDES})

add_library(Asm SHARED 
	${CMAKE_CURRENT_SOURCE_DIR}/Asm.cpp
)
set_target_properties(Asm PROPERTIES SUFFIX ".dubsl")
set_target_properties(Asm PROPERTIES PREFIX "")
message(${GMP_LIBRARIES})
target_link_libraries(Asm DubbelAssembler DubbelDisassembler DubbelBuilder DubbelVM ${GMP_LIBRARIES} ${GMPXX_LIBRARIES})

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
install(TARGETS Asm RUNTIME DESTINATION lib)
else()
install(TARGETS Asm LIBRARY DESTINATION lib)
endif()
