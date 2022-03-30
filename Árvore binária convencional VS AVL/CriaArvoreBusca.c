#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

#include "CriaArvoreBusca.h"
#include "Util.h"

typedef struct no{
    char *palavra;
    int altura; // tamanho
    struct no *esquerdo;
    struct no *direito;

} No;

No *CriaNo (char *palavra){
    char *NovaPalavra;
    No *novo = mallocSafe(sizeof(No));
    NovaPalavra = mallocSafe(strlen(palavra)+1);
    strcpy(NovaPalavra, palavra);
    novo->palavra = NovaPalavra;
    novo->direito = NULL;
    novo->esquerdo = NULL;
    novo->altura = 0;
    return novo;

}

void liberaNo(No *r){
    if (r != NULL){
        liberaNo(r->esquerdo);
        liberaNo(r->direito);
        free(r->palavra);
        free(r);
    }
}

void imprime(No *r){
    if (r != NULL){
        printf("%s ",r->palavra);
        imprime(r->esquerdo);
        imprime(r->direito);
    }
}

int pertence (No *r, char *palavra){
    if (r == NULL)
        return 0;
    if (strcmp(palavra, r->palavra) == 0)
        return 1;
    else if (pertence(r->esquerdo,palavra))
        return 1;
    else
        return pertence(r->direito,palavra);
    }
//retorna o lado direito da raiz
No *direita(No *raiz){
    if(raiz!= NULL)
        return raiz->direito;
    else
        return NULL;
}
//retorna o lado esquedo da raiz
No *esquerda(No *raiz){
    if(raiz!= NULL)
        return raiz->esquerdo;
    else
        return NULL;
}
//retorna a palavra do nó
char *PalavradoNo(No *no){
    if(no != NULL)
        return no->palavra;
    return false;
}
int altura(No *r) {
    if (r == NULL)
        return -1;
    return r->altura;
}
int max(int a, int b) {
    return (a > b) ? a : b;
}
/* Obtem o fator de balanceamento do nó */
int getFB(No *r) {
    return altura(r->esquerdo) - altura(r->direito);
}

No *rotacaoDireita(No *A) {
    No *B = A->esquerdo;

    // Realiza a rotação
    A->esquerdo = B->direito;
    B->direito = A;

    // Atualiza as alturas dos nós
    A->altura = max(altura(A->esquerdo), altura(A->direito)) + 1;
    B->altura = max(altura(B->esquerdo), altura(B->direito)) + 1;

    // Retorna a nova raiz
    return B;
}

No *rotacaoEsquerda(No *A) {
    No *B = A->direito;

    // Realiza a rotação
    A->direito = B->esquerdo;
    B->esquerdo = A;

    // Atualiza as alturas dos nós
    A->altura = max(altura(A->esquerdo), altura(A->direito)) + 1;
    B->altura = max(altura(B->esquerdo), altura(B->direito)) + 1;

    // Retorna a nova raiz
    return B;
}
No *insere(No *r, No* novo) {
    /*PASSO 1: Faz a inserção normal de uma ABB */
    if (r == NULL) return novo;
    if(r->palavra > novo->palavra)
        r->esquerdo = insere(r->esquerdo, novo);
    else
        r->direito = insere(r->direito, novo);

    /*PASSO 2: Atualiza a altura do nó*/
    r->altura = max(altura(r->esquerdo), altura(r->direito)) + 1;

    /*PASSO 3: Obter o fator de balanceamento do nó e verifica se é necessário o rebalanceamento */
    int fb = getFB(r);

    //Rotação RR
    if (fb > 1 && novo->palavra < r->esquerdo->palavra /*ou getFB(r->esq) >= 0 */)
        return rotacaoDireita(r);
    //Rotação LL
    if (fb < -1 && novo->palavra > r->direito->palavra /*ou getFB(r->dir) <= 0 */)
        return rotacaoEsquerda(r);
    //Rotação LR
    if (fb > 1 && novo->palavra > r->esquerdo->palavra /*ou getFB(r->esq) < 0 */) {
        r->esquerdo = rotacaoEsquerda(r->esquerdo);
        return rotacaoDireita(r);
    }
    //Rotação RL
    if (fb < -1 && novo->palavra < r->direito->palavra /*ou getFB(r->dir) > 0 */) {
        r->direito = rotacaoDireita(r->direito);
        return rotacaoEsquerda(r);
    }
    return r;
}

//Aqui cria a arvore BTS
No *CriaArvore(No *raiz,char *palavra){
    No *aux = CriaNo(palavra);
    No *pai = NULL;
    if (raiz==NULL)
        raiz = aux;
    else {
        No *atual = raiz;
        while(atual != NULL ){
            pai = atual;
            if (strcmp(atual->palavra,palavra) > 0)
                atual = atual -> esquerdo;
            else
                atual = atual -> direito;
        }
        if(strcmp(pai->palavra , palavra) > 0)
            pai->esquerdo = aux;
        else
            pai->direito = aux;
    }
    return raiz;
}
