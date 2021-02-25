#ifndef TP2_VIRTUAL_H
#define TP2_VIRTUAL_H
#include "page_table.h" 

extern int faults_counter; // Número de page faults
extern int dirty_counter; // Número de páginas sujas escritas no disco

// Variável para armazenar o conteúdo do arquivo de log
extern char *log_file;

// Estrutura para representar o algoritmo de substituição escolhido
// e suas funções auxiliares
struct replacement_alg {
	char *name;
	void (*init) (void); // Inicializa dados, caso necessário
	void (*ref) (page_table_item *); // Realiza alguma ação a cada referência a uma página
	int (*replace) (); // Seleciona a página que será substituida
};

extern void (*init_function) ();
extern void (*ref_function) (page_table_item *);
extern int (*replace_function) ();

#endif