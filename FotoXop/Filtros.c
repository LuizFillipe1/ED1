#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Imagem.h"
#include "Filtros.h"

void escurecerImagem(Imagem *img){
    int v;
    printf("Digite o fator de escurecimento: ");
    scanf("%d", &v);

    for (int h = 0; h < obtemAltura(img); h++) {
        for (int w = 0; w < obtemLargura(img); w++) {
            Pixel pixel = obtemPixel(img, h, w);
            pixel.cor[RED]   = (((int)pixel.cor[RED]   - v) >= 0 ? (pixel.cor[RED]   - v) : 0);
            pixel.cor[GREEN] = (((int)pixel.cor[GREEN] - v) >= 0 ? (pixel.cor[GREEN] - v) : 0);
            pixel.cor[BLUE]  = (((int)pixel.cor[BLUE]  - v) >= 0 ? (pixel.cor[BLUE]  - v) : 0);
            recolorePixel(img, h, w, pixel);
        }
    }
}

void clarearImagem(Imagem *img){
    int v;

    printf("Digite o fator de clareamento: ");
    scanf("%d", &v);

    for (int h = 0; h < obtemAltura(img); h++) {
        for (int w = 0; w < obtemLargura(img); w++) {
            Pixel pixel = obtemPixel(img, h, w);
            pixel.cor[RED]   = (((int)pixel.cor[RED]   + v) <= 255 ? (pixel.cor[RED]   + v) : 255);
            pixel.cor[GREEN] = (((int)pixel.cor[GREEN] + v) <= 255 ? (pixel.cor[GREEN] + v) : 255);
            pixel.cor[BLUE]  = (((int)pixel.cor[BLUE]  + v) <= 255 ? (pixel.cor[BLUE]  + v) : 255);
            recolorePixel(img, h, w, pixel);
        }
    }
}

void escalaDeCinzaImagem(Imagem *img){

    for (int h = 0; h < obtemAltura(img); h++) {
        for (int w = 0; w < obtemLargura(img); w++) {
            int a;

            Pixel pixel = obtemPixel(img, h, w);
            a = ((pixel.cor[RED] * 0.3) + (pixel.cor[GREEN] * 0.59) + (pixel.cor[BLUE] * 0.11));
            pixel.cor[RED]   = a ;
            pixel.cor[GREEN] = a ;
            pixel.cor[BLUE]  = a ;
            recolorePixel(img, h, w, pixel);
        }
    }
}

