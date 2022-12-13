/*
=========================================================================================
AUTOR:	Henrique Almeida de Oliveira
Disciplina: Topicos de Programacao Avancada

					Trabalho 01 – Tabela Hash
	Objetivos:
	- Representar computacionalmente uma Tabela Hash com lista encadeada.
	- Implementar um algoritmo que gere e manipule uma Tabela Hash com matricula e nome (Aluno).
=========================================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include"lista.h"
#include"hash.h"

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

	setlocale(LC_ALL, "");

	// ABRIR ARQUIVO
	FILE *fileLoad;
	fileLoad = fopen( "Lista_Aluno_Matricula.txt" , "r" );  // Cria um arquivo texto para gravação

	if (fileLoad == NULL){
		printf("Problemas na Leitura do arquivo\n");
		return;
	}

	// INICIAR TABELA HASH
	size = 0.75*calcSize(fileLoad);
	fseek(fileLoad, 0, SEEK_SET);
	Tlist tabHash[size];

	for(i=0; i<size; i++){
		initializeList(&tabHash[i]);
	}

	// INICIAR BANCO DE DADOS
	fseek(fileLoad, 0, SEEK_SET);
	initializeDB(tabHash, fileLoad, size);
	fclose(fileLoad);

	// MENU DE USUÁRIO
	do {
		op = menu();

		switch(op){
		   case 1: addElementHash(tabHash, size); break;
		   case 2: searchStudent(tabHash, size); break;
		   case 3: removeHash(tabHash, size); break;
		   case 4: saveFile(tabHash, size);
		   case 222: printHash(tabHash, size); break;
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
    printf("3 - Remover.\n");
	printf("4 - Salvar.\n\n");
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
		printf("\n+-------------------------------------------------+\n");
		system("PAUSE");
	}
	return opcao;
}
