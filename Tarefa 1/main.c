/*
=========================================================================================
AUTORES: 	
			Henrique Almeida de Oliveira
			Luiz Eduardo Marchiori
Disciplina: Tópicos de Programação Avançada

Biblioteca de lista Simplesmente encadeada com sentinela
=========================================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include"lista.h"

/*
=========================================================================================
			Exemplo usando sentinelaSimples.h
*/

void limparBuffer(){
    char c;
    while((c= getchar()) != '\n' && c != EOF);
}

int menu(){
	int opcao;
	system("@cls||clear"); //Limpa a Tela e posiciona o 
	               //CURSOR no canto esquerdo superior da mesma
    printf("\n\n\n\t     =====| MENU |=====\n\n");
    printf("0 - SAIR (Encerrar Programa).\n\n");
    printf("1 - Adicionar.\n");
    printf("2 - Exibir Lista Completa.\n");
    printf("3 - Remover.\n\n");
    printf("\tInforme OPCAO desejada: ");
    
    scanf("%d",&opcao);
	
	if ((opcao > 3) || (opcao < 0)){
		printf("\n\n\n");
		printf("\t+-------------------------------------------------+");
		printf("\t|   ERRO:                                         |");
		printf("\t|                                                 |");
		printf("\t|   OPCAO INVALIDA!!!                             |");
		printf("\t|                                                 |");
		printf("\t|   Tente outra vez.                              |");
		printf("\t+-------------------------------------------------+\n\n");
		system("PAUSE");
	}
	return opcao;
}

void main(){	
	Tlist example;
	initializeList(&example);   
	int op;
		
	do {
		op = menu();
		
		switch(op){
		   case 1: addElement(&example); break;
		   case 2: printList(&example); break;
		   case 3: removeElement(&example); break;	
		}//switch
		limparBuffer();
		printf("\nPressione qualquer tecla para continuar. . .");
		char c = getchar();
	    system("@cls||clear");
		
	} while(op != 0);
	
	
    }
