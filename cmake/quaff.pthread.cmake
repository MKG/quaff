################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Find pthreads and set proper flags for quaff
################################################################################
FIND_PACKAGE(Threads)
IF(Threads_FOUND)
SET(QUAFF_HAS_THREADS_SUPPORT 1)
ELSE(Threads_FOUND)
SET(QUAFF_HAS_THREADS_SUPPORT 0)
ENDIF(Threads_FOUND)


