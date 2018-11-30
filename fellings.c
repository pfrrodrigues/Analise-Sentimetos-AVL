#include "fellings.h"


 extern int g_comp_insere; // Variavel para contar o numero de insercoes
extern int g_comp_consulta; // Variavel para contar o numero de comparacoes

Nodo* Inicializa() {
    return NULL;
}/* Inicializa uma abp com NULL*/


 void Menu() {
    printf("+"); Print_Carac('-', 60); printf("+\n");                         // +-----------------------------------+
    printf("|\t\t\t\t%-29s|\n", "MENU");                                     // |              menu                 |
    printf("+"); Print_Carac('-', 60); printf("+\n");                         // +-----------------------------------+
    printf("%-61s|\n", "|");                                                 // |                                   |
    printf("|\t  %-5sExecutar algoritmo de AS com ABP\t\t     |\n", "1.");   // |         1. XXXXXXXXXXXX           |
    printf("|\t  %-5sExecutar algoritmo de AS com AVL\t\t     |\n", "2.");   // |         2. XXXXXXXXXXXX           |
    printf("|\t  %-5sEncerrar programa\t\t\t     |\n", "3.");                // |         3. XXXXXXXXXXXX           |
    printf("%-61s|\n", "|");                                                 // |                                   |
    printf("+"); Print_Carac('-', 60); printf("+\n");                         // +-----------------------------------+

}/* Imprime o menu de opcoes */


 int Le_Opcao(int msl,int msb) {
    int op; // Variavel auxiliar para ler a opcao digitada pelo usuario

    do {
        printf("\t\t\t\tOpcao: ");
        scanf("%d",&op);
    } while (op <= msl && op >= msb);

    return op;
}/* Le opcoes, e as valida de acordo com os parametros */

void Print_Carac(char c, int z) {

    int i; // contador

    for (i = 0; i < z; i++) {
        printf("%c", c);
    }
}/* Imprime um character 'z' vezes */

void Imprime_Estatisticas(char* tipoArvore, int nmrComparacoes, int nmrConsultas) {

    printf("+"); Print_Carac('-', 60); printf("+\n");
    printf("|   arvore\t| \tcomparacoes\t|  consultas   \t     |\n");
    printf("+"); Print_Carac('-', 60); printf("+\n");
    printf("|     %-10s|         %-14d|   %-17d|\n", tipoArvore, nmrComparacoes, nmrConsultas);
    printf("+"); Print_Carac('-', 60); printf("+\n");
}/*
 * Exibe estatisticas de comparacoes de consultas de uma determinada arvore
 * sendo o tipo de arvore, o numero de comparacoes e o numero de consultas
 * passados por parametro
 */


Nodo *Consulta_Palavras(Nodo *abp, char palavra[]) {

    while(abp != NULL) {
        g_comp_consulta++;

         if (strcmp(palavra, abp->info.palavra) == 0) {
            g_comp_consulta++; // Incrementa o contador de consultas

            return abp;
        }/* Se a palavra da abp for igual a palavra procurada retorna abp */
        else {
            g_comp_consulta++;

            if(strcmp(palavra, abp->info.palavra) < 0)
                return Consulta_Palavras(abp->esq, palavra);
                /* Se a palavra da abp for menor, em ordem lexicografica
                retorna Consulta_Palavras da abp esquerda */
            else
               return Consulta_Palavras(abp->dir, palavra);
               /* Senao retorna a abp direita */
        } 
    }
    return NULL;  
}


