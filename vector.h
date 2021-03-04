#ifndef VECTOR
#define VECTOR

#include <stdio.h>

// Nó do vetor armazena os dados dele e um ponteiro para o próximo nó
typedef struct Node {
	int data; // Para guardar o número da frame
	int bit; // Armazena se a frame possui uma segunda chance ou não 
			 // (1 caso possua e 0 caso não possua)
	struct Node* next;
} Node;


typedef struct Vector {
	struct Node* head; // Armazena o nó inicial do vetor
	struct Node* tail; // Armazena o nó final do vetor
	size_t size; // Armazena o tamanho do vetor	
} Vector;

// Inicializa o vetor
struct Vector* init_vector();

// Insere um elemento no inicio do vetor
void vector_push(struct Vector* vec, int data);

// Remove o elemento com o valor dado 
struct Node* remove_data_from_vector(struct Vector* vec, int data);

// Remove o primeiro item do vetor
struct Node* vector_pop(struct Vector* vec);

// Remove o primeiro item do vetor cujo bit é zero
struct Node* remove_first_bit_zero_from_vector(struct Vector* vec);

// Seta o bit do nó cujo valor é data para 1
int set_node_bit_to_one(struct Vector* vec, int data);

// Desaloca o vetor
void free_vector(struct Vector* vec);

// Imprime os elementos do vetor (para debug)
void print_vector(struct Vector* vec);

#endif