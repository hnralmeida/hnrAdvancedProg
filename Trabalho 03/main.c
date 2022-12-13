/*
=========================================================================================
AUTOR: 	Henrique Almeida de Oliveira

Disciplina: Tecnicas de Programacao Avancada
Professor: Eduardo Max Amaral

Objetivos:
- Implementar uma lista de adjacência para representar uma Matriz Adjacancia.
- Implementar uma lista de adjacência para representar uma Matriz Adjacancia (grafo 
ponderado -> matriz de pesos).
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
	setlocale(LC_ALL, "Portuguese");
	cidades = initializeGraph(cidades);
	cidades = initializeCities(cidades);

	// LOOP PRINCIPAL, INTERAÇÃO COM O USUÁRIO
	do {
		op = menu();

		switch(op){
		   case 1: createCity(&cidades); break;
		   case 2: createEdge(&cidades); break;
		   case 3: printCity(cidades); break;
		   case 4: search(cidades); break;
		   case 5: makeWay(cidades); break;
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
    printf("1 - Inserir nova cidade.\n");
	printf("2 - Criar Caminho entre Cidades.\n");
	printf("3 - Listar Cidades.\n");
	printf("4 - Procurar Cidade.\n");
	printf("5 - Procurar menor caminho.\n");

    printf("================================================\n");

    printf("\n\tInforme OPCAO desejada: ");
    scanf("%d",&opcao);
    printf("\n================================================\n");

	if ((opcao > 6) || (opcao < 0)){
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
