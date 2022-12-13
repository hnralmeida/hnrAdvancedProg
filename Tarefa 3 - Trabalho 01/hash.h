/*
=========================================================================================
AUTOR:	Henrique Almeida de Oliveira
Disciplina: Topicos de Programacao Avancada

					Trabalho 01 – Tabela Hash

Biblioteca de HASH
=========================================================================================
*/

#ifndef HASH_H_
#define HASH_H_

/*
=========================================================================================
			Tipo Abstrato de Dados
*/

/* Implementa adicionao de um elemento na tabela hash */
void addElementHash (Tlist list[], unsigned long long int size);

/* Imprimir valores na tabela hash */
void printHash(Tlist list[], unsigned long long int size);

/* Remover valores da tabela hash */
void removeHash(Tlist list[], unsigned long long int size); 

/* Conta o numero de linhas em um arquivo */
 unsigned long long int calcSize(FILE* f);

/* Inicializar hash a partir de banco de dados no ponto de onde parou */
void initializeDB(Tlist list[], FILE* f, unsigned long long int size);

/* Procura na tabela hash pela matricula informada e declara o nome e matricula dele
	ou informa que nao o encontrou
*/
void searchStudent(Tlist list[], unsigned long long int size);

/* Salva a tabela hash no arquivo Lista_Aluno_Matricula.txt  */
void saveFile(Tlist vetor[], unsigned long long int size);

#endif // HASH_H_
