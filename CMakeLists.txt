# --------------------------------------------------------------------------
# $Revision$
# $Date$
# --------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.0)
project (Knapsack)

include_directories ("${PROJECT_SOURCE_DIR}")

# Optionen für Doxygen
include(CMakeDoxygen.txt)

enable_testing()

# C++11-Support im Intel-Compiler aktivieren
if(UNIX)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif(UNIX)

# Für Visual Studio (ein "multi-target IDE" muss die folgende Variable verändert werden
set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "Nur Release" FORCE)

# Microsoft Visual Studio dazu bringen cmath wie im Standard zu verwenden und anderes
# das wir Microsoft verdanken ...
if(MSVC)
        add_definitions(-D_USE_MATH_DEFINES)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)      
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /NODEFAULTLIB:LIBCMT.lib" )
endif()

# Hier kann man einschalten ob Debug-Informationen mit generiert werden
option(AddDebugBuild "EnableDebugging" OFF)
if (AddDebugBuild)
	if(CMAKE_CONFIGURATION_TYPES)
		list(APPEND CMAKE_CONFIGURATION_TYPES Debug)
		list(REMOVE_DUPLICATES CMAKE_CONFIGURATION_TYPES)
		set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING "Add the configurations that we need" FORCE)
	endif(CMAKE_CONFIGURATION_TYPES)
endif(AddDebugBuild)

# Für Makefiles und ordentliche IDEs
SET(CMAKE_BUILD_TYPE Release CACHE STRING "Nur Release" Force)

# XCode arbeitet scheinbar nicht mit relativen Pfadangaben
if(NOT APPLE) 
    # Use relative paths
    set(CMAKE_USE_RELATIVE_PATHS TRUE CACHE STRING "Relative Pfade" FORCE)
endif(NOT APPLE)

# ------------------------------------------------------------------
# Ausführbare Programme
add_library (knapsack
	main/KnapSackSolver.h main/KnapSackSolver.cp
	main/KnapSack.h main/KnapSack.cpp
	main/algorithms/BruteForceSolver.h main/algorithms/BruteForceSolver.cpp
	main/algorithms/NemhauserUllmannSolver.h main/algorithms/NemhauserUllmannSolver.cpp
	main/algorithms/FeasibleBruteForceSolver.h main/algorithms/FeasibleBruteForceSolver.cpp
	util/GetWalltime.h util/GetWalltime.cpp
	util/io/KnapSackReader.h util/io/KnapSackReader.cpp
	util/io/KnapSackWriter.h util/io/KnapSackWriter.cpp
	util/StringUtils.h util/StringUtils.cpp
	util/MyMath.h util/MyMath.cpp
)

add_executable (knapsackStarter main/Main.cpp)
target_link_libraries (knapsackStarter knapsack)

# Tests
add_executable (readerTest  test/ReaderTest.cpp test/TestData.h)
target_link_libraries (readerTest knapsack)
add_test (NAME readerTest COMMAND readerTest)

add_executable (writerTest  test/WriterTest.cpp util/TestUtils.h)
target_link_libraries (writerTest knapsack)
add_test (NAME writerTest COMMAND writerTest)

add_executable (knapSackSolverTest  test/KnapSackSolverTest.cpp util/TestUtils.h)
target_link_libraries (knapSackSolverTest knapsack)
add_test (NAME knapSackSolverTest COMMAND knapSackSolverTest)

add_executable (bruteForceSolverTest  test/BruteForceSolverTest.cpp util/TestUtils.h)
target_link_libraries (bruteForceSolverTest knapsack)
add_test (NAME bruteForceSolverTest COMMAND bruteForceSolverTest)
