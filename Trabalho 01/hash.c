/*
=========================================================================================
AUTOR:	Henrique Almeida de Oliveira
Disciplina: Topicos de Programacao Avancada

					Trabalho 01 – Tabela Hash

Implementação de hash.h
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

/* Procura na tabela hash pela matricula informada
	0 - nao existe registro // 1 - existe registro
*/
int searchReg(Tlist list[], unsigned long long int reg, unsigned long long int size){
	int i = 0;
	int rest = (int) (reg % size);
	Tlist *auxSec = &(list[rest]);
	Tnode *aux = auxSec->first;
	
	// Percorre toda lista da tabela com o respectivo resto
	while (aux!=NULL){
		if (reg == aux->reg) return 1;
		aux = aux->next;
	}
	return 0;
}

/* Procura na tabela hash pela matricula informada e retorna seu node */
Tnode* searchTnode(Tlist list[], unsigned long long int reg, unsigned long long int size){
	int i = 0;
	int rest = (int) (reg % size);
	Tlist *auxList = &list[rest];
	Tnode *aux = auxList->first;

	// Percorre toda lista da tabela com o respectivo resto
	while (aux!=NULL){
		if (reg == aux->reg) return aux;
		aux = aux->next;
	}
	return NULL;

}

void addElementHash (Tlist list[], unsigned long long int size){
	unsigned long long int reg=0;
	string name;
	
	printf("\n\n\n");
	printf("\t=====| INSERE NOVO NO |=====\n\n");

	// Consulta no terminal Aluno a ser adicionado enquanto a matricula for FALSE
	while(!reg){
		printf("Informe número da matrícula: ");
		scanf("%llu", &reg);
		
		printf("\nInforme nome do aluno: ");
		scanf(" %[^\n50]s", name);

		// Se a matricula existe na tabela, matricula vira FALSE
		if(searchReg(list, reg, size)) {
			Tnode* aux = searchTnode(list, reg, size);
			printf("\nMatricula %llu ja cadastradada para %s", aux->reg, aux->name);
			reg = 0;
		}//if
	}//while

	// Adiciona na tabela hash o Aluno passado no terminal
	unsigned long long int rest = reg % size;
	addIn(&list[rest], reg, name);	
}

void printHash(Tlist * list, unsigned long long int size){
	int i = 0;

	// Percorre toda tabela hash imprimindo as listas
	for(i=0; i<size; i++){
		printf("\n[%d]", i);
		printList(&list[i]);
	}//for
}

void removeHash(Tlist list[], unsigned long long int size){
	unsigned long long int reg;
	
	printf("\n\n\t=====| REMOVER No |=====\n\n");
	printf("\tInforme MATRICULA a ser REMOVIDA: ");
	scanf("%llu", &reg);

	// Remove a matricula indicada na lista correspondete da tabela hash
	unsigned long long int rest = reg % size;
	removeIn(&list[rest], reg);
}

unsigned long long int calcSize(FILE* f){
	string s;
	unsigned long long int i=0;

	// Move o cursor para o inicio do arquivo
	fseek(f, 0, SEEK_SET);

	// Percorre todas linhas do arquivo e adiciona 1 no contador 
	// para cada linha percorrida
	while (!feof(f)){
      	fscanf(f, " %[^\n]s", s);
    	i++;
  	}//while

	// Move o cursor para o inicio do arquivo
	fseek(f, 0, SEEK_SET);

	return i;
}

void initializeDB(Tlist list[], FILE* f, unsigned long long int size){
	string name;
	unsigned long long int reg;
	int rest, i=0;

	// Percorre todo arquivo pegando dados do aluno
	while (!feof(f)){
		// Toda linha impar eh o nome de um aluno
      	fscanf(f, " %[^\n]s", name);
		// Toda linha par eh o numero de uma matricula
		fscanf(f, "%llu", &reg);
		// Adiciona o Aluno na lista correspondete da tabela hash
		rest = (int) (reg % size);		
		addIn(&list[rest], reg, name);
  	}//while
}

void saveFile(Tlist list[], unsigned long long int size){
    FILE *file;
    int i;
    Tlist *listPass;
    file = fopen("matriculasTeste.txt", "w");

	// Percorre toda tabela hash
    for(i = 0; i < size; i++){
        listPass = &list[i];
        Tnode *node = listPass->first; 

		// Salva os dados de Aluno em cada lista da tabela hash 
        while(node != NULL){
            fprintf(file, "%s\n",  node->name);
            fprintf(file, "%llu\n", node->reg);
            node = node->next;
        }//while
    }//for
    fclose(file);
}

void searchStudent(Tlist list[], unsigned long long int size){
	unsigned long long int reg;
	
	printf("\n\n\t=====| PROCURAR No |=====\n\n");
	printf("\tInforme MATRICULA a ser PROCURADA: ");
	scanf("%llu", &reg);

	// Procura na lista correspondete da tabela hash pela matricula do aluno
	int rest = (int) (reg % size);
	Tnode *node = searchTnode(list, reg, size);

	// Se o aluno existr (se existir matricula cadastrada) imprime Aluno
	if(node!=NULL) {
		printf("\t+-------------------------------------------------+");
		printf("\n\t\tAluno: %s\n\t\tMatricula: %llu\n", node->name, node->reg);
		printf("\t+-------------------------------------------------+");
	}else{
		printf("\t+-------------------------------------------------+");
		printf("\n\t\tMatricula não encontrada");
		printf("\n\t+-------------------------------------------------+");
	}//if
}
