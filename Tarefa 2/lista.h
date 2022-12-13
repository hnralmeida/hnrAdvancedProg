/*
=========================================================================================
AUTORES: 	
			Henrique Almeida de Oliveira
			Luiz Eduardo Marchiori
Disciplina: Tópicos de Programação Avançada

Biblioteca de lista Simplesmente encadeada com sentinela
=========================================================================================
*/

#ifndef LISTA_H_
#define LISTA_H_

/*
=========================================================================================
			Tipo Abstrato de Dados
*/

typedef struct typeElement Tnode;

typedef struct typeElement{
	int value;
	Tnode *next;
}Tnode;

typedef struct typeList {
	int total;
	Tnode *first, *last;
}Tlist;

// inicializa lista com ponteiros nulos
void initializeList(Tlist *list);

// adiciona curso passada como parâmetro na lista 
void addElement(Tlist *list);

// subfuncao de addElement
void addIn(Tlist * list, int value);

// imprimir valores na lista
void printList(Tlist *list);

// remover valores da lista
void removeElement(Tlist *list);

// subfuncao de removeElement
void removeIn(Tlist * list, int value);

#endif // LISTA_H_
