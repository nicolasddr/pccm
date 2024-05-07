#include <stdio.h>
#include <stdlib.h>

struct _arco;

typedef struct _vertice {
    int n;
    int g_entrada;
    int g_saida;
    struct _arco **vizinhos; // Mudança para ponteiro duplo
} Vertice;

typedef struct _arco {
    Vertice saida;
    Vertice entrada;
    int custo;
} Arco;



void insereVertice(Vertice *vertices, int g_entrada, int g_saida, int n) {
    Vertice *novo = (Vertice*)malloc(sizeof(Vertice));
    novo->n = n;
    novo->g_entrada = g_entrada;
    novo->g_saida = g_saida;
    novo->vizinhos = (struct _arco**)malloc(sizeof(struct _arco*) * g_saida); // Correção na alocação
    for (int i = 0; i < g_saida; i++) {
        novo->vizinhos[i] = NULL; // Inicializa os vizinhos como NULL
    }
    vertices[n-1] = *novo;
}

void insereArco(Vertice *vertices, int saida, int entrada, int custo) {
    Arco *novo = (Arco*)malloc(sizeof(Arco));
    novo->saida = vertices[saida-1];
    novo->entrada = vertices[entrada-1];
    novo->custo = custo;

    // Adiciona o novo arco à lista de vizinhos do vértice de saída
    int i;
    for (i = 0; i < vertices[saida-1].g_saida; i++) {
        if (vertices[saida-1].vizinhos[i] == NULL) {
            vertices[saida-1].vizinhos[i] = novo;
            break; // Interrompe o loop quando encontrar uma posição livre
        }
    }
}

void imprimirGrafo(Vertice *vertices, int n_vertices){
    for(int i=0; i<n_vertices; i++){
        printf("[%d]", i+1);
        Vertice *atual = &vertices[i];
        
        if(atual->g_saida == 0){
            printf(" -> sem vizinhos\n");
        } else {
            for(int j=0; j<atual->g_saida; j++){
                Arco *arco_atual = atual->vizinhos[j];
                Vertice *vizinho_atual = &arco_atual->entrada;
                printf(" ->%d (%d)", vizinho_atual->n, arco_atual->custo);
            }
            printf("\n");

        }
        
    }
}



int main() {
    int n_vertices = 10; 
    Vertice *vertices = (Vertice*)malloc(sizeof(Vertice) * n_vertices); 

    insereVertice(vertices, 0, 2, 1);
    insereVertice(vertices, 2, 0, 2);
    insereArco(vertices, 1, 2, 3);
    insereArco(vertices, 1, 2, 4);
    
    imprimirGrafo(vertices, 2);
    
    free(vertices);

    return 0;
}

