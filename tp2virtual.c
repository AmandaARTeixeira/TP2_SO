#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>

#include "tp2virtual.h"
#include "page_table.h"

// Definindo globais declaradas em tp2virtual.h e page_table.h
int faults_counter = 0;		
int dirty_counter = 0; 
char *log_file = NULL;

// Variáveis para contar o número de páginas lidas e escritas
int read_count = 0;
int write_count = 0;
 
 // Array para mapear o nome do algoritmo ao nome das funções
int num_algs = 4;
struct replacement_alg algs[] = {
	{"rand", rand_init, rand_ref, rand_replace},
	{"2a", segunda_chance_init, segunda_chance_ref, segunda_chance_replace},
	{"lru", lru_init, lru_ref, lru_replace}, 
	{"fifo", fifo_init, fifo_ref, fifo_replace}
};

// Declarando funções
void (*init_function) () = NULL;
void (*ref_function) (page_table_item *) = NULL;
int (*replace_function) () = NULL;
	
// Função para leitura do arquivo e acessos a memoria
void execute(FILE *log) {
	unsigned v_addr;
	char rw;

	while (fscanf(log,"%x %c",&v_addr,&rw)!=EOF)  {
		get_frame(v_addr, rw);

		if(rw == 'W') {
			write_count++;
		} else if(rw == 'R') {
			read_count++;
		}
	}
	
}

int main(int argc, char *argv[]) {
	int opt;
	
	if(argc != 6) {
	
		FILE *file = stdin;

		char *alg = NULL;
		unsigned page_size = 0;
		unsigned mem_size = 0;

		alg = argv[1];
		log_file = argv[2];
		sscanf (argv[3],"%d", &page_size);
		sscanf (argv[4],"%d", &mem_size);

		if(log_file != NULL) {
			if((file = fopen(log_file, "r")) == NULL) {
				printf("Erro ao abrir o arquivo de entrada");
				exit(1);
			}
		}

		// Initializa a page_table e a frames_list
		init_page_table(page_size);
		init_frames_list(mem_size, page_size);

		// Inicializando funções do algoritmo de substituição
		int i;
		for (i = 0; i < num_algs; i++) {
			if(strcmp(algs[i].name, alg) == 0) {
				init_function = algs[i].init;
				ref_function = algs[i].ref;
				replace_function = algs[i].replace;
				break;
			}
		}

		if(i >= num_algs) {
			printf("Esse algorítimo não foi implementado\n");

			exit(1);
		}

		// Inicializa o algoritmo de substituição
		init_function();

		execute(file);

		// Imprime as informações necessárias
		printf("\nArquivo de entrada: %s\n", log_file);
		printf("Tamanho da memória: %d KB\n", mem_size);
		printf("Tamanho das páginas: %d KB\n", page_size);
		printf("Tecnica de reposição: %s\n", alg);
		printf("Total de acessos a memória: %d\n", (read_count + write_count));
		printf("Páginas lidas: %d\n", read_count);
		printf("Páginas escritas: %d\n", write_count);
		printf("Page faults:  %d\n", faults_counter);
		printf("Páginas sujas: %d\n\n", dirty_counter);

		// Imprime a tabela final
		print_frames();

		// Desaloca as estruturas
		destroy_page_table();
		destroy_frames_list();
		

		} else {
			// Se o número de argumentos estiver errado avisa como se usa o tp
			printf("USAGE: tp2virtual algoritimo nome_arquivo tamanho_pagina tamanho_memoria\n");
			exit(1);
		}

	return 0;
}