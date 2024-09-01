CFLAGS = -std=c99 -Wall -Wextra -Wpedantic -Werror -Os
CC     = cc

SOURCES = main.c buffer.c view.c wav.c util.c
OBJECTS = ${SOURCES:.c=.o}
BINARY  = audio

all: ${BINARY}

${BINARY}: ${OBJECTS}
	${CC} -o $@ $^

%.o: %.c
	${CC} ${CFLAGS} -c -o $@ $^

clean:
	rm ${BINARY} *.o
