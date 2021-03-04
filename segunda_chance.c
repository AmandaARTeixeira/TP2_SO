#include <stdio.h>
#include <stdlib.h>
#include "page_table.h"
#include "vector.h"

struct Vector* vec_2a;

/* Algoritmo 2a para escolher a pagina a ser substituida
 * @return: o número do frame que sera desalocado
 */
int segunda_chance_replace() {
    struct Node* node = remove_first_bit_zero_from_vector(vec_2a);

    return node->data;
}


/* Algoritimo utilizado para colocar o frame_number do final da fila assim que
 * ele for acessado para que o primeiro da fila sempre seja o último usado
 * @param: a página com o número da memória física utilizada.
 */
void segunda_chance_ref(page_table_item *p) {
	// Se o frame_number estiver no vetor seta seu bit para 1 e se não coloca ele 
	// na fila
	if(set_node_bit_to_one(vec_2a, p->frame_number) == 0) {
		vector_push(vec_2a, p->frame_number);
	}

	return;
}

// Inicializa o vetor
void segunda_chance_init() {
	vec_2a = init_vector();
}