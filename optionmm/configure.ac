dnl
dnl $Id: configure.ac,v 1.10 2004/01/13 18:09:24 cholm Exp $ 
dnl  
dnl  Copyright (C) 2002 Christian Holm Christensen <cholm@nbi.dk> 
dnl
dnl  This library is free software; you can redistribute it and/or 
dnl  modify it under the terms of the GNU Lesser General Public License 
dnl  as published by the Free Software Foundation; either version 2.1 
dnl  of the License, or (at your option) any later version. 
dnl
dnl  This library is distributed in the hope that it will be useful, 
dnl  but WITHOUT ANY WARRANTY; without even the implied warranty of 
dnl  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
dnl  Lesser General Public License for more details. 
dnl 
dnl  You should have received a copy of the GNU Lesser General Public 
dnl  License along with this library; if not, write to the Free 
dnl  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
dnl  02111-1307 USA 
dnl
AC_DEFUN(AC_DEBUG, 
[
  AC_REQUIRE([AC_PROG_CC])
  AC_REQUIRE([AC_PROG_CXX])
  AC_MSG_CHECKING(wether to make debug objects)
  AC_ARG_ENABLE(debug, 
    [  --enable-debug          Enable debugging symbols in objects], 
    user_debug=$enableval, user_debug=yes )
  if test "x$user_debug" = "xno" || test "x$ac_cv_prog_cc_g" = "xno" ; then 
    CFLAGS=`echo $CFLAGS | sed 's,-g,,'`
    CXXFLAGS=`echo $CXXFLAGS | sed 's,-g,,'`
  fi
  AC_MSG_RESULT($user_debug 'CFLAGS=$CFLAGS')
])

AC_DEFUN(AC_OPTIMIZATION, [
  AC_REQUIRE([AC_PROG_CC])
  AC_REQUIRE([AC_PROG_CXX])
        
  AC_ARG_ENABLE(optimization, 
    [  --enable-optimization   Enable optimization of objects],
      user_optim=$enableval, user_optim=yes )

  AC_MSG_CHECKING(for optimiztion level) 
    
  if test "x$user_optim" = "xno" ; then 
    CFLAGS=`echo $CFLAGS | sed 's,-O2,,'`
    CXXFLAGS=`echo $CXXFLAGS | sed 's,-O2,,'`
  elif test "x$user_optim" = "xyes" ; then 
    :
  else 
    CFLAGS=`echo $CFLAGS | sed "s,-O2,-O$user_optim,"`
    CXXFLAGS=`echo $CXXFLAGS | sed "s,-O2,-O$user_optim,"`
  fi
  AC_MSG_RESULT($user_optim 'CFLAGS=$CFLAGS')
])

AC_INIT(Option--, 2.2, cholm@nbi.dk, optionmm)
AC_PREREQ(2.53)
AC_COPYRIGHT(GNU Lesser General Public License)
AC_REVISION($Revision: 1.10 $)
AC_CONFIG_AUX_DIR(config)

AM_INIT_AUTOMAKE([$PACKAGE_TARNAME], [$PACKAGE_VERSION])
AM_CONFIG_HEADER(config/config.hh)

AC_PROG_CC
AC_PROG_CXX

dnl AC_LIBTOOL_DLOPEN
dnl AC_LIBTOOL_WIN32_DLL
dnl AC_DISABLE_SHARED
dnl AC_DISABLE_STATIC
dnl AC_PROG_LIBTOOL

AC_DEBUG
AC_OPTIMIZATION

AC_PATH_PROG(PERL, perl)
AC_PATH_PROG(DOXYGEN, doxygen)
AM_CONDITIONAL(HAVE_DOXYGEN, test ! "x$DOXYGEN" = "x")

AC_PATH_PROG(DOT, dot)
if ! test "x$DOT" = "x" ; then
   HAVE_DOT=YES
   DOT_PATH=`dirname $DOT`
fi
AC_SUBST([DOT_PATH])
AC_SUBST([HAVE_DOT])

dnl For test suite 
AC_CONFIG_TESTDIR([tests])
AC_CONFIG_FILES([tests/Makefile tests/package.m4])

AC_CONFIG_FILES([Makefile 
		 optionmm/Makefile 
		 support/Makefile
		 support/optionmm-config 
		 doc/Makefile
		 doc/doxyconfig
		 debian/Makefile
		 ide/Makefile])
AC_OUTPUT

dnl
dnl EOF
dnl 
