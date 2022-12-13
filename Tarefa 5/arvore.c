
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
#include "arvore.h"

/*
=========================================================================================
			Implementacao
*/

// Funcao padrao, tira caracteres indesejados para leitura de strings
void limparBuffer(){
    char c;
    while((c= getchar()) != '\n' && c != EOF);
}

// Funcao recursiva, retorna struct no encontrada correspondente a parametro nome
TTree *digThrowTree(TTree* node, int reg){
	if (node==NULL){ 	// nesse ponto indica que nao foi possivel encontrar o no procurado pelo parametro
		return NULL; 	
	}else if(node->reg == reg){ 	// se compativel com o parametro, retorna o no desejado
		return node;						
	}else if(node->reg > reg){	// procura nos valores menores que o no
		digThrowTree(node->left, reg);
	}else{									// procura nos valores maiores que o no
		digThrowTree(node->right, reg);
	}//if
}

int treeHigh(TTree* node){
	if (node==NULL){
		return -1;
	}else{
		node->nl = treeHigh(node->left) + 1;
		node->nr = treeHigh(node->right) + 1;
		int i = (node->nl > node->nr) ? node->nl : node->nr;
		return i;
	}
}

// funcao que inicializa a sentinela vaiza e com 0 nos
void inicitializeSentinel(TSentinel **L){
	(*L) = (TSentinel*) malloc(sizeof(TSentinel));
	(*L)->root = NULL;
	(*L)->total = 0;
	(*L)->high = 0;
}

// serie de subfuncao de inseraNaSentinela implementa rotacoes
void rotateLL(TTree **raiz){
	TTree* no = (*raiz)->left;
	if(no!=NULL) (*raiz)->left = no->right;
	if(no!=NULL) no->right = *raiz;
	(*raiz) = no;
	printf("\nrotateLL");
}

void rotateRR(TTree **raiz){
	TTree* no = (*raiz)->right;
	if(no!=NULL) (*raiz)->right = no->left;
	if(no!=NULL) no->left = (*raiz);
	(*raiz) = no;
	printf("\nrotateRR");
}

void rotateLR(TTree **raiz){
	rotateRR(&(*raiz)->left);
	rotateLL(raiz);
	printf("\nrotateLR");
}

void rotateRL(TTree **raiz){
	rotateLL(&(*raiz)->right);
	rotateRR(raiz);
	printf("\nrotateRL");
}


// subfuncao de insertRegister, chamada por insereNaArvore
// retorna um ponteiro para o no com os atributos desejados
TTree *inicializaTree(int reg){
	TTree *no = (TTree *)malloc(sizeof(TTree));
	no->right = NULL;
    no->left=NULL;
	no->nl=0;
	no->nr=0;
	no->reg = reg;
	return no;
}

// calcula a altura de um node
int alturaNo(TTree *raiz) {
    if (raiz==NULL) // se não existe o nodo, retorna a altura -1
        return -1;
    else
        return ( (raiz->nl) > (raiz->nr) ? (raiz->nl) : (raiz->nr) );
}

// subfuncao de insertRegister, chamada por insereNaSentinela
// encontra o pai do no inserido
TTree *insereNaArvore(TTree **node, int reg){
	if((*node)==NULL){	// verifica se o no pode ser inserido
		(*node) = inicializaTree(reg);

	}else if(reg > (*node)->reg){ // procura nos nos a direita um no NULL
		(*node)->right = insereNaArvore(&(*node)->right, reg);
	}else { // procura nos nos a esquerda um no NULL
		(*node)->left = insereNaArvore(&(*node)->left, reg);
	}
	
    return (*node);
}

// subfuncao de insertRegister, chamada por insertRegister
// manipula a sentinela e automatiza insersao
void insereNaSentinela(TSentinel **L, int reg){
	(*L)->total++;
	TTree* root = (*L)->root;
	root = insereNaArvore(&(*L)->root, reg);
}

// subfuncao de insertRegister, cuida do balanceamento
void treeAVL(TTree** root){
	printf("\ntreeAvl");
	int diff = ((*root)->nl - (*root)->nr);
	if( diff > 1) {
		if( (*root)->left!=NULL && (*root)->reg < (*root)->left->reg )
			rotateLL(root);
		else
			rotateLR(root);
	}else if( ((*root)->nl-(*root)->nr) < -1){
		if( (*root)->right!=NULL && (*root)->right->reg < (*root)->reg )
			rotateRR(root);
		else
			rotateRL(root);
	}
	printf("\ntest if");
	if((*root)!=NULL&&(*root)->left!=NULL) {
		printf("\nif root->left");
		treeAVL(&(*root)->left);}
	printf("\ngoin' R");
	if((*root)!=NULL&&(*root)->right!=NULL) treeAVL(&(*root)->right);
}

