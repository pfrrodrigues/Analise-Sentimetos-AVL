#include "fellings.h"

extern int g_comp = 0;
extern int g_cons = 0;

int main(void){

    setlocale(LC_ALL," ");

    FILE * lexico;
    FILE * texto;
    FILE * saida;

    Nodo *arvore;
    Nodo *aux;
    arvore = Inicializa();


    int soma_sentimento = 0;
    char original[TAM_PALAVRA];
    int soma_tudo = 0;
    char *bagunca;
    char palavra[TAM_PALAVRA], linha[TAM_PALAVRA];
    int sentimento;
    char c;
    char separador[] = {" ,.&*%\?!;/-'@\"$#=><()][}{:\n\t\\"};
    int balanceado=0;

    /*
    if(argc != 4){ //Numero incorreto de parametros
        printf("Numero incorreto de parametros.\n Para chamar o programa digite: feelings <arq_lexico> <arq_texto> <arq_saida>\n");
        return 1;
    }else{

        */

        printf("\n\n %-10s\n", "Algoritmo de Analise de Sentimentos com implementacao ABP/AVL");
        printf(" %-10s\n", "Por: Arthur Camargo e Pablo Rodrigues");
        printf(" %-10s\n\n\n", "Ultima modificacao: 01/11/2018");

        menu();
        int opcao = leOpcao(1,3);

        do {

            if(!(lexico = fopen("lexicon_2k_shuffled.txt", "r"))){
               printf("Error ao abrir o arquivo %s", "lexicon_2k_shuffled.txt");      //Arquivo lexico nao abriu
               return 1;
            } else {
                    g_comp = 0;
                    g_cons = 0;
                    arvore = Inicializa();
                    switch (opcao) {
                    case 1: // caso opcao seja executar algoritmo de ABP
                        while(fscanf(lexico,"%s\t%d", &palavra, &sentimento) != EOF){
                            arvore = InsereAbp_sentimento(arvore, sentimento, palavra);
                        }
                        fclose(lexico);
                    break;
                    case 2: // caso a opcao seja executar algoritmo de AVL
                         while(fscanf(lexico,"%s\t%d", &palavra, &sentimento) != EOF){
                            arvore = InsereAvl_sentimento(arvore, sentimento, palavra, &balanceado);
                        }
                        fclose(lexico);
                    break;
                    case 3: // caso a opcao seja encerrar o programa
                         printf("\n  \t\t\tPrograma Encerrado\n");
                         return 0;
                    break;
                }
            }



            if(!(texto = fopen("movieReviews1000.txt", "r"))){
                printf("Error ao abrir o arquivo %s", "movieReviews1000.txt");     //Arquivo texto nao abriu
                return 1;
            }

            if(!(saida = fopen("saida.txt", "w"))){
                printf("Error ao abrir o arquivo %s", "saida.txt");                //Arquivo de saida nao abriu
                return 1;
            }

            while(fgets(linha, TAM_PALAVRA, texto)){
                strcpy(original,linha);
                soma_sentimento = 0;
                bagunca = strtok(linha, separador);
                while(bagunca != NULL){
                    bagunca = strlwr(bagunca);

                    aux = Consulta_sentimento(arvore, bagunca);

                    if(aux){
                        sentimento = aux->info.sent;
                        soma_sentimento += sentimento;
                    }
                    bagunca = strtok(NULL, separador);
                }
                fprintf(saida,"Sentimento : %d -> ", soma_sentimento);
                fprintf(saida,"%s", original);

            }
        fclose(texto);
        fclose(saida);

        if (opcao == 1) {
            imprimeEstatisticas("ABP", g_comp, g_cons);
        }

         if (opcao == 2) {
            imprimeEstatisticas("AVL", g_comp, g_cons);
        }

        menu();
        opcao = leOpcao(1,3);
    } while (opcao != 3);

    printf("\n  \t\t\tPrograma Encerrado\n");
    return 0;
}
