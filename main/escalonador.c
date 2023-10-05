#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "escalonador.h"
#include "fila_fifo.h"
#include "logtree.h"

void e_inicializar (Escalonador *e, int caixas, int delta_t, int n_1, int n_2, int n_3, int n_4, int n_5){
    e -> caixas = caixas;
    e -> delta_t = delta_t;
    e -> n_1 = n_1;
    e -> n_2 = n_2;
    e -> n_3 = n_3;
    e -> n_4 = n_4;
    e -> n_5 = n_5; 
    e -> d1 = n_1; // d1, d2, d3, d4, d5 servirão como disciplinas de atendimento "temporárias" que terão seu valor alterado conforme o programa
    e -> d2 = n_2; // atribui clientes para cada fila.
    e -> d3 = n_3;
    e -> d4 = n_4;
    e -> d5 = n_5;
}

int e_inserir_por_fila (Escalonador *e, int classe, int num_conta, int qtde_operacoes){ // Caso a classe seja 1, insere na primeira fila... 
    if (classe == 1)
        f_inserir(&(e -> f1), num_conta, qtde_operacoes); 
    else if (classe == 2)
        f_inserir(&(e -> f2), num_conta, qtde_operacoes);
    else if (classe == 3)
        f_inserir(&(e -> f3), num_conta, qtde_operacoes);
    else if (classe == 4)
        f_inserir(&(e -> f4), num_conta, qtde_operacoes);
    else if (classe == 5)
        f_inserir(&(e -> f5), num_conta, qtde_operacoes);
    else 
        return(0);
}


int e_consultar_prox_fila(Escalonador *e){ // A partir daqui as funções são bem semelhantes e usam da disciplina de atendimento temporaria "dn", para consultar algo do próximo cliente. 
    if (e_consultar_qtde_clientes(e) == 0)
        return(-1);
    if (e -> d1 != 0 && f_num_elementos(&(e -> f1)) != 0)
        return(1);
    if (e -> d2 != 0 && f_num_elementos(&(e -> f2)) != 0)
        return(2);
    if (e -> d3 != 0 && f_num_elementos(&(e -> f3)) != 0)
        return(3);
    if (e -> d4 != 0 && f_num_elementos(&(e -> f4)) != 0)
        return(4);
    if (e -> d5 != 0 && f_num_elementos(&(e -> f5)) != 0)
        return(5);
    else{ 
        e -> d1 = e -> n_1;
        e -> d2 = e -> n_2;
        e -> d3 = e -> n_3;
        e -> d4 = e -> n_4;
        e -> d5 = e -> n_5;
        return(e_consultar_prox_fila(e));
    } 
}


int e_obter_prox_num_conta(Escalonador *e){   
    if (e_consultar_qtde_clientes(e) == 0)
        return(-1);

    if (e -> d1 != 0 && f_num_elementos(&(e -> f1)) != 0){  // Após obter cada "próximo da fila", tiramos 1 da disciplina de atendimento temporária criada.
        (e -> d1)--;
        return(f_obter_proxima_chave(&(e -> f1)));
    }
    if (e -> d2 != 0 && f_num_elementos(&(e -> f2)) != 0){
        (e -> d2)--;
        return(f_obter_proxima_chave(&(e -> f2)));
    }
    if (e -> d3 != 0 && f_num_elementos(&(e -> f3)) != 0){
        (e -> d3)--;
        return(f_obter_proxima_chave(&(e -> f3)));
    }
    if (e -> d4 != 0 && f_num_elementos(&(e -> f4)) != 0){
        (e -> d4)--;
        return(f_obter_proxima_chave(&(e -> f4)));
    }
    if (e -> d5 != 0 && f_num_elementos(&(e -> f5)) != 0){
        (e -> d5)--;
        return(f_obter_proxima_chave(&(e -> f5)));
    }
    else{   // Caso todas as disciplinas temporárias forem nulas, significa que está na hora de retornar ao valor original.
        e -> d1 = e -> n_1;
        e -> d2 = e -> n_2;
        e -> d3 = e -> n_3;
        e -> d4 = e -> n_4;
        e -> d5 = e -> n_5;
        return(e_obter_prox_num_conta(e)); // Como tudo era nulo e foi retornado ao valor original, chamamos a função novamente para obter o valor de fato
    }
}


