 #include "fellings.h"


extern int g_comp;
extern int g_cons;

Nodo* Inicializa(){
    return NULL;
    }



 /*
  * função do menu de opções
  */
 void menu() {
    printf("+"); printCarac('-', 60); printf("+\n");                         // +-----------------------------------+
    printf("|\t\t\t\t%-29s|\n", "MENU");                                     // |              menu                 |
    printf("+"); printCarac('-', 60); printf("+\n");                         // +-----------------------------------+
    printf("%-61s|\n", "|");                                                 // |                                   |
    printf("|\t  %-5sExecutar algoritmo de AS com ABP\t\t     |\n", "1.");   // |         1. XXXXXXXXXXXX           |
    printf("|\t  %-5sExecutar algoritmo de AS com AVL\t\t     |\n", "2.");   // |         2. XXXXXXXXXXXX           |
    printf("|\t  %-5sEncerrar programa\t\t\t     |\n", "3.");                // |         3. XXXXXXXXXXXX           |
    printf("%-61s|\n", "|");                                                 // |                                   |
    printf("+"); printCarac('-', 60); printf("+\n");                         // +-----------------------------------+

 }

/*
 * le opção fornecida pelo usuario
 * e valida opcao conforme o intervalo passado como
 * parametro para a funcao
 */
 int leOpcao(int msl,int msb) {
    int opcao; // variavel auxiliar para ler a opção digitada pelo usuario

    do {
        printf("\t\t\t\topcao: ");
        scanf("%d",&opcao);
    } while (opcao < msl || opcao > msb);

    return opcao;
 }

 /*
  * printa o caractere passado como parametro
  * o numero de vezes passados através da var
  * qtd.
  */
  void printCarac(char c, int z) {

    int i; // contador

    for (i = 0; i < z; i++) {
        printf("%c", c);
    }
  }

/*
 * exibe estatisticas de comparações de consultas de uma determinada árvore
 * sendo o tipo de árvore, o numero de comparações e o numero de consultas
 * passados por parâmetro
 */
 void imprimeEstatisticas(char* tipoArvore, int nmrComparacoes, int nmrConsultas) {
    printf("+"); printCarac('-', 60); printf("+\n");
    printf("|   arvore\t| \tcomparacoes\t|  consultas   \t     |\n");
    printf("+"); printCarac('-', 60); printf("+\n");
    printf("|     %-10s|         %-14d|   %-17d|\n", tipoArvore, nmrComparacoes, nmrConsultas);
    printf("+"); printCarac('-', 60); printf("+\n");
 }


void ImprimeArvoreBonita(Nodo *a, int traco){

    int i;

    if(a == NULL)
        return;

    traco ++;

    printf("\n");
    for( i = 0; i < traco; i ++){
         printf("=");
    }
    printf("%d - %d # %d\n", strlen(a->info.palavra), a->FB, a->info.sent);

    ImprimeArvoreBonita(a->esq, traco);
    ImprimeArvoreBonita(a->dir, traco);
}
void imprimir(Nodo *a){
    printf("(");
    if(a == NULL)
        return; // imprime -1 se encontrar um no folha
    else{
        printf("%d, ", strlen(a->info.palavra));
        imprimir(a->esq);
        imprimir(a->dir);
    }
    printf(")");
}

Nodo *Consulta_sentimento(Nodo *abp, char palavra[]){

    if (!abp)
        return NULL;

    if(strcmp(palavra, abp->info.palavra) == 0){
        return abp;
        }
    else {
        if (strcmp(palavra,abp->info.palavra) < 0) {
            g_cons++;
            return Consulta_sentimento(abp->esq, palavra);
        }
        else {
            g_cons++;
            return Consulta_sentimento(abp->dir, palavra);
        }
    }

}

