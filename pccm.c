#include <stdio.h>
#include <stdlib.h>

//Struct para representar um arco
typedef struct _arco {
    int destino;
    int custo;
    struct _arco *prox; //Ponteiro para o próximo arco da mesma origem
} Arco;

//Structt para representar um vértice do grafo
typedef struct _vertice {
    int indice;
    int g_saida;
    int g_entrada;
    Arco *adjacencias; //Lista de adjacencias que contem os arcos que saem deste vertice
} Vertice;

void adicionarArco(Vertice *vertice, int destino, int custo){
    Arco *novo = (Arco*)malloc(sizeof(Arco));

    novo->destino = destino;
    novo->custo = custo;
    novo->prox = vertice->adjacencias; //Proximo arco aponta para a lista de adjacencias

    //Adiciona novo arco a lista de arcos que saem deste vertice
    vertice->adjacencias = novo;

}

void imprimirGrafo(Vertice *vertices, int n_vertices){
    
    for(int i=0; i<n_vertices; i++){
        printf("Vértice %d:", i);
        Arco *atual = vertices[i].adjacencias;

        while(atual != NULL){
            printf(" -> %d (%d)", atual->destino, atual->custo);
            atual = atual->prox;
        }
        printf("\n");

    }

}


void bellmanFord(Vertice *vertices, int n_vertices, int inicio){

    int anterior[n_vertices];
    int distancia[n_vertices];

    for(int i=0; i<n_vertices; i++){
        distancia[i] = 100000;
        anterior[i] = -1;
    }

    distancia[inicio] = 0;

    //Repete o relaxamento por n(G) - 1
    for(int i=0; i<n_vertices-1; i++){

        //Percorre todos os vertices para percorrer as adjacencias
        for(int origem=0; origem<n_vertices; origem++){
            Arco *atual = vertices[origem].adjacencias;

            //Percorre todas as adjacencias do vertice de origem
            while(atual != NULL){
                int u = origem;
                int v = atual->destino;
                int custo = atual->custo;

                if((distancia[u] != 100000) && (distancia[u] + custo < distancia[v]) ){
                    distancia[v] = distancia[u] + custo;
                    anterior[v] = u;
                }
                //Vai para o proximo arco da lista de adjacencias do vertice de origem
                atual = atual->prox;
            }
        }
    }

    printf("Menor caminho a partir do vértice %d:\n", inicio);
    for(int i = 0; i < n_vertices; i++){
        printf("Vértice %d: Distância = %d, Anterior = %d\n", i, distancia[i], anterior[i]);
    }


}


int main(int argc, char *argv[]){
    char *arquivo = argv[1];
    char s = argv[2][0];

    int inicio = atoi(&s);

    int n_vertices, n_arcos;
    char id;

    //Abre o arquivo de entrada .txt com os grafos
    FILE *entrada = fopen(arquivo, "r");

    //Cria um vetor para armazenar uma linha
    char linha[256];

    //Armazena a entrada da primeira linha
    fgets(linha, 256, entrada);

    //Lê o a primeira linha e armazena os valores do número de vértices e arcos
    sscanf(linha, "%c %d %d", &id, &n_vertices, &n_arcos);

    //Inicializa vetor que contem os vertices
    Vertice *vertices = (Vertice*)malloc(sizeof(Vertice) * n_vertices); 

    int indice, g_saida, g_entrada;
    for(int i=0; i<n_vertices; i++){
        fgets(linha, 256, entrada);
        sscanf(linha, "%c %d %d %d", &id, &indice, &g_saida, &g_entrada);

        vertices[i].indice = indice;
        vertices[i].g_saida = g_saida;
        vertices[i].g_entrada = g_entrada;
        vertices[i].adjacencias = NULL;

    }

    int origem, destino, custo;
    for(int i=0; i<n_arcos; i++){
        fgets(linha, 256, entrada);
        sscanf(linha, "%c %d %d %d", &id, &origem, &destino, &custo);

        //Adiciona arco na lista de adjacencias do vertice de origem deste arco
        adicionarArco(&vertices[origem], destino, custo); 
    
    }

    //imprimirGrafo(vertices, n_vertices);

    bellmanFord(vertices, n_vertices, inicio);

    free(vertices);

    return 0;
}