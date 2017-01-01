PROJECT( XPlanePositionProviderPlugin )

INCLUDE_DIRECTORIES(
 ${CMAKE_CURRENT_SOURCE_DIR}
 ${CMAKE_CURRENT_BINARY_DIR}
)

set( xplane_SRCS XPlanePositionProviderPlugin.cpp )
set( XPlanePositionProviderPlugin_LIBS )

marble_add_plugin( XPlanePositionProviderPlugin ${xplane_SRCS} )
