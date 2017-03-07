# Try to find the GMP libraries:
# GMP_FOUND - System has GMP lib
# GMP_INCLUDE_DIR - The GMP include directory
# GMP_LIBRARIES - Libraries needed to use GMP

if (GMP_INCLUDE_DIR AND GMP_LIBRARIES)
	# Already in cache, be silent
	set(GMP_FIND_QUIETLY TRUE)
endif (GMP_INCLUDE_DIR AND GMP_LIBRARIES)

find_path(GMP_INCLUDE_DIR NAMES gmp.h)
find_library(GMP_LIBRARIES NAMES gmp)

if(GMP_INCLUDE_DIR AND GMP_LIBRARIES)
   set(GMP_FOUND TRUE)
endif(GMP_INCLUDE_DIR AND GMP_LIBRARIES)

if(GMP_FOUND)
	message(STATUS "Configured GMP: ${GMP_LIBRARIES}")
else(GMP_FOUND)
	message(STATUS "Could NOT find GMP")
endif(GMP_FOUND)

mark_as_advanced(GMP_INCLUDE_DIR GMP_LIBRARIES)
