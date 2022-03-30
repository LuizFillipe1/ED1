#ifndef EP3_CRIA_ARVORE_BUSCA_H
#define EP3_CRIA_ARVORE_BUSCA_H

typedef struct no No;

No *CriaNo (char *palavra);

void liberaNo(No *r);

void imprime(No *r);

int pertence (No *r, char *palavra);

No *CriaArvore(No *raiz,char *palavra);

No *direita(No *raiz);

No *esquerda(No *raiz);

char *PalavradoNo(No *no);

double MyClock();

No *insere(No *r, No *novo);

No *rotacaoEsquerda(No *A);

No *rotacaoDireita(No *A);

int getFB(No *r);

int altura(No *r);

int max(int a, int b);

#endif