void filtroSobel(Imagem *img){
    int auxRED, auxRED1;
    int auxGREEN, auxGREEN1;
    int auxBLUE, auxBLUE1;

    Imagem *cpy = NULL;
    cpy = copiaImagem(img);

    for (int h = 1; h < obtemAltura(img)-1; h++) {
        for (int w = 1; w < obtemLargura(img)-1; w++) {
            Pixel pixel = obtemPixel(cpy, h, w);
            Pixel pixelAux1 = obtemPixel(cpy,h-1,w-1);
            Pixel pixelAux2 = obtemPixel(cpy,h-1,w);
            Pixel pixelAux3 = obtemPixel(cpy,h-1,w+1);
            Pixel pixelAux4 = obtemPixel(cpy,h,w-1);
            Pixel pixelAux6 = obtemPixel(cpy,h,w+1);
            Pixel pixelAux7 = obtemPixel(cpy,h+1,w-1);
            Pixel pixelAux8 = obtemPixel(cpy,h+1,w);
            Pixel pixelAux9 = obtemPixel(cpy,h+1,w+1);

            //Fazendo o Gy
            auxRED =         (((int)pixelAux1.cor[RED] *1)    + ((int)pixelAux2.cor[RED] *2)  +
                              ((int)pixelAux3.cor[RED] *1)    + ((int)pixelAux4.cor[RED] *0)  +
                              ((int)pixelAux6.cor[RED] *0)    + ((int)pixelAux7.cor[RED] *-1) +
                              ((int)pixelAux8.cor[RED] *-2)   + ((int)pixelAux9.cor[RED] *-1));
            auxGREEN =       (((int)pixelAux1.cor[GREEN] *1)  + ((int)pixelAux2.cor[GREEN] *2)  +
                              ((int)pixelAux3.cor[GREEN] *1)  + ((int)pixelAux4.cor[GREEN] *0)  +
                              ((int)pixelAux6.cor[GREEN] *0)  + ((int)pixelAux7.cor[GREEN] *-1) +
                              ((int)pixelAux8.cor[GREEN] *-2) + ((int)pixelAux9.cor[GREEN] *-1));
            auxBLUE =        (((int)pixelAux1.cor[BLUE] *1)   + ((int)pixelAux2.cor[BLUE] *2) +
                              ((int)pixelAux3.cor[BLUE] *1)   + ((int)pixelAux4.cor[BLUE] *0) +
                              ((int)pixelAux6.cor[BLUE] *0)   + ((int)pixelAux7.cor[BLUE] *-1)+
                              ((int)pixelAux8.cor[BLUE] *-2)  + ((int)pixelAux9.cor[BLUE] *-1));

            auxRED =   (auxRED)   < 0 ? 0 : auxRED;
            auxGREEN = (auxGREEN) < 0 ? 0 : auxGREEN;
            auxBLUE =  (auxBLUE)  < 0 ? 0 : auxBLUE;
            auxRED =   (auxRED)   > 255 ? 255 : auxRED;
            auxGREEN = (auxGREEN) > 255 ? 255 : auxGREEN;
            auxBLUE =  (auxBLUE)  > 255 ? 255 : auxBLUE;

            //Fazendo Gx

            auxRED1 =        (((int)pixelAux1.cor[RED] *1)    + ((int)pixelAux2.cor[RED] *0)  +
                              ((int)pixelAux3.cor[RED] *-1)   + ((int)pixelAux4.cor[RED] *2)  +
                              ((int)pixelAux6.cor[RED] *-2)   + ((int)pixelAux7.cor[RED] *1)  +
                              ((int)pixelAux8.cor[RED] *0)    + ((int)pixelAux9.cor[RED] *-1));

            auxGREEN1 =      (((int)pixelAux1.cor[GREEN] *1)  + ((int)pixelAux2.cor[GREEN] *0)  +
                              ((int)pixelAux3.cor[GREEN] *-1) + ((int)pixelAux4.cor[GREEN] *2)  +
                              ((int)pixelAux6.cor[GREEN] *-2) + ((int)pixelAux7.cor[GREEN] *1)  +
                              ((int)pixelAux8.cor[GREEN] *0)  + ((int)pixelAux9.cor[GREEN] *-1));

            auxBLUE1 =       (((int)pixelAux1.cor[BLUE] *1)   + ((int)pixelAux2.cor[BLUE] *0)   +
                              ((int)pixelAux3.cor[BLUE] *-1)  + ((int)pixelAux4.cor[BLUE] *2)   +
                              ((int)pixelAux6.cor[BLUE] *-2)  + ((int)pixelAux7.cor[BLUE] *1)   +
                              ((int)pixelAux8.cor[BLUE] *0)   + ((int)pixelAux9.cor[BLUE] *-1));

            auxRED1 =   (auxRED1)   < 0 ? 0 : auxRED1;
            auxGREEN1 = (auxGREEN1) < 0 ? 0 : auxGREEN1;
            auxBLUE1 =  (auxBLUE1)  < 0 ? 0 : auxBLUE1;
            auxRED1 =   (auxRED1)   > 255 ? 255 : auxRED1;
            auxGREEN1 = (auxGREEN1) > 255 ? 255 : auxGREEN1;
            auxBLUE1 =  (auxBLUE1)  > 255 ? 255 : auxBLUE1;

            pixel.cor[RED]   = (auxRED+auxRED1)/2;
            pixel.cor[GREEN]   = (auxGREEN+auxGREEN1)/2;
            pixel.cor[BLUE]   = (auxBLUE+auxBLUE1)/2;
            recolorePixel(img, h, w, pixel);

            }
    }
    liberaImagem(cpy);
}

