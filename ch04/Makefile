include ../Make.defines

PROGS =file_type access mask chmod unlink futimens chdir getcwd

all:	${PROGS}

%:	%.c 
	${CC} ${CFLAGS} $@.c -o $@  ${LIBS}

clean:
	rm -f ${PROGS} ${CLEANFILES}
