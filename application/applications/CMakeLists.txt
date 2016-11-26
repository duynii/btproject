FILE( GLOB source   *.cpp )
FILE( GLOB includes *.h )
SOURCE_GROUP( ${TARGET_NAME} FILES ${source} ${includes} )

ADD_EXECUTABLE( bt-app bt-app.cpp )
TARGET_LINK_LIBRARIES ( bt-app btproject_application ${btproject_ALL_EXTERNAL_LIBRARIES} )
INSTALL( TARGETS bt-app RUNTIME DESTINATION ${btproject_INSTALL_BIN_DIR} COMPONENT Runtime )
