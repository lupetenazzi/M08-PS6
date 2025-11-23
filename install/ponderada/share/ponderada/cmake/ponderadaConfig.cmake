# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_ponderada_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED ponderada_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(ponderada_FOUND FALSE)
  elseif(NOT ponderada_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(ponderada_FOUND FALSE)
  endif()
  return()
endif()
set(_ponderada_CONFIG_INCLUDED TRUE)

# output package information
if(NOT ponderada_FIND_QUIETLY)
  message(STATUS "Found ponderada: 0.0.0 (${ponderada_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'ponderada' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ponderada_DEPRECATED_QUIET)
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(ponderada_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${ponderada_DIR}/${_extra}")
endforeach()
