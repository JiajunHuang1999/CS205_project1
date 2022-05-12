EXECS = 8_puzzle
COMPILE ?= g++ -std=c++11
CFLAGS ?= -O3 


all: ${EXECS}

8_puzzle: main.cpp
	${COMPILE} ${CFLAGS} -o 8_puzzle main.cpp

clean: 
	rm -f ${EXECS} 