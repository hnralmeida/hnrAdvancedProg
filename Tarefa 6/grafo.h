/*
=========================================================================================
AUTOR: 	Henrique Almeida de Oliveira
Disciplina: Técnico de Programação Avançada
Professor: Eduardo Max Amaral
Objetivos:
- Implementar uma lista de adjacência para representar uma Matriz Adjacência.
- Implementar uma lista de adjacência para representar uma Matriz Adjacência (grafo 
ponderado -> matriz de pesos).
=========================================================================================
			Tipo Abstrato de Dados
*/

#ifndef GRAFO_H_
#define GRAFO_H_

typedef struct adjacent Tadjacent;

typedef struct vertex Tvertex;

typedef struct graph Tgraph;

typedef char string[40];

typedef struct adjacent{
    Tvertex* vertex;
    Tadjacent* next;
    int distance;
}Tadjacent;

typedef struct vertex {
    string city_name;
	Tadjacent* adjacent;
    int number_adjacent;
}Tvertex;

typedef struct graph {
	Tvertex* item;
	Tgraph* next;
}Tgraph;

// Funcoes padrao
void limparBuffer();

// Funcao de inicializar grafo vazio
Tgraph* initializeGraph(Tgraph* graph);
// Iniciar o mapa exemplo
Tgraph* initializeCities(Tgraph* graph);
// Insertir cidades com nome
void createCity(Tgraph** graph);
// Imprimir cidades e adjacencias
void printCity(Tgraph* graph);
// Criar caminhos, arestas, entre cidades
void createEdge(Tgraph** graph);
// Procurar e retorna a cidade, vertice, com nome correspondente e suas adjacencias
void search(Tgraph* graph);

#endif