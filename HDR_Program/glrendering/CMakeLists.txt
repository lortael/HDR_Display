set(GLRENDERING_SRCS
#   ${CMAKE_CURRENT_SOURCE_DIR}/GlRender.cpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/GlRender.h
   ${CMAKE_CURRENT_SOURCE_DIR}/RenderingWidget.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/RenderingWidget.h
   ${CMAKE_CURRENT_SOURCE_DIR}/Shader.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/Shader.h
   ${CMAKE_CURRENT_SOURCE_DIR}/Mesh.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/Mesh.h
   ${CMAKE_CURRENT_SOURCE_DIR}/Camera.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/Camera.h
   ${CMAKE_CURRENT_SOURCE_DIR}/Object.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/Object.h
   ${CMAKE_CURRENT_SOURCE_DIR}/OpenGL.h

   ${CMAKE_CURRENT_SOURCE_DIR}/ObjFormat/ObjFormat.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/ObjFormat/ObjFormat.h
   ${CMAKE_CURRENT_SOURCE_DIR}/ObjFormat/ObjUtil.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/ObjFormat/ObjUtil.h
)

#add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/ObjFormat )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/GL )

add_library(glrendering ${GLRENDERING_SRCS})
