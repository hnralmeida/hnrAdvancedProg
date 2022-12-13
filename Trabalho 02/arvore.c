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
*/

#include<stdio.h>
#include<string.h>
#include<locale.h>
#include<stdlib.h>
#include "arvore.h"

/*
=========================================================================================
			Implementação
*/

// Funcao padrao, tira caracteres indesejados para leitura de strings
void limparBuffer(){
    char c;
    while((c= getchar()) != '\n' && c != EOF);
}

// Funcao recursiva, retorna struct no encontrada correspondente a parametro nome
TTree *digThrowTree(TTree* node, string name){
	if (node==NULL){ 	// nesse ponto indica que nao foi possivel encontrar o no procurado pelo parametro
		return NULL; 	
	}else if(!strcmp(node->name, name)){ 	// se compativel com o parametro, retorna o no desejado
		return node;						
	}else if(strcmp(node->name, name)>0){	// procura nos valores menores que o no
		digThrowTree(node->left, name);
	}else{									// procura nos valores maiores que o no
		digThrowTree(node->right, name);
	}//if
}

// funcao que inicializa a sentinela vaiza e com 0 nos
void inicializaSentinel(TSentinel *L){
	L->root = NULL;
	L->total = 0;
}

// subfunção de insertRegister, chamada por insereNaArvore
// retorna um ponteiro para o no com os atributos desejados
TTree *inicializaTree(string nome, string reg){
	TTree *no = (TTree *)malloc(sizeof(TTree));
	no->right = NULL;
    no->left=NULL;
	strcpy(no->name, nome);
	strcpy(no->reg, reg);
	return no;
}

// subfunção de insertRegister, chamada por insereNaSentinela
// encontra o pai do no inserido
TTree *insereNaArvore(TTree **node, string nome, string reg){
	if((*node)==NULL){	// verifica se o no pode ser inserido
		(*node) = inicializaTree(nome, reg);
	}else if(strcmp(nome, (*node)->name)>0){ // procura nos nos a direita um no NULL
		(*node)->right = insereNaArvore(&(*node)->right, nome, reg);
	}else { // procura nos nos a esquerda um no NULL
		(*node)->left = insereNaArvore(&(*node)->left, nome, reg);
	}
	return (*node);
}

// subfunção de insertRegister, chamada por insertRegister
// manipula a sentinela e automatiza insersao
void insereNaSentinela(TSentinel **L, string nome, string reg){
	(*L)->total++;
	(*L)->root = insereNaArvore(&(*L)->root, nome, reg);
}

// Funcao para inserir um aluno com nome e matricula
void insertRegister(TSentinel *L){
    string nome, reg;
	TTree* valid;

	// recebe dados do usuario
	printf("\nDigite o nome e matricula para adicionar: ");
	limparBuffer();
	scanf("%[^\n40]s", nome);
    limparBuffer();
	scanf("%[^\n40]s", reg);
	
	// verifica se já não existe o valor passado na árvore
	valid = digThrowTree(L->root, nome); 
 	
	if (valid==NULL) insereNaSentinela(&L, nome, reg); // se nao estiver adicionado, adiciona o registro
	else printf("Valor ja existe na arvore");
}

// Subfunção de preOrderList
void digTreePre(TTree* node){
	if(node==NULL) return;
	printf("\n%s \t %s", node->reg, node->name);
    digTreePre(node->left);
	digTreePre(node->right);
}

// Listar alunos em Pré-ordem por nome
void preOrderList(TSentinel *L){
	TTree *aux = L->root;

	printf("\n============================");
	printf("\n\tLista de Alunos (Pre-Ordem)");
	printf("\n============================");

	digTreePre(aux);
}

// Subfunção de inOrderList
void digTreeEm(TTree* node){
	if(node==NULL) return;
	digTreeEm(node->left);
	printf("\n%s \t %s", node->reg, node->name);
	digTreeEm(node->right);
}

// Listar alunos Em-ordem por nome
void inOrderList(TSentinel *L){
	TTree *aux = L->root;

	printf("\n============================");
	printf("\n\tLista de Alunos (Em Ordem)");
	printf("\n============================");

	digTreeEm(aux);
}

// Subfunção de posOrderList
void digTreePos(TTree* node){
	if(node==NULL) return;
	digTreePos(node->left);
	digTreePos(node->right);
    printf("\n%s \t %s", node->reg, node->name);
}

// Listar alunos em pos ordem por nome
void posOrderList(TSentinel *L){
	TTree *aux = L->root;

	printf("\n============================");
	printf("\n\tLista de Alunos (Pos-Ordem)");
	printf("\n============================");

	digTreePos(aux);
}

// Consultar alunos por Nome
void searchNode(TSentinel *L){
	TTree *aux = L->root;
	//se nao for uma arvore vazia, procura na arvore
	if(aux == NULL){
		printf("\nArvore Vazia!");
	}else{
		printf("\nQual pessoa deseja procurar?\n> ");
		string nome;
		limparBuffer();
		scanf("%[^\n40]s", nome);
		TTree *x = digThrowTree(aux, nome); //se o nome existir, retorna no com o nome
		if (x==NULL){ // se no nao existir, variavel esta null
			printf("\nNao encontrado!");
		}else{
			printf("\nEncontrado!");
			printf("\n%s \t %s", x->reg, x->name);
		}//if...else
	}//if...else
}

