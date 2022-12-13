/*
=========================================================================================
AUTORES: 	
			Henrique Almeida de Oliveira
			Luiz Eduardo Marchiori
Disciplina: Tópicos de Programação Avançada

Biblioteca de HASH
=========================================================================================
*/

#ifndef HASH_H_
#define HASH_H_

/*
=========================================================================================
			Tipo Abstrato de Dados
*/

// adiciona um vetor na tabela hash
void addElementHash (Tlist list[], int tam);

// imprimir valores na tabela hash
void printHash(Tlist list[], int tam);

// remover valores da tabela hash
void removeHash(Tlist list[], int tam); 

#endif // HASH_H_
