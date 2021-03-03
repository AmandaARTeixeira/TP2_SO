#include <stdio.h>
#include <stdlib.h>
#include "page_table.h"
#include "vector.h"

struct Vector* vec;

/* Algoritmo lru para escolher a pagina a ser substituida
 * @return: o número do frame que sera desalocado
 */
int lru_replace() {
    struct Node* node = vector_pop(vec);

    return node->data;
}


/* Algoritimo utilizado para colocar o frame_number do final da fila assim que
 * ele for acessado para que o primeiro da fila sempre seja o último usado
 * @param: a página com o número da memória física utilizada.
 */
void lru_ref(page_table_item *p) {
	// Se o frame_number estiver no vetor retira ele para colocar no fim da fila
	remove_data_from_vector(vec, p->frame_number);

	// Coloca o frame_number no fim da fila
	vector_push(vec, p->frame_number);

	return;
}

// Inicializa o vetor
void lru_init() {
	vec = init_vector();
}