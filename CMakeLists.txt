
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
        optimized btproject_application
        debug btproject_base-d
        optimized btproject_base )


IF(UNIX AND NOT QNXNTO AND NOT APPLE)
    SET( btproject_ALL_EXTERNAL_LIBRARIES rt pthread )
ENDIF(UNIX AND NOT QNXNTO AND NOT APPLE)

SET( btproject_ALL_EXTERNAL_LIBRARIES ${Boost_LIBRARIES} ${btproject_ALL_EXTERNAL_LIBRARIES} )

SET( btproject_ALL_LIBRARIES ${btproject_ALL_LIBRARIES} ${btproject_ALL_LIBRARIES} ${btproject_ALL_EXTERNAL_LIBRARIES} ) # as gcc parses library list only once
SET( btproject_EXTERNAL_INCLUDES ${Boost_INCLUDE_DIRS} )


# ADD_CUSTOM_TARGET(uninstall COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
# 
# FILE( GLOB btproject_PACKAGE_CMAKEFILES ${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles/*.cmake )
# 
# INCLUDE( ${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles/generate_${PROJECT_NAME}_config.cmake )
# 
# CONFIGURE_FILE( ${PROJECT_SOURCE_DIR}/CMakeFiles/use_${PROJECT_NAME}.cmake.in
#                 ${PROJECT_BINARY_DIR}/CMakeFiles/use_${PROJECT_NAME}.cmake COPYONLY IMMEDIATE )
# 
# SET( btproject_PACKAGE_CMAKEFILES ${btproject_PACKAGE_CMAKEFILES} ${PROJECT_BINARY_DIR}/CMakeFiles/use_${PROJECT_NAME}.cmake )
# INSTALL( FILES ${btproject_PACKAGE_CMAKEFILES}
#          DESTINATION ${btproject_INSTALL_PACKAGE_DIR} )

#-----------------------------------------------------------------------------
# add sources

ADD_SUBDIRECTORY( application )
#ADD_SUBDIRECTORY( base )


#in future, may need to add third party dlls somehow, if they are linked as dlls. Not needed for statically linking to boost.
# #if we set them up to install to bin they might be packaged through, e.g. roughly (using GLOB):
# #install(FILES "${Boost_LIBRARY_DIRS}/*.dll" DESTINATION bin )
# 
# #the following set up optional parameters for cpack
# SET(CPACK_PACKAGE_NAME "comma")
# SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Command line utilities to manipulate various structured and unstructured data from offline or real time data.")
# SET(CPACK_PACKAGE_VENDOR "Australian Centre for Field Robotics")
# SET(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/COPYING")
# SET(CPACK_PACKAGE_VERSION_MAJOR "1")
# SET(CPACK_PACKAGE_VERSION_MINOR ${COMMITDATE})
# SET(CPACK_PACKAGE_VERSION_PATCH ${COMMITHASH})
# SET(CPACK_PACKAGE_CONTACT "t.teo@acfr.usyd.edu.au")
# 
# # If the user builds shared, make sure that the RPM package (that might be generated) runs ldconfig when it's installed.
# IF( BUILD_SHARED_LIBS )
# 	SET(CPACK_RPM_SPEC_MORE_DEFINE "%posttrans -p /sbin/ldconfig")
# ENDIF( BUILD_SHARED_LIBS )


# #this line finds the appropriate Visual Studio DLLS in windows. Maybe it would find other dlls if a different build tool were used. Probably should be windows only.
# INCLUDE( InstallRequiredSystemLibraries )
# 
# #this line does all the work. Actually, even if this is the only line, you get all but the dlls...
# INCLUDE( CPack )


