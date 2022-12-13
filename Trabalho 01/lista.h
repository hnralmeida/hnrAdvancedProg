/*
=========================================================================================
AUTOR:	Henrique Almeida de Oliveira
Disciplina: Topicos de Programacao Avancada

					Trabalho 01 – Tabela Hash

Biblioteca de lista Simplesmente encadeada com sentinela
=========================================================================================
*/

#ifndef LISTA_H_
#define LISTA_H_

/*
=========================================================================================
			Tipo Abstrato de Dados
*/

typedef char string[50];

/* Estrutura de elementos, cada uma representa um aluno com nome (name) e matricula (reg) 
*/
typedef struct typeElement Tnode;

typedef struct typeElement{
	unsigned long long int reg;
	string name;
	Tnode *next;
}Tnode;

/* Estrutura de lista dos elementos alunos */
typedef struct typeList {
	int total;
	Tnode *first, *last;
}Tlist;

/* inicializa lista com ponteiros nulos */
void initializeList(Tlist *list);

/* adiciona valor passado na lista */
void addIn(Tlist * list, unsigned long long int reg, string name);

/* implementa adicao de cursos */
void addElement(Tlist *list);

/* imprimir valores na lista */
void printList(Tlist *list);

/* implementa a remocao valores da lista */
void removeElement(Tlist *list);

/* remove valor passado da lista */
void removeIn(Tlist * list, unsigned long long int reg);

#endif // LISTA_H_
