/*
=========================================================================================
AUTOR:	Henrique Almeida de Oliveira
Disciplina: Topicos de Programacao Avancada

					Trabalho 01 � Tabela Hash

Biblioteca de lista Simplesmente encadeada com sentinela
=========================================================================================
*/

#ifndef HASHOPEN_H_
#define HASHOPEN_H_

/*
=========================================================================================
			Tipo Abstrato de Dados
*/

/* Estrutura de elementos, cada uma representa um aluno com nome (name) e matricula (reg) 
*/
typedef struct typeElement Tnode;

typedef struct typeElement{
	unsigned long long int reg;
	int flag;
}Tnode;

/* Estrutura de lista dos elementos alunos */
typedef struct typeList {
	unsigned long long int total;
	unsigned long long int size;
	Tnode **vetor;
}hashTable;

/* Calcula numero de linhas em um arquivo */
unsigned long long int calcSize(FILE* f);

/* inicializa lista com ponteiros nulos */
void initializeList(hashTable *list, unsigned long long int size);

/* carrega os dados de um arquivo no programa*/
void initializeDB(hashTable *list, FILE* f);

/* adiciona valor passado na lista */
void addIn(hashTable * list, unsigned long long int reg);

/* implementa adicao de cursos */
void addElement(hashTable *list);

/* imprimir valores na lista */
void printHashTable(hashTable *list);

/* procura na hash aberta pelo registro passado */
Tnode* searchTnode(hashTable *list, unsigned long long int reg);

/* implementa procura por resgistro na hash */
void searchStudent(hashTable *list);

/* implementa a remocao valores da lista */
void removeElement(hashTable *list);

/* remove valor passado da lista */
void removeIn(hashTable * list, unsigned long long int reg);

#endif // HASHOPEN_H_
