ALL:	main

main:	main.o escalonador.o logtree.o fila_fifo.o
		gcc main.o escalonador.o logtree.o fila_fifo.o -o main

main.o:	main.c escalonador.h 
		gcc -c main.c

fila_fifo.o:	fila_fifo.c fila_fifo.h
			gcc -c fila_fifo.c

logtree.o:	logtree.c logtree.h
			gcc -c logtree.c

escalonador.o:	escalonador.c escalonador.h fila_fifo.h logtree.h
		gcc -c escalonador.c

clean: 
		rm -f *.o main