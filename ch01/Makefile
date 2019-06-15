include ../Make.defines

PROGS = dirent copy

all:	${PROGS}

%:	%.c 
	${CC} ${CFLAGS} $@.c -o $@  ${LIBS}

clead:
	rm -f ${PROGS} ${CLEANFILES}
