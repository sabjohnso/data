#
# ... Build script for data
#

cmake_minimum_required( VERSION 3.7 )

project( DATA )
set( DATA_MAJOR 0)
set( DATA_MINOR 1)
set( DATA_UPDATE 0)
set( DATA_VERSION data-${DATA_MAJOR}.${DATA_MINOR} )
set( DATA_VERSION_UPDATE ${DATA_VERSION}.${DATA_UPDATE} )

option( BUILD_DATA_TESTING  "Build the data  tests" ON )
option( BUILD_DATA_DOCUMENTATION "Build the data documentation" ON )

include_directories( 
  ${DATA_SOURCE_DIR}
  ${DATA_BINARY_DIR} )

if( NOT DATA_INSTALL_INCLUDE_DIR)
  set( DATA_INSTALL_INCLUDE_DIR include/data
    CACHE PATH "Path for installation of header files" )
endif( NOT DATA_INSTALL_INCLUDE_DIR)

add_subdirectory( data )



#
# ... Testing 
#
if( BUILD_DATA_TESTING )
  enable_testing()
  add_subdirectory( data_testing )
endif( BUILD_DATA_TESTING )



#
# ... Documentation
#
if( BUILD_DATA_DOCUMENTATION )

  configure_file( Doxyfile.in Doxyfile )

  if( NOT DATA_INSTALL_DOC_DIR)
    set( DATA_INSTALL_DOC_DIR share/doc/${DATA_VERSION}
      CACHE PATH "Path for installation of documentation files" )
  endif( NOT DATA_INSTALL_DOC_DIR)

  if( NOT DATA_INTALL_MAN_DIR)
    set( DATA_INTALL_MAN_DIR include/data
      CACHE PATH "Path for installation of man files" )
  endif( NOT DATA_INTALL_MAN_DIR)

  find_package( Doxygen REQUIRED )

  add_custom_command(
    OUTPUT ${DATA_BINARY_DIR}/doxygen.log
    COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile > doxygen.log
    MAIN_DEPENDENCY Doxyfile
    DEPENDS ${DATA_BINARY_DIR}/data
    WORKING_DIRECTORY ${DATA_BINARY_DIR} )

  add_custom_target(
    data_documentation ALL
    DEPENDS ${DATA_BINARY_DIR}/doxygen.log )

  install( DIRECTORY ${DATA_BINARY_DIR}/doc/html DESTINATION ${DATA_INSTALL_DOC_DIR} )
  install( DIRECTORY ${DATA_BINARY_DIR}/doc/man DESTINATION ${DATA_INTALL_MAN_DIR} )
endif( BUILD_DATA_DOCUMENTATION )

# end of build definition for data
