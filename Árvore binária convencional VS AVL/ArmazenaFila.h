#ifndef EP3_ARMAZENAFILA_H
#define EP3_ARMAZENAFILA_H

typedef struct fila Fila;
typedef struct no1 No1;

Fila *CriaFila();

No1 *criaNo1();

void liberaFila(Fila *f);

void enqueue(Fila *, char *palavra);

void dequeue(Fila *);

No1 *front(Fila *);

int filaVazia(Fila *);

void imprimePalavra(No1 *);

char *frontPalavra(Fila *f) ;

int busca (Fila* l, char *v);

void liberaNo1(No1 *r);

#endif