#include <stdio.h>
#include <stdlib.h>

#include "Distancia.h"
#include "Util.h"
#include "ArmazenaFila.h"
#include "CriaArvoreBusca.h"

int Distancia(No *raiz, char *palavra ){

    if(raiz != NULL){
        if(distanciaEdicao(PalavradoNo(raiz),palavra)  <= 2 )
            printf("\033[1;32m%s\033[00m ", PalavradoNo(raiz));
        else if(distanciaEdicao(PalavradoNo(raiz),palavra)  <= 2 )
            printf("\033[1;32m%s\033[00m ", PalavradoNo(raiz));
        Distancia(direita(raiz),palavra);
        Distancia(esquerda(raiz),palavra);
    }

    return 0;
}



