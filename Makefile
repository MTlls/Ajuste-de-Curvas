override CFLAGS += -Wall -g -O3 -mavx -march=native -I${LIKWID_HOME}/include # gerar "warnings" detalhados e infos de depuração
LFLAGS = -lm -L${LIKWID_HOME}/lib -llikwid
PROGRAM=ajustePol

# Lista de arquivos para distribuição
DISTFILES = *.c *.h README* Makefile *.in *.sh
DISTDIR = `basename ${PWD}`


objs = ajustePol.o libMatematicaDouble.o utils.o libMatriz.o

all: $(PROGRAM)

ajustePol: $(objs)
	$(CC) $^ $(CFLAGS) $(LFLAGS) -o $@

main.o: main.c libMatematicaDouble.h utils.h
libMatematicaDouble.o: libMatematicaDouble.c libMatematicaDouble.h utils.h
utils.o: utils.c utils.h libMatematicaDouble.h
libMatriz.o: libMatriz.c libMatriz.h libMatematicaDouble.h

clean:
	@echo "Limpando sujeira..."
	@rm -f $(objs) *~ *.o $(PROGRAM)

purge: clean
	@echo "Limpando tudo..."
	@rm -f $(PROGRAM) *.o core a.out *.log $(DISTDIR) $(DISTDIR).tar

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tar) ..."
	@ln -s . $(DISTDIR)
	@tar -cvf $(DISTDIR).tar $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)
