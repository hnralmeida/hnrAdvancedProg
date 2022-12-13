/*
=========================================================================================
AUTOR:	Henrique Almeida de Oliveira
Disciplina: Topicos de Programacao Avancada

					Trabalho 01 � Tabela Hash

Implementacao de lista.h
=========================================================================================
*/

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include "hashopen.h"

/*
=========================================================================================
			Implementacao de lista.h
*/

unsigned long long int calcSize(FILE* f){
	unsigned long long int i=0;
	char s[40];

	// Move o cursor para o inicio do arquivo
	fseek(f, 0, SEEK_SET);

	// Percorre todas linhas do arquivo e adiciona 1 no contador 
	// para cada linha percorrida
	while (!feof(f)){
      	fscanf(f, " %[^\n]s", s);
    	i++;
  	}//while

	// Move o cursor para o inicio do arquivo
	fseek(f, 0, SEEK_SET);

	return i;
}

void initializeDB(hashTable *list, FILE* f){
	unsigned long long int reg, i=0;
	
	// Percorre todo arquivo pegando dados do aluno
	while (!feof(f)){
		// Toda linha eh o numero de uma matricula
		fscanf(f, "%llu", &reg);
		addIn(list, reg);
  	}//while
}

void initializeList(hashTable *list, unsigned long long int size){
	list->size = size;
	list->total = 0;
	list->vetor = (Tnode**) malloc( size * sizeof(Tnode*) );
	for(unsigned long long int i=0; i<size; i++) list->vetor[i] = NULL;
}

unsigned long long int rehash(hashTable *list, unsigned long long int reg, unsigned long long int index){
	unsigned long long int h1 = 1 + (reg% (list->size - 1) );
	unsigned long long int rh = (index + h1) % (list->size);
	Tnode** vetor = list->vetor;

	if(vetor[rh]!=NULL){
		if(!(vetor[rh]->flag)){
			vetor[rh]->flag = 1;
			vetor[rh]->reg = reg;
			return rh;
		}else{
			rehash(list, reg, rh);
		}
	}else{
		Tnode* newNode = (Tnode*)malloc(sizeof(Tnode));
		newNode->flag=1;
		newNode->reg=reg;
		vetor[rh]=newNode;
		return rh;
	}
}

void addIn(hashTable * list, unsigned long long int reg){
	// Inicializar um novo node com os dados passados
	Tnode** vetor = list->vetor;
	unsigned long long int h = reg % list->size;
	
	if(vetor[h]!=NULL){
		if(!(list->vetor[h]->flag)){
			vetor[h]->reg = reg;
			vetor[h]->flag= 1;
		}else{
			h= rehash(list, reg, h);
		}
	}else{
		Tnode* newNode = (Tnode*)malloc(sizeof(Tnode));
		newNode->flag=1;
		newNode->reg=reg;
		vetor[h]=newNode;
	}

	list->total++;
}

void addElement(hashTable *list){
	unsigned long long int reg;
	
	// Consulta no terminal o Aluno a ser adicionado 
	printf("\n\n\n");
	printf("\t=====| INSERE NOVO NO |=====\n\n");
	printf("Informe valor: ");
	scanf("%llu", &reg);

	Tnode* valid=NULL;
	valid = searchTnode(list, reg);
	if(valid!=NULL && valid->flag){
		printf("\nRegistro ja existe");
		return;
	}

	// Adiciona na lista o Aluno passado no terminal
	addIn(list, reg);
}

void printHashTable(hashTable *list){
	unsigned long long int i=0;
	Tnode** vetor = list->vetor;

	// Percorre toda a lista imprimindo aluno
	for (i; i<(list->size); i++){
		if(vetor[i]!=NULL){
			if(vetor[i]->flag) printf("\n -> %llu", vetor[i]->reg);
			else printf("\n -");
		}else printf("\n -");
	}//for
	printf("\n\n");
}

Tnode* reSearch(hashTable* list, unsigned long long int reg, unsigned long long int index){
	unsigned long long int h1 = 1 + (reg% (list->size - 1) );
	unsigned long long int rh = (index + h1) % (list->size);

	Tnode* node; 
	Tnode** vetor = list->vetor;

	if(vetor[rh]!=NULL) {
		if (vetor[rh]->reg == reg) return vetor[rh];
		else return reSearch(list, reg, rh);
	}else return NULL;

}

Tnode* searchTnode(hashTable *list, unsigned long long int reg){
	unsigned long long int h = (int) (reg % list->size);
	Tnode** vetor = list->vetor;
	Tnode* node;

	// Percorre toda lista da tabela com o respectivo resto
	if(vetor[h]!=NULL) {
		if (vetor[h]->reg == reg) return vetor[h];
		else node = reSearch(list, reg, h);
	}else return NULL;
	return node;
}

void searchStudent(hashTable *list){
	unsigned long long int reg;
	float init = (float) clock();
	
	printf("\n\n\t=====| PROCURAR No |=====\n\n");
	printf("\tInforme MATRICULA a ser PROCURADA: ");
	scanf("%llu", &reg);

	// Procura na lista correspondete da tabela hash pela matricula 
	unsigned long long int rest = (unsigned long long int) (reg % list->size);
	Tnode *node = searchTnode(list, reg);

	// Se o aluno existr (se existir matricula cadastrada) imprime Aluno
	if(node!=NULL) {
		printf("\t+-------------------------------------------------+");
		printf("\n\t\tRegistro: %llu\n", node->reg);
		printf("\t+-------------------------------------------------+");
	}else{
		printf("\t+-------------------------------------------------+");
		printf("\n\t\tMatricula não encontrada");
		printf("\n\t+-------------------------------------------------+");
	}//if
	
	float end = (float) clock();
	float delta = (end-init)/1000;
	printf("\n\nEssa procura levou %.2fms", delta);
}