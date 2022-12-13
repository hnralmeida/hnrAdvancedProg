/*
=========================================================================================
AUTOR:	Henrique Almeida de Oliveira
Disciplina: Topicos de Programacao Avancada

					Trabalho 01 � Tabela Hash
	Objetivos:
	- Representar computacionalmente uma Tabela Hash com lista encadeada.
	- Implementar um algoritmo que gere e manipule uma Tabela Hash com matricula e nome (Aluno).
=========================================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<time.h>
#include"hashopen.h"

/*
=========================================================================================
*/

/* Funcao auxiliar que limpa dados do buffer 
	Essencial para leitura de char
*/
void limparBuffer();

/* Retorna a opcao do menu disponicel com a tarefa a ser executada 
1	Inserir novo aluno
2	Remover aluno
3	Buscar aluno
4	Salvar base de dados
0	Sair do programa
Existe ainda a opcao secreta 222 que imprime no terminal a tabela hash.
*/
int menu();

/*
	FUNCAO PRINCIPAL
*/
void main(){

	int op, i=0;
	unsigned long long int size;
	time_t exc;
	float init = (float) clock();

	setlocale(LC_ALL, "");

	// ABRIR ARQUIVO
	char* arq = "reg1.txt";
	FILE *fileLoad;
	fileLoad = fopen( arq , "r" );  // Abre um arquivo texto para leitura

	if (fileLoad == NULL){
		printf("Problemas na Leitura do arquivo\n");
		return;
	}

	// INICIAR TABELA HASH
	size = 1.5*calcSize(fileLoad);
	fseek(fileLoad, 0, SEEK_SET);
	hashTable tabHash;
	initializeList(&tabHash, size);

	// INICIAR BANCO DE DADOS
	fseek(fileLoad, 0, SEEK_SET);
	initializeDB(&tabHash, fileLoad);
	fclose(fileLoad);
	
	float end = (float) clock();
	float delta = (end-init)/1;
	printf("\nArquivo Iniciado apos %0.2f us\n", delta);
	system("pause");
	
	// MENU DE USUARIO
	do {
		printf("...");
		op = menu();

		switch(op){
		   case 1: addElement(&tabHash); break;
		   case 2: searchStudent(&tabHash); break;
		   case 3: printHashTable(&tabHash); break;
		}//switch
		limparBuffer();
		printf("\nPressione qualquer tecla para continuar. . .");
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
	system("@cls||clear"); //Limpa a Tela e posiciona o
	               //CURSOR no canto esquerdo superior da mesma
    printf("\n\n\n\t     =====| MENU |=====\n\n");
    printf("0 - SAIR (Encerrar programa sem salvar alteracoes).\n\n");
    printf("1 - Adicionar.\n");
    printf("2 - Procurar estudante.\n");
	printf("3 - Imprimir.\n\n");
    printf("\tInforme OPCAO desejada: ");

    scanf("%d",&opcao);

	if (opcao==222) return 222;
	if ((opcao > 4) || (opcao < 0)){
		printf("\n\n\n");
		printf("\n+-------------------------------------------------+");
		printf("\n|   ERRO:                                         |");
		printf("\n|                                                 |");
		printf("\n|   OPCAO INVALIDA!!!                             |");
		printf("\n|                                                 |");
		printf("\n|   Tente outra vez.                              |");
		printf("\n+-------------------------------------------------+\n\n");
		system("PAUSE");
	}
	return opcao;
}
