/*
=========================================================================================
AUTOR:	Henrique Almeida de Oliveira
Disciplina: Topicos de Programacao Avancada

					Trabalho 01 – Tabela Hash

Implementacao de lista.h
=========================================================================================
*/

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

/*
=========================================================================================
			Implementacao de lista.h
*/


void initializeList(Tlist *list){
	list->first=NULL;
	list->last=NULL;
	list->total=0;
}

void addIn(Tlist * list, unsigned long long int reg, string name){
	// Inicializar um novo node com os dados passados
	Tnode *newNode = (Tnode *)malloc(sizeof(Tnode));
	int flag=1;
	newNode->reg = reg;
	newNode->next = NULL;
	strcpy(newNode->name, name);	

	if(list->first == NULL){
		//Lista VAZIA: inserir o primeiro No.
		list->first = newNode;
		list->last = newNode;
	} else {
		//Lista possui pelo menos um No Inserir dados em
		//ordem crescente.
		Tnode *actual = list->first;
		Tnode *previous = NULL;
		
		while(actual != NULL && (newNode->reg >= actual->reg) ){
			previous = actual;
			actual = actual->next;
		}//while
		
		if (actual == NULL && (previous!= list->first) ){
			previous->next = newNode;
			list->last = newNode;
		}else if (actual == list->first){
			newNode->next = actual; 
			list->first = newNode;
		}else{
			newNode->next = actual;
			previous->next = newNode;
		}//if ... else


	}//if ... else
	
	list->total++;
}

void addElement(Tlist *list){
	unsigned long long int reg;
	string name;
	
	// Consulta no terminal o Aluno a ser adicionado 
	printf("\n\n\n");
	printf("\t=====| INSERE NOVO NO |=====\n\n");
	printf("Informe valor: ");
	scanf("%llu", &reg);

	printf("\nInforme nome do aluno: ");
	scanf("%s", &name);

	// Adiciona na lista o Aluno passado no terminal
	addIn(list, reg, name);
}

void printList(Tlist *list){
	int i=0;
	Tnode *cell = list->first;
	
	// Se a lista for vazia imprime somente o hifen
	if(cell == NULL) printf(" -");

	// Percorre toda a lista imprimindo aluno
	while (cell!=NULL){
		printf(" -> %s [%llu]", cell->name, cell->reg);
		cell = cell->next;
	}//while
}

void removeIn(Tlist * list, unsigned long long int reg){

	Tnode *actual = list->first, *prev = NULL;
	string removed_name;
	unsigned long long int removed_reg;
	int removed = 0;

	if(actual == NULL)
		// Se node atual for vazio nao percorre nada
		printf("\nNao ha nada para remover na lista");
	else{
		// Percorre toda lista procurando a matricula
		while(actual != NULL && (actual->reg != reg)){
			prev = actual;
			actual = actual->next;
		}//while

		// Se a matricula existir, salva os dados removidos
		if(actual!=NULL){
			strcpy(removed_name, actual->name);
			removed_reg = actual->reg;
			removed = 1;
			list->total--;
		}else {
			printf("Esse elemento nao existe");
			return;
		}//if ... else
		
		//verificar se remover o ultimo
		if(actual->next == list->last){ 
			prev->next = NULL;
			list->last = prev;
			free(actual);
		}else if(prev == NULL){ // verificar se remover o primeiro;
			prev = actual->next;
			list->first = prev;
			free(actual);
		}else{ // caso remover algum do meio qualquer
			prev->next = actual->next;
			free(actual);
		}//if ... else

	}//if ... else
	
	// a flag removed indica ... se algo foi removido da lista
	if(removed){
		printf("\n\n\n");
		printf("\n+--------------------------------------+");
		printf("\n\tAVISO:");
		printf("\n\t%s", removed_name);
		printf("\n\t%llu", removed_reg);
		printf("\n\tREMOVIDO com SUCESSO !!!\t");
		printf("\n+--------------------------------------+\n\n\n");
	} else {
		printf("\n\n\n");
		printf("+--------------------------------------+\n");
		printf("|  ALERTA:                             |\n");
		printf("|                                      |\n");
		printf("|  No NAO ENCONTRADO e nem REMOVIDO!!! |\n");
		printf("|                                      |\n");
		printf("+--------------------------------------+\n\n\n");

	}//if ... else
}

void removeElement(Tlist *list){

	unsigned long long int reg;
	
	printf("\n\n\t=====| REMOVER No |=====\n\n");
	printf("\tInforme VALOR a ser REMOVIDO: ");
	scanf("%llu", &reg);

	// Remove a matricula indicada no terminal da lista 
	removeIn(list, reg);
}
