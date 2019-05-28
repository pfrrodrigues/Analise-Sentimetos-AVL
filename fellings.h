#ifndef fellings_h
#define felings_h


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#define TAM_PALAVRA (1000)

int g_comp_insere; /*Variavel global para contar comparacoes ao inserir um nodo novo*/
int g_comp_consulta; /*Variavel global para contar consultas ao consultar a arvore*/

struct S_Dado{
    int sent;
    char palavra[TAM_PALAVRA];
    };
typedef struct S_Dado Dado;/*Estrutura que armazena o sentimento e a palavra*/

struct S_Nodo{
    Dado info;
    int FB;
    struct S_Nodo *esq;
    struct S_Nodo *dir;
    };
typedef struct S_Nodo Nodo; /*Arvore Binaria com filho esquerdo, filho direito,
                                informacoes e fator de balanceamento*/

char *strlwr (char *str);
 /*Funcao transformar uma string em minusculas */

Nodo *Consulta_Palavras(Nodo* abp, char palavra[]);
/* Funcao que faz a busca em uma arvore dada uma arvore de palavras
    e a palavra */

Nodo* Inicializa();
/* Fucao que inicializa um nodo */

Nodo* InsereAbp_Sentimento(Nodo *abp,int sentimento,char palavra[]);
/* Insere uma palavra em uma ABP */

Nodo* InsereAvl_Sentimento(Nodo *avl, int sentimento, char palavra[], int *balanceado);
/* Insere uma palavra em uma AVL */

Nodo* Rotacao_dupla_esq(Nodo *p);
/* Efetua uma rotacao dupla a esquerda em uma AVL */

Nodo* Rotacao_dupla_dir(Nodo *p);
/* Efetua uma rotacao dupla a direita em uma AVL */

Nodo* Rotacao_simples_dir(Nodo *p);
/* Efetua uma rotacao simples a direita em uma AVL */

Nodo* Rotacao_simples_esq(Nodo *p);
/* Efetua uma rotacao simples a esquerda em uma AVL */

Nodo* Roda_direita(Nodo *avl,int *balanceado);
/* Verifica o tipo de rotacao dado que sera a direita em uma AVL */

Nodo* Roda_esquerda(Nodo *avl,int *balanceado);
/* Verifica o tipo de rotacao dado que sera a esquerda em uma AVL */

void Menu();
/* Imprime o menu */

void Print_Carac(char, int);
/* Imprime um caracter varias vezes */

void Imprime_Estatisticas(char*, int, int);
/* Imprime as estatisticas dadas */

int Le_Opcao(int, int);
/* Le uma opcao do menu */

#endif
