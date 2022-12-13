/*
=========================================================================================
AUTORES: 	
			Henrique Almeida de Oliveira
			
Disciplina: Topicos de Programacao Avancada

Biblioteca de BINARIO
=========================================================================================
*/

#ifndef BINARIO_H_
#define BINARIO_H_

/*
=========================================================================================
			Tipo Abstrato de Dados
*/

typedef struct NoTree TTree;

typedef struct NoTree{
	int value;
	TTree *esq, *dir;
}TTree;

typedef char string[40];

typedef struct tipoSentinel {
	int total;
	TTree* root;
}TSentinel;

// Funcoes padrao
int menu();
void limparBuffer();

// FunÃ§Ã£o de Lista SEABB
void initializeSentinel(TSentinel *L); // inicia uma lista com raiz nula
void insertTree(TSentinel *L); // insere um registro a partir da entrada padrÃ£o
void printDepthFirst(TSentinel *L); //percurso em profundidade
void printInOrder(TSentinel *L); //percurso in order
void printPosOrder(TSentinel *L); //percurso pos order
void removeTree(TSentinel *L); //remove um valor da arvore
void searchValue(TSentinel *L); //procura um valor na arvore
void automatico(TSentinel *L); //adiciona valores padrao na arvore [12,5,1,2,15,25]

#endif // BINARIO_H_