int e_consultar_prox_num_conta (Escalonador *e){ // d1, d2... é o digito que representa o mesmo valor de n1..., só que altera com o tempo, sendo usado para a disciplina de atendimento
    if (e_consultar_qtde_clientes(e) == 0)
        return(-1);
    if (e -> d1 != 0 && f_num_elementos(&(e -> f1)) != 0)
        return(f_consultar_proxima_chave(&(e -> f1)));
    if (e -> d2 != 0 && f_num_elementos(&(e -> f2)) != 0)
        return(f_consultar_proxima_chave(&(e -> f2)));
    if (e -> d3 != 0 && f_num_elementos(&(e -> f3)) != 0)
        return(f_consultar_proxima_chave(&(e -> f3)));
    if (e -> d4 != 0 && f_num_elementos(&(e -> f4)) != 0)
        return(f_consultar_proxima_chave(&(e -> f4)));
    if (e -> d5 != 0 && f_num_elementos(&(e -> f5)) != 0)
        return(f_consultar_proxima_chave(&(e -> f5)));      
    if (e_consultar_qtde_clientes(e) == 0)
        return (-1);
    e -> d1 = e -> n_1;
    e -> d2 = e -> n_2;
    e -> d3 = e -> n_3;
    e -> d4 = e -> n_4;
    e -> d5 = e -> n_5;
    e_consultar_prox_num_conta(e);  
}

int e_consultar_prox_qtde_oper (Escalonador *e){ 
    if (e_consultar_qtde_clientes(e) == 0)
        return(-1);
    if (e -> d1 != 0 && f_num_elementos(&(e -> f1)) != 0)
        return(f_consultar_proximo_valor(&(e -> f1)));
    if (e -> d2 != 0 && f_num_elementos(&(e -> f2)) != 0)
        return(f_consultar_proximo_valor(&(e -> f2)));
    if (e -> d3 != 0 && f_num_elementos(&(e -> f3)) != 0)
        return(f_consultar_proximo_valor(&(e -> f3)));
    if (e -> d4 != 0 && f_num_elementos(&(e -> f4)) != 0)
        return(f_consultar_proximo_valor(&(e -> f4)));
    if (e -> d5 != 0 && f_num_elementos(&(e -> f5)) != 0)
        return(f_consultar_proximo_valor(&(e -> f5)));       
    e -> d1 = e -> n_1;
    e -> d2 = e -> n_2;
    e -> d3 = e -> n_3;
    e -> d4 = e -> n_4;
    e -> d5 = e -> n_5;
    e_consultar_prox_qtde_oper(e);
}


int e_consultar_qtde_clientes (Escalonador *e){ // Retorna quantos clientes tem em cada fila
    return(f_num_elementos(&(e -> f1))+f_num_elementos(&(e -> f2))+f_num_elementos(&(e -> f3))+f_num_elementos(&(e -> f4))+f_num_elementos(&(e -> f5)));
}


int e_consultar_tempo_prox_cliente (Escalonador *e){
    if (e_consultar_qtde_clientes(e) == 0)
        return -1;
    return((e -> delta_t * e_consultar_prox_qtde_oper(e)));
}


int e_conf_por_arquivo(Escalonador *e, char *nome_arq_conf){
    FILE *arq;
    int caixas, delta_t, n_1, n_2, n_3, n_4, n_5, conta, operacoes, classe, i;
    char buffer[100], class[100];
    arq = fopen(nome_arq_conf, "rt");
    f_inicializar(&(e -> f1));
    f_inicializar(&(e -> f2));
    f_inicializar(&(e -> f3));
    f_inicializar(&(e -> f4));
    f_inicializar(&(e -> f5));
    log_inicializar(&(e -> l));

    if (arq == NULL) // Caso o arquivo esteja vazio...
        return 0;

    while (fgetc(arq) != '=');

    fgetc(arq);

    fscanf(arq, "%d", &(e -> caixas));      /*Como o arquivo recebido é nada agradável de se mexer, é preciso "ler" coisas inúteis para chegarmos nas informações que queremos
                                                nesse caso, é possível usar do formato do arquivo para ler estes caracteres inuteis.*/  
    while(fgetc(arq) != '=');
    fgetc(arq);
    
    fscanf(arq, "%d", &(e -> delta_t));
    
    while(fgetc(arq) != '{');

    fscanf(arq, "%d%*[, \t\n]", &(e -> n_1));
    fscanf(arq, "%d%*[, \t\n]", &(e -> n_2));
    fscanf(arq, "%d%*[, \t\n]", &(e -> n_3));
    fscanf(arq, "%d%*[, \t\n]", &(e -> n_4));
    fscanf(arq, "%d%*[, \t\n]", &(e -> n_5));   
    e -> d1 = e -> n_1;
    e -> d2 = e -> n_2;
    e -> d3 = e -> n_3;
    e -> d4 = e -> n_4;
    e -> d5 = e -> n_5;
    fgetc(arq);
    
    // Baseado na classe, inserimos os dados recebidos da linha na fila correspondente.
    while(fscanf(arq, "%s %s %s %d %s %d %s", class, buffer, buffer, &conta, buffer, &operacoes, buffer) != EOF){ 
        if (strcmp(class, "Premium") == 0)
            classe = 1;
        else if (strcmp(class, "Ouro") == 0)    
            classe = 2;
        else if (strcmp(class, "Prata") == 0)
            classe = 3;
        else if (strcmp(class, "Bronze") == 0)
            classe = 4;
        else if (strcmp(class, "Leezu") == 0)
            classe = 5;
        

        e_inserir_por_fila(e, classe, conta, operacoes);
        
    }
    fclose(arq);
    return 1;
}


