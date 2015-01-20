#
# $Id: Makefile.am,v 1.3 2003/06/22 00:07:06 cholm Exp $ 
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

EXTRA_DIST		= optionmm.dsw liboptionmm.dsp tryit.dsp demo.dsp \
			  liboptionmm.dev demo.dev tryit.dev cl
CLEANFILES		= *~ *.dep *.mak *.plg *.ncb *.opt Makefile.win \
			  *.a *.exe *.layout *.dll *.def
noinst_SCRIPTS		= cl

clean-local:
	rm -rf .debug .release build
#
# EOF
#
