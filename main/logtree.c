#include <stdio.h>
#include <stdlib.h>
#include "logtree.h"

void log_inicializar(Log **l){
    *l = NULL;
}

void log_registrar(Log **l, int conta, int classe, int timer, int caixa){
    Log *temp = *l;
    while(temp != NULL){
        if (classe < (temp -> classe))
            l = &(temp -> esq);
        else
            l = &(temp -> dir);
        temp = *l;
    }
    temp = malloc(sizeof(Log));
    temp -> timer = timer;
    temp -> conta = conta;
    temp -> classe = classe;
    temp -> caixa = caixa;
    temp -> esq = NULL;
    temp -> dir = NULL;
    *l = temp;
}

/* A função abaixo não utiliza a da soma e de quantidade
para evitar percorrer a árvore mais de uma vez.*/

float log_media_por_classe(Log **l, int classe){ 
    float cont = 0, sum = 0;
    Log *temp = *l;
    while(temp != NULL){
        if (classe < temp -> classe)
            temp = temp -> esq;
        else if (classe > temp -> classe)
            temp = temp -> dir;
        else if (classe == temp -> classe) { // Se a classe for igual, 
            sum += temp -> timer;
            temp = temp -> dir;
            cont++;
        }
    }
    if (cont != 0)
        return (sum / cont);
    return(-1); // Retorna -1 no caso que dividiria por 0.
}


int log_obter_soma_por_classe(Log **l, int classe){
    int sum = 0;
    Log *temp = *l;
    while(temp != NULL){
        if (classe < temp -> classe)
            temp = temp -> esq;
        else if (classe > temp -> classe)
            temp = temp -> dir;
        else if (classe == temp -> classe) { // Se a classe for igual, 
            sum += temp -> timer;
            temp = temp -> dir;
        }
    }
    return (sum);
}

int log_obter_contagem_por_classe(Log ** l, int classe){
    int cont = 0;
    Log *temp = *l;
    while(temp != NULL){
        if (classe < temp -> classe)
            temp = temp -> esq;
        else if (classe > temp -> classe)
            temp = temp -> dir;
        else if (classe == temp -> classe) { // Se a classe for igual, 
            temp = temp -> dir;
            cont++;
        }
    }
    return (cont);
}


