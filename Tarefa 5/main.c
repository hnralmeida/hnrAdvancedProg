/*
=========================================================================================
AUTOR: 	Henrique Almeida de Oliveira

Disciplina: Tecnicas de Programacao Avancada
Professor: Eduardo Max Amaral

Objetivos;
- Representar computacionalmente uma arvore Binaria.
- Implementar um algoritmo que gere e manipule uma arvore Binaria com matricula e nome
(Aluno).
=========================================================================================
*/

#include<stdio.h>
#include<string.h>
#include<locale.h>
#include<stdlib.h>
#include "arvore.h"

int menu();

/*
=========================================================================================
			Funcao Principal
*/

void main(){
    // INICIALIZAR VARIAVEIS DO PROGRAMA
	int op;
    unsigned long long int size;
	TSentinel* lista;
	setlocale(LC_ALL, "Portuguese");
	inicitializeSentinel(&lista);

    // ABRIR ARQUIVO
	FILE *fileLoad;
	fileLoad = fopen( "Lista_Aluno_Matricula.txt" , "r" );  // Cria um arquivo texto para gravação

	if (fileLoad == NULL){
		printf("Problemas na Leitura do arquivo\n");
		return;
	}

    // SINCRONIZAR COM BASE DE DADOS
    size = calcSize(fileLoad);
	//initializeDB(&lista, fileLoad, size);

	// LOOP PRINCIPAL, INTERAÇÃO COM O USUÁRIO
	do {
		op = menu();

		switch(op){
		   case 1: insertRegister(&lista); break;
		   case 2: RemoveNode(lista); break;
		   case 3: searchNode(lista); break;
           case 4: saveBase(lista); break;
		   case 5: preOrderList(lista); break;
		   case 6: inOrderList(lista); break;
           case 7: posOrderList(lista); break;
		   case 222: automatico(lista); break;
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
    printf("1 - Inserir novo aluno.\n");
	printf("2 - Remover aluno.\n");
	printf("3 - Buscar aluno.\n");
    printf("4 - Salvar base de dado.\n");
    printf("5 - Listar alunos em pre ordem.\n");
    printf("6 - Listar alunos em ordem.\n");
    printf("7 - Listar alunos em por ordem.\n");
    
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
