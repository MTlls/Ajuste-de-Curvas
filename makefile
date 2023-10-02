CFLAGS = -Wall -g # gerar "warnings" detalhados e infos de depuração
LDLIBS = -lm

PROGRAM=main

objs = main.o libDouble.o utils.o

all: $(PROGRAM)

main: $(objs)

main.o: main.c libDouble.h utils.h
# libMatriz.o: libMatriz.c libMatriz.h
libDouble.o: libDouble.c utils.h
utils.o: utils.c utils.h libDouble.h

clean:
	-rm -f $(objs) *~ *.o $(PROGRAM)

purge: clean
	-rm -f main