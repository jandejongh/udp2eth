PROG = udp2eth

PREFIX:=/usr/local

OPTIONMM:=./optionmm

CXX=g++
INSTALL_DIR:=install -d
INSTALL_BIN:=install

LDFLAGS += -Wl,-rpath -Wl,/usr/local/lib -L/usr/local/lib

.PHONY: ALL clean install

ALL: ${PROG}

clean:
	rm -f ${PROG} *.o
	
SOURCESCXXDEP:= udp2eth.cc

SOURCESCXXCMP:= udp2eth.cc

${PROG}: ${SOURCESCXXDEP}
	${CXX} -I. -I${OPTIONMM} -o $@ ${SOURCESCXXCMP} ${LDFLAGS}

install: ALL
	$(INSTALL_DIR) $(PREFIX)/bin
	$(INSTALL_BIN) udp2eth $(PREFIX)/bin
