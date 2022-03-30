#include <stdio.h>
#include <stdlib.h>

#include "Fila.h"

struct fila {
    Objeto *inicio;
    Objeto *fim;
    int n;
};

Fila *criaFila() {
    Fila *f = mallocSafe(sizeof(Fila));
    f->inicio = f->fim = NULL;
    f->n = 0;
    return f;
}

/* Faz a desalocação da fila */
void liberaFila(Fila *f) {
    //AVISO(Fila.c: ainda não completei a função 'liberaFila');
    Objeto *aux = f->inicio;
    while(filaVazia(f) != true){
        dequeue(f);
        aux = front(f);
    }
    free(f);
    f=NULL;
}

/* Insere um novo objeto a fila */
void enqueue(Fila *f, Objeto *o) {
    if(filaVazia(f)){
        f->inicio = o;
        f->fim = o;
        f->n++;
    }
    else{
    f->fim->proximo = o;
    f->fim = o;
    f->n++;

    }
}

/*Remove (apaga) o primeiro elemento da fila */
void dequeue(Fila *f) {
    if (!filaVazia(f)){
        Objeto *temp = f->inicio;
        f->inicio = f->inicio->proximo;
        f->n--;
        free(temp);
    }
}

/* Retorna o primeiro elemento da fila */
Objeto *front(Fila *f) {
    if (filaVazia(f)){
        return NULL;
    }
    return f->inicio;
}

/* Verifica se a fila está vazia */
bool filaVazia(Fila *f) {
    return (f==NULL || f->n == 0);
}

/* Retorna o número de elementos na fila */
int tamanhoFila(Fila *f) {
    if (filaVazia(f)) return 0;
    return f->n;
}

/* Retorna uma cópia da fila passada como parâmetro */
Fila *copiaFila(Fila *f) {
    //AVISO(Fila.c: ainda não completei a função 'copiaFila');
    Fila *copia = criaFila();
    Objeto *aux = f->inicio;
    Objeto *aux1 = NULL;
    while(aux != NULL){
        aux1 = copiaObjeto(aux);
        enqueue(copia,aux1);
        aux = aux->proximo;
    }
    return copia;
}

/* Fução que imprime os elementos da fila
 * Essa função pode ajudar a detectar problemas nos objetos da fila
 * Para imprimir um objeto, use a função imprimeObjeto.
 */
void imprimeFila(Fila *f, int tipo) {
    Objeto *aux = f->inicio;
    while(aux != NULL){
        imprimeObjeto(aux,tipo);
        aux = aux->proximo;
    }
}

/* Função de Alta Ordem que recebe uma fila e uma função (cb).
 * Para cada objeto da fila, aplique a função cb ao objeto.
 */
void converteElementosFila(Fila *f, void (*cb)(Objeto *)) {
    Objeto *aux = f->inicio;
    while(aux != NULL){
        cb(aux);
        aux = aux->proximo;
    }
}
