#
# $Id: Makefile.am,v 1.8 2003/06/22 00:07:06 cholm Exp $
#
#   General C++ parser and lexer
#   Copyright (C) 2002	Christian Holm Christensen <cholm@nbi.dk>
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
#
EXTRA_DIST		= header.html footer.html style.css doxyconfig.in \
			  mainpage.cc examples.cc lgpl.cc fdl.cc \
			  favicon.png logo.png
CLEANFILES		= *~ 
if HAVE_DOXYGEN
HTML			= html/index.html doxyconfig.in
else 
HTML			=
endif

all-local:$(HTML) 

clean-local:
	rm -rf *~ html latex man doxyconfig $(PACKAGE).tags .xvpics

html/index.html $(PACKAGE).tags: doxyconfig header.html footer.html style.css \
				 mainpage.cc examples.cc lgpl.cc fdl.cc
	$(DOXYGEN) $<  
	if test -f logo.png ; then cp logo.png html ; fi
	if test -f favicon.png ; then cp favicon.png html ; fi

tar-ball:$(HTML)
	if test -f html/index.html ; then \
	  mv html $(PACKAGE) ;  \
	  tar -czvf ../$(PACKAGE)-$(VERSION)-doc.tar.gz $(PACKAGE) ; \
	  mv $(PACKAGE) html ; fi 


#
# EOF
#
