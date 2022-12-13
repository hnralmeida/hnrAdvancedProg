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
#include "grafo.h"

#define INFINITY INT_MAX/2

/*
=========================================================================================
			Implementacao
*/
/**
 * @brief Retira do flush quaisquer dados
 *
 */
void limparBuffer(){
    char c;
    while((c= getchar()) != '\n' && c != EOF);
}

/**
 * @brief Cria um Grado vazio
 * 
 * @param graph 
 * @return Tgraph* 
 */
Tgraph* initializeGraph(Tgraph* graph){
    graph = (Tgraph*)malloc(sizeof(Tgraph));
    graph->item=NULL;
    graph->next=NULL;
    return graph;
}

/**
 * @brief Procura o vertice com nome passado
 * 
 * @param graph 
 * @param name 
 * @return Tvertex* 
 */
Tvertex* searchCity(Tgraph* graph, string name){
    if(graph->item == NULL) return NULL;
	Tgraph* aux = graph;

    // Percorre os nos do grafo em ordem de adição
	while(aux!=NULL){
		if(strcmp(name, (aux->item)->city_name)!=0)
			aux = aux->next;
		else
			return aux->item;
	}
	return NULL;
}

/**
 * @brief Procura o vertice com código passado
 * 
 * @param graph 
 * @param code 
 * @return Tvertex* 
 */
Tvertex* searchCode(Tgraph* graph, int code){
    if(graph->item == NULL) return NULL;
	Tgraph* aux = graph;

    // Percorre os nos do grafo em ordem de adição
	while(aux!=NULL){
		if(code != aux->item->code)
			aux = aux->next;
		else
			return aux->item;
	}
	return NULL;
}

/**
 * @brief Cria um vertice (nó) com código e nome passados, subfunção de newGraph
 * 
 * @param name 
 * @param code 
 * @return Tvertex* 
 */
Tvertex *initializeVertex(string name, int code){
    Tvertex *newCity = (Tvertex *)malloc(sizeof(Tvertex));
	newCity->number_adjacent = 0;
	newCity->adjacent = NULL;
    newCity->code = code;
	strcpy(newCity->city_name, name);
    return newCity;
}

/**
 * @brief Aloca espaço para um novo vertice (nó) com os parametros passados
 * 
 * @param name 
 * @param code 
 * @return Tgraph* 
 */
Tgraph *newGraph(string name, int code){
    Tgraph* newNode = (Tgraph *)malloc(sizeof(Tgraph));
	newNode->item = initializeVertex(name, code);
	newNode->next = NULL;
    return newNode;
}

/**
 * @brief Conta o número de nós no Grafo, subfunção de insertCity
 * 
 * @param graph 
 */
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

/**
 * @brief Procura a posição para adicionar um novo vertice (nó) ao grafo
 * 
 * @param graph 
 * @param name 
 * @param code 
 * @return Tgraph* 
 */
