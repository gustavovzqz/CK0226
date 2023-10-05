This project is a C program that simulates a queue system for a bank. The Cochinchina Bank needs a system to organize the queues for its cashiers. The bank has 10 cashiers, and each day, a different number of cashiers (from 1 to 10) are operational. There are 5 classes of customers, each identified by a number:

    Premium Customer
    Gold Customer
    Silver Customer
    Bronze Customer
    Leezu Customer

The bank wants to provide differentiated treatment to its most important customers, listed above in decreasing order of "importance." As a result, there are 5 distinct queues, depending on the customer's class.

Each customer who arrives at the bank is characterized by their account number (an integer), their account class (ranging from 1 to 5 as defined above), and the quantity (integer) of financial operations they wish to perform.

The bank follows a specific scheduling procedure for each round of service, using the following steps:

Step 1. Serve Premium customer(s), if any.
Step 2. Then serve Gold customer(s), if any.
Step 3. Then serve Silver customer(s), if any.
Step 4. Then serve Bronze customer(s), if any.
Step 5. Then serve Leezu customer(s), if any, and go back to the first step for the next round.

This set {Step 1; Step 2; Step 3; Step 4; Step 5} is called the "Service Discipline."

To determine which cashier serves the customer, each cashier has a timer. When a customer with "M" financial operations is about to be served, the timer is set to call another customer within "M * Δt" minutes, where "Δt" is the time required for the cashier to process each financial operation. Consider that the value of "Δt" is given as a parameter.

The program should be able to:

    Simulate the service of all customers in all queues following a predefined Service Discipline and using a predefined number of cashiers (between 1 and 10).
    Calculate the waiting time for all customers, identified by their account number. Waiting time is the time elapsed from the start of cashier service until the moment the customer is called to the counter.
    Monitor the occupancy of cashiers through individual timers for each cashier.
    Determine the elapsed time from the start of service for the first customer to the end of service for the last customer.

For each customer served, the program should display:

    The cashier who will serve the customer.
    The customer's account number.
    The customer's account class.
    The time it will take for the customer to be served for their desired number of financial operations.
    The time the customer waited to be served.

Finally, the program should display the total service time, which is the time elapsed from the start of service for the first customer to the end of service for the last customer.

Please note:

    The basic unit of time is a minute.
    Ignore the queuing times (formation of queues), calling times, and any other times that are not related to cashier service.
    Assume that there are no customers with duplicate account numbers.

Implementation Details

The program is divided into several parts:
Part I: FIFO Queue Data Structure

A FIFO (First In, First Out) queue data structure should be implemented using pointers and dynamic memory allocation. The queue stores integer values, and each value is associated with an integer key. There should be no duplicate keys in the queue. The following functions are part of this queue API:

    void f_inicializar (Fila_FIFO **f): Initializes the queue.
    int f_inserir (Fila_FIFO **f, int chave, int valor): Inserts an integer value indexed by a key into the queue. Returns 1 for successful insertion and 0 for any issues (duplicate key or lack of memory).
    int f_obter_proxima_chave (Fila_FIFO **f): Returns the key of the next element in the queue and removes it from the queue. Returns -1 if the queue is empty.
    int f_consultar_proxima_chave (Fila_FIFO **f): Returns the key of the element at the head of the queue without removing it.
    int f_consultar_proximo_valor (Fila_FIFO **f): Returns the value stored in the element at the head of the queue without removing it.
    int f_num_elementos (Fila_FIFO **f): Returns the number of elements in the queue.
    int f_consultar_chave_por_posicao (Fila_FIFO **f, int posicao): Returns the key of the element at the specified position in the queue. Returns -1 if the desired position does not exist. Position indexing starts from 1.
    int f_consultar_valor_por_posicao (Fila_FIFO **f, int posicao): Returns the value of the element at the specified position in the queue. Returns -1 if the desired position does not exist. Position indexing starts from 1.

Part II: Time Logger

A time logger is implemented using a Binary Search Tree (BST) data structure. The program's files for this part are "logtree.c" and "logtree.h". The following functions should be implemented:

    void log_inicializar(Log **l): Initializes the time logger.
    void log_registrar(Log **l, int conta, int classe, int timer, int caixa): Records the service time for an account with the specified account number, class, waiting time (timer), and cashier number (caixa).
    float log_media_por_classe(Log **l, int classe): Returns the average waiting time, in minutes, for customers in the specified class.
    int log_obter_soma_por_classe(Log **l, int classe): Returns the sum of waiting times for all customers in the specified class.
    int log_obter_contagem_por_classe(Log **l, int classe): Returns the number of customers served in the specified class.

Part III: Scheduler

A scheduler is developed to handle 5 different queues based on the specified service discipline. The program files for the scheduler are "escalonador.c" and "escalonador.h".
