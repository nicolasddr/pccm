#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int vertice;
    int peso;
    struct Node *prox;
} Node;

typedef struct {
    int n_vertices;
    int n_arcos;
    Node **adjacencias;
} Grafo;

void inicializaGrafo(Grafo *grafo, int n_vertices){
    grafo->n_vertices = n_vertices;
    grafo->n_arcos = 0;
    grafo->adjacencias = (Node**)malloc(n_vertices * sizeof(Node*));
    for(int i=0; i<n_vertices; i++){
        grafo->adjacencias[i] = NULL;
    }
}

void imprimirGrafo(Grafo *grafo){
    printf("\nImprimindo grafo com %d vértices e %d arcos\n", grafo->n_vertices, grafo->n_arcos);
    Node* atual;
    for(int i=0; i<grafo->n_vertices; i++){
        printf("[%d]", i);
        atual = grafo->adjacencias[i];
        while(atual){
            printf(" ->%d (%d)", atual->vertice, atual->peso);
            atual = atual->prox;
        }
        printf("\n");
    }
}

void insereAresta(Grafo *grafo, int v1, int v2, int peso){
    Node *novo, *ant = NULL;
    Node *atual = grafo->adjacencias[v1];
    while(atual && atual->vertice<v2){
        ant = atual;
        atual = atual->prox;
    }

    novo = (Node*)malloc(sizeof(Node));
    novo->vertice = v2;
    novo->peso = peso;
    novo->prox = atual;

    if(ant) ant->prox = novo;
    else grafo->adjacencias[v1] = novo;

    grafo->n_arcos++;

}

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

    

    Grafo *grafo = (Grafo*)malloc(sizeof(Grafo)); 
    inicializaGrafo(grafo, n_vertices);

    //Lê cada linha e armazena os valores dos vértices e arcos nas respectivas variáveis
    while(id != 'T'){
        fgets(linha, 256, entrada); 
        sscanf(linha, "%c %d %d %d", &id, &a, &b, &c);

        if(id == 'N'){
            printf("vertice");
        } else if(id == 'E'){
            insereAresta(grafo, a, b, c);
        }

        
    }

    imprimirGrafo(grafo);

    return 0;
}