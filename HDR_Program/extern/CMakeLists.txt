set(EXTERN_SRCS
   ${CMAKE_CURRENT_SOURCE_DIR}/rgbe.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/lodepng.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/rgbe.h
   ${CMAKE_CURRENT_SOURCE_DIR}/lodepng.h
)

add_library(extern ${EXTERN_SRCS})
