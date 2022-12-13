/*
=========================================================================================
AUTORES: 	
			Henrique Almeida de Oliveira
			
Disciplina: Topicos de Programacao Avancada

Implementacao da biblioteca BINARIO
=========================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include "binario.h"
/*
=========================================================================================
			Implementacao
*/

TTree *digThrowTree(TTree* node, int v); //funcao de busca

void initializeSentinel(TSentinel *L){
	L->root = NULL;
	L->total = 0;
}

void initializeTree(TTree* no, int add){
    no->value = add;
	no->esq = NULL;
	no->dir = NULL;
}


void insereNaArvore(TTree **node, TTree* insert){
	if((*node)==NULL){
		(*node) = insert;
	}else if( insert->value > (*node)->value ){
		insereNaArvore(&(*node)->dir, insert);
	}else {
		insereNaArvore(&(*node)->esq, insert);
	}
}

// Funcao para inserir um registro
void insertTree(TSentinel *L){
	int reg;
	TTree* valid;

	printf("\nDigite o numero para adicionar: ");
	scanf("%d", &reg);
	
	// verifica se já não existe o valor passado na árvore
	valid = digThrowTree(L->root, reg); 
	TTree *no = (TTree *)malloc(sizeof(TTree));
	
	// coloca o no na arvore
    initializeTree(no, reg);
 	
	if (valid==NULL) {
		insereNaArvore(&(L->root), no);
		L->total++;
	}
	else printf("Valor ja existe na arvore");
	
}

void printDepth(TTree* node){
	if(node==NULL) return; 	 
	printf("- %d ", node->value);
	printDepth(node->esq);
	printDepth(node->dir);
}

void printDepthFirst(TSentinel *L){
	
	printf("\n============================");
	printf("\n Percurso em Pre-Ordem");
	printf("\n============================\n");

	TTree* node = L->root;
	printDepth(node);
}

void printIn(TTree* node){
	if(node==NULL) return; 	 
	printIn(node->esq);
	printf("- %d ", node->value);
	printIn(node->dir);
}

void printInOrder(TSentinel *L){
	
	printf("\n================================================\n");
	printf("\n Percurso In Order");
	printf("\n================================================\n\n");

	TTree* node = L->root;
	printIn(node);
	printf("\n\n================================================\n\n");
}

void printPos(TTree* node){
	if(node==NULL) return; 	 
	printPos(node->esq);
	printPos(node->dir);
	printf("- %d ", node->value);
}

void printPosOrder(TSentinel *L){
	
	printf("\n============================");
	printf("\n Percurso Pos Order");
	printf("\n============================\n");

	TTree* node = L->root;
	printPos(node);
}

//subfuncao de removerGeral utilizada para pegar o nÃƒÂ³ mais a direita da subarvore esquerda do nÃƒÂ³ que serÃƒÂ¡ removido
TTree *raizDireita(TTree **no){
	if ((*no)->dir != NULL){
		return raizDireita(&(*no)->dir);
	} else {
		TTree *aux = (*no);
		if ((*no)->esq != NULL)
			*no = (*no)->esq;
		else
			(*no) = NULL;
	return aux;
	}
}

// subfuncao de removeTree
TTree* removerArvore(TTree **nodo, int valorNovo){
	if((*nodo) == NULL){
		return NULL;
	}else if((*nodo)->value > valorNovo){
		(*nodo)->esq = removerArvore(&(*nodo)->esq, valorNovo);
	}else if((*nodo)->value < valorNovo){
		(*nodo)->dir = removerArvore(&(*nodo)->dir, valorNovo);
	}else{
		if((*nodo)->dir == NULL && (*nodo)->esq == NULL){
			free((*nodo));
			(*nodo) = NULL;
		}else if((*nodo)->esq == NULL){
			TTree *temporario = (*nodo);
			(*nodo) = (*nodo)->dir;
			free(temporario);
		}else if((*nodo)->dir == NULL){
			TTree *temporario = (*nodo);
			(*nodo) = (*nodo)->esq;
			free(temporario);
		}else{
			TTree *prov = (*nodo)->esq;
			while(prov->dir != NULL){
				prov = prov->dir;
			}
			(*nodo)->value = prov->value;
			prov->value = valorNovo;
			
			(*nodo)->esq = removerArvore(&(*nodo)->esq, valorNovo);
		}
	}
	
	return (*nodo);
}

void removeTree(TSentinel *L){
	int reg;
	TTree *node = L->root;

	printf("\nDigite o numero para apagar: ");
	scanf("%d", &reg);

	L->root = removerArvore(&node, reg);
	L->total--;
	if(L->total==0) L->root==NULL;
	//return L->root;
}

// SubfunÃ§Ã£o de procuraValor, recursiva, retorna struct tree encontrada
TTree *digThrowTree(TTree* node, int v){
	TTree *x;

	if(node!=NULL) x = node;

	if (node==NULL){
		return NULL;
	}else if(x->value == v){
		return x;
	}else if(x->value>v){
		digThrowTree(node->esq, v);
	}else{
		digThrowTree(node->dir, v);
	}
}

void searchValue(TSentinel *L){

	TTree *aux = L->root;
	int valor;

	if(aux == NULL){
		printf("\nArvore Vazia!");
	}else{
		printf("\nQual valor deseja procurar?\n> ");
		scanf("%d", &valor);
		TTree *x = digThrowTree(aux, valor);

		if (x==NULL){
			printf("\nNao encontrado!");
		}else{
			printf("\nEncontrado!");
			printf("\n%d", x->value);
		}
	}
}

void insereAuto(TTree **root, int reg){
	
	TTree *no = (TTree *)malloc(sizeof(TTree));
    initializeTree(no, reg);

	insereNaArvore(root, no);
}

void automatico(TSentinel *L){
	insereAuto(&(L->root), 12);
	insereAuto(&(L->root), 5);
	insereAuto(&(L->root), 1);
	insereAuto(&(L->root), 2);
	insereAuto(&(L->root), 15);
	insereAuto(&(L->root), 25);
}