// Funcao para inserir um aluno com nome e matricula
void insertRegister(TSentinel **L){
    int reg;
	TTree* valid;

	// recebe dados do usuario
	printf("\nDigiteum registro para adicionar: ");
	scanf("%d", &reg);
	
	// verifica se ja nao existe o valor passado na arvore
	valid = digThrowTree((*L)->root, reg); 
	(*L)->high = treeHigh((*L)->root);
	printf("\nAVL going on");
	if((*L)->root!=NULL) treeAVL(&((*L)->root));
	printf("\nAVL OK");
 	
	if (valid==NULL) insereNaSentinela(L, reg); // se nao estiver adicionado, adiciona o registro
	else printf("Valor ja existe na arvore");
}

// Subfuncao de preOrderList
void digTreePre(TTree* node){
	if(node==NULL) return;
	printf("\n%d", node->reg);
    digTreePre(node->left);
	digTreePre(node->right);
}

// Listar alunos em PrÃ©-ordem por nome
void preOrderList(TSentinel *L){
	TTree *aux = L->root;

	printf("\n============================");
	printf("\n\tLista de Alunos (Pre-Ordem)");
	printf("\n\tAltura: %d", L->high);
	printf("\n============================");

	digTreePre(aux);
}

// Subfuncao de inOrderList
void digTreeEm(TTree* node){
	if(node==NULL) return;
	digTreeEm(node->left);
	printf("\n%d", node->reg);
	digTreeEm(node->right);
}

// Listar alunos Em-ordem por nome
void inOrderList(TSentinel *L){
	TTree *aux = L->root;

	printf("\n============================");
	printf("\n\tLista de Alunos (Em Ordem)");
	printf("\n\tAltura: %d", L->high);
	printf("\n============================");

	digTreeEm(aux);
}

// Subfuncao de posOrderList
void digTreePos(TTree* node){
	if(node==NULL) return;
	digTreePos(node->left);
	digTreePos(node->right);
    printf("\n%d", node->reg);
}

// Listar alunos em pos ordem por nome
void posOrderList(TSentinel *L){
	TTree *aux = L->root;

	printf("\n============================");
	printf("\n\tLista de Alunos (Pos-Ordem)");
	printf("\n\tAltura: %d", L->high);
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
		int reg;
		scanf("%d", &reg);
		TTree *x = digThrowTree(aux, reg); //se o nome existir, retorna no com o nome
		if (x==NULL){ // se no nao existir, variavel esta null
			printf("\nNao encontrado!");
		}else{
			printf("\nEncontrado!");
			printf("\n%d", x->reg);
		}//if...else
	}//if...else
}

// subfuncao de RemoveNode, chamada por removerArvore
// utilizada para pegar o nodo mais a direita da subarvore esquerda do nodo que sera removido
TTree *raizDireita(TTree **no){
	if ((*no)->right != NULL){ // navega a direita atÃ© achar o no mais a direita
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

// subfuncao de RemoveNode, remove da Ã¡rvore o aluno do parametro
void removerArvore(TSentinel *L, TTree **raiz, int apagar){
	int resposta = 0;
	if (*raiz == NULL){ // se a arvore estiver vazia, nao ha o que remover
		printf("\nNome nao encontrado!\n\n");
		return;
	}

	if (apagar < (*raiz)->reg){ //verifica nos nos se o nome vem antes (A-Z)
		removerArvore(L, &(*raiz)->left, apagar);
	} else if (apagar > (*raiz)->reg){ //verifica nos nos se o nome vem depois (A-Z)
        removerArvore(L, &(*raiz)->right, apagar);
    } else { // nome para apagar esta no no atual, confirmar
        printf("\n============================");
        printf("\n   Apagar %d?\n   1 - Sim\n   0 - Nao\n\n-> ", (*raiz)->reg);
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
            printf("\n   %d apagado(a) !\n\n", apagar);
        } else {
            printf("\n============================");
            printf("\n%d nao apagado (a)", apagar);
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
		int reg;
		scanf("%d", &reg);
		removerArvore(L, &aux, reg);
		L->high = treeHigh(L->root);
		L->total--;
	}//if...else
}

// funcao que adiciona valores default
void automatico(TSentinel *L){
	int matricula[10] = {100, 101, 102, 103, 104, 105, 106, 107, 108, 109};
	int i;
	for (i=0; i<10; i++)
		insereNaArvore(&(L->root), matricula[i]);
	L->high = treeHigh(L->root);
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
void initializeDB(TSentinel *L, FILE* f){
	int reg;

	// Percorre todo arquivo pegando dados do aluno
	while (!feof(f)){
		// Toda linha eh um numero 
		fscanf(f, " %d", &reg);
		// Adiciona o Aluno na lista correspondete da tabela hash
		insereNaArvore(&(L->root), reg);
  	}//while
	L->high = treeHigh(L->root);
}

// subfuncao de saveBase, percorre todos nos salvando os dados
void saveThrow(TTree* node, FILE* file){
    if(node==NULL) return;
	saveThrow(node->left, file);
    fprintf(file, "%d\n", node->reg);
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