Nodo* InsereAbp_sentimento(Nodo *abp,int sentimento,char palavra[] ){

    if(abp == NULL){
        Nodo* novo;
        novo = (Nodo*) malloc(sizeof(Nodo));
        novo->info.sent = sentimento;
        strcpy(novo->info.palavra, palavra);
        novo->dir = NULL;
        novo->esq = NULL;
        return novo;
    }else{
        if(strcmp(palavra , abp->info.palavra) < 0){
            g_comp++;
            abp->esq = InsereAbp_sentimento(abp->esq, sentimento, palavra);
        }else{
            g_comp++;
            abp->dir =InsereAbp_sentimento(abp->dir, sentimento, palavra);
        }
    }
    return abp;
}

Nodo* InsereAvl_sentimento(Nodo *abp, int sentimento, char palavra[],int *balanceado){

    if(abp == NULL){
        abp = (Nodo*) malloc(sizeof(Nodo));
        abp->info.sent = sentimento;
        strcpy(abp->info.palavra, palavra);
        abp->dir = NULL;
        abp->esq = NULL;
        abp->FB = 0;
        *balanceado = 1;
        return abp;

    }else if(strcmp(palavra ,abp->info.palavra) <= 0){
        g_comp++;
        abp->esq = InsereAvl_sentimento(abp->esq, sentimento, palavra, balanceado);

        if(*balanceado){
            switch(abp->FB){
                case -1: abp->FB = 0; *balanceado = 0; break;
                case  0: abp->FB = 1; break;
                case  1: abp = Roda_direita(abp, balanceado);break;
            }
        }
    }else{
        g_comp++;
        abp->dir = InsereAvl_sentimento(abp->dir, sentimento, palavra, balanceado);

        if(*balanceado){
            switch(abp->FB){
                case  1: abp->FB = 0; *balanceado = 0; break;
                case  0: abp->FB = -1; break;
                case -1:  abp = Roda_esquerda(abp, balanceado);break;
            }
        }
    }
    return abp;
}

Nodo* Roda_direita(Nodo *abp, int *balanceado){
    Nodo *novo;
    novo = abp->esq;

    if(novo->FB >= 0){
        abp = Rotacao_simples_dir(abp);
    }
    else{
        abp = Rotacao_dupla_dir(abp);
    }

    abp->FB = 0;
    *balanceado = 0;
    return abp;

}

Nodo* Roda_esquerda(Nodo *abp, int *balanceado){
    Nodo *novo;
    novo = abp->dir;

    if(novo->FB <= 0){
        abp = Rotacao_simples_esq(abp);
    }
    else{
        abp = Rotacao_dupla_esq(abp);

    }

    abp->FB = 0;
    *balanceado = 0;
    return abp;
}

Nodo* Rotacao_simples_dir(Nodo *abp){
    Nodo *u;
    u = abp->esq;
    abp->esq = u->dir;
    u->dir = abp;
    abp->FB = 0;

    return u;
}

Nodo* Rotacao_simples_esq(Nodo *abp){
    Nodo *u;
    u = abp->dir;
    abp->dir = u->esq;
    u->esq = abp;
    abp->FB = 0;

    return u;
}

Nodo* Rotacao_dupla_dir(Nodo *abp){
    Nodo *u;
    Nodo *v;
    u = abp->esq;
    v = u->dir;
    abp->esq = v->dir;
    u->dir = v->esq;
    v->dir = abp;
    v->esq = u;

    if(v->FB == 1)
        abp->FB = -1;
    else
        abp->FB = 0;

    if(v->FB == -1)
        u->FB = 1;
    else
        u->FB = 0;

    return v;
}

Nodo* Rotacao_dupla_esq(Nodo *abp){
    Nodo *u;
    Nodo *v;
    u = abp->dir;
    v = u->esq;
    abp->dir = v->esq;
    u->esq = v->dir;
    v->dir = u;
    v->esq = abp;

    if(v->FB == -1)
        abp->FB = 1;
    else
        abp->FB = 0;

    if(v->FB == 1)
        u->FB = -1;
    else
        u->FB = 0;

    return v;
}

char *strlwr(char *str)
{
  unsigned char *p = (unsigned char *)str;

  while (*p) {
     *p = tolower((unsigned char)*p);
      p++;
  }

  return str;
}