Tgraph* insertCity(Tgraph** graph, string name, int code){
    int flag=0;
    if((*graph)->item==NULL){
        // substitui item pelo novo vetor (ja estava inicializado com NULL)
        (*graph) = newGraph(name, code);
        flag=1;
    }else if(strcmp(name, (*graph)->item->city_name)<0){
        Tgraph* newNode = newGraph(name, code);
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

/**
 * @brief Create a City object
 * 
 * @param graph 
 */
void createCity(Tgraph** graph){
    string name; int code;
	Tvertex* valid = NULL;

	// recebe dados do usuario
	printf("\nDigite o nome da cidade para adicionar: ");
	scanf("%s", name);
    printf("\nDigite o codigo da cidade para adicionar: ");
	scanf("%d", &code);

	// verifica se ja nao existe o valor passado na arvore

	valid = searchCity((*graph), name); 

	if (valid == NULL) (*graph) = insertCity(graph, name, code); // se nao estiver adicionado, adiciona o registro
    else printf("Valor ja existe na lista");
}

/**
 * @brief Lista os vertices adjacents ao vertex que chamou a função
 * 
 * @param adjacent 
 */
void printAdjacent(Tadjacent* adjacent){
    if(adjacent==NULL){
        printf("\n");
    }else{
        printf("\n\t%s (%.2f km)", adjacent->vertex->city_name, adjacent->distance);
        printAdjacent(adjacent->next);
    }
}

/**
 * @brief Nomeia o vertice e faz chamar a subfunção para mostrar adjacências
 * 
 * @param vertex 
 */
void printVertex(Tvertex* vertex){
    if(vertex==NULL){
        printf("\n====================");
    }else{
        printf("\n%s (%d Adjacentes)", vertex->city_name, vertex->number_adjacent);
        printAdjacent(vertex->adjacent);
    }
}

/**
 * @brief Imprime as cidades com suas adjacências com auxílio das subfunções.
 * 
 * @param graph 
 */
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

/**
 * @brief Mostra a lista de cidades
 * 
 * @param graph 
 */
void printCity(Tgraph* graph){
    Tgraph* aux = graph;
    Tvertex* vertex;
    if(aux->item==NULL) printf("\nCidade Vazia");
    else{
        while(aux!=NULL){
            vertex = aux->item;
            if(vertex==NULL){
                printf("\n====================");
            }else{
                printf("\n%d - %s", vertex->code, vertex->city_name);
            }
            aux = aux->next;
        }
    }
}

/**
 * @brief Cria uma adjac~encias para a lista de adjacências
 * 
 * @param city 
 * @param distance 
 * @return Tadjacent* 
 */
Tadjacent* initAdjacent(Tvertex* city, float distance){
    Tadjacent* aux = (Tadjacent*)malloc(sizeof(Tadjacent));
    aux->distance = distance;
    aux->vertex = city;
    aux->next=NULL;
    return aux;
}

/**
 * @brief cria uma conexão entra as cidades que são parâmetros
 * 
 * @param city1 
 * @param city2 
 * @param distance 
 */
void insertEdge(Tvertex* city1, Tvertex* city2, float distance){
    
    if(city1==NULL){
        printf("\nCidade Origem não existe");
        return;
    }else if(city2==NULL){
        printf("\nCidade Destino não existe");
        return;
    }

    // Se a lista de adjacências for vazia, cria uma nova
    if((city1)->adjacent==NULL){
        (city1)->adjacent = initAdjacent(city2, distance);
        (city1)->number_adjacent = 1;
    // Procura a posição para adicionara cidade na lista
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

/**
 * @brief Faz interação com usuário para chamar a função de inserir ligações
 * 
 * @param graph 
 */
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

/**
 * @brief Faz interface com o usuário para procurar uma cidade
 * 
 * @param graph 
 */
void search(Tgraph* graph){
    string name;
	Tvertex* valid = NULL;

	// recebe dados do usuario
	printf("\nDigite o nome da cidade a procurar: ");
	limparBuffer();
	scanf(" %[^\n]s", name);

	// verifica se existe
	valid = searchCity((graph), name); 

    if(valid==NULL) printf("\nCidade nao existe");
    else{
        printf("Cidade %s", valid->city_name);
        printAdjacent(valid->adjacent);
    }
}

/**
 * @brief Vê se há nós abertos na pesquisa
 * 
 * @param open 
 * @param origin 
 * @return int 
 */
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

/**
 * @brief Percorre os vertices e adjacências procurando o destino
 * 
 * @param pre 
 * @param open 
 * @param dist 
 * @param origin 
 * @param destiny 
 * @return Tvertex** 
 */
Tvertex** mine(Tvertex* pre[], int open[], float dist[], Tvertex* origin, Tvertex* destiny){
    // Enquanto houver vertices abertos
    Tadjacent* aux1 = origin->adjacent;
    Tvertex* shortWay, **aux2;
    float shortPath=INFINITY;
    int i, n; 

    // Fechar o nodo
    open[origin->code-1]=0;

    // Recalcular as estimativas de distancias
    while(aux1 != NULL){
        if(open[aux1->vertex->code-1]){
            // Se o nodo for mais curto que o registrado como predecessor, atualiza o predecessor
            if(aux1->distance < dist[aux1->vertex->code-1]||aux1->vertex->code==destiny->code){
                dist[aux1->vertex->code-1] = aux1->distance+dist[origin->code-1];
                pre[aux1->vertex->code-1] = origin;
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

/**
 * @brief Função para procurar menor caminho
 * 
 * @param graph 
 */
void djiskra(Tgraph* graph){
    Tvertex *origin, *destiny, *aux, *prev;
    int i, n;
    float MIN_DIST=0;

    // entrada de cidade
	printf("\nQual o codigo da cidade de origem?\n");
	scanf("%d", &n);
	// verifica se existe a cidade passada de origem
	origin = searchCode((graph), n);

    // entrada de cidade
	printf("\nQual o codigo da cidade de destino?\n");
	scanf("%d", &n);
	// verifica se existe a cidade passada de origem
	destiny = searchCode((graph), n);

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
    dist[origin->code-1]=0;

    // se existir a cidade, chama a subfuncao que escreve o menor caminho
    Tvertex** way = (Tvertex**) malloc((graph->size)*sizeof(Tvertex*));
    if(origin==NULL) {
        printf("\nCidade origem nao existe");
        return;
    }
    else if(destiny==NULL) {
        printf("\nCidade destino nao existe");
        return;
    }
    else{        
        way = mine(pre, open, dist, origin, destiny);
        printf("\nAchou");
    }

    // Listar Saida
    aux = destiny;
    printf("\n(");
    while(aux->code!=origin->code){
        printf("%d - %s, ", aux->code, aux->city_name);
        prev = aux;
        aux = way[aux->code-1];
        if(aux!=NULL){ 
            Tadjacent* auxAdj = aux->adjacent;
            while(auxAdj!=NULL&&auxAdj->vertex->code!=prev->code) auxAdj=auxAdj->next;
            MIN_DIST += auxAdj->distance;
        }
    }
    printf("%d - %s)\nDistancia Total: %.2f km", origin->code, origin->city_name, MIN_DIST);
}

/**
 * @brief Lê os dados do arquivo de entrada e coloca no grafo
 * 
 * @param graph 
 * @return Tgraph* 
 */
Tgraph* initializeCities(Tgraph* graph){
    FILE* file;
    int n_cities, i, j;
    float dist;
    string s;
    char* arrayList[2];
    file = fopen("entrada.txt", "r");
    
    // Pegar o numero N de cidades
    fgets(s, 40, file);
    n_cities = atoi(s);
    char* cities[n_cities];
    printf("\nadd %d cities", n_cities);
    char* arr;

    // Loop para registrar as cidades (primeiras N+1 Linhas)
    for (i=0; i<n_cities; i++){
        fgets(s, 40, file);
		arr = strtok(s, ";");
		arrayList[0] = arr;
		arr = strtok(NULL, ";\n");
		arrayList[1] = arr;
		graph = insertCity(&graph, arrayList[1], atoi(arrayList[0]));
        cities[i] = (char*) malloc(40* sizeof(char));
		strcpy(cities[i], arrayList[1]);

	}

	// Loop para registrar as distancias (depois das N+1 Linhas)
	for (i=0; i<n_cities; i++){
        for(j=0; j<n_cities; j++){
            fscanf(file, "%f", &dist);
            fscanf(file, "%c", &arrayList[0]);
		    if(dist!=0) insertEdge(searchCity(graph, cities[i]), searchCity(graph, cities[j]), dist );
            arr = strtok(NULL, ";\n");
        }
	}
    return graph;
}
