/*
=========================================================================================
AUTORES: 	
			Henrique Almeida de Oliveira
			Luiz Eduardo Marchiori
Disciplina: Tópicos de Programação Avançada

Implementação de sentinelaSimples.h
=========================================================================================
*/

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include "lista.h"

/*
=========================================================================================
			Implementação de sentinelaSimples.h
*/


// inicializa lista com ponteiros nulos
void initializeList(Tlist *list){
	list->first=NULL;
	list->last=NULL;
	list->total=0;
}

void addIn(Tlist * list, int value){
	Tnode *newNode = (Tnode *)malloc(sizeof(Tnode));
	int flag=1;
	newNode->value = value;
	newNode->next = NULL;
	
	if(list->first == NULL){
		//Lista VAZIA: inserir o primeiro N?.
		list->first = newNode;
		list->last = newNode;
	} else {
		//Lista possui pelo menos um N?: Inserir dados em
		//ordem crescente.
		Tnode *actual = list->first;
		Tnode *previous = NULL;
		
		while(actual != NULL && (newNode->value >= actual->value) ){
			previous = actual;
			actual = actual->next;
		}	
		
		if (actual == NULL && (previous!= list->first) ){
			previous->next = newNode;
			list->last = newNode;
		}else if (actual == list->first){
			newNode->next = actual; 
			list->first = newNode;
		}else{
			newNode->next = actual;
			previous->next = newNode;
		}


	}//if ... else
	
	list->total++;
}

// adiciona curso passada como parâmetro na lista 
void addElement(Tlist *list){
	int value;
	
	printf("\n\n\n");
	printf("\t=====| INSERE NOVO NO |=====\n\n");
	printf("Informe valor: ");
	scanf("%d", &value);
	
	addIn(list, value);
}

// imprimir valores na lista
void printList(Tlist *list){
	int i=0;
	Tnode *cell = list->first;
	printf("\nImprimindo um total de %d valores da Lista:\n", list->total);
	while (cell!=NULL){
		printf("[%d]: %d \n", i++, cell->value);
		cell = cell->next;
	}
}

void removeIn(Tlist * list, int value){

	Tnode *actual = list->first, *prev = NULL;
	int removed = 0;

	if(actual == NULL)
		printf("\nNão há nada para remover na lista");
	else{
		while(actual != NULL&& actual->value != value){
			prev = actual;
			actual = actual->next;
		}//while

		if(actual!=NULL){
			removed = 1;
			list->total--;
		}
		
		if(actual->next == list->last){ //verificar se remover o ultimo
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
		}//if
	}
	
	if(removed){
		printf("\n\n\n");
		printf("+--------------------------------------+\n");
		printf("|  AVISO:                              |\n");
		printf("|                                      |\n");
		printf("|  No REMOVIDO com SUCESSO !!!         |\n");
		printf("|                                      |\n");
		printf("+--------------------------------------+\n\n\n");
		
	} else {
		printf("\n\n\n");
		printf("+--------------------------------------+\n");
		printf("|  ALERTA:                             |\n");
		printf("|                                      |\n");
		printf("|  No NAO ENCONTRADO e nem REMOVIDO!!! |\n");
		printf("|                                      |\n");
		printf("+--------------------------------------+\n\n\n");

	}
}

// remover valores da lista
void removeElement(Tlist *list){

	int value;
	
	printf("\n\n\t=====| REMOVER No |=====\n\n");
	printf("\tInforme VALOR a ser REMOVIDO: ");
	scanf("%d", &value);

	removeIn(list, value);
}
