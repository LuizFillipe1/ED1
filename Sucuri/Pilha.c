#include <stdio.h>
#include <stdlib.h>

#include "Pilha.h"

typedef struct pilha {
    Objeto *inicio;
    int n;
} Pilha;

Pilha *criaPilha(){
    Pilha *p = mallocSafe(sizeof(Pilha));
    p->inicio  = NULL;
    p->n = 0;
    return p;
}

void liberaPilha(Pilha *p) {
    //AVISO(Pilha.c: ainda não completei a função 'liberaPilha');
    Objeto *aux = p->inicio;
    while(pilhaVazia(p) != true){
        desempilha(p);
        aux = topoPilha(p);
    }
    free(p);
    p = NULL;
}

void empilha(Pilha *p, Objeto *no) {
    if(pilhaVazia(p)){
        p->inicio = no;
        p->n++;
    }
    else{
        no->proximo = p->inicio;
        p->inicio = no;
        p->n++;
    }
}

void desempilha(Pilha *p){
   //AVISO(Pilha.c: ainda não completei a função 'desempilha');
    if(!pilhaVazia(p)){
        Objeto *temp = p->inicio;
        p->inicio = p->inicio->proximo;
        p->n--;
        free(temp);
    }
}

Objeto *topoPilha(Pilha *p){
    //AVISO(Pilha.c: ainda não completei a função 'top');
    if(pilhaVazia(p)){
        return NULL;
    }
    return p->inicio;

}

bool pilhaVazia(Pilha *p){
    return (p==NULL || p->n == 0);
}

int tamanhoPilha(Pilha *p){
    return p->n;
}

void imprimePilha(Pilha *pilha, int tipo) {
    Objeto *aux = pilha->inicio;
    while(aux != NULL){
        imprimeObjeto(aux,tipo);
        aux = aux->proximo;
    }
}

