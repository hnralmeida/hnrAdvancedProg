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
			Implementacao de hash.h
*/

// adiciona um vetor na tabela hash
void addElementHash (Tlist list[], int tam){
	int value;
	
	printf("\n\n\n");
	printf("\t=====| INSERE NOVO NO |=====\n\n");
	printf("Informe valor: ");
	scanf("%d", &value);
	
	int rest = value % tam;
	
	addIn(&list[rest], value);
	
}

// imprimir valores na tabela hash
void printHash(Tlist * list, int tam){
	int i = 0;
	for(i=0; i<tam; i++){
		printf("\n[%d]", i);
		printList(&list[i]);
	}
}

// remover valores da tabela hash
void removeHash(Tlist list[], int tam){
	int value;
	
	printf("\n\n\t=====| REMOVER No |=====\n\n");
	printf("\tInforme VALOR a ser REMOVIDO: ");
	scanf("%d", &value);

	int rest = value % tam;
	removeIn(&list[rest], value);
}