void deteccaoBordasLaplace(Imagem *img) {

    Imagem *cpy = NULL;
    cpy = copiaImagem(img);
    int auxRED, auxRED1;
    int auxGREEN, auxGREEN1;
    int auxBLUE, auxBLUE1;
    for (int h = 1; h < obtemAltura(img)-1; h++) {
        for (int w = 1; w < obtemLargura(img)-1; w++) {
            Pixel pixel = obtemPixel(cpy, h, w);
            Pixel pixelAux1 = obtemPixel(cpy,h-1,w-1);
            Pixel pixelAux2 = obtemPixel(cpy,h-1,w);
            Pixel pixelAux3 = obtemPixel(cpy,h-1,w+1);
            Pixel pixelAux4 = obtemPixel(cpy,h,w-1);
            Pixel pixelAux5 = obtemPixel(cpy,h,w);    //  <-- tem esse a mais que o de sobel
            Pixel pixelAux6 = obtemPixel(cpy,h,w+1);
            Pixel pixelAux7 = obtemPixel(cpy,h+1,w-1);
            Pixel pixelAux8 = obtemPixel(cpy,h+1,w);
            Pixel pixelAux9 = obtemPixel(cpy,h+1,w+1);

            //fazendo usando a matriz de laplace

            auxRED =         (((int)pixelAux1.cor[RED] *0)   + ((int)pixelAux2.cor[RED] *-1)+
                              ((int)pixelAux3.cor[RED] *0)   + ((int)pixelAux4.cor[RED] *-1)+
                              ((int)pixelAux5.cor[RED] *4)   + ((int)pixelAux6.cor[RED] *-1)+
                              ((int)pixelAux7.cor[RED] *0)   + ((int)pixelAux8.cor[RED] *-1)+
                              ((int)pixelAux9.cor[RED] *0));
            auxGREEN =       (((int)pixelAux1.cor[GREEN] *0) + ((int)pixelAux2.cor[GREEN] *-1)+
                              ((int)pixelAux3.cor[GREEN] *0) + ((int)pixelAux4.cor[GREEN] *-1)+
                              ((int)pixelAux5.cor[GREEN] *4) + ((int)pixelAux6.cor[GREEN] *-1)+
                              ((int)pixelAux7.cor[GREEN] *0) + ((int)pixelAux8.cor[GREEN] *-1)+
                              ((int)pixelAux9.cor[GREEN] *0));
            auxBLUE =        (((int)pixelAux1.cor[BLUE] *0)  + ((int)pixelAux2.cor[BLUE] *-1)+
                              ((int)pixelAux3.cor[BLUE] *0)  + ((int)pixelAux4.cor[BLUE] *-1)+
                              ((int)pixelAux5.cor[BLUE] *4)  + ((int)pixelAux6.cor[BLUE] *-1)+
                              ((int)pixelAux7.cor[BLUE] *0)  + ((int)pixelAux8.cor[BLUE] *-1)+
                              ((int)pixelAux9.cor[BLUE] *0));

            auxRED =   (auxRED)   < 0 ? 0 : auxRED;
            auxGREEN = (auxGREEN) < 0 ? 0 : auxGREEN;
            auxBLUE =  (auxBLUE)  < 0 ? 0 : auxBLUE;
            auxRED =   (auxRED)   > 255 ? 255 : auxRED;
            auxGREEN = (auxGREEN) > 255 ? 255 : auxGREEN;
            auxBLUE =  (auxBLUE)  > 255 ? 255 : auxBLUE;

            pixel.cor[RED]   = auxRED;
            pixel.cor[GREEN]   = auxGREEN;
            pixel.cor[BLUE]   = auxBLUE;
            recolorePixel(img, h, w, pixel);

            }
    }
    liberaImagem(cpy);
}

