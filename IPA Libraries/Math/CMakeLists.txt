include_directories("${PROJECT_SOURCE_DIR}/Dubbel Virtual Machine")
include_directories(${GMP_INCLUDES})

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	# on MSVC place the mpfr.dll and mpfr.h in the project root
	find_path(MPFR_INCLUDES NAMES mpfr.h PATHS ${CMAKE_SOURCE_DIR} ${INCLUDE_INSTALL_DIR})
	find_library(MPFR_LIBRARIES mpfr PATHS ${CMAKE_SOURCE_DIR} ${LIB_INSTALL_DIR})
	include(FindPackageHandleStandardArgs)
	find_package_handle_standard_args(MPFR DEFAULT_MSG MPFR_INCLUDES MPFR_LIBRARIES)
	mark_as_advanced(MPFR_INCLUDES MPFR_LIBRARIES)
	# copy mpir library to the output path
	add_custom_target(MPFR_COPY ALL COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/mpfr.dll ${EXECUTABLE_OUTPUT_PATH})
else()
	if (MPFR_INCLUDES AND MPFR_LIBRARIES)
	set(MPFR_FIND_QUIETLY TRUE)
	endif (MPFR_INCLUDES AND MPFR_LIBRARIES)
	find_path(MPFR_INCLUDES NAMES mpfr.h PATHS $ENV{MPFRDIR} ${INCLUDE_INSTALL_DIR})
	find_library(MPFR_LIBRARIES mpfr PATHS $ENV{MPFRDIR} ${LIB_INSTALL_DIR})
	include(FindPackageHandleStandardArgs)
	find_package_handle_standard_args(MPFR DEFAULT_MSG MPFR_INCLUDES MPFR_LIBRARIES)
	mark_as_advanced(MPFR_INCLUDES MPFR_LIBRARIES) 
endif()

include_directories(${MPFR_INCLUDES})

add_library(Math SHARED 
	${CMAKE_CURRENT_SOURCE_DIR}/Math.cpp
)
set_target_properties(Math PROPERTIES SUFFIX ".dubsl")
set_target_properties(Math PROPERTIES PREFIX "")

target_link_libraries(Math DubbelVM ${GMP_LIBRARIES} ${GMPXX_LIBRARIES} ${MPFR_LIBRARIES})

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
install(TARGETS Math RUNTIME DESTINATION lib)
else()
install(TARGETS Math LIBRARY DESTINATION lib)
endif()
