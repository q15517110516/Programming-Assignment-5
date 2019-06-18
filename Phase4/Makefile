# Makefile for UD CISC user-level thread library

CC = gcc
CFLAGS = -g

LIBOBJS = t_lib.o 

TSTOBJS = T6.o T8.o T5.o philosophers.o 3test.o

# specify the executable 

EXECS = T6 T8 T5 philosophers 3test

# specify the source files

LIBSRCS = t_lib.c

TSTSRCS = T6.c T8.c T5.c philosophers.c 3test.c

# ar creates the static thread library

t_lib.a: ${LIBOBJS} Makefile
	ar rcs t_lib.a ${LIBOBJS}

# here, we specify how each file should be compiled, what
# files they depend on, etc.

t_lib.o: t_lib.c t_lib.h Makefile
	${CC} ${CFLAGS} -c t_lib.c

T8.o: T8.c ud_thread.h Makefile
	${CC} ${CFLAGS} -c T8.c
	
T8: T8.o t_lib.a Makefile
	${CC} ${CFLAGS} T8.o t_lib.a -o T8

T6.o: T6.c ud_thread.h Makefile
	${CC} ${CFLAGS} -c T6.c

T6: T6.o t_lib.a Makefile
	${CC} ${CFLAGS} T6.o t_lib.a -o T6
	
T5.o: T5.c ud_thread.h Makefile
	${CC} ${CFLAGS} -c T5.c
	
T5: T5.o t_lib.a Makefile
	${CC} ${CFLAGS} T5.o t_lib.a -o T5
	
philosophers.o: philosophers.c ud_thread.h Makefile
	${CC} ${CFLAGS} -c philosophers.c
	
philosophers: philosophers.o t_lib.a Makefile
	${CC} ${CFLAGS} philosophers.o t_lib.a -o philosophers
	
3test.o: 3test.c ud_thread.h Makefile
	${CC} ${CFLAGS} -c 3test.c
	
3test: 3test.o t_lib.a Makefile
	${CC} ${CFLAGS} 3test.o t_lib.a -o 3test

clean:
	rm -f t_lib.a ${EXECS} ${LIBOBJS} ${TSTOBJS} 
