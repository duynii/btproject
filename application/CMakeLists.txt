SET( PROJECT "application" )
SET( TARGET_NAME btproject_${PROJECT} )

FILE( GLOB source   ${SOURCE_CODE_BASE_DIR}/${PROJECT}/*.cpp)
FILE( GLOB includes ${SOURCE_CODE_BASE_DIR}/${PROJECT}/*.h)

SOURCE_GROUP( ${TARGET_NAME} FILES ${source} ${includes} )

ADD_LIBRARY( ${TARGET_NAME} ${source} ${includes} )
SET_TARGET_PROPERTIES( ${TARGET_NAME} PROPERTIES ${btproject_LIBRARY_PROPERTIES} )
TARGET_LINK_LIBRARIES( ${TARGET_NAME} ${btproject_ALL_EXTERNAL_LIBRARIES} )
#TARGET_LINK_LIBRARIES( ${TARGET_NAME} ${btproject_ALL_EXTERNAL_LIBRARIES} btproject_base btproject_string )

INSTALL( FILES ${includes} DESTINATION ${btproject_INSTALL_INCLUDE_DIR}/${PROJECT} )
INSTALL(
    TARGETS ${TARGET_NAME}
    RUNTIME DESTINATION ${btproject_INSTALL_BIN_DIR} COMPONENT Runtime     # .exe, .dll
    LIBRARY DESTINATION ${btproject_INSTALL_LIB_DIR} COMPONENT Runtime     # .so, mod.dll
    ARCHIVE DESTINATION ${btproject_INSTALL_LIB_DIR} COMPONENT Development # .a, .lib
)

if( btproject_BUILD_APPLICATIONS )
    add_subdirectory( applications )
endif( btproject_BUILD_APPLICATIONS )

IF( btproject_BUILD_TESTS )
    ADD_SUBDIRECTORY( test )
ENDIF( btproject_BUILD_TESTS )
