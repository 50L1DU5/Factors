CC=clang
FLAGS=-O2 -Wall -Wextra -pedantic -lm
EXEC=factorizor

all: ${EXEC}

factorizor: factorizor.c
	${CC} ${FLAGS} -o $@ $<
clean:
	rm ${EXEC}
