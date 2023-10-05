#include <stdio.h>
#include <stdlib.h>
#include "fila_fifo.h"

void f_inicializar (Fila_FIFO **f){
    *f = NULL;
}

int f_inserir (Fila_FIFO **f, int chave, int valor){
    Fila_FIFO *temp, *new = malloc(sizeof(Fila_FIFO));
    int i = 0;
    if (new){ // Só entra aqui se new for diferente de NULL
        new -> chave = chave;
        new -> valor = valor;
        new -> prox = NULL;
        if (*f == NULL){ // Caso a fila esteja vazia
            *f = new;
        }
        else {
            temp = *f;
            while (temp -> prox != NULL){
                temp = temp -> prox;
                if (temp -> chave == chave)
                    return(0); // Se houver uma chave igual
            }
            temp -> prox = new;
        }
        return(1);
    }
    return(0); 
}
    

int f_obter_proxima_chave (Fila_FIFO **f){ //Basicamente o "Enqueue"
    int key;
    if (*f != NULL){ // Só entra se há elementos na fila
        key = (*f) -> chave;
        *f = (*f) -> prox;
        return(key);
    }
    return(-1);
}


int f_consultar_proxima_chave (Fila_FIFO **f){ // O mesmo da função anterior, mas não remove o elemento
    int key;
    if (*f != NULL){ // Só entra se há elementos na fila
        key = (*f) -> chave;
        return(key);
    }
    return(-1);
}


int f_consultar_proximo_valor (Fila_FIFO **f){
    int val;
    if (*f != NULL){ // Só entra se há elementos na fila
        val = (*f) -> valor;
        return(val);
    }
    return(-1);
}


int f_num_elementos (Fila_FIFO **f){
    Fila_FIFO *temp = *f;
    int i = 1;
    if (*f != NULL){
        while (temp -> prox != NULL){
            temp = temp -> prox;
            i++;
        }
        return(i);
    }
    return(0); // Caso a fila esteja vazia (*f == NULL)
}


int f_consultar_chave_por_posicao (Fila_FIFO **f, int posicao){
    int val, i = 1;
    Fila_FIFO *temp = *f;

    if (posicao == 1)
        return((*f) -> chave);

    while (temp != NULL){
        if (posicao == i){
            return (temp -> chave);
        }
        temp = temp -> prox;
        i++;
    }
    return(-1);
}


int f_consultar_valor_por_posicao (Fila_FIFO **f, int posicao){
    int i = 1;
    Fila_FIFO *temp = *f;

    if (posicao == 1)
        return((*f) -> valor);

    while (temp != NULL){
        if (posicao == i){
            return (temp -> valor);
        }
        temp = temp -> prox;
        i++;
    }
    return(-1);
}
