# include "tp2virtual.h"
# include "page_table.h"

unsigned s = 0;	// Número de bits a serem descartados para identificar a página de um endereço
unsigned num_pages = 0;	// Numero total de páginas armazenadas na tabela
unsigned page_size = 0;	// Tamanho de cada página em bytes
unsigned num_frames = 0; // Número de frames na memoria fisica
page_table_item* page_table = NULL;	// Tabela de páginas
frame* frames_list = NULL;	// Lista de frames

/* Inicializa a tabela de paginas
*  
*  @param: page_size_kb eh o tamanho de uma pagina em kbytes;
*
*/	
void init_page_table(unsigned page_size_kb) {
	
	// Inicializa parametros gerais. Chamadas devem ser feitas nessa ordem.
	set_page_size(page_size_kb);
	set_s();
	set_num_pages();
	// Preenche a tabela
	page_table = (page_table_item*) malloc( (num_pages+1) * sizeof(page_table_item));

	int i;
	for (i = 0; i < num_pages; i++) {
		page_table[i].valid = 0;
		page_table[i].dirty = 0;
		page_table[i].on_swap = 0;
		page_table[i].frame_number  = 0;
	}	
}

/* Inicializa a lista de frames
*  
*  @param: page_table phys_mem_size;
*  num_pages é o numero total de paginas. 	 
*
*/	
void init_frames_list(unsigned phys_mem_size, unsigned page_size) {
	num_frames = phys_mem_size / page_size;	

	frames_list = (frame*) malloc( (num_frames+1) * sizeof(frame));
	int i;
	for (i = 0; i < num_frames; i++) {
		frames_list[i].allocated = 0;
		frames_list[i].p = NULL;
	}
}	

/* Seta o valor de page_size em bites
*
*  @param: page_size_kb eh o tamanho de cada pagina em kb
*/	
void set_page_size(int page_size_kb) {
	page_size =  page_size_kb * 1024;
}

/* Determina o valor de s, ou seja, o numero de bits a serem descartados
*  em um endereco virtual para identificar a pagina associada.
*/	
void set_s() {
	
	unsigned tmp;
	/* Derivar o valor de s: */
	tmp = page_size;
	s = 0;
	while (tmp>1) {
		tmp = tmp>>1;
		s++;
	}
}

// Determina o numero de paginas presentes na tabela
void set_num_pages() {
	num_pages = 2 << (N_BITS_ADDR-s);
}


/* Procura um frame livre. Caso encontrado, o associa a uma página virtual (p).
*  Caso não seja encontrado, chama o algoritmo de substituição, que define qual
*  frame será retirado da memória sua associação alterada.
*  
* @param: ponteiro para um item da tabela de páginas
* @return: número do frame associado à página
*
*/	
int allocate_frame(page_table_item *p) {
	
	int frame_idx = find_free_frame(); 
	
	if ( frame_idx == -1) {
		frame_idx = replace_function();
		
		// Pagina correspondente ao frame desalocado pela função de substituição
		page_table_item *replaced_pg = frames_list[frame_idx].p;
		
		if (replaced_pg->dirty) {
			dirty_counter++;
			replaced_pg->on_swap = 1; // Pagina so precisa ir pro swap se estava modificada
		} 
		
		replaced_pg->valid = 0;
		replaced_pg->dirty = 0;
	} 
	
	// Alocando o frame para a página apontada por p
	p->valid = 1;
	p->dirty = 0;
	p->on_swap = 0;
	p->frame_number = frame_idx;
	frames_list[frame_idx].allocated = 1;
	frames_list[frame_idx].p = p;
	
	return frame_idx;
}

/* Procura um frame livre na lista de frames
*
*  @return: se encontrado, retorna o numero do frame; 
*                 senão, retorna -1.
*
*/
int find_free_frame() {
	int idx = -1;
	int i;
	for (i = 0; i < num_frames; i++) {
		if (!frames_list[i].allocated) {
			idx = i;
			break;
		}
	}
	
	return idx;
}

// Destroi a tabela de paginas
void destroy_page_table() {
	free(page_table);
}


// Destroi a lista de frames
void destroy_frames_list() {
	free(frames_list);
}

/* A partir de um endereco virtual e da tabela de paginas, determina para qual 
*  frame na memoria esse endereco deve ser mapeado. Ao longo do processo, 
*  sao feitas algumas verificacoes.
* 
*  Caso a pagina correspondente esteja valida, nao ha nenhuma tarefa
*  adicional.
*
*  Caso a pagina correspondente esteja invalida e esteja em swap, a pagina
*  deve ser trazida de volta para a memoria principal.
* 
*  Caso a pagina correspondente esteja invalida e nao esteja em swap, isso 
*  significa que tal referencia eh a primeira para essa pagina. Nesse caso um 
*  novo frame eh alocado para a pagina
* 
*  @param: v_addr eh o endereco virtual e s eh o numero de bits utilizados para indexar
*				   a tabela de paginas.
*				   type indica se o acesso eh de leitura (R) ou escrita (W)
*  @return: o endereco fisico. (?)
*
*/
unsigned get_frame(addr v_addr, char type) {
	unsigned pg_idx = v_addr >> s;
	
	page_table_item* page = &page_table[pg_idx];
	page->logic_addr = v_addr;
	page->last_op = type;
	if (!(page->valid)) { // Página nao é valida, um frame deve ser alocado para ela
		faults_counter++;
	    allocate_frame(page);
	} 

	if (type == 'W') {
		page->dirty = 1;
	} 

	// Chamada para atualizar a referência necessária para o algoritmo de substituição
	ref_function(page);
	
	return page->frame_number;
}

// Imprime a tabela de páginas
void print_frames() {
	printf("Endereço Lógico\t|Última operação|Dirty bit\n");

	for (int i = 0; i < num_frames; ++i)
	{
		printf("%3lx   \t|%3c\t\t|%3d\t\n", frames_list[i].p->logic_addr, frames_list[i].p->last_op, frames_list[i].p->dirty);
	}
}	
	