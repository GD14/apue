include ../Make.defines 

all:    ${LIB_OBJS}
	ar rv ${LIBRONG_NAME} $?
	${RANLIB} ${LIBRONG_NAME}
clean:
	rm -f ${PROGS} ${CLEANFILES}
