/*
=========================================================================================
AUTOR: 	Henrique Almeida de Oliveira
Disciplina: Tecnicas de Programacao Avancada
Professor: Eduardo Max Amaral
=========================================================================================
*/

#include<stdio.h>
#include<string.h>
#include<locale.h>
#include<stdlib.h>
#include "grafo.h"

/*
=========================================================================================
			Implementacao
*/

void limparBuffer(){
    char c;
    while((c= getchar()) != '\n' && c != EOF);
}

Tgraph* initializeGraph(Tgraph* graph){
    graph = (Tgraph*)malloc(sizeof(Tgraph));
    graph->item=NULL;
    graph->next=NULL;
    return graph;
}

// procura o vertice com nome passado
Tvertex* searchCity(Tgraph* graph, string name){
    if(graph->item == NULL) return NULL;
	Tgraph* aux = graph;

	while(aux!=NULL){
		if(strcmp(name, (aux->item)->city_name)!=0)
			aux = aux->next;
		else
			return aux->item;
	}
	return NULL;
}

Tvertex *initializeVertex(string name){
    Tvertex *newCity = (Tvertex *)malloc(sizeof(Tvertex));
	newCity->number_adjacent = 0;
	newCity->adjacent = NULL;
	strcpy(newCity->city_name, name);
    return newCity;
}

Tgraph *newGraph(string name){
    Tgraph* newNode = (Tgraph *)malloc(sizeof(Tgraph));
	newNode->item = initializeVertex(name);
	newNode->next = NULL;
    return newNode;
}


Tgraph* insertCity(Tgraph** graph, string name){
    int flag=0;
    if((*graph)->item==NULL){
        // substitui item pelo novo vetor (ja estava inicializado com NULL)
        (*graph) = newGraph(name);
        flag=1;
    }else if(strcmp(name, (*graph)->item->city_name)<0){
        Tgraph* newNode = newGraph(name);
        newNode->next = (*graph);
        graph = &(newNode);
    }else{
        //Lista auxiliar de busca
        Tgraph *aux = (*graph), *previous=NULL;
        while(aux!=NULL && (strcmp(name, aux->item->city_name)>0)){
            previous = aux;
            aux = aux->next;
        }

        if (aux == NULL)
			previous->next = newGraph(name);
		else{
            Tgraph* newNode = newGraph(name);
			newNode->next = aux;
			previous->next = newNode;
		}
    }
    return (*graph);
}

void createCity(Tgraph** graph){
    string name;
	Tvertex* valid = NULL;

	// recebe dados do usuario
	printf("\nDigite o nome da cidade para adicionar: ");
	scanf("%s", name);

	// verifica se ja nao existe o valor passado na arvore

	valid = searchCity((*graph), name); 

	if (valid == NULL) (*graph) = insertCity(graph, name); // se nao estiver adicionado, adiciona o registro
    else printf("Valor ja existe na lista");
}

void printAdjacent(Tadjacent* adjacent){
    if(adjacent==NULL){
        printf("\n");
    }else{
        printf("\n\t%s (%d km)", adjacent->vertex->city_name, adjacent->distance);
        printAdjacent(adjacent->next);
    }
}

void printVertex(Tvertex* vertex){
    if(vertex==NULL){
        printf("\n====================");
    }else{
        printf("\n%s (%d Adjacentes)", vertex->city_name, vertex->number_adjacent);
        printAdjacent(vertex->adjacent);
    }
}

void printCity(Tgraph* graph){
    Tgraph* aux = graph;
    if(aux->item==NULL) printf("\nCidade Vazia");
    else{
        while(aux!=NULL){
            printVertex(aux->item);
            aux = aux->next;
        }
    }
}

Tadjacent* initAdjacent(Tvertex* city, int distance){
    Tadjacent* aux = (Tadjacent*)malloc(sizeof(Tadjacent));
    aux->distance = distance;
    aux->vertex = city;
    aux->next=NULL;
    return aux;
}

void insertEdge(Tvertex* city1, Tvertex* city2, int distance){
    if(city1==NULL){
        printf("\nCidade Origem não existe");
        return;
    }else if(city2==NULL){
        printf("\nCidade Destino não existe");
        return;
    }

    if((city1)->adjacent==NULL){
        (city1)->adjacent = initAdjacent(city2, distance);
        (city1)->number_adjacent = 1;
    }else if(strcmp(city2->city_name, (city1)->adjacent->vertex->city_name)<0){
        Tadjacent* aux = initAdjacent(city2, distance);
        aux->next = (city1)->adjacent;
        (city1)->adjacent = aux;
        (city1)->number_adjacent++;
    }else{
        Tadjacent *actual = (city1)->adjacent;
		Tadjacent *previous = NULL;
        (city1)->number_adjacent++;

		while(actual != NULL && strcmp(city2->city_name, actual->vertex->city_name)>0 ){
			previous = actual;
			actual = actual->next;
		}	
		
		if (actual == NULL){
			previous->next = initAdjacent(city2, distance);
		}else{
			previous->next = initAdjacent(city2, distance);
            previous->next->next = actual;
		}
    }
}

