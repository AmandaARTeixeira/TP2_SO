#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 

// Numero de bits de um endereco
#define N_BITS_ADDR	32

extern unsigned s; // Numero de bits a serem descartados para identificar a pagina de um endereco
extern unsigned num_pages; // Numero total de paginas armazenadas na tabela
extern unsigned page_size;	// Tamanho de cada pagina em bytes

typedef unsigned long addr;	// Tipo para armazenar enderecos

typedef struct {
	short int valid; // 1 se o frame estiver na memória, se não, é igual a 0.
	short int dirty; // 1 se o frame tiver sido modificado desde que foi carregado na memória, 0 caso contrario.
	short int on_swap;	// 1 se o frame estiver no disco para swap, 0 caso contrário.
	int frame_number;	// Numero do frame.
} page_table_item;

typedef struct {
	short int allocated; // 1 se o frame estiver alocado na memória física, 0 caso contrário
	page_table_item *p;	// Ponteiro para a entrada correspondente na tabela de páginas
} frame;

/* A estrutura a seguir lista os frames (páginas físicas) presentes na memória física,
*  indicando se os mesmos estão ou não mapeados para alguma página virtual.
*  O índice de cada frame é o número que o identifica na tabela de páginas.
*/
extern frame* frames_list;

// Tabela de paginas
extern page_table_item* page_table;			

// Função para inicializar a lista de frames
void init_frames_list(unsigned phys_mem_size, unsigned page_size);

// Função para inicializar a tabela de páginas
void init_page_table(unsigned page_size_kb);

// Função para traduzir endereco logico e buscar um frame
unsigned get_frame(addr v_addr, char type);

// Funções para desalocar as estruturas
void destroy_page_table();
void destroy_frames_list();

// A seguir estão protótipos de funções que serão utilizadas pelos algoritmos
// de substituição.
extern void rand_ref(page_table_item *);
extern void lru_ref(page_table_item *);
extern void clock_ref(page_table_item *);
extern void fifo_ref(page_table_item *);

extern int rand_replace();
extern int lru_replace();
extern int clock_replace();
extern int fifo_replace();

extern void rand_init();
extern void lru_init();
extern void clock_init();
extern void fifo_init();

// Funcoes auxiliares
void set_page_size(int page_size_kb);
void set_s();
void set_num_pages();
int find_free_frame();
void print_page_table();

#endif 