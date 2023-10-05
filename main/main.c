/*      Trabalho realizado por:
    Gustavo Fernandez Vidal Vazquez - 537296
    Lucas Rodrigues Aragão - 538390

OBSERVAÇÕES: 
1) No arquivo de teste enviado pelo professor, há um erro na saída do tempo médio, em vez de 'clientes Leezu' está escrito 'clientes Comuns'

2) Em alguns casos de teste, o arquivo gerado pelo meu programa difere do arquivo gerado pelo professor nas casas decimais na linha "Tempo medio de espera dos  clientes..."
A diferença é mínima e de díficil ajuste pois precisariamos saber como o programa que gerou os arquivos de teste fez as divisões com 'float'.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "escalonador.h"
#include "fila_fifo.h"
#include "logtree.h"


int main(int narg, char *argv[]){
    Escalonador *e = malloc(sizeof(Escalonador));
    char namein[20] = "entrada-", nameout[20] = "saida-";
    int n;
    n = atoi(argv[1]);
    if (n < 10){   // Série de tratamento para ler o arquivo "entrada-... .txt e saida-... .txt"
        strcat(namein, "000");
        strcat(nameout, "000");
        strcat(namein, argv[1]);
        strcat(nameout, argv[1]);
        strcat(nameout, ".txt");
        strcat(namein, ".txt");
    }   
    else if (n < 100){
        strcat(nameout, "00");
        strcat(namein, "00");
        strcat(namein, argv[1]);
        strcat(nameout, argv[1]);
        strcat(nameout, ".txt");
        strcat(namein, ".txt");
    }
    else if (n < 1000){
        strcat(nameout, "0");
        strcat(namein, "0");
        strcat(namein, argv[1]);
        strcat(nameout, argv[1]);
        strcat(nameout, ".txt");
        strcat(namein, ".txt");
    }
    else {
        strcat(nameout, argv[1]);
        strcat(namein, argv[1]);
        strcat(namein, ".txt");
        strcat(nameout, ".txt");
    }

    
    if (e_conf_por_arquivo(e, namein) == 1) // Se for possível realizar a configuração por arquivo
        e_rodar(e, namein, nameout); 

    return EXIT_SUCCESS;

}