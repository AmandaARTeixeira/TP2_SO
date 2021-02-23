#include <stdio.h>
#include <stdlib.h>
#include "page_table.h"

extern int num_frames;
extern frame* frames_list;

int counter; 



/* Algoritmo fifo para escolher a pagina a ser substituida
 * @return: o numero do frame que sera desalocado
 */
int fifo_replace() {
    int frame_number = counter;
    
	counter += 1;
    if (counter == num_frames){
        counter = 0;
    }
    
	return frame_number;
}

/* Funcao chamada para todo acesso a uma pagina, caso seja necessario
*  atualizar alguma informacao para que o algoritmo funcione corretamente.
 * @param: item da tabela de páginas correspondente.
 */
void fifo_ref(page_table_item *p) {
	return;
}

// Inicializa o contador
void fifo_init() {
    counter = 0;
}