// subfuncao de RemoveNode, chamada por removerArvore
// utilizada para pegar o nó mais a direita da subarvore esquerda do nó que será removido
TTree *raizDireita(TTree **no){
	if ((*no)->right != NULL){ // navega a direita até achar o no mais a direita
		return raizDireita(&(*no)->right);
	} else { // retorna no que estava mais a direita
		TTree *aux1 = *no;
		if ((*no)->left != NULL)
			*no = (*no)->left;
		else
			*no = NULL;
		return aux1;
	}
}

// subfuncao de RemoveNode, remove da árvore o aluno do parametro
void removerArvore(TSentinel *L, TTree **raiz, string apagar){
	int resposta = 0;
	if (*raiz == NULL){ // se a arvore estiver vazia, nao ha o que remover
		printf("\nNome nao encontrado!\n\n");
		return;
	}

	if (strcmp(apagar, (*raiz)->name) < 0){ //verifica nos nos se o nome vem antes (A-Z)
		removerArvore(L, &(*raiz)->left, apagar);
	} else if (strcmp(apagar, (*raiz)->name) > 0){ //verifica nos nos se o nome vem depois (A-Z)
        removerArvore(L, &(*raiz)->right, apagar);
    } else { // nome para apagar esta no no atual, confirmar
        printf("\n============================");
        printf("\n   Apagar %s?\n   1 - Sim\n   0 - Nao\n\n-> ", (*raiz)->name);
        scanf("%i", &resposta);
        printf("\n============================");

        if (resposta){ // se confirmado exclusao
            TTree *aux = (*raiz);
            if (((*raiz)->left == NULL) && ((*raiz)->right == NULL)){ //verifica se tem filhos
                free(aux);
                (*raiz) = NULL;
                if (L->root == (*raiz)) (L->root)=NULL;
            } else if ((*raiz)->left == NULL){ // so um filho a direita
                if (L->root == (*raiz)) (L->root)=(*raiz)->right;
                (*raiz) = (*raiz)->right;
                aux->right = NULL;
                free(aux);
                aux = NULL;
            }else if ((*raiz)->right == NULL){ // so um filho a esquerda
                    if (L->root == (*raiz)) (L->root)=(*raiz)->left;
                    (*raiz) = (*raiz)->left;
                    aux->left = NULL;
                    free(aux);
                    aux = NULL;
            }else { // dois filhos, chama funcao que desloca o filho a esquerda mais a direita
                if (L->root == (*raiz)) (L->root)=aux;
                aux = raizDireita(&(*raiz)->left);
                aux->left = (*raiz)->left;
                aux->right = (*raiz)->right;
                free((*raiz));
                (*raiz) = aux;
            }//if...else if...else if...else
            printf("\n   %s apagado(a) !\n\n", apagar);
        } else {
            printf("\n============================");
            printf("\n%s não apagado (a)", apagar);
        }//if...else 
    }//if...else if...else
}

// Remover aluno da arvore
void RemoveNode(TSentinel *L){
	TTree *aux = L->root;

	if(aux == NULL){
		printf("\nLista Vazia!");
	}else{
		printf("\nQual pessoa deseja remover?\n> ");
		string nome;
		limparBuffer();
		scanf("%[^\n40]s", nome);
		removerArvore(L, &aux, nome);
		L->total--;
	}//if...else
}

// funcao que adiciona valores default
void automatico(TSentinel *L){
	string nome[10] = {"Yuri Duarte","Luiz Felipe Nascimento", "Calebe Fernandes" ,
						"Maria Vitoria Pires", "Diogo da Mota","Yasmin da Paz" ,
						"Maria Julia Sales","Juliana Duarte", "Kaique da Rocha",
						"Lucas Gabriel Sales"};

	string matricula[10] = {"0x0000001", "0x0000002", "0x000003", "0x0000004", 
"0x0000005", "0x0000006", "0x0000007","0x0000008", "0x0000009", "0x000000A"};
	int i;
	for (i=0; i<10; i++)
		insereNaArvore(&(L->root), nome[i], matricula[i]);
}

// calcula o numero de linhas do aquivo
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

// usa os valores do arquivo f para registrar no banco de dados
void initializeDB(TSentinel *L, FILE* f, unsigned long long int size){
	string name, reg;
	int i=0;

	// Percorre todo arquivo pegando dados do aluno
	while (!feof(f)){
		// Toda linha impar eh o nome de um aluno
      	fscanf(f, " %[^\n]s", name);
		// Toda linha par eh o numero de uma matricula
		fscanf(f, " %[^\n]s", reg);
		// Adiciona o Aluno na lista correspondete da tabela hash
		insereNaArvore(&(L->root), name, reg);
  	}//while
}

// subfuncao de saveBase, percorre todos nos salvando os dados
void saveThrow(TTree* node, FILE* file){
    if(node==NULL) return;
	saveThrow(node->left, file);
    fprintf(file, "%s\n",  node->name);
    fprintf(file, "%s\n", node->reg);
	saveThrow(node->right, file);
}

// Funcao apra salvar os dados de um arquivo
void saveBase(TSentinel *L){
    FILE *file;
    unsigned long long int i = L->total;
    file = fopen("Lista_Aluno_Matricula_Atual.txt", "w");
    TTree *node = L->root; 
	// Salva os dados de Aluno em cada lista da tabela hash 
    saveThrow(node, file);
    fclose(file);
}