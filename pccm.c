#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    char *arquivo = argv[1];
    char inicio = argv[2][0];

    int n_vertices, n_arcos;
    char id;

    int a, b, c;

    printf("Grafos: %s\n", arquivo);
    printf("Início: %c\n", inicio);

    //Abre o arquivo de entrada .txt com os grafos
    FILE *entrada = fopen(arquivo, "r");

    //Cria um vetor para armazenar uma linha
    char linha[256];

    //Armazena a entrada de uma linha
    fgets(linha, 256, entrada);

    //Lê o a primeira linha e armazena os valores do número de vértices e arcos
    sscanf(linha, "%c %d %d", &id, &n_vertices, &n_arcos);

    //Lê cada linha e armazena os valores dos vértices e arcos nas respectivas variáveis
    while(id != 'T'){
        fgets(linha, 256, entrada); 
        sscanf(linha, "%c %d %d %d", &id, &a, &b, &c);
        printf("%c ", id);
        printf("%d ", a);
        printf("%d ", b);
        printf("%d\n", c);
    }

    

    return 0;
}