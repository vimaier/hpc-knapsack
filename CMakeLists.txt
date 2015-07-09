# --------------------------------------------------------------------------
# $Revision$
# $Date$
# --------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.0)
project (Knapsack)

include_directories ("${PROJECT_SOURCE_DIR}")

# OpenMP
find_package ( OpenMP REQUIRED )
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")

# Optionen für Doxygen
include(CMakeDoxygen.txt)

enable_testing()

# C++11-Support im Intel-Compiler aktivieren
if(UNIX)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif(UNIX)

# Compiler Optimierung ausschalten
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

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

# Hier kann man einschalten ob Profiling-Informationen mit generiert werden
option(AddProfilingInformation "EnableProfiling" OFF)
if (AddProfilingInformation)
	set( CMAKE_CXX_FLAGS "-pg ${CMAKE_CXX_FLAGS}" )
	set( CMAKE_EXE_LINKER_FLAGS " -pg ${CMAKE_EXE_LINKER_FLAGS}" )
endif(AddProfilingInformation)

# Hiermit wird der Eclipse-Indexer auf C++11 aufgerüstet
option(AddCpp11EclipseSupport "EnableCpp11EclipseSupport" OFF)
if (AddCpp11EclipseSupport)
	set( CMAKE_CXX_COMPILER_ARG1 "-std=c++11 ${CMAKE_CXX_COMPILER_ARG1}" )
endif(AddCpp11EclipseSupport)

# Für Makefiles und ordentliche IDEs
SET(CMAKE_BUILD_TYPE Release CACHE STRING "Nur Release" Force)

# DebugBuild für Eclipse. Unter Eclipse ist es nicht moeglich Release und Debug builds zu haben.
option(EclipseDebugBuild "CreateEclipseDebugBuild" OFF)
if (EclipseDebugBuild)
	SET(CMAKE_BUILD_TYPE Debug)
endif(EclipseDebugBuild)

# XCode arbeitet scheinbar nicht mit relativen Pfadangaben
if(NOT APPLE) 
    # Use relative paths
    set(CMAKE_USE_RELATIVE_PATHS TRUE CACHE STRING "Relative Pfade" FORCE)
endif(NOT APPLE)

# Benötigte Dateien im Ordner 'res' nach build kopieren
file(COPY res DESTINATION ${CMAKE_BINARY_DIR})

# ------------------------------------------------------------------
# Ausführbare Programme
add_library (knapsack
	main/KnapSackSolver.h main/KnapSackSolver.cpp
	main/KnapSack.h main/KnapSack.cpp
	main/algorithms/BruteForceSolver.h main/algorithms/BruteForceSolver.cpp
	main/algorithms/NemhauserUllmannSolver.h main/algorithms/NemhauserUllmannSolver.cpp
	main/algorithms/NemhauserUllmannSolverRLP.h main/algorithms/NemhauserUllmannSolverRLP.cpp
	main/algorithms/NemhauserUllmannRLPParallelSolver.h main/algorithms/NemhauserUllmannRLPParallelSolver.cpp
	main/algorithms/NemhauserUllmannParallelSolver.h main/algorithms/NemhauserUllmannParallelSolver.cpp
	main/algorithms/DynamicProgrammingSolver.h main/algorithms/DynamicProgrammingSolver.cpp
	main/algorithms/DynamicProgrammingLowMemorySolver.h main/algorithms/DynamicProgrammingLowMemorySolver.cpp
	main/algorithms/DynamicProgrammingLowMemoryParallelSolver.h main/algorithms/DynamicProgrammingLowMemoryParallelSolver.cpp
	main/algorithms/DynamicProgrammingParallelSolver.h main/algorithms/DynamicProgrammingParallelSolver.cpp
	util/GetWalltime.h util/GetWalltime.cpp
	util/io/KnapSackReader.h util/io/KnapSackReader.cpp
	util/io/KnapSackWriter.h util/io/KnapSackWriter.cpp
	util/io/StatisticsWriter.h util/io/StatisticsWriter.cpp
	util/StringUtils.h
	util/MyMath.h util/MyMath.cpp
)

