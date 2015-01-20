#!/usr/bin/make -f
# -*- mode: makefile -*- 
#
# $Id: autogen.sh,v 1.4 2002/12/30 01:43:21 cholm Exp $
#
#   General C++ parser and lexer
#   Copyright (C) 2002  Christian Holm Christensen <cholm@nbi.dk>
#
#   This library is free software; you can redistribute it and/or
#   modify it under the terms of the GNU Lesser General Public License 
#   as published by the Free Software Foundation; either version 2 of 
#   the License, or (at your option) any later version.  
#
#   This library is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#   Lesser General Public License for more details. 
#
#   You should have received a copy of the GNU Lesser General Public
#   License along with this library; if not, write to the Free
#   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, 
#   MA 02111-1307  USA  
#
CXX		= g++
CC		= gcc
PREFIX		= $(HOME)/tmp
CONFFLAGS	= --prefix=$(PREFIX) --disable-optimization \
		  --with-ylmm-prefix=$(PREFIX)
PACKAGE		:= $(strip $(shell grep AC_INIT configure.ac |\
			sed 's/.*([^,]*,\([^,]*\),[^,]*,\(.*\)).*/\2/'))
VERSION		:= $(strip $(shell grep AC_INIT configure.ac |\
			sed 's/.*([^,]*,\([^,]*\),[^,]*,\(.*\)).*/\1/'))

all:	setup
	./configure $(CONFFLAGS) CXX=$(CXX) CC=$(CC) 

setup: 	ChangeLog
	libtoolize --automake
	aclocal 
	autoheader
	automake -a 
	autoconf 

make:	all
	$(MAKE) -f Makefile 

ChangeLog:
	rm -f $@
	touch $@
	rcs2log > $@

dists:	ChangeLog
	$(MAKE) dist
	$(MAKE) tar-ball -C doc 

show:
	@echo "$(PACKAGE) version $(VERSION)"
clean: 
	find . -name Makefile 		| xargs rm -f 
	find . -name Makefile.in 	| xargs rm -f 
	find . -name "*~" 		| xargs rm -f 
	find . -name core 		| xargs rm -f 
	find . -name .libs 		| xargs rm -rf 
	find . -name .deps 		| xargs rm -rf 
	find . -name "*.lo" 		| xargs rm -f 
	find . -name "*.o" 		| xargs rm -f 
	find . -name "*.la" 		| xargs rm -rf
	find . -name "*.log" 		| xargs rm -rf

	rm -f 	config/missing       	\
	  	config/mkinstalldirs 	\
	  	config/ltmain.sh     	\
	  	config/config.guess 	\
		config/config.sub 	\
		config/install-sh 	\
		config/ltconfig 	\
		config/config.hh 	\
		config/config.hh.in 	\
		config/stamp-h		\
		config/stamp-h.in	\
		config/stamp-h1		\
		config/depcomp

	rm -rf 	aclocal.m4 		\
		autom4te.cache		\
		config.cache 		\
		config.status  		\
		config.log 		\
		config.guess		\
		config.sub		\
		configure 		\
		INSTALL 		\
		ChangeLog		\
		configure-stamp		\
		build-stamp		\
		libtool			\
		.tm_project.cache

	rm -rf  support/optionmm-config

	rm -rf  doc/doxyconfig		\
		doc/html 		\
		doc/optionsmm.tags

	rm -rf	tests/autom4te.cache		\
		tests/package.m4		\
		tests/atconfig			\
		tests/atlocal			\
		tests/testsuite			\
		tests/testsuite.log		\
		tests/testsuite.dir		\
		tests/tryit			\
		tests/demo

	rm -rf  debian/liboptionmm1		\
		debian/liboptionmm-dev		\
		debian/liboptionmm-doc		\
		debian/tmp			\
		debian/*.debhelper		\
		debian/*.substvars		\
		debian/files


	rm -rf  $(PACKAGE)-*.tar.gz 

#
# EOF
#
