cmake_minimum_required (VERSION 2.6)

set (DRAUGHT_VERSION 1.0)
set (DRAUGHT_VERSION_MAJOR 1)
set (DRAUGHT_VERSION_MINOR 0)

project ("Draught Framework")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#enable optimization for g++
if(CMAKE_COMPILER_IS_GNUCXX)
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif(CMAKE_COMPILER_IS_GNUCXX)

#set default prefix to /usr in Unix
if (UNIX AND CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set (CMAKE_INSTALL_PREFIX "/usr" CACHE PATH "default install path" FORCE )
endif()

#enable C++11
set (CMAKE_CXX_STANDARD 11)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/Output/)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/Output/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${LIBRARY_OUTPUT_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${LIBRARY_OUTPUT_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${LIBRARY_OUTPUT_PATH})

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	# tell the compiler to ingnore includeing wingdi.h
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DNOGDI")
	# on MSVC place the mpir.dll , mpir.h and mpirxx.h in the project root
	find_path(GMP_INCLUDES NAMES mpir.h mpirxx.h PATHS ${CMAKE_SOURCE_DIR} ${INCLUDE_INSTALL_DIR})
	find_library(GMP_LIBRARIES mpir PATHS ${CMAKE_SOURCE_DIR} ${LIB_INSTALL_DIR})
	include(FindPackageHandleStandardArgs)
	find_package_handle_standard_args(GMP DEFAULT_MSG GMP_INCLUDES GMP_LIBRARIES)
	mark_as_advanced(GMP_INCLUDES GMP_LIBRARIES)
	set(GMPXX_LIBRARIES "")
	# copy mpir library to the output path
	add_custom_target(MPIR_COPY ALL COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/mpir.dll ${EXECUTABLE_OUTPUT_PATH})
else()
	# try to find the GNU Multiple Precision Arithmetic Library (GMP)
	# see http://gmplib.org/
	if (GMP_INCLUDES AND GMP_LIBRARIES)
	set(GMP_FIND_QUIETLY TRUE)
	endif (GMP_INCLUDES AND GMP_LIBRARIES)
	find_path(GMP_INCLUDES NAMES gmp.h gmpxx.h PATHS $ENV{GMPDIR} ${INCLUDE_INSTALL_DIR})
	find_library(GMP_LIBRARIES gmp gmpxx PATHS $ENV{GMPDIR} ${LIB_INSTALL_DIR})
	find_library(GMPXX_LIBRARIES gmpxx PATHS $ENV{GMPDIR} ${LIB_INSTALL_DIR})
	include(FindPackageHandleStandardArgs)
	find_package_handle_standard_args(GMP DEFAULT_MSG GMP_INCLUDES GMP_LIBRARIES GMPXX_LIBRARIES)
	mark_as_advanced(GMP_INCLUDES GMP_LIBRARIES GMPXX_LIBRARIES)
endif()

#list compiler flags
message ("C++ flags: " ${CMAKE_CXX_FLAGS})

option (USE_DUBBEL_BUILDER "Use Dubbel Builder" ON)
option (USE_DUBBEL_ASSEMBLER_LIBRARY "Use Dubbel Assembler Library" ON)
option (USE_DUBBEL_ASSEMBLER "Use Dubbel Assembler" ON)

option (USE_DUBBEL_DISASSEMBLER_LIBRARY "Use Dubbel Disassembler Library" ON)
option (USE_DUBBEL_DISASSEMBLER "Use Dubbel Disassembler" ON)

option (USE_DUBBEL_VIRTUAL_MACHINE "Use Dubbel Virtual Machine" ON)
option (USE_DUBBEL_LOADER "Use Dubbel Loader" ON)
option (USE_DUBBEL_ARCHIVER "Use Dubbel Archiver" ON)

option (USE_STOUT_COMPILER_LIBRARY "Use Stout Compiler Library" ON)
option (USE_STOUT_COMPILER "Use Stout Compiler" ON)
option (USE_STOUT_LOADER "Use Stout Loader" ON)

option (USE_IPA "Use IPA Libraries" ON)

if (USE_DUBBEL_BUILDER)
	add_subdirectory ("Dubbel Builder")
	set (SELECTED_DIRS ${SELECTED_DIRS} " Dubbel Builder")
	if (USE_DUBBEL_ASSEMBLER_LIBRARY)
		add_subdirectory ("Dubbel Assembler Library")
		set (SELECTED_DIRS ${SELECTED_DIRS} " Dubbel Assembler Library")
		if (USE_DUBBEL_ASSEMBLER)
			add_subdirectory ("Dubbel Assembler")
			set (SELECTED_DIRS ${SELECTED_DIRS} " Dubbel Assembler")
		endif (USE_DUBBEL_ASSEMBLER)
	endif (USE_DUBBEL_ASSEMBLER_LIBRARY)
	if (USE_STOUT_COMPILER_LIBRARY)
		add_subdirectory ("Stout Compiler Library")
		set (SELECTED_DIRS ${SELECTED_DIRS} " Stout Compiler Library")
		if (USE_STOUT_COMPILER)
			add_subdirectory ("Stout Compiler")
			set (SELECTED_DIRS ${SELECTED_DIRS} " Stout Compiler")
		endif (USE_STOUT_COMPILER)	
	endif (USE_STOUT_COMPILER_LIBRARY)
endif (USE_DUBBEL_BUILDER)

if (USE_DUBBEL_DISASSEMBLER_LIBRARY)
	add_subdirectory ("Dubbel Disassembler Library")
	set (SELECTED_DIRS ${SELECTED_DIRS} " Dubbel Disassembler Library")
	if (USE_DUBBEL_DISASSEMBLER)
		add_subdirectory ("Dubbel Disassembler")
		set (SELECTED_DIRS ${SELECTED_DIRS} " Dubbel Disassembler")
	endif (USE_DUBBEL_DISASSEMBLER)
endif (USE_DUBBEL_DISASSEMBLER_LIBRARY)

if (USE_DUBBEL_VIRTUAL_MACHINE)
	add_subdirectory ("Dubbel Virtual Machine")
	set (SELECTED_DIRS ${SELECTED_DIRS} " Dubbel Virtual Machine")
	if (USE_DUBBEL_LOADER)
		add_subdirectory ("Dubbel Loader")
		set (SELECTED_DIRS ${SELECTED_DIRS} " Dubbel Loader")
	endif (USE_DUBBEL_LOADER)
	if (USE_DUBBEL_ARCHIVER)
		add_subdirectory ("Dubbel Archiver")
		set (SELECTED_DIRS ${SELECTED_DIRS} " Dubbel Archiver")
	endif (USE_DUBBEL_ARCHIVER)
	if (USE_DUBBEL_BUILDER AND USE_STOUT_COMPILER_LIBRARY AND USE_STOUT_LOADER)
		add_subdirectory ("Stout Loader")
		set (SELECTED_DIRS ${SELECTED_DIRS} " Stout Loader")
	endif (USE_DUBBEL_BUILDER AND USE_STOUT_COMPILER_LIBRARY AND USE_STOUT_LOADER)
endif (USE_DUBBEL_VIRTUAL_MACHINE)

if (USE_IPA)
	add_subdirectory ("IPA Libraries")
	set (SELECTED_DIRS ${SELECTED_DIRS} " IPA Libraries")
endif(USE_IPA)

message("Selected directories: " ${SELECTED_DIRS})
