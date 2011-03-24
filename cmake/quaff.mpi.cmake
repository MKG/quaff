################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Find MPI
################################################################################

INCLUDE(FindMPI)
IF(MPI_FOUND)
SET(QUAFF_HAS_MPI_SUPPORT 1)
ELSE(MPI_FOUND)
SET(QUAFF_HAS_MPI_SUPPORT 0)
ENDIF(MPI_FOUND)

