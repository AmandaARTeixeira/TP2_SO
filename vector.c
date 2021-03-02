#include <stdlib.h>

#include "vector.h"

/* Inicializa o vetor
 *  
 * @return: vetor inicializado;
 *
 */
struct Vector* init_vector() {
	struct Vector* vec = (struct Vector *) malloc(sizeof(struct Vector));

	vec->head = NULL;
	vec->tail = NULL;
	vec->size = 0;

	return vec;
}

/* Coloca um elemento no final do vetor
 *  
 * @param: vec é o vetor no qual será inserido o elemento;
 * data é o valor do nó a ser colocado;
 *
 */
void vector_push(struct Vector* vec, void* data) {
	struct Node* node = (struct Node *)malloc(sizeof(struct Node));
	node->data = data;
	node->next = NULL;

	if(vec->head == NULL) {
		vec->tail = node;
		vec->head = node;
	} else {
		vec->tail->next = node;
		vec->tail = node;
	}

	vec->size++;
}

/* Elimina um item do vetor
 *  
 * @param: vec é o vetor do qual será removido o elemento;
 * data é o valor do nó a ser removido;
 * @return: nó que foi removido;
 *
 */
struct Node* remove_data_from_vector(struct Vector* vec, void* data) {
	struct Node* current = vec->head;
	struct Node* previous = NULL;

	if(vec->head == NULL) {
		return NULL;
	}

	while(current->data != data) {

		if(current->next == NULL) {
			return NULL;
		} else {
			previous = current;
			current = current->next;
		}
	}

	if(current == vec->head) {
		vec->head = vec->head->next;
	} else {
		previous->next = current->next;
	}

	vec->size--;

	return current;
}

/* Elimina um item do inicio do vetor
 *  
 * @param: vec é o vetor do qual será removido o elemento;
 * @return: nó que foi removido;
 *
 */
struct Node* vector_pop(struct Vector* vec) {
	struct Node* ref = vec->head;

	vec->head = vec->head->next;

	vec->size--;

	return ref;
}

/* Desaloca o vetor
 *  
 * @param: vec é o vetor a ser desalocado;
 *
 */
void free_vector(struct Vector* vec) {
	while(vec->size > 0) {
		Node *node = vector_pop(vec);

		free(node);
	}
}

/* Imprime os itens do do vetor (função de debug)
 *  
 * @param: vec é o vetor a ser imprimido;
 *
 */
void print_vector(struct Vector* vec) {
	struct Node* aux = vec->head;

    printf("Vetor:\n");

	while(aux != NULL) {
		printf("%p\n", aux->data);

		aux = aux->next;
	}
}
