include ../Make.defines

PROGS = pipe mymore popen add drive_add

all:	${PROGS}

%:	%.c 
	${CC} ${CFLAGS} $@.c -o $@  ${LIBS}

clean:
	rm -f ${PROGS} ${CLEANFILES}