add_executable (knapsackStarter main/Main.cpp)
target_link_libraries (knapsackStarter knapsack)

# Tests
add_executable (readerTest  test/ReaderTest.cpp test/TestData.h)
target_link_libraries (readerTest knapsack)
add_test (NAME readerTest COMMAND readerTest)

add_executable (writerTest  test/WriterTest.cpp util/TestUtils.h test/TestData.h)
target_link_libraries (writerTest knapsack)
add_test (NAME writerTest COMMAND writerTest)

add_executable (knapSackSolverTest  test/KnapSackSolverTest.cpp util/TestUtils.h test/TestData.h)
target_link_libraries (knapSackSolverTest knapsack)
add_test (NAME knapSackSolverTest COMMAND knapSackSolverTest)

add_executable (bruteForceSolverTest  test/BruteForceSolverTest.cpp util/TestUtils.h test/TestData.h)
target_link_libraries (bruteForceSolverTest knapsack)
add_test (NAME bruteForceSolverTest COMMAND bruteForceSolverTest)

add_executable (nemhauserUllmannSolverTest  test/NemhauserUllmannSolverTest.cpp util/TestUtils.h test/TestData.h)
target_link_libraries (nemhauserUllmannSolverTest knapsack)
add_test (NAME nemhauserUllmannSolverTest COMMAND nemhauserUllmannSolverTest)

add_executable (nemhauserUllmannParallelSolverTest  test/NemhauserUllmannParallelSolverTest.cpp util/TestUtils.h test/TestData.h)
target_link_libraries (nemhauserUllmannParallelSolverTest knapsack)
add_test (NAME nemhauserUllmannParallelSolverTest COMMAND nemhauserUllmannParallelSolverTest)

add_executable (nemhauserUllmannSolverRLPTest  test/NemhauserUllmannSolverRLPTest.cpp util/TestUtils.h test/TestData.h)
target_link_libraries (nemhauserUllmannSolverRLPTest knapsack)
add_test (NAME nemhauserUllmannSolverRLPTest COMMAND nemhauserUllmannSolverRLPTest)

add_executable (nemhauserUllmannRLPParallelSolverTest  test/NemhauserUllmannRLPParallelSolverTest.cpp util/TestUtils.h test/TestData.h)
target_link_libraries (nemhauserUllmannRLPParallelSolverTest knapsack)
add_test (NAME nemhauserUllmannRLPParallelSolverTest COMMAND nemhauserUllmannRLPParallelSolverTest)

add_executable (dynamicProgrammingSolverTest  test/DynamicProgrammingSolverTest.cpp util/TestUtils.h test/TestData.h)
target_link_libraries (dynamicProgrammingSolverTest knapsack)
add_test (NAME dynamicProgrammingSolverTest COMMAND dynamicProgrammingSolverTest)

add_executable (dynamicProgrammingParallelSolverTest  test/DynamicProgrammingParallelSolverTest.cpp util/TestUtils.h test/TestData.h)
target_link_libraries (dynamicProgrammingParallelSolverTest knapsack)
add_test (NAME dynamicProgrammingParallelSolverTest COMMAND dynamicProgrammingParallelSolverTest)

add_executable (dynamicProgrammingLowMemorySolverTest  test/DynamicProgrammingLowMemorySolverTest.cpp util/TestUtils.h test/TestData.h)
target_link_libraries (dynamicProgrammingLowMemorySolverTest knapsack)
add_test (NAME dynamicProgrammingLowMemorySolverTest COMMAND dynamicProgrammingLowMemorySolverTest)

add_executable (dynamicProgrammingLowMemoryParallelSolverTest  test/DynamicProgrammingLowMemoryParallelSolverTest.cpp util/TestUtils.h test/TestData.h)
target_link_libraries (dynamicProgrammingLowMemoryParallelSolverTest knapsack)
add_test (NAME dynamicProgrammingLowMemoryParallelSolverTest COMMAND dynamicProgrammingLowMemoryParallelSolverTest)

