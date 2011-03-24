################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Find OpenMP and set proper flags for quaff
################################################################################
FIND_PACKAGE(OpenMP)
IF(OPENMP_FOUND)
SET(QUAFF_HAS_OPENMP_SUPPORT 1)
ELSE(OPENMP_FOUND)
SET(QUAFF_HAS_THREADS_SUPPORT 0)
ENDIF(OPENMP_FOUND)
