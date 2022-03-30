#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ArmazenaFila.h"
#include "Util.h"

typedef struct no1 {
    char *palavra;
    struct no1 *proximo;
}No1 ;

typedef struct fila {
    No1 *inicio;
    No1 *fim;
    int n;
}Fila ;

No1 *criaNo1() {
    No1 *no = mallocSafe(sizeof(No1));
    no->palavra = NULL;
    no->proximo = NULL;
    return no;
}

Fila *CriaFila() {
    Fila *f = mallocSafe(sizeof(Fila));
    f->inicio = f->fim = NULL;
    f->n = 0;
    return f;
}

void liberaFila(Fila *f) {
    //AVISO(Fila.c: ainda não completei a função 'liberaFila');
    No1 *atual = f->inicio;

    while(filaVazia(f) != true){
        dequeue(f);
        atual = front(f);
    }
    free(f);
    f=NULL;
}

void liberaNo1(No1 *r){
    if (r != NULL){
        liberaNo1(r->proximo);
        free(r->palavra);
        free(r);
    }
}

/* Insere um novo objeto a fila */
void enqueue(Fila *f, char *palavra) {
    No1 *no = mallocSafe(sizeof(No1));
    no->palavra = mallocSafe(sizeof(char)*(strlen(palavra)+1));
    strcpy(no->palavra, palavra);
    no->proximo = NULL;
    if(filaVazia(f)){
       f->inicio = no;
    }
    else
        f->fim->proximo = no;
    f->fim = no;
    f->n++;
}

/*Remove (apaga) o primeiro elemento da fila */
void dequeue(Fila *f) {
    if (!filaVazia(f)){
        No1 *temp = f->inicio;
        f->inicio = f->inicio->proximo;
        f->n--;
        free(temp->palavra);
        free(temp);
    }
}

/* Retorna o primeiro elemento da fila */

No1 *front(Fila *f) {
    if (filaVazia(f)){
        return NULL;
    }
    return f->inicio;
}
char *frontPalavra(Fila *f) {
    if (filaVazia(f)){
        return NULL;
    }
    return f->inicio->palavra;
}

/* Verifica se a fila está vazia */
int filaVazia(Fila *f) {
    return (f==NULL || f->n == 0);
}

/* Retorna o número de elementos na fila */
int tamanhoFila(Fila *f) {
    if (filaVazia(f)) return 0;
    return f->n;
}
int busca (Fila* l, char *v) {
    No1* p = front(l);
    if (filaVazia(l))
        return 1;
    while(p!=NULL){ 
        if (strcmp(p->palavra , v) == 0)
            return -1; 
        p = p->proximo;
    }
    return 1; /* não achou o elemento */
}

void imprimePalavra(No1 *f) {
    printf("%s",f->palavra);
}
