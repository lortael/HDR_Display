set(EXTERN_SRCS
   ${SOURCE}
   ${CMAKE_CURRENT_SOURCE_DIR}/rgbe.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/lodepng.cpp
   ${HEADERS}
   ${CMAKE_CURRENT_SOURCE_DIR}/rgbe.h
   ${CMAKE_CURRENT_SOURCE_DIR}/lodepng.h
)

add_library(extern ${EXTERN_SRCS})
