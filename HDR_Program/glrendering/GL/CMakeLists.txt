set(GL_SRCS
#   ${CMAKE_CURRENT_SOURCE_DIR}/GlRender.cpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/GlRender.h
   ${CMAKE_CURRENT_SOURCE_DIR}/glcorearb.h
)

add_library(glcore ${GL_SRCS})
