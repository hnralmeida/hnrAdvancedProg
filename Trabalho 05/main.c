/*
=========================================================================================
AUTOR: 	Henrique Almeida de Oliveira

Disciplina: Tecnicas de Programacao Avancada
Professor: Eduardo Max Amaral

Objetivos:
- Representar um grafo computacionalmente
- Implementar o algoritmo de Dijkstra
========================0=================================================================
*/

#include<stdio.h>
#include<string.h>
#include<locale.h>
#include<stdlib.h>
#include "grafo.h"

int menu();

/*
=========================================================================================
			Funcao Principal
*/

void main(){
    // INICIALIZAR VARIAVEIS DO PROGRAMA
	int op;
    int size;
	Tgraph* cidades;
	setlocale(LC_ALL, "en-US");
	cidades = initializeGraph(cidades);
	cidades = initializeTiles(cidades);

	// LOOP PRINCIPAL, INTERAÇÃO COM O USUÁRIO
	do {
		op = menu();

		switch(op){
		   case 1: printTile(cidades); break;
		   case 2: printGraph(cidades); break;
		   case 3: search(cidades); break;
		   case 4: dijskra(cidades); break;
		   default: break;
		}//switch
		printf("\nPressione qualquer tecla para continuar. . .");
		limparBuffer();
		char c = getchar();
	    system("@cls||clear");

	} while(op != 0);

}

// FUNCAO QUE DISPONIBILIA OPCOES DE OPERACAO AO USUARIO
int menu(){
	int opcao;
    printf("\n================| MENU |================\n\n");
    printf("0 - SAIR (Encerrar Programa).\n\n");
	printf("1 - Listar Cidades.\n");
	printf("2 - Listar Estradas de Cidades.\n");
	printf("3 - Procurar Cidade.\n");
	printf("4 - Procurar menor caminho.\n");

    printf("================================================\n");

    printf("\n\tInforme OPCAO desejada: ");
    scanf("%d",&opcao);
    printf("\n================================================\n");

	if ((opcao > 4) || (opcao < 0)){
		printf("\n\n\n");
		printf("\n\t+------------------------+");
		printf("\n\t|   ERRO:                |");
		printf("\n\t|                        |");
		printf("\n\t|   OPCAO INVALIDA!!!    |");
		printf("\n\t|                        |");
		printf("\n\t|   Tente outra vez.     |");
		printf("\n\t+------------------------+");
		system("PAUSE");
	}
	return opcao;
}
