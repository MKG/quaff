################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################
cmake_minimum_required(VERSION 2.6)

################################################################################
# Project quaff
################################################################################
project(nt2)

SET(QUAFF_VERSION_NUMBER "2.0.0")
SET(QUAFF_VERSION "${QUAFF_VERSION_NUMBER}")

################################################################################
# Global Options
################################################################################
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

SET(INCLUDE_INSTALL_DIR
    "${CMAKE_INSTALL_PREFIX}/include/quaff"
    CACHE PATH
    "The directory where we install the header files"
    FORCE)

################################################################################
# Find module specific informations
################################################################################
INCLUDE(quaff.boost)
INCLUDE(quaff.mpi)
INCLUDE(quaff.openmp)
INCLUDE(quaff.pthread)

################################################################################
# Generate bootstrap.hpp
################################################################################
CONFIGURE_FILE( ${PROJECT_SOURCE_DIR}/cmake/bootstrap.hpp.cmake
                ${PROJECT_BINARY_DIR}/include/quaff/sdk/bootstrap.hpp
              )

################################################################################
# Build libquaff
################################################################################
FILE( GLOB_RECURSE QUAFF_SOURCES
      ${PROJECT_SOURCE_DIR}/src/*
    )

SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE})
INCLUDE_DIRECTORIES( ${PROJECT_BINARY_DIR}/include)
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/include)

ADD_LIBRARY(quaff SHARED ${QUAFF_SOURCES})
SET_TARGET_PROPERTIES(quaff PROPERTIES VERSION 2.0.0 SOVERSION 2)

################################################################################
# Install libquaff
################################################################################
INSTALL( DIRECTORY ${PROJECT_SOURCE_DIR}/include/
         DESTINATION ${CMAKE_INSTALL_PREFIX}/include
         FILES_MATCHING
         PATTERN "*.hpp"
       )

INSTALL( DIRECTORY ${PROJECT_BINARY_DIR}/include/
         DESTINATION ${CMAKE_INSTALL_PREFIX}/include
         FILES_MATCHING
         PATTERN "*.hpp"
       )

INSTALL( TARGETS quaff
	      LIBRARY DESTINATION lib/
	      ARCHIVE DESTINATION lib/)

################################################################################
# Add Unit Tests
################################################################################
ENABLE_TESTING()
ADD_CUSTOM_TARGET(unit)
#ADD_SUBDIRECTORY(unit EXCLUDE_FROM_ALL)
