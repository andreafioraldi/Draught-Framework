include_directories (${CMAKE_CURRENT_SOURCE_DIR})
include_directories ("${PROJECT_SOURCE_DIR}/Dubbel Builder")
include_directories(${GMP_INCLUDES})

#find_package(BISON)
#find_package(FLEX)
#BISON_TARGET(MyParser Parser.y ${PROJECT_SOURCE_DIR}/Parser.cpp DEFINES_FILE ${PROJECT_SOURCE_DIR}/Parser.h)
#FLEX_TARGET(MyLexer Lexer.l  ${PROJECT_SOURCE_DIR}/Lexer.cpp)
#ADD_FLEX_BISON_DEPENDENCY(MyLexer MyParser)

add_library(StoutCompiler SHARED 
	${CMAKE_CURRENT_SOURCE_DIR}/Compiler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Consts.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Node.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Parser.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Lexer.cpp
)

target_link_libraries(StoutCompiler DubbelBuilder ${GMP_LIBRARIES})

if(WIN32)
install(TARGETS StoutCompiler RUNTIME DESTINATION lib)
else()
install(TARGETS StoutCompiler LIBRARY DESTINATION lib)
endif()
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/StoutCompiler.h DESTINATION include)


