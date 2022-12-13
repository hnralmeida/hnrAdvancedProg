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
#include<limits.h>
#include <math.h>
#include "grafo.h"

#define TAM 10

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
Tvertex* searchTile(Tgraph* graph, string name){
    if(graph->item == NULL) return NULL;
	Tgraph* aux = graph;

	while(aux!=NULL){
		if(strcmp(name, (aux->item)->tile)!=0)
			aux = aux->next;
		else
			return aux->item;
	}
	return NULL;
}

// procura o vertice com nome passado
Tvertex* searchCode(Tgraph* graph, int code){
    if(graph->item == NULL) return NULL;
	Tgraph* aux = graph;

	while(aux!=NULL){
		if(code != aux->item->code)
			aux = aux->next;
		else
			return aux->item;
	}
	return NULL;
}

Tvertex *initializeVertex(string name, int code){
    Tvertex *newCity = (Tvertex *)malloc(sizeof(Tvertex));
	newCity->number_adjacent = 0;
	newCity->adjacent = NULL;
    newCity->code = code;
	strcpy(newCity->tile, name);
    return newCity;
}

Tgraph *newGraph(string name, int code){
    Tgraph* newNode = (Tgraph *)malloc(sizeof(Tgraph));
	newNode->item = initializeVertex(name, code);
	newNode->next = NULL;
    return newNode;
}

void count(Tgraph** graph){
    Tgraph* aux= *graph;
    int i=0;

    while(aux!=NULL){
        i++;
        aux = aux->next;
    }
    aux= *graph;
    while(aux!=NULL){
        aux->size = i;
        aux = aux->next;
    }
}

Tgraph* insertTile(Tgraph** graph, string name, int code){
    int flag=0;
    if((*graph)->item==NULL){
        // substitui item pelo novo vetor (ja estava inicializado com NULL)
        (*graph) = newGraph(name, code);
        flag=1;
    }else if(strcmp(name, (*graph)->item->tile)<0){
        Tgraph* newNode = newGraph(name, code);
        newNode->next = (*graph);
        graph = &(newNode);
    }else{
        //Lista auxiliar de busca
        Tgraph *aux = (*graph), *previous=NULL;
        while(aux!=NULL && (strcmp(name, aux->item->tile)>0)){
            previous = aux;
            aux = aux->next;
        }

        if (aux == NULL)
			previous->next = newGraph(name, code);
		else{
            Tgraph* newNode = newGraph(name, code);
			newNode->next = aux;
			previous->next = newNode;
		}
    }
    count(graph);
    return (*graph);
}

void createTile(Tgraph** graph){
    string name; int code;
	Tvertex* valid = NULL;

	// recebe dados do usuario
	printf("\nDigite o nome da cidade para adicionar: ");
	scanf("%s", name);
    printf("\nDigite o codigo da cidade para adicionar: ");
	scanf("%d", &code);

	// verifica se ja nao existe o valor passado na arvore

	valid = searchTile((*graph), name); 

	if (valid == NULL) (*graph) = insertTile(graph, name, code); // se nao estiver adicionado, adiciona o registro
    else printf("Valor ja existe na lista");
}

void printAdjacent(Tadjacent* adjacent){
    if(adjacent==NULL){
        printf("\n");
    }else{
        printf("\n\t%s (%.2f km)", adjacent->vertex->tile, adjacent->distance);
        printAdjacent(adjacent->next);
    }
}

void printVertex(Tvertex* vertex){
    if(vertex==NULL){
        printf("\n====================");
    }else{
        printf("\n%s (%d Adjacentes)", vertex->tile, vertex->number_adjacent);
        printAdjacent(vertex->adjacent);
    }
}

void printGraph(Tgraph* graph){
    Tgraph* aux = graph;
    if(aux->item==NULL) printf("\nCidade Vazia");
    else{
        while(aux!=NULL){
            printVertex(aux->item);
            aux = aux->next;
        }
    }
}

