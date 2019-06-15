include ../Make.defines

PROGS = keep_alive

all:	${PROGS}

%:	%.c 
	${CC} ${CFLAGS} $@.c -o $@  ${LIBS}

clean:
	rm -f ${PROGS} ${CLEANFILES}
