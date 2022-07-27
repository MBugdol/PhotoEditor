# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\PhotoEditor_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\PhotoEditor_autogen.dir\\ParseCache.txt"
  "PhotoEditor_autogen"
  )
endif()
