/*
=========================================================================================
AUTOR: 	Henrique Almeida de Oliveira

Disciplina: Técnico de Programação Avançada
Professor: Eduardo Max Amaral

Objetivos;
• Representar computacionalmente uma Árvore Binária.
• Implementar um algoritmo que gere e manipule uma Árvore Binária com matricula e nome
(Aluno).

=========================================================================================
			Tipo Abstrato de Dados
*/

#ifndef ARVORE_H_
#define ARVORE_H_

typedef struct tipoPerson TPerson;

typedef struct NoTree TTree;

typedef char string[40];

typedef struct NoTree {
	TTree *left;
	TTree *right;
	string name;
	string reg;
}TTree;

typedef struct tipoLista {
	unsigned long long int total;
	TTree* root;
}TSentinel;

// Funções padrão
void limparBuffer();

// Função de Lista SEABB
void inicializaSentinel(TSentinel *L);
void insertRegister(TSentinel *L);
void preOrderList(TSentinel *L);
void inOrderList(TSentinel *L);
void posOrderList(TSentinel *L);
void searchNode(TSentinel *L);
void RemoveNode(TSentinel *L);
void saveBase(TSentinel *L);
unsigned long long int calcSize(FILE* fileLoad);
void initializeDB(TSentinel *L, FILE* f, unsigned long long int size);
void automatico(TSentinel *L);

#endif