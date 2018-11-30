#include "fellings.h"

extern int g_comp_insere; // Variavel para contar o numero de insercoes
extern int g_comp_consulta; // Variavel para contar o numero de consultas

int main(int argc, char *argv[]) {

    setlocale(LC_ALL," ");

    FILE * lexico;// Variavel de tipo arquivo para ler o lexico
    FILE * texto; // Variavel de tipo arquivo para ler o text
    FILE * saida; // Variavel de tipo arquivo para ler o saida

    Nodo *arvore; // Arvore que sera usada para armazenar o lexico
    Nodo *aux; // Nodo auxiliar

    arvore = Inicializa(); /*Inicializa a Arvore com NULL*/

    int opcao = 0; // opcoes do menu

    int soma_sentimento = 0; // Acumulador de nodos em uma fras
    int sentimento = 0; // Salva o sentimento de um nodo
    int balanceado = 0;
    /* Usado para verificar se o nodo de uma avl esta balanceado */


    char *palavras_temp;
    char palavra[TAM_PALAVRA];
    char linha[TAM_PALAVRA];
    char frase_original[TAM_PALAVRA];
    char separador[] = {" \n\t\'\""};


    if (argc != 4) {
        printf("Numero incorreto de parametros.\nPara chamar o programa digite: feelings <arq_lexico> <arq_texto> <arq_saida>\n");
         return -1;
    }/* Verifica se possui o numero correto de parametros */
    else {

        printf("\n\n %-10s\n", "Algoritmo de Analise de Sentimentos com implementacao ABP/AVL");
        printf(" %-10s\n", "Por: Arthur Camargo e Pablo Rodrigues");
        printf(" %-10s\n\n\n", "Ultima modificacao: 30/11/2018");

        /* Imprime o nome da dupla */

        do {
            clock_t begin = clock(); /* Comeca a contagem do tempo de execucao */

            Menu();                    /* Le o menu e pede uma opcao */
            opcao = Le_Opcao(1,3);


            if ((lexico = fopen(argv[1], "r")) == NULL) {
               printf("Error ao abrir o arquivo %s", argv[1]);
               return -1;
            }/*Verifica se o lexico abriu*/
            else {
                g_comp_insere = 0;
                g_comp_consulta = 0;
                arvore = Inicializa();
                switch (opcao) {
                    case 1:
                    /* Caso tenha que executar algoritmo de ABP */
                        while (fscanf(lexico,"%s\t%d", &palavra, &sentimento) != EOF) {
                            arvore = InsereAbp_Sentimento(arvore, sentimento, palavra);
                        }
                        fclose(lexico);
                    break;

                    case 2:
                    /* Caso tenha que executar algoritmo da AVL */
                         while (fscanf(lexico,"%s\t%d", &palavra, &sentimento) != EOF) {
                            arvore = InsereAvl_Sentimento(arvore, sentimento, palavra, &balanceado);
                        }
                        fclose(lexico);
                    break;

                    case 3:
                    /* Caso tenha que sair */
                         printf("\n  \t\t\tPrograma Encerrado\n");
                         return 0;
                    break;
                }
            }

            if (!(texto = fopen(argv[2], "r"))) {
              printf("Error ao abrir %s", argv[2]);
                return -1;
            }/* Verifica se o texto abriu */

            if (!(saida = fopen(argv[3], "w"))) {
                printf("Error ao abrir %s", argv[3]);                //Arquivo de saida nao abriu
                return -1;
            }/* Verifica se a saida abriu */

            while (fgets(linha, TAM_PALAVRA, texto)) {
                /* Le o texto linha por linha */
                strcpy(frase_original,linha); // Salva a linha original
                soma_sentimento = 0;// Zera o sentimento da frase

                palavras_temp = strtok(linha, separador);
                /* Divide a linha em palavras de acordo
                    com os caracteres especiais especificados*/

                while (palavras_temp != NULL) {
                    /* Le palavra por palavra da frase */
                    palavras_temp = strlwr(palavras_temp);
                    /* Transforma as palavras em minusculas */
                    aux = Consulta_Palavras(arvore, palavras_temp);
                    /* Consulta o sentimento de cada palavra
                        e armazena em um nodo auxiliar */

                    if (NULL != aux) {
                        sentimento = aux->info.sent;
                        soma_sentimento += sentimento;
                    }/* Se o nodo nao for NULL, pega o sentimento
                        e soma ao contador de sentimento da frase */

                    palavras_temp = strtok(NULL, separador);
                    /* Divide a linha em palavras */
                }

                fprintf(saida,"%d ", soma_sentimento);
                /* Imprime o sentimento da frase */
                fprintf(saida,"%s", frase_original);
                /* Imprime a frase original */
            }

            fclose(texto); // Fecha os arquivos
            fclose(saida); // *

            clock_t end = clock(); // Finaliza a contagem do tempo de execucao
            double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
            /* Calcula o tempo gasto (final - inicial/ numero de clocks) */

            printf("Tempo de execucao: %lf\n", time_spent);
            /* Imprime o tempo de execucao */

            if (opcao == 1) {
                Imprime_Estatisticas("ABP", g_comp_insere, g_comp_consulta);
            }/* Se foi executado o algoritmo da abp
                imprime as estatisticas da abp */
            if (opcao == 2) {
               Imprime_Estatisticas("AVL", g_comp_insere, g_comp_consulta);
            }/* Se for executado o algoritmo da avl
               imprime as estatisticas da avl */

        } while (opcao != 3);
    }
    printf("\n  \t\t\tPrograma Encerrado\n");
    /* FIM */
    return 0;
}