void meuFiltro(Imagem *img){
    /* Em uma tentativa de criar um filtro para remover ruidos, surgiu esse que eu gostei.
    Localiza os contornos dos obejetos e dá um toque neon verde*/
    int auxRED, auxRED1;
    int auxGREEN, auxGREEN1;
    int auxBLUE, auxBLUE1;
    int vetorRED[9], vetorGREEN[9], vetorBLUE[9];

    Imagem *cpy = NULL;
    cpy = copiaImagem(img);

    for (int h = 1; h < obtemAltura(img)-1; h++) {
        for (int w = 1; w < obtemLargura(img)-1; w++) {
            Pixel pixel = obtemPixel(cpy, h, w);

            /*Armazena cada pixel dos seus vizinhos e seu mesmo*/
            Pixel pixelAux1 = obtemPixel(cpy,h-1,w-1);
            Pixel pixelAux2 = obtemPixel(cpy,h-1,w);
            Pixel pixelAux3 = obtemPixel(cpy,h-1,w+1);
            Pixel pixelAux4 = obtemPixel(cpy,h,w-1);
            Pixel pixelAux5 = obtemPixel(cpy,h,w);
            Pixel pixelAux6 = obtemPixel(cpy,h,w+1);
            Pixel pixelAux7 = obtemPixel(cpy,h+1,w-1);
            Pixel pixelAux8 = obtemPixel(cpy,h+1,w);
            Pixel pixelAux9 = obtemPixel(cpy,h+1,w+1);
             /*Armazena esses valores dos pixels em um vetor */
            vetorRED[0] = (int)pixelAux1.cor[RED];
            vetorRED[1] = (int)pixelAux2.cor[RED];
            vetorRED[2] = (int)pixelAux3.cor[RED];
            vetorRED[3] = (int)pixelAux4.cor[RED];
            vetorRED[4] = (int)pixelAux5.cor[RED];
            vetorRED[5] = (int)pixelAux6.cor[RED];
            vetorRED[6] = (int)pixelAux7.cor[RED];
            vetorRED[7] = (int)pixelAux8.cor[RED];
            vetorRED[8] = (int)pixelAux9.cor[RED];

            vetorGREEN[0] = (int)pixelAux1.cor[GREEN];
            vetorGREEN[1] = (int)pixelAux2.cor[GREEN];
            vetorGREEN[2] = (int)pixelAux3.cor[GREEN];
            vetorGREEN[3] = (int)pixelAux4.cor[GREEN];
            vetorGREEN[4] = (int)pixelAux5.cor[GREEN];
            vetorGREEN[5] = (int)pixelAux6.cor[GREEN];
            vetorGREEN[6] = (int)pixelAux7.cor[GREEN];
            vetorGREEN[7] = (int)pixelAux8.cor[GREEN];
            vetorGREEN[8] = (int)pixelAux9.cor[GREEN];

            vetorBLUE[0] = (int)pixelAux1.cor[BLUE];
            vetorBLUE[1] = (int)pixelAux2.cor[BLUE];
            vetorBLUE[2] = (int)pixelAux3.cor[BLUE];
            vetorBLUE[3] = (int)pixelAux4.cor[BLUE];
            vetorBLUE[4] = (int)pixelAux5.cor[BLUE];
            vetorBLUE[5] = (int)pixelAux6.cor[BLUE];
            vetorBLUE[6] = (int)pixelAux7.cor[BLUE];
            vetorBLUE[7] = (int)pixelAux8.cor[BLUE];
            vetorBLUE[8] = (int)pixelAux9.cor[BLUE];
            /*Ordena os valores em ordem crescente */
            int aux=0;
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    if (vetorRED[i] < vetorRED[j]){
                        aux = vetorRED[i];
                        vetorRED[i]=vetorRED[j];
                        vetorRED[j]=aux;
                    }
                }
            }
            /*Ordena os valores em ordem crescente */
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    if (vetorGREEN[i] < vetorGREEN[j]){
                        aux = vetorGREEN[i];
                        vetorGREEN[i]=vetorGREEN[j];
                        vetorGREEN[j]=aux;
                    }
                }
            }
            /*Ordena os valores em ordem crescente */
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    if (vetorBLUE[i] < vetorBLUE[j]){
                        aux = vetorBLUE[i];
                        vetorBLUE[i]=vetorBLUE[j];
                        vetorBLUE[j]=aux;
                    }
                }
            }
            /*Pega o valor do pixel nessas posições*/
            auxRED = vetorRED[4];
            auxGREEN = vetorGREEN[7];
            auxBLUE = vetorBLUE[0];


            auxRED =   (auxRED)   < 0 ? 0 : auxRED;
            auxGREEN = (auxGREEN) < 0 ? 0 : auxGREEN;
            auxBLUE =  (auxBLUE)  < 0 ? 0 : auxBLUE;
            auxRED =   (auxRED)   > 255 ? 255 : auxRED;
            auxGREEN = (auxGREEN) > 255 ? 255 : auxGREEN;
            auxBLUE =  (auxBLUE)  > 255 ? 255 : auxBLUE;

            pixel.cor[RED]   = auxRED;
            pixel.cor[GREEN]   = auxGREEN;
            pixel.cor[BLUE]   = auxBLUE;
            recolorePixel(img, h, w, pixel);

            }
    }
    liberaImagem(cpy);
}

