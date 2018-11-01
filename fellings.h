#ifndef _FELLINGS_H_
#define _FELLINGS_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#define TAM_PALAVRA 1000

int g_comp;
int g_cons;

struct S_Dado{
    int sent;
    char palavra[TAM_PALAVRA];
    };
typedef struct S_Dado Dado;

struct S_Nodo{
    Dado info;
    int FB;
    struct S_Nodo *esq;
    struct S_Nodo *dir;
    };
typedef struct S_Nodo Nodo;

char *strlwr (char *str);
Nodo *Consulta_sentimento(Nodo* abp, char palavras[]);
void imprimir(Nodo *a);
Nodo* Inicializa();
void ImprimeArvoreBonita(Nodo *abp, int traco);
Nodo* InsereAbp_sentimento(Nodo *abp,int sentimento,char palavra[]);
Nodo* Atualiza_arvore(Nodo *abp);
int Altura(Nodo *abp);
int fatores(Nodo* abp);
Nodo* InsereAvl_sentimento(Nodo *abp, int sentimento, char palavra[], int *balanceado);
Nodo* Rotacao_dupla_esq(Nodo *abp);
Nodo* Rotacao_dupla_dir(Nodo *abp);
Nodo* Rotacao_simples_dir(Nodo *abp);
Nodo* Rotacao_simples_esq(Nodo *abp);
Nodo* Roda_direita(Nodo *abp,int *balanceado);
Nodo* Roda_esquerda(Nodo *abp,int *balanceado);
void menu();
void printCarac(char, int);
int leOpcao(int, int);
void imprimeEstatisticas(char*, int, int);


#endif
