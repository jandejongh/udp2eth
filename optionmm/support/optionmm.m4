dnl -*- mode: Autoconf -*- 
dnl
dnl $Id: optionmm.m4,v 1.3 2003/12/18 16:24:18 cholm Exp $ 
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

dnl AM_PATH_OPTIONMM([MINIMUM-VERSION 
dnl                   [,ACTION-IF_FOUND 
dnl                    [, ACTION-IF-NOT-FOUND]])
AC_DEFUN(AM_PATH_OPTIONMM,
[
    AC_ARG_WITH(optionmm-prefix,
        [  --with-optonmm-prefix   Prefix where Option-- is installed],
        optionmm_prefix=$withval, optionmm_prefix="")

    if test "x${OPTIONMM_CONFIG+set}" != xset ; then 
        if test "x$optionmm_prefix" != "x" ; then 
	    OPTIONMM_CONFIG=$optionmm_prefix/bin/optionmm-config
	fi
    fi   
    AC_PATH_PROG(OPTIONMM_CONFIG, optionmm-config, no)
    optionmm_min_version=ifelse([$1], ,0.1,$1)
    
    AC_MSG_CHECKING(for Option-- version >= $optionmm_min_version)

    optionmm_found=no    
    if test "x$OPTIONMM_CONFIG" != "xno" ; then 
       OPTIONMM_CPPFLAGS=`$OPTIONMM_CONFIG --cppflags`
       
       optionmm_version=`$OPTIONMM_CONFIG -V` 
       optionmm_vers=`echo $optionmm_version | \
         awk 'BEGIN { FS = " "; } \
	   { printf "%d", ($''1 * 1000 + $''2) * 1000 + $''3;}'`
       optionmm_regu=`echo $optionmm_min_version | \
         awk 'BEGIN { FS = " "; } \
	   { printf "%d", ($''1 * 1000 + $''2) * 1000 + $''3;}'`
       if test $optionmm_vers -ge $optionmm_regu ; then 
            optionmm_found=yes
       fi
    fi
    AC_MSG_RESULT($optionmm_found - is $optionmm_version) 
   
    if test "x$optionmm_found" = "xyes" ; then 
        ifelse([$2], , :, [$2])
    else 
        ifelse([$3], , :, [$3])
    fi
    AC_SUBST(OPTIONMM_CPPFLAGS)
])

dnl
dnl EOF
dnl 