Nodo *InsereAbp_Sentimento(Nodo *abp,int sentimento,char palavra[]) {


    if (NULL == abp) {
        g_comp_insere++; // Incrementa o numero de comparacoes para se inserir

        Nodo* novo;
        novo = (Nodo*) malloc(sizeof(Nodo));
        novo->info.sent = sentimento;
        strcpy(novo->info.palavra, palavra);
        novo->dir = NULL;
        novo->esq = NULL;
        return novo;
    }/* Se a abp for nula retorna um novo nodo com os valores dados */
    else if (strcmp(palavra , abp->info.palavra) < 0) {
        g_comp_insere++; // Incrementa o numero de comparacoes para se inserir

        abp->esq = InsereAbp_Sentimento(abp->esq, sentimento, palavra);
    }/* Se a palavra a ser inserida for menor, lexicograficamente
        que a abp, Insere na abp da esquerda */
    else {
        g_comp_insere++; // Incrementa o numero de comparacoes para se inserir

        abp->dir = InsereAbp_Sentimento(abp->dir, sentimento, palavra);
    }/* Senao insere na abp da direita */
    return abp;
}

Nodo* InsereAvl_Sentimento(Nodo *avl, int sentimento, char palavra[],int *balanceado) {


    if (avl == NULL) {
        g_comp_insere++;// Incrementa o numero de comparacoes para se inserir

        avl = (Nodo*) malloc(sizeof(Nodo));
        avl->info.sent = sentimento;
        strcpy(avl->info.palavra, palavra);
        avl->dir = NULL;
        avl->esq = NULL;
        avl->FB = 0;
        *balanceado = 1;
        return avl;
    } /* Se a AVL for nula, retorna um novo nodo com as informacoes dadas */

    else if (strcmp(palavra ,avl->info.palavra) <= 0) {
        g_comp_insere++;// Incrementa o numero de comparacoes para se inserir

        avl->esq = InsereAvl_Sentimento(avl->esq, sentimento, palavra, balanceado);
        /* Se o novo nodo for menor, lexicograficamente
            Insere o nodo na AVL da esquerda */
        if (*balanceado) {
            switch (avl->FB) {
                case -1: avl->FB = 0; *balanceado = 0; break;
                /* Caso a AVL tenha balanceamento -1, fica 0 e o nodo se torna
                    balanceado */
                case  0: avl->FB = 1; break;
                /* Caso a avl tenha balanceamento 0, fica 1 */
                case  1: avl = Roda_direita(avl, balanceado); break;
                /* Caso a avl tenha balanceamento 1, e efetuado
                    uma rotacao para direita */
            }
        }/* Verifica se o nodo esta balanceado */
     }
     else {
         g_comp_insere++;// Incrementa o numero de comparacoes para se inserir


         avl->dir = InsereAvl_Sentimento(avl->dir, sentimento, palavra, balanceado);
         /* Senao Insere o nodo na AVL da esquerda */
         if (*balanceado) {
             switch (avl->FB) {
                 case  1: avl->FB = 0; *balanceado = 0; break;
                 /* Caso a AVL tenha balanceamento 1, fica 0 e o nodo se torna
                     balanceado */
                 case  0: avl->FB = -1; break;
                 /* Caso a AVL tenha balancemento 0, fica -1 */
                 case -1: avl = Roda_esquerda(avl, balanceado); break;
                 /* Caso a AVL tenha balanceamento -1, e efetuado
                    uma rotacao para esquerda */
            }
        }/* Verifica se o nodo esta balanceado */
    }
    return avl;
}

Nodo* Roda_direita(Nodo *avl, int *balanceado) {
    Nodo *novo;
    novo = avl->esq;

    if (0 <= novo->FB) {
        avl = Rotacao_simples_dir(avl);
    } /* Se o balanceamento do nodo for positivo
        efetua uma rotacao simples */
    else {
        avl = Rotacao_dupla_dir(avl);
    }/* Senao efetua uma rotacao dupla */

    avl->FB = 0;        // * Torna o nodo balanceado
    *balanceado = 0;    // *

    return avl;

}

