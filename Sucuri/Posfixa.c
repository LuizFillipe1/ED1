#include <stdio.h>
#include <stdlib.h>

#include "Posfixa.h"
#include "Pilha.h"

/* A função recebe uma fila de objetos em notação infixa e converte (retorna)
 * a correspondente em notação pós-fixa.
 * Para evitar problemas de vazamento de memória e/ou falha de segmentação, faça
 * cópia dos objetos.
 * Lembre-se que a função 'desempilha' (Pilha.h) e 'dequeue' (Fila.h)
 * fazem a desalocação dos objetos(liberaObjeto)
 */
Fila *infixaParaPosfixa(Fila *infixa) {
    //AVISO(Posfixa.c: ainda não completei a função 'infixaParaPosfixa');
    Fila *filaSaida = criaFila();
    Pilha *Pilha1 = criaPilha();
    Objeto *copia = NULL;
    Objeto *aux = front(infixa) ;

    while(aux != NULL ){
        if(aux->categoria == 7){
            copia = copiaObjeto(aux);
            empilha(Pilha1,copia);
        }
        else if(aux->categoria == 8){
            while(topoPilha(Pilha1)->categoria !=7 ){
                copia = copiaObjeto(topoPilha(Pilha1));
                enqueue(filaSaida,copia);
                desempilha(Pilha1);
            }
            desempilha(Pilha1);
        }
        else if(aux->categoria == 11 || aux->categoria == 12 ){
            copia = copiaObjeto(aux);
            enqueue(filaSaida,copia);
        }
        else if ( aux->categoria >=0 && aux->categoria <7) {
            if(pilhaVazia(Pilha1)){
                copia = copiaObjeto(aux);
                empilha(Pilha1,copia);
            }
            else{
                if(getPrecedenciaOperadores(topoPilha(Pilha1)->categoria) > (getPrecedenciaOperadores(aux->categoria))){
                    while(pilhaVazia(Pilha1) == false ){
                        copia = copiaObjeto(topoPilha(Pilha1));
                        enqueue(filaSaida,copia);
                        desempilha(Pilha1);
                    }
                    copia = copiaObjeto(aux);
                    empilha(Pilha1,copia);
                    }
                else if(getPrecedenciaOperadores(topoPilha(Pilha1)->categoria) == (getPrecedenciaOperadores(aux->categoria))){
                    copia = copiaObjeto(aux);
                    empilha(Pilha1,copia);
                    }

                else if(getPrecedenciaOperadores(topoPilha(Pilha1)->categoria) < (getPrecedenciaOperadores(aux->categoria))){
                    copia = copiaObjeto(aux);
                    empilha(Pilha1,copia);
                    }
                else{
                    while(pilhaVazia(Pilha1) == false ){
                        copia = copiaObjeto(topoPilha(Pilha1));
                        enqueue(filaSaida,copia);
                        desempilha(Pilha1);
                    }
                }
            }
        }
        aux = aux->proximo;
    }

    while(pilhaVazia(Pilha1) != true ){
        copia = copiaObjeto(topoPilha(Pilha1));
        enqueue(filaSaida,copia);
        desempilha(Pilha1);
    }
    liberaObjeto(aux);
    liberaFila(infixa);
    liberaPilha(Pilha1);
    return filaSaida;
}

void imprimePosFixa(Fila *posfixa) {
    Fila *f = copiaFila(posfixa);
    while(!filaVazia(f)) {
        Objeto *obj = front(f);
        imprimeObjeto(obj, POSFIXA);
        dequeue(f);
    }
    printf("\n");
    liberaFila(f);
}