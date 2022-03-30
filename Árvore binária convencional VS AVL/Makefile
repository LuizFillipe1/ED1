CFLAGS=-O0 -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wshadow
LIBS=-lm
EXECUTAVEL=EP3

all: $(EXECUTAVEL)

$(EXECUTAVEL): main.o Util.o ArmazenaFila.o CriaArvoreBusca.o Distancia.o
	gcc main.o Util.o ArmazenaFila.o CriaArvoreBusca.o Distancia.o $(LIBS) -o $(EXECUTAVEL)

main.o: main.c
	gcc $(CFLAGS) -c main.c

Util.o: Util.c
	gcc $(CFLAGS) -c Util.c

ArmazenaFila.o: ArmazenaFila.o
	gcc $(CFLAGS) -c ArmazenaFila.c

CriaArvoreBusca.o: CriaArvoreBusca.o
	gcc $(CFLAGS) -c CriaArvoreBusca.c
Distancia.o: Distancia.o
	gcc $(CFLAGS) -c Distancia.c

clean:
	rm -rf *.o $(EXECUTAVEL)

memcheck: $(EXECUTAVEL)
	valgrind --tool=memcheck --leak-check=full ./$(EXECUTAVEL) -d Dicionario.txt -t TextoExemplo.txt -avl

run: $(EXECUTAVEL)
	./$(EXECUTAVEL) -d Dicionario.txt -t TextoExemplo.txt