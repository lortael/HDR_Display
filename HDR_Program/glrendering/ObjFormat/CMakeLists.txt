set(OBJFORMAT_SRCS
   ${CMAKE_CURRENT_SOURCE_DIR}/ObjFormat.cpp   
   ${CMAKE_CURRENT_SOURCE_DIR}/ObjFormat.h
   ${CMAKE_CURRENT_SOURCE_DIR}/ObjUtil.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/ObjUtil.h
)

add_library(objformat ${OBJFORMAT_SRCS})
