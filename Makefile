CC = g++
BIN = chem
NEC = -std=c++14 -ftrapv
OOPTS = -Ofast -mtune=native -fno-rtti -DNDEBUG -s -fno-exceptions \
	-floop-interchange -ftree-loop-distribution -floop-strip-mine \
	-floop-block -flto=8 -ftree-vectorize

all:
	${CC} ${NEC} ${OOPTS} chem.cpp parser.cpp -o ${BIN}

clean:
	rm -f ${BIN}