Nodo* Roda_esquerda(Nodo *avl, int *balanceado){
    Nodo *novo;
    novo = avl->dir;

    if (0 >= novo->FB) {
        avl = Rotacao_simples_esq(avl);
    }/* Se o balanceamento do nodo for positivo
        efetua uma rotacao simples */
    else {
        avl = Rotacao_dupla_esq(avl);
    }/* Senao efetua uma rotacao dupla */

    avl->FB = 0;        //* Torna o nodo balanceado
    *balanceado = 0;    // *

    return avl;
}

Nodo* Rotacao_simples_dir(Nodo *p){
    Nodo *u;
    u = p->esq;
    /* u recebe o nodo esquedo de p */                       //         u
    p->esq = u->dir;                                         //        /  \
    /* o nodo esquerdo de p recebe o nodo direito do u */    //       p   p->esq
    u->dir = p;                                              //     /  \
    /* p recebe o nodo direito do u */                       // u->dir p->dir

    p->FB = 0;    //Balanceia o nodo

    return u;
}

Nodo* Rotacao_simples_esq(Nodo *p){
    Nodo *u;
    u = p->dir;
    /* u recebe o nodo direito de p */                      //          u
    p->dir = u->esq;                                        //         /  \
    /* o nodo direito de p recebe o nodo esquerdo de u */   //    p->dir   p
    u->esq = p;                                             //           /   \
    /* p recebe o nodo esquerdo de u */                     //       u->esq  p->esq
    p->FB = 0;  //Balanceia o nodo

    return u;
}

Nodo* Rotacao_dupla_dir(Nodo *p){
    Nodo *u;
    Nodo *v;
    u = p->esq;                                             /*            v                */
    /* u recebe o nodo esquerdo de p */                     /*         /     \             */
    v = u->dir;                                             /*       /         \           */
    /* v recebe o nodo direito de u */                      /*      u            p         */
    p->esq = v->dir;                                        /*    /    \       /    \      */
    /* o nodo esquerdo de p recebe o nodo direito de v */   /* u->esq v->esq v->dir p->dir */
    u->dir = v->esq;
    /* o nodo direito de u recebe o nodo esquerdo de v */
    v->dir = p;
    /* o nodo direito de v recebe o p */
    v->esq = u;
    /* o nodo esquerdo de v recebe o u */

    if(v->FB == 1)
    /* Se o balanceamento do v era 1, o p vira -1 */
        p->FB = -1;
    else
        p->FB = 0;
    /* Senao vira o p 0 */

    if(v->FB == -1)
    /* Se o balanceamento do v era -1, o u vira 1 */
        u->FB = 1;
    else
    /* Senao o u vira 0 */
        u->FB = 0;

    return v;
}

Nodo* Rotacao_dupla_esq(Nodo *p){
    Nodo *u;
    Nodo *v;
    u = p->dir;                                             /*            v                */
    /* u recebe o nodo direito de p */                      /*         /     \             */
    v = u->esq;                                             /*       /         \           */
    /* v recebe o nodo esquerdo de u */                     /*      p            u         */
    p->dir = v->esq;                                        /*    /    \       /    \      */
    /* o nodo direito de p recebe o nodo esquerdo de v */   /* p->esq v->esq v->dir u->dir */
    u->esq = v->dir;
    /* o nodo esquerdo de u recebe o nodo direito de v */
    v->dir = u;
    /* o nodo direito de v recebe u */
    v->esq = p;
    /* o nodo esquerdo de v recebe p */

    if(v->FB == -1)
    /* Se o balanceamento do v era -1, o p vira 1 */
        p->FB = 1;
    else
    /* Senao o p vira 0 */
        p->FB = 0;

    if(v->FB == 1)
    /* Se o balanceamento de v era 1, o u vira -1 */
        u->FB = -1;
    else
    /* Senao o u vira 0 */
        u->FB = 0;

    return v;
}

char *strlwr(char *str)
{
  unsigned char *p = (unsigned char *)str;

  while (*p) {
     *p = tolower((unsigned char)*p);
      p++;
  } /* Enquanto a string p existir
        diminui o valor da letra e incrementa o ponteiro*/

  return str;
}
