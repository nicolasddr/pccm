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
    int processado;
    int reduzido_processado; //Se foi reduzido após ser processado
    int reduzido; //Se foi reduzido, mas não processado
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

void imprimirOrdem(int ordem[], int n_vertices, int i){
    printf("O %d", i);
    for(int j=0; j<n_vertices; j++){
        printf(" %d", ordem[j]);
    }
    printf("\n");
}



void bellmanFord(Vertice *vertices, int n_vertices, int inicio){

    //Inicializa vetores anteriorm distancia e ordem inicial
    int anterior[n_vertices];
    int distancia[n_vertices];
    int ordem_inicial[n_vertices];


    //Atribui valores iniciais dos vetores
    for(int i=0; i<n_vertices; i++){
        distancia[i] = 100000;
        anterior[i] = -1;
        ordem_inicial[i] = i; //Inicializa o vetor com os vértices em sequência
        vertices[i].processado = 0; //Marca todos os vértices como não processado
        vertices[i].reduzido = 0;
        vertices[i].reduzido_processado = 0;
    }
    distancia[inicio] = 0;

    //Preparar ordem inicial
    for(int i=inicio; i>0; i--){
       ordem_inicial[i] =ordem_inicial[i-1];
    }
    ordem_inicial[0] = inicio;



    //Repete o relaxamento por n(G) - 1
    for(int i=0; i<n_vertices; i++){
        
        imprimirOrdem(ordem_inicial, n_vertices, i);

        //Percorre todos os vertices para percorrer as adjacencias
        for(int j=0; j<n_vertices; j++){

            int origem = ordem_inicial[j];

            

            Arco *atual = vertices[origem].adjacencias;

            //Percorre todas as adjacencias do vertice de origem
            while(atual != NULL){
                int u = origem;
                int v = atual->destino;
                int custo = atual->custo;

                if((distancia[u] != 100000) && (distancia[u] + custo < distancia[v]) ){
                    distancia[v] = distancia[u] + custo;
                    anterior[v] = u;

                    //Se o vértice foi reduzido após ser processado
                    if(vertices[v].processado == 0){
                        vertices[v].reduzido = 1; //Vertice foi reduzido e só foi processado depois
                    } else {
                        vertices[v].reduzido_processado = 1;
                        vertices[v].reduzido = 0;
                    }

                    
                }
                //Marca como processado
                vertices[origem].processado = 1;
    
                //Vai para o proximo arco da lista de adjacencias do vertice de origem
                atual = atual->prox;
            }

        }

        //Alterar ordem
        int nova_ordem[n_vertices];
        
        //Vértices reduzidos após serem processados
        int ki=0;
        for(int k=0; k<n_vertices; k++){
            if(vertices[ordem_inicial[k]].reduzido_processado == 1){
                nova_ordem[ki] = ordem_inicial[k];
                ki++;
            }
        }

        //Vértices reduzidos e depois processados
        for(int k=0; k<n_vertices; k++){
            if(vertices[ordem_inicial[k]].reduzido == 1){
                nova_ordem[ki] = ordem_inicial[k];
                ki++;

            }
        }

        //Vértices que não foram reduzidos
        for(int k=0; k<n_vertices; k++){
            if(vertices[ordem_inicial[k]].reduzido == 0 && vertices[ordem_inicial[k]].reduzido_processado == 0){
                nova_ordem[ki] = ordem_inicial[k];
                ki++;
            }
        }

        for(int l=0; l<n_vertices; l++){
            ordem_inicial[l] = nova_ordem[l]; 
        }
        
        //Desmarcar vértices
        for(int f=0; f<n_vertices; f++){
            vertices[f].processado = 0;
            vertices[f].reduzido = 0;
            vertices[f].reduzido_processado = 0;
        }
        


    }



    //IMPRESSÃO DO CAMINHO

    int comprimento[n_vertices];
    for(int i=0; i<n_vertices; i++){
        comprimento[i] = 1;
    }
    
    
    //Imprimir o caminho dos vértices
    for(int t = 0; t<n_vertices; t++){
       

        //Achar o caminho de s até o vértice t
        int ant = anterior[t];
        int caminho[n_vertices];

        caminho[0] = t; //O fim do caminho de s até t é o próprio vértice t

        for(int i=1; i<n_vertices; i++){
            if(ant == -1){
                break;
            }
            caminho[i] = ant; //Adiciona o anterior ao caminho
            comprimento[t] += 1;
            ant = anterior[ant];
        }

        

        //Imprimir os caminhos
        if(anterior[t] == -1 && t != inicio){ //Se não há caminho até o vértice t
            printf("U %d", t);
            printf("\n");
        } else { //Existe camihno até o vértice t
            printf("P %d %d %d", t, distancia[t], comprimento[t]);
            for(int i=comprimento[t]-1; i>=0; i--){
                printf(" %d", caminho[i]);
            }
            printf("\n");
        }
        
        
        
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
