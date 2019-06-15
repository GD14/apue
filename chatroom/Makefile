include ../Make.defines

PROGS =	server client 

all:	${PROGS}

%:	%.c 
	${CC} ${CFLAGS} $@.c -o $@  ${LIBS}

clead:
	rm -f ${PROGS} ${CLEANFILES}
