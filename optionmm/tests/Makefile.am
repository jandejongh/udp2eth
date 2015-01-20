#
# $Id: Makefile.am,v 1.5 2003/12/18 11:15:12 cholm Exp $ 
#  
#  Copyright (C) 2002 Christian Holm Christensen <cholm@nbi.dk> 
#
#  This library is free software; you can redistribute it and/or 
#  modify it under the terms of the GNU Lesser General Public License 
#  as published by the Free Software Foundation; either version 2.1 
#  of the License, or (at your option) any later version. 
#
#  This library is distributed in the hope that it will be useful, 
#  but WITHOUT ANY WARRANTY; without even the implied warranty of 
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
#  Lesser General Public License for more details. 
# 
#  You should have received a copy of the GNU Lesser General Public 
#  License along with this library; if not, write to the Free 
#  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
#  02111-1307 USA 
#
EXTRA_DIST		= testsuite.at testsuite $(srcdir)/package.m4
TESTSUITE		= $(srcdir)/testsuite
AUTOM4TE		= autom4te
AUTOTEST		= $(AUTOM4TE) --language=autotest
AM_CPPFLAGS		= -I$(top_srcdir)
CLEANFILES		= testsuite.log atconfig *~ 
noinst_PROGRAMS		= tryit demo
tryit_SOURCES		= tryit.cc
demo_SOURCES		= demo.cc


check-local: $(TESTSUITE) # atlocal 
	$(SHELL) $(TESTSUITE) AUTOTEST_PATH=tests

clean-local:
	rm -rf testsuite.dir 

$(TESTSUITE):	$(srcdir)/testsuite.at $(srcdir)/package.m4 
	$(AUTOTEST) -I $(srcdir) $@.at -o $@.tmp
	mv $@.tmp $@

#
# EOF
#
