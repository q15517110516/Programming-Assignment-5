# Makefile for UD CISC user-level thread library
test=T1
all:${test}

CC = gcc
CFLAGS = -g

LIBOBJS = t_lib.o 

# specify the executable 


# specify the source files

LIBSRCS = t_lib.c

TSTSRCS = ${test}.c

# ar creates the static thread library

t_lib.a: ${LIBOBJS} Makefile
	ar rcs t_lib.a ${LIBOBJS}

# here, we specify how each file should be compiled, what
# files they depend on, etc.

t_lib.o: t_lib.c t_lib.h Makefile
	${CC} ${CFLAGS} -c t_lib.c

${test}.o: ${test}.c ud_thread.h Makefile
	${CC} ${CFLAGS} -c ${test}.c

${test}: ${test}.o t_lib.a Makefile
	${CC} ${CFLAGS} ${test}.o t_lib.a -o ${test}

clean:
	rm -f t_lib.a ${LIBOBJS} *.o ${test}
