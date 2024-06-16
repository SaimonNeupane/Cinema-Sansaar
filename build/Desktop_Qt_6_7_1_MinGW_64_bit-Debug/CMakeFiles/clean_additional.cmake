# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Snasaar-Cinema_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Snasaar-Cinema_autogen.dir\\ParseCache.txt"
  "Snasaar-Cinema_autogen"
  )
endif()
