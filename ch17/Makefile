include ../Make.defines

PROGS =	msguds sendmsg 

all:	${PROGS}

%:	%.c 
	${CC} ${CFLAGS} $@.c -o $@  ${LIBS}

clean:
	rm -f ${PROGS} ${CLEANFILES}
