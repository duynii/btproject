
PROJECT( "btproject" )

cmake_minimum_required(VERSION 2.6)


ENABLE_TESTING()

# ---------------------------------------------------------------------------
# set compiler and linker flags and variables

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

IF(WIN32)
  SET(CMAKE_CXX_WARNING_LEVEL 4)
  IF(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    STRING(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  ELSE(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  ENDIF(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
  ADD_DEFINITIONS(/wd4512)
  ADD_DEFINITIONS(/wd4127)
  ADD_DEFINITIONS(/wd4996)
  ADD_DEFINITIONS(/wd4800)
  ADD_DEFINITIONS(/wd4244)
  SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D \"NOMINMAX\"")
  ADD_DEFINITIONS(-D_USE_MATH_DEFINES)
  ADD_DEFINITIONS(-DWIN32_LEAN_AND_MEAN) #used to fix winsock redefinition error
ENDIF(WIN32)

IF( CMAKE_SIZEOF_VOID_P EQUAL 8 )
  SET( IS_64_BIT TRUE )
ELSE( CMAKE_SIZEOF_VOID_P EQUAL 8 )
  SET( IS_64_BIT FALSE )
ENDIF( CMAKE_SIZEOF_VOID_P EQUAL 8 )

option( USE_CXX11 "build with C++11 support" ON )
if( USE_CXX11 )
    if( UNIX )
        # A much better way to do this is with CXX_STANDARD but that requires CMake 3.1
        include( CheckCXXCompilerFlag )
        CHECK_CXX_COMPILER_FLAG( "-std=c++11" compiler_supports_cxx11 )
        CHECK_CXX_COMPILER_FLAG( "-std=c++0x" compiler_supports_cxx0x )
        if( compiler_supports_cxx11 )
            set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
        elseif( compiler_supports_cxx0x )
            set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x" )
        else()
            message( FATAL_ERROR "USE_CXX11 set to ON but ${CMAKE_CXX_COMPILER} has no C++11 support")
        endif()
    endif()
endif()

IF( WIN32 )
    # improve later
    #FIND_PATH( Eigen_INCLUDE_DIR NAMES Eigen/CMakeLists.txt PATHS $ENV{EIGEN_ROOT} )
    FIND_PATH( Eigen_INCLUDE_DIR NAMES signature_of_eigen3_matrix_library PATHS $ENV{EIGEN_ROOT} )
ELSEIF( APPLE )
    # actually the following line will probably work everywhere, not just APPLE (but have not tested on Windows yet)
    FIND_PATH( Eigen_INCLUDE_DIR NAMES signature_of_eigen3_matrix_library PATHS $ENV{EIGEN_ROOT} PATH_SUFFIXES eigen3 )
ELSE( WIN32 )
    #FIND_PATH( Eigen_INCLUDE_DIR Eigen/Core PATHS $ENV{EIGEN_ROOT} /usr/include/eigen3 /usr/local/include/eigen3 )
    FIND_PATH( Eigen_INCLUDE_DIR NAMES signature_of_eigen3_matrix_library PATHS $ENV{EIGEN_ROOT} /usr/include/eigen3 /usr/local/include/eigen3 )
ENDIF( WIN32 )
IF( NOT EXISTS ${Eigen_INCLUDE_DIR} )
    MESSAGE( "could not find Eigen - should be the path containing the Eigen 3 directory and /Eigen/Eigen, /Eigen/Core, etc..." )
ELSE( NOT EXISTS ${Eigen_INCLUDE_DIR} )
INCLUDE_DIRECTORIES( ${Eigen_INCLUDE_DIR} )
ENDIF( NOT EXISTS ${Eigen_INCLUDE_DIR} )


IF(CMAKE_BUILD_TOOL MATCHES "make")
  IF(NOT CMAKE_CXX_FLAGS MATCHES "-Wall")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
  ENDIF(NOT CMAKE_CXX_FLAGS MATCHES "-Wall")
  IF(NOT CMAKE_C_FLAGS MATCHES "-Wall")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
  ENDIF(NOT CMAKE_C_FLAGS MATCHES "-Wall")

  IF( IS_64_BIT )
    IF(NOT CMAKE_CXX_FLAGS MATCHES "-fPIC")
      SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
    ENDIF(NOT CMAKE_CXX_FLAGS MATCHES "-fPIC")
    IF(NOT CMAKE_C_FLAGS MATCHES "-fPIC")
      SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
    ENDIF(NOT CMAKE_C_FLAGS MATCHES "-fPIC")
  ENDIF( IS_64_BIT )

ENDIF(CMAKE_BUILD_TOOL MATCHES "make")

SET( SOURCE_CODE_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
SET( LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib )

SET( EXECUTABLE_OUTPUT_PATH
     ${PROJECT_BINARY_DIR}/bin CACHE PATH
     "Single output directory for building all executables." )

SET( btproject_LIBRARY_PROPERTIES ${btproject_LIBRARY_PROPERTIES} DEBUG_POSTFIX "-d" )

IF( NOT btproject_INSTALL_BIN_DIR )
  SET( btproject_INSTALL_BIN_DIR bin )
ENDIF( NOT btproject_INSTALL_BIN_DIR )

IF( NOT btproject_INSTALL_INCLUDE_DIR )
    SET( btproject_INSTALL_INCLUDE_DIR include/${PROJECT_NAME} )
ENDIF( NOT btproject_INSTALL_INCLUDE_DIR )

IF( NOT btproject_INSTALL_LIB_DIR)
  SET( btproject_INSTALL_LIB_DIR lib )
ENDIF( NOT btproject_INSTALL_LIB_DIR )

IF( NOT btproject_INSTALL_PACKAGE_DIR )
  SET( btproject_INSTALL_PACKAGE_DIR CMakeFiles )
ENDIF( NOT btproject_INSTALL_PACKAGE_DIR )

INCLUDE_DIRECTORIES( ${SOURCE_CODE_BASE_DIR}/../ )
INCLUDE_DIRECTORIES( ${btproject_INSTALL_INCLUDE_DIR}/../ )

OPTION( BUILD_TESTS "build unit tests" ON )
SET( btproject_BUILD_TESTS ${BUILD_TESTS} )

OPTION( BUILD_APPLICATIONS "build applications" ON )
SET( btproject_BUILD_APPLICATIONS ${BUILD_APPLICATIONS} )

SET(btproject_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})

IF( NOT BUILD_SHARED_LIBS )
    SET( Boost_USE_STATIC_LIBS ON )
ENDIF( NOT BUILD_SHARED_LIBS )

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIRS} )
LINK_DIRECTORIES( ${Boost_LIBRARY_DIRS} )

IF( btproject_BUILD_TESTS )

    # todo: maybe else clause is actually the right way to do things
    IF( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" OR ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
        FIND_PATH( GTest_SOURCE_DIR NAMES CMakeLists.txt HINTS /usr/src/gtest DOC "source code of gtest" )
        ADD_SUBDIRECTORY( ${GTest_SOURCE_DIR} gtest )
        INCLUDE_DIRECTORIES( src ${GTest_SOURCE_DIR}/include ${GTest_SOURCE_DIR} )
        SET( GTEST_BOTH_LIBRARIES gtest gtest_main )
    ELSE( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" OR ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
        FIND_PACKAGE( GTest )
        INCLUDE_DIRECTORIES( ${GTEST_INCLUDE_DIRS} )
    ENDIF( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" OR ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
	
#TT: Install tests to dir. This allows them to be packed by CPack.
SET ( btproject_CPP_TESTS_INSTALL_DIR bin CACHE PATH "Install directory for cpp unit tests" )
ENDIF( btproject_BUILD_TESTS )

# SET( comma_ALL_LIBRARIES
#         debug comma_application-d
#         optimized comma_application
#         debug comma_base-d
#         optimized comma_base
#         debug comma_csv-d
#         optimized comma_csv )

SET( btproject_ALL_LIBRARIES
        debug btproject_application-d
        optimized btproject_application )


IF(UNIX AND NOT QNXNTO AND NOT APPLE)
    SET( btproject_ALL_EXTERNAL_LIBRARIES rt pthread )
ENDIF(UNIX AND NOT QNXNTO AND NOT APPLE)

SET( btproject_ALL_EXTERNAL_LIBRARIES ${Boost_LIBRARIES} ${btproject_ALL_EXTERNAL_LIBRARIES} )

SET( btproject_ALL_LIBRARIES ${btproject_ALL_LIBRARIES} ${btproject_ALL_LIBRARIES} ${btproject_ALL_EXTERNAL_LIBRARIES} ) # as gcc parses library list only once
SET( btproject_EXTERNAL_INCLUDES ${Boost_INCLUDE_DIRS}  ${Eigen_INCLUDE_DIR} )


#-----------------------------------------------------------------------------
# add sources

ADD_SUBDIRECTORY( application )
#ADD_SUBDIRECTORY( base )
