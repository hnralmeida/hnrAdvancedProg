/*
=========================================================================================
AUTORES: 	
			Henrique Almeida de Oliveira
			
Disciplina: Topicos de Programacao Avancada

Funcao principal utilizando binario com os objetivos de:

- Implementar uma biblioteca de arvores para armazenar numeros inteiros.
- Utilizacao de chave com valor numerico.
- Biblioteca que tem metodos para inserir um elemento na arvore, remover um elemento, 
        pesquisar por um elemento, imprimir os 3 caminhamentos classicos.
=========================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "binario.h"

void limparBuffer();

int menu();

/*
=========================================================================================
			Funcao Principal
*/

int main(){
	int op;
	TSentinel lista;
	setlocale(LC_ALL, "Portuguese");

	initializeSentinel(&lista);

	do {
		op = menu();

		switch(op){
		   case 1: insertTree(&lista); break;
		   case 2: printDepthFirst(&lista); break;
		   case 3: printInOrder(&lista); break;
		   case 4: printPosOrder(&lista); break;
		   case 5: searchValue(&lista); break;
		   case 6: removeTree(&lista); break;
		   case 222: automatico(&lista); break;
		}//switch
		printf("\nPressione qualquer tecla para continuar. . .");
		limparBuffer();
		char c = getchar();
	    system("@cls||clear");

	} while(op != 0);

}

void limparBuffer(){
    char c;
    while((c= getchar()) != '\n' && c != EOF);
}

int menu(){
	int opcao;
    printf("\n================| MENU |================\n\n");
    printf("0 - SAIR (Encerrar Programa).\n\n");
    printf("1 - Inserir valor.\n");
    printf("2 - Listar Pessoas em Pre-Ordem.\n");
    printf("3 - Listar Pessoas em In-Ordem.\n");
    printf("4 - Listar Pessoas em Pos-Ordem.\n");
	printf("5 - Procurar por valor.\n");
    printf("6 - Remover valor.\n");
    printf("================================================\n");

    printf("\n\tInforme OPCAO desejada: ");
    scanf("%d",&opcao);
    printf("\n================================================\n");

    if (opcao == 222){
		return opcao;
	}

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
