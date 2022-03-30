#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Avalia.h"
#include "Categorias.h"
#include "Pilha.h"
#include "Util.h"


/* Recebe uma fila de objetos em notação pós-fixa, avalia e retorna o resultado da expressação */
Objeto *avalia(Fila *posFixa) {
    //Tentei verificar todos os casos em que algum dos operando pode ser Float
    Pilha *Pilha2 = criaPilha();
    Objeto *aux = front(posFixa);
    Objeto *copia = NULL;

    while(aux){
        while(aux->categoria == 11 || aux->categoria == 12){
            copia = copiaObjeto(aux);
            empilha(Pilha2,copia);
            aux = aux->proximo;
        }
        if(aux->categoria >=0 && aux->categoria <7){
            switch (aux->categoria) {
            case 0:
                copia = copiaObjeto(topoPilha(Pilha2));
                desempilha(Pilha2);
                if (copia->categoria == 11 && topoPilha(Pilha2)->categoria == 11) {
                    topoPilha(Pilha2)->valor.vFloat = pow(topoPilha(Pilha2)->valor.vFloat , copia->valor.vFloat);
                }
                else if (copia->categoria == 11 && topoPilha(Pilha2)->categoria == 12) {
                    topoPilha(Pilha2)->categoria = 11;
                    topoPilha(Pilha2)->valor.vFloat = pow(topoPilha(Pilha2)->valor.vInt , copia->valor.vFloat);
                }
                else if (copia->categoria == 12 && topoPilha(Pilha2)->categoria == 11) {
                    topoPilha(Pilha2)->valor.vFloat = pow(topoPilha(Pilha2)->valor.vFloat , copia->valor.vInt);
                }
                else{
                    topoPilha(Pilha2)->valor.vInt = pow(topoPilha(Pilha2)->valor.vInt, copia->valor.vInt);
                }
                break;
            case 1:
                copia = copiaObjeto(topoPilha(Pilha2));
                desempilha(Pilha2);
                if (copia->categoria == 11 && topoPilha(Pilha2)->categoria == 11) {
                    topoPilha(Pilha2)->valor.vFloat = fmod(topoPilha(Pilha2)->valor.vFloat , copia->valor.vFloat);
                }
                else if (copia->categoria == 11 && topoPilha(Pilha2)->categoria == 12) {
                    topoPilha(Pilha2)->categoria = 11;
                    topoPilha(Pilha2)->valor.vFloat = fmod(topoPilha(Pilha2)->valor.vInt , copia->valor.vFloat);
                }
                else if (copia->categoria == 12 && topoPilha(Pilha2)->categoria == 11) {
                    topoPilha(Pilha2)->valor.vFloat = fmod(topoPilha(Pilha2)->valor.vFloat , copia->valor.vInt);
                }
                else{
                    topoPilha(Pilha2)->valor.vInt = fmod(topoPilha(Pilha2)->valor.vInt , copia->valor.vInt);
                    }
                break;
            case 2:
                copia = copiaObjeto(topoPilha(Pilha2));
                desempilha(Pilha2);
                if (copia->categoria == 11 && topoPilha(Pilha2)->categoria == 11) {
                    topoPilha(Pilha2)->valor.vFloat = topoPilha(Pilha2)->valor.vFloat * copia->valor.vFloat;
                }
                else if (copia->categoria == 11 && topoPilha(Pilha2)->categoria == 12) {
                    topoPilha(Pilha2)->categoria = 11;
                    topoPilha(Pilha2)->valor.vFloat = topoPilha(Pilha2)->valor.vInt * copia->valor.vFloat;
                }
                else if (copia->categoria == 12 && topoPilha(Pilha2)->categoria == 11) {
                    topoPilha(Pilha2)->valor.vFloat = topoPilha(Pilha2)->valor.vFloat * copia->valor.vInt;
                }
                else{
                    topoPilha(Pilha2)->valor.vInt = topoPilha(Pilha2)->valor.vInt * copia->valor.vInt;
                    }
                break;
            case 3:
                copia = copiaObjeto(topoPilha(Pilha2));
                desempilha(Pilha2);
                if (copia->categoria == 11 && topoPilha(Pilha2)->categoria == 11) {
                    topoPilha(Pilha2)->valor.vFloat = topoPilha(Pilha2)->valor.vFloat / copia->valor.vFloat;
                }
                else if (copia->categoria == 11 && topoPilha(Pilha2)->categoria == 12) {
                    topoPilha(Pilha2)->categoria = 11;
                    topoPilha(Pilha2)->valor.vFloat = topoPilha(Pilha2)->valor.vInt / copia->valor.vFloat;
                }
                else if (copia->categoria == 12 && topoPilha(Pilha2)->categoria == 11) {
                    topoPilha(Pilha2)->valor.vFloat = topoPilha(Pilha2)->valor.vFloat / copia->valor.vInt;
                }
                else{
                    topoPilha(Pilha2)->valor.vInt = topoPilha(Pilha2)->valor.vInt / copia->valor.vInt;
                    }
                break;
            case 4:
                copia = copiaObjeto(topoPilha(Pilha2));
                desempilha(Pilha2);
                if (copia->categoria == 11 && topoPilha(Pilha2)->categoria == 11) {
                    topoPilha(Pilha2)->valor.vFloat = topoPilha(Pilha2)->valor.vFloat + copia->valor.vFloat;
                }
                else if (copia->categoria == 11 && topoPilha(Pilha2)->categoria == 12) {
                    topoPilha(Pilha2)->categoria = 11;
                    topoPilha(Pilha2)->valor.vFloat = topoPilha(Pilha2)->valor.vInt + copia->valor.vFloat;
                }
                else if (copia->categoria == 12 && topoPilha(Pilha2)->categoria == 11) {
                    topoPilha(Pilha2)->valor.vFloat = topoPilha(Pilha2)->valor.vFloat + copia->valor.vInt;
                }
                else{
                    topoPilha(Pilha2)->valor.vInt = topoPilha(Pilha2)->valor.vInt + copia->valor.vInt;
                    }
                break;
            case 5:
                copia = copiaObjeto(topoPilha(Pilha2));
                desempilha(Pilha2);
                if (copia->categoria == 11 && topoPilha(Pilha2)->categoria == 11) {
                    topoPilha(Pilha2)->valor.vFloat = topoPilha(Pilha2)->valor.vFloat - copia->valor.vFloat;
                }
                else if (copia->categoria == 11 && topoPilha(Pilha2)->categoria == 12) {
                    topoPilha(Pilha2)->categoria = 11;
                    topoPilha(Pilha2)->valor.vFloat = topoPilha(Pilha2)->valor.vInt - copia->valor.vFloat;
                }
                else if (copia->categoria == 12 && topoPilha(Pilha2)->categoria == 11) {
                    topoPilha(Pilha2)->valor.vFloat = topoPilha(Pilha2)->valor.vFloat - copia->valor.vInt;
                }
                else{
                    topoPilha(Pilha2)->valor.vInt = topoPilha(Pilha2)->valor.vInt - copia->valor.vInt;
                }
                break;
            case 6:
                copia = copiaObjeto(topoPilha(Pilha2));
                if (copia->categoria == 11) {
                    topoPilha(Pilha2)->valor.vFloat = -copia->valor.vFloat ;
                }
                else{
                    topoPilha(Pilha2)->valor.vInt = -copia->valor.vInt ;
                }
                break;
            default:
                break;
            }
        }
        aux = aux->proximo;
        liberaObjeto(copia);
    }

    liberaObjeto(aux);
    liberaFila(posFixa);
    copia = topoPilha(Pilha2);
    free(Pilha2);
    return copia;
}
