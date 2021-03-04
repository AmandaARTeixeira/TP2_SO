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
void vector_push(struct Vector* vec, int data) {
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
struct Node* remove_data_from_vector(struct Vector* vec, int data) {
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

/* Elimina o primeiro item do vetor com o bit zero e seta os bits pelo qual ele passou
 * para zero
 *  
 * @param: vec é o vetor do qual será removido o elemento;
 * @return: nó que foi removido;
 *
 */
struct Node* remove_first_bit_zero_from_vector(struct Vector* vec) {
	struct Node* current = vec->head;
	struct Node* previous = NULL;

	if(vec->head == NULL) {
		return NULL;
	}

	while(current->bit > 0) {

		if(current->next == NULL) {
			current = vec->head;
		} else {
			previous = current;
			previous->bit = 0;
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

/* Elimina um item do vetor
 *  
 * @param: vec é o vetor do qual o vetor será atualizado o elemento;
 * data é o valor do nó a ser removido;
 * @return: retorna 1 se o nó existir e 0 se não
 *
 */
int set_node_bit_to_one(struct Vector* vec, int data) {
	struct Node* current = vec->head;
	struct Node* previous = NULL;

	if(vec->head == NULL) {
		return 0;
	}

	while(current->data != data) {

		if(current->next == NULL) {
			return 0;
		} else {
			previous = current;
			current = current->next;
		}
	}

	current->bit = 0;

	return 1;
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
		printf("%d\n", aux->data);

		aux = aux->next;
	}
}
