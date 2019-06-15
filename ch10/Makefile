include ../Make.defines

PROGS = sigusr

all:	${PROGS}

%:	%.c 
	${CC} ${CFLAGS} $@.c -o $@  ${LIBS}

clean:
	rm -f ${PROGS} ${CLEANFILES}