void e_rodar (Escalonador *e, char *nome_arq_in, char *nome_arq_out){
   int cai[e -> caixas]; // Alocação de um vetor para representar o timer de cada caixa
   int conta, maior = 0, oper = 0, i, j, min = 0, classe, c1, c2, c3, c4, c5;
   int clientes_caixas[e -> caixas]; // Vetor para armazenar quantos clientes cada caixa atendeu
   float operclasse[5] = {0, 0, 0, 0, 0};
   char categoria[5][8] = {"Premium", "Ouro", "Prata", "Bronze", "Leezu"};
   FILE *arq = fopen(nome_arq_out, "wt");


   for (i = 0; i < e -> caixas; i++){ // Inicializa os contador dos caixas e os caixas
        clientes_caixas[i] = 0;
        cai[i] = 0;
   }



    while (e_consultar_qtde_clientes(e) != 0){
        for (j = 0; j < e -> caixas; j++){ // Percorremos todos os caixas e entramos no que está vazio.
            if (cai[j] == 0 && e_consultar_qtde_clientes(e) != 0){ // Perguntamos novamente se a quantidade de clientes é zero pois ela pode ter se tornado zero dentro do laço "para"
                clientes_caixas[j]++;
                cai[j] = e_consultar_tempo_prox_cliente(e);
                operclasse[e_consultar_prox_fila(e) - 1] += e_consultar_prox_qtde_oper(e);
                log_registrar(&(e -> l), e_consultar_prox_num_conta(e), e_consultar_prox_fila(e), min, j);
                fprintf(arq,"T = %d min: Caixa %d chama da categoria %s cliente da conta %d para realizar %d operacao(oes).\n",
                min, j + 1, categoria[e_consultar_prox_fila(e) - 1], e_consultar_prox_num_conta(e), e_consultar_prox_qtde_oper(e));
                e_obter_prox_num_conta(e);
            }
            cai[j]--; // Diminuindo o tempo total de cada caixa por interação
        }
        min++; // Adicionando as interações ao tempo total
    }
    for(j = 0; j < e -> caixas; j++){ // Ao final do código, para considerar o tempo de todos, precisamos adicionar último tempo que está no caixa (o maior deles)
        if (cai[j] > maior)
            maior = cai[j];
    }
    min += maior; // Adicionamos o "último tempo" ao tempo total
    c1 = log_obter_contagem_por_classe(&(e -> l), 1);
    c2 = log_obter_contagem_por_classe(&(e -> l), 2);
    c3 = log_obter_contagem_por_classe(&(e -> l), 3);
    c4 = log_obter_contagem_por_classe(&(e -> l), 4);
    c5 = log_obter_contagem_por_classe(&(e -> l), 5);

    // Parte final da inserção dos arquivos
    fprintf(arq, "Tempo total de atendimento: %d minutos.\n", min);
    fprintf(arq, "Tempo medio de espera dos %d clientes Premium: %.2f\n", c1, log_media_por_classe(&(e -> l), 1));
    fprintf(arq, "Tempo medio de espera dos %d clientes Ouro: %.2f\n", c2, log_media_por_classe(&(e -> l), 2));
    fprintf(arq, "Tempo medio de espera dos %d clientes Prata: %.2f\n", c3, log_media_por_classe(&(e -> l), 3));
    fprintf(arq, "Tempo medio de espera dos %d clientes Bronze: %.2f\n", c4, log_media_por_classe(&(e -> l), 4));
    fprintf(arq, "Tempo medio de espera dos %d clientes Leezu: %.2f\n", c5, log_media_por_classe(&(e -> l), 5));


    fprintf(arq, "Quantidade media de operacoes por cliente Premium = %.2f\n", operclasse[0] / c1);
    fprintf(arq, "Quantidade media de operacoes por cliente Ouro = %.2f\n", operclasse[1] / c2);
    fprintf(arq, "Quantidade media de operacoes por cliente Prata = %.2f\n", operclasse[2] / c3);
    fprintf(arq, "Quantidade media de operacoes por cliente Bronze = %.2f\n", operclasse[3] / c4);
    fprintf(arq, "Quantidade media de operacoes por cliente Leezu = %.2f\n", operclasse[4] / c5);

    for (i = 1; i <= e -> caixas; i++){
        fprintf(arq, "O caixa de número %d atendeu %d clientes.\n", i, clientes_caixas[i - 1]);
    }

    fclose(arq);    
    
}
