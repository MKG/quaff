################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include/)
SET(SOURCES
    #environment.cpp
    seq.cpp
    pardo.cpp
    pipe.cpp
    )

################################################################################
# For each filename
################################################################################
FOREACH( SRC ${SOURCES})
  ##**************************************************************************
  ## Build the executable filename from the example source filename
  ##**************************************************************************
  STRING(REGEX REPLACE ".cpp" ".unit" EXECUTABLE "${SRC}")
  STRING(REGEX REPLACE ".cpp" "-unit" TEST       "${SRC}")

  ##**************************************************************************
  ## Add as a target
  ##**************************************************************************
  ADD_EXECUTABLE(${EXECUTABLE} ${SRC})
  TARGET_LINK_LIBRARIES(${EXECUTABLE} quaff)
  ADD_TEST(${TEST} ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE})
  ADD_DEPENDENCIES(unit ${EXECUTABLE})
ENDFOREACH()
