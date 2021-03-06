#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "tp2virtual.h"
#include "page_table.h"


extern int num_frames;
extern frame* frames_list;

/* A página a ser removida é escolhida usando o algoritmo rand. 
 * Retorna o número do quadro da página (que também é o índice 
 * na frames_list) da página a ser despejada.
 */
int rand_replace() {
	// escolha o índice na frame_list para remover uma página
	int idx = (int)(random() % num_frames);
	
	return idx;
}

// Esse algoritimo não precisa dessa função. Elas estão ai apenas para compatibilidade.
void rand_ref(page_table_item *p) {
	return;
}

void rand_init() {
}
