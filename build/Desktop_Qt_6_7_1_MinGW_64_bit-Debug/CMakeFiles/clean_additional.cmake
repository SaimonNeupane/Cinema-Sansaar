# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Cinema-Sansaar_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Cinema-Sansaar_autogen.dir\\ParseCache.txt"
  "Cinema-Sansaar_autogen"
  )
endif()