void createEdge(Tgraph** graph){
    string name1, name2;
    int distance;
    Tvertex* city1=NULL, * city2=NULL;
	// recebe dados das cidades
    limparBuffer();
	printf("\nDigite o nome da cidade origem: ");
	scanf(" %[^\n]s", name1);

    limparBuffer();
    printf("\nDigite o nome da cidade destino: ");
	scanf(" %[^\n]s", name2);

    printf("\nDigite a distancia entre as cidades: ");
	scanf("%d", &distance);

    city1 = searchCity((*graph), name1); 
	if (city1 != NULL){
        city2 = searchCity((*graph), name2); 
        // se nao estiver adicionado, adiciona o registro
        if (city2 != NULL){
            insertEdge(city1, city2, distance);
            insertEdge(city2, city1, distance);
        }
        else printf("Cidade %s nao existe", name2);
    }
    else printf("Cidade %s nao existe", name1);
}

void search(Tgraph* graph){
    string name;
	Tvertex* valid = NULL;

	// recebe dados do usuario
	printf("\nDigite o nome da cidade a procurar: ");
	scanf("%s", name);

	// verifica se existe
	valid = searchCity((graph), name); 

    if(valid==NULL) printf("\nCidade nao existe");
    else{
        printf("Cidade %s", valid->city_name);
        printAdjacent(valid->adjacent);
    }
}

Tgraph* initializeCities(Tgraph* graph){
	graph = insertCity(&graph, "Oradea");
	graph = insertCity(&graph, "Zerind");
	graph = insertCity(&graph, "Arad");
	graph = insertCity(&graph, "Sibiu");
	graph = insertCity(&graph, "Timisoara");
	graph = insertCity(&graph, "Rimnicu Vilcea");
	graph = insertCity(&graph, "Lugoj");
	graph = insertCity(&graph, "Pitesti");
	graph = insertCity(&graph, "Mehadia");
	graph = insertCity(&graph, "Drobeta");
	graph = insertCity(&graph, "Craiova");
	insertEdge(searchCity(graph, "Oradea"), searchCity(graph, "Zerind"), 71 );
	insertEdge(searchCity(graph, "Oradea"), searchCity(graph, "Sibiu"), 151 );
	insertEdge(searchCity(graph, "Zerind"), searchCity(graph, "Arad"), 75 );
	insertEdge(searchCity(graph, "Zerind"), searchCity(graph, "Oradea"), 71 );
	insertEdge(searchCity(graph, "Arad"), searchCity(graph, "Zerind"), 75 );
	insertEdge(searchCity(graph, "Arad"), searchCity(graph, "Sibiu"), 140 );
	insertEdge(searchCity(graph, "Arad"), searchCity(graph, "Timisoara"), 118 );
	insertEdge(searchCity(graph, "Sibiu"), searchCity(graph, "Oradea"), 151);
	insertEdge(searchCity(graph, "Sibiu"), searchCity(graph, "Arad"), 140);
	insertEdge(searchCity(graph, "Sibiu"), searchCity(graph, "Rimnicu Vilcea"), 80);
	insertEdge(searchCity(graph, "Timisoara"), searchCity(graph, "Arad"), 118);
	insertEdge(searchCity(graph, "Timisoara"), searchCity(graph, "Lugoj"), 111);
	insertEdge(searchCity(graph, "Lugoj"), searchCity(graph, "Timisoara"), 111);
	insertEdge(searchCity(graph, "Lugoj"), searchCity(graph, "Mehadia"), 70);
	insertEdge(searchCity(graph, "Mehadia"), searchCity(graph, "Lugoj"), 70);
	insertEdge(searchCity(graph, "Mehadia"), searchCity(graph, "Drobeta"), 75);
	insertEdge(searchCity(graph, "Drobeta"), searchCity(graph, "Mehadia"), 75);
	insertEdge(searchCity(graph, "Drobeta"), searchCity(graph, "Craiova"), 120);
	insertEdge(searchCity(graph, "Craiova"), searchCity(graph, "Drobeta"), 120);
	insertEdge(searchCity(graph, "Craiova"), searchCity(graph, "Rimnicu Vilcea"), 146);
	insertEdge(searchCity(graph, "Craiova"), searchCity(graph, "Pitesti"), 138);
	insertEdge(searchCity(graph, "Pitesti"), searchCity(graph, "Craiova"), 138);
	insertEdge(searchCity(graph, "Pitesti"), searchCity(graph, "Rimnicu Vilcea"), 97);
	insertEdge(searchCity(graph, "Rimnicu Vilcea"), searchCity(graph, "Pitesti"), 97);
	insertEdge(searchCity(graph, "Rimnicu Vilcea"), searchCity(graph, "Craiova"), 146);
	insertEdge(searchCity(graph, "Rimnicu Vilcea"), searchCity(graph, "Sibiu"), 80);

	return graph;
}