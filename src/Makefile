BIN=ark
CC=ark.c
LIBS=-ljansson -lcurl
FLAGS=-Wall -Wextra


all:
	gcc ${CC} -o ${BIN} ${LIBS} ${FLAGS}
	gcc ${CC} -o ${BIN}-debug ${LIBS} ${FLAGS} -D ARK_DEBUG -ggdb
