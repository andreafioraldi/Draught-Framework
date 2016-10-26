include_directories (${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${GMP_INCLUDES})

add_library(DubbelVM SHARED
	${CMAKE_CURRENT_SOURCE_DIR}/Archive.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ArithmeticOperators.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/BitwiseOperators.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Build.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Built-in.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Cell.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ComparisonOperators.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ExecCode.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Methods.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Object.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/SpecialOperators.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Var.cpp
)

if (UNIX)
	set(LIB_DL dl)
else (UNIX)
	set(LIB_DL "")
endif (UNIX)

target_link_libraries(DubbelVM ${GMP_LIBRARIES} ${GMPXX_LIBRARIES} ${LIB_DL})

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
install(TARGETS DubbelVM RUNTIME DESTINATION lib)
install(CODE "execute_process(COMMAND setx /M DUBBEL_LIBPATH \"${CMAKE_INSTALL_PREFIX}\\lib\")")
else()
install(TARGETS DubbelVM LIBRARY DESTINATION lib)
endif()
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Dubbel.h DESTINATION include)
if (UNIX)
	install(CODE "execute_process(COMMAND sh \"${CMAKE_CURRENT_SOURCE_DIR}/install_unix.sh\" \"${CMAKE_INSTALL_PREFIX}\")")
endif (UNIX)