void printTile(Tgraph* graph){
    Tgraph* aux = graph;
    Tvertex* vertex;
    if(aux->item==NULL) printf("\nCidade Vazia");
    else{
        while(aux!=NULL){
            vertex = aux->item;
            if(vertex==NULL){
                printf("\n====================");
            }else{
                printf("\n%d - %s", vertex->code, vertex->tile);
            }
            aux = aux->next;
        }
    }
}

Tadjacent* initAdjacent(Tvertex* city, float distance){
    Tadjacent* aux = (Tadjacent*)malloc(sizeof(Tadjacent));
    aux->distance = distance;
    aux->vertex = city;
    aux->next=NULL;
    return aux;
}

void insertEdge(Tvertex* city1, Tvertex* city2, float distance){
    // printf("\n%s -> %s", city1->tile, city2->tile);
    if(city1==NULL){
        return;
    }else if(city2==NULL){
        return;
    }

    if((city1)->adjacent==NULL){
        (city1)->adjacent = initAdjacent(city2, distance);
        (city1)->number_adjacent = 1;
    }else if(strcmp(city2->tile, (city1)->adjacent->vertex->tile)<0){
        Tadjacent* aux = initAdjacent(city2, distance);
        aux->next = (city1)->adjacent;
        (city1)->adjacent = aux;
        (city1)->number_adjacent++;
    }else{
        Tadjacent *actual = (city1)->adjacent;
		Tadjacent *previous = NULL;
        (city1)->number_adjacent++;

		while(actual != NULL && strcmp(city2->tile, actual->vertex->tile)>0 ){
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

    city1 = searchTile((*graph), name1); 
	if (city1 != NULL){
        city2 = searchTile((*graph), name2); 
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
	limparBuffer();
	scanf(" %[^\n]s", name);

	// verifica se existe
	valid = searchTile((graph), name); 

    if(valid==NULL) printf("\nCidade nao existe");
    else{
        printf("Cidade %s", valid->tile);
        printAdjacent(valid->adjacent);
    }
}

int hasOpen(int open[], Tvertex* origin){
    Tadjacent* aux = origin->adjacent;
    int total=0, closed=0;
    while(aux!=NULL){
        total++;
        if(!open[aux->vertex->code-1]) closed++;
        aux=aux->next;
    }
    if(total==closed) return 0;
    else return 1;
}

Tvertex** mine(Tvertex* pre[], int open[], float dist[], Tvertex* origin, Tvertex* destiny){
    // Enquanto houver vertices abertos
    Tadjacent* aux1 = origin->adjacent;
    Tvertex* shortWay, **aux2;
    float shortPath=INFINITY;

    // Fechar o nodo
    open[origin->code]=0;

    // Recalcular as estimativas de distancias
    while(aux1 != NULL){

        // Calcular distancia até origem (G)
        dist[aux1->vertex->code] = dist[origin->code]+1;

        // Calcular distancia até destino (H)
        int i1 = aux1->vertex->code/TAM;
        int j1 = aux1->vertex->code%TAM;
        int i2 = destiny->code/TAM;
        int j2 = destiny->code%TAM;
        aux1->distance = (float) ((i1-i2)*(i1-i2)+(j1-j2)*(j1-j2));

        if(open[aux1->vertex->code]){
            // Se o nodo for mais curto que o registrado como predecessor, atualiza o predecessor
            if( (aux1->distance + dist[aux1->vertex->code]) < shortPath || aux1->vertex->code==destiny->code){
                shortPath = (aux1->distance + dist[aux1->vertex->code]);
                pre[aux1->vertex->code] = origin;
                shortWay = aux1->vertex;
            }
        }
        aux1 = aux1->next;
    }
    
    // vertice aberto minimo e condicao de parada
    if(destiny->code!=shortWay->code&&hasOpen(open, shortWay)){
        aux2= mine(pre, open, dist, shortWay, destiny);
    }
    return pre;
}

void dijskra(Tgraph* graph){
    Tvertex *origin, *destiny, *aux, *prev;
    int i, n;
    string s;
    float MIN_DIST=0;

    // entrada de cidade
	printf("\nQual a coordenada de origem?\n");
	scanf("%s", s);
	// verifica se existe a cidade passada de origem
	origin = searchTile((graph), s);

    // entrada de cidade
	printf("\nQual a coordenada de destino?\n");
	scanf("%s", s);
	// verifica se existe a cidade passada de origem
	destiny = searchTile((graph), s);

    Tvertex* pre[graph->size];
    int open[graph->size];
    float dist[graph->size];

    // Inicializar o vetor de abertos, de distancias e precedecessores
    for(i=0; i<graph->size; i++){
        open[i]=1;
        dist[i]=INFINITY;
        pre[i]=NULL;
    }

    // modifica o nodo inicial
    dist[origin->code]=0;

    // se existir a cidade, chama a subfuncao que escreve o menor caminho
    Tvertex** way = (Tvertex**) malloc((graph->size)*sizeof(Tvertex*));
    if(origin==NULL||origin->number_adjacent==0) {
        printf("\nCoordenada origem nao pode ser acessada");
        return;
    }
    else if(destiny==NULL||destiny->number_adjacent==0) {
        printf("\nCoordenada destino nao pode ser acessada");
        return;
    }
    else{        
        way = mine(pre, open, dist, origin, destiny);
    }

    // Listar Saida
    aux = destiny;
    printf("\n(");
    while(aux->code!=origin->code){
        printf("%s -> ", aux->tile);
        prev = aux;
        aux = way[aux->code];
        if(aux!=NULL){ 
            Tadjacent* auxAdj = aux->adjacent;
            while(auxAdj!=NULL&&auxAdj->vertex->code!=prev->code) auxAdj=auxAdj->next;
            MIN_DIST++;
        }
    }
    printf(" %s)\nPassos Totais: %.2f ", origin->tile, MIN_DIST);
}

Tgraph* initializeTiles(Tgraph* graph){
    FILE* file;
    int i, j, tiles[TAM][TAM];
    float dist;
    string r, s, line;
    file = fopen("entrada.txt", "r");
    char *arr, *arrayList[TAM];

    // Ler linha i do arquivo e guardar em um vetor
    for (i=0; i<TAM; i++){
        fgets(line, 40, file);
        // Para cada coluna, registra o valor da entrada em tiles
        for(j=0; j<TAM; j++){
            if(!j){
                arr = strtok(line, " ");
                arrayList[0] = arr;
            }else{
                arr = strtok(NULL, " \n");
                arrayList[j] = arr;
            }
            dist = atoi(arrayList[j]);
            tiles[i][j]=dist;
        }
    }

    // Inicia as casas do tabuleiro com nome em coordenadas
    for (i=0; i<TAM; i++) {
        for(j=0; j<TAM; j++){
            sprintf(s, "%d,%d", i, j);
            insertTile(&graph, s , i*TAM+j);
        }
    }

	// Loop para registrar o tabuleiro de acordo com a matriz tiles
	for (i=0; i<TAM; i++){
        for(j=0; j<TAM; j++){
            sprintf(s, "%d,%d", i, j);
            if(tiles[i][j]) continue;
            
            dist = INFINITY;
            // Vê para cada vizinho se ele está livre
            if(!tiles[i-1][j]){
                sprintf(r, "%d,%d", i-1, j);
                insertEdge(searchTile(graph, r), searchTile(graph, s), dist );
            }

            if(!tiles[i][j+1]){
                sprintf(r, "%d,%d", i, j+1);
                insertEdge(searchTile(graph, r), searchTile(graph, s), dist );
            }
            if(!tiles[i][j-1]){
                sprintf(r, "%d,%d", i, j-1);
                insertEdge(searchTile(graph, r), searchTile(graph, s), dist );
            }
            if(!tiles[i+1][j]){
                sprintf(r, "%d,%d", i+1, j);
                insertEdge(searchTile(graph, r), searchTile(graph, s), dist );
            }
        }
	}
    return graph;
}
