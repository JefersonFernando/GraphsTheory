#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <locale.h>
#include <limits.h>
#define vertice int

// Estrutura do grafo, Ver � a quantidade de vertices, verX e verY s�o as coordenadas de cada vertice, Ar � a quantidade de arestas e adjacencia
// � a matriz de adjacencia que representa as liga��es entre os vertices.

struct grafo {

    int Ver;
    int* VerX;
    int* VerY;
    int Ar;
    int** adjacencia;

};

// Definindo o tipo Grafo.

typedef struct grafo* Grafo;

FILE* outputFile;

// Alocação de matriz, as variaveis r e c determinam a quantidade de linhas e colunas enquanto a val � o valor de cada posição.

static int** Matriz(int r, int c, int val) {

    int** matriz = malloc(r * sizeof(int*));

    for (vertice i = 0; i < r; ++i) {
        matriz[i] = malloc(c * sizeof(int));
    }
    for (vertice i = 1; i < r; ++i) {
        for (vertice j = 1; j < r; ++j)
            matriz[i][j] = val;
    }
    return matriz;
}

// Inicializa��o de um grafo com 0 arrestas e v para quantidade de vertices.

Grafo constroiGrafo(int v) {

    Grafo G = malloc(sizeof * G);
    G->Ver = v;
    G->VerX = malloc(v * sizeof(int*));
    G->VerY = malloc(v * sizeof(int*));
    G->Ar = 0;
    G->adjacencia = Matriz(v + 1, v + 1, 0);

    return G;

}

// Mostra a matriz de adjacencia por completo.
void exibeMatriz(Grafo g) {
    for (vertice v = 1; v < g->Ver + 1; ++v) {
        for (vertice w = 1; w < g->Ver + 1; ++w)
            printf("%d  ", g->adjacencia[v][w]);
        printf("\n");
    }
    printf("\n");
}

// Insere uma aresta com peso passado por parametro entre os vertices v-w no grafo caso essa aresta nao exista.

void insereAresta(Grafo g, vertice v, vertice w, int peso) {

    if (g->adjacencia[v][w] == 0) {
        g->adjacencia[v][w] = peso;
        g->Ar++;
    }
}

// Importa o grafo de um arquivo de texto.

Grafo importarGrafo(char* path) {

    FILE* file;

    file = fopen(path, "r");
    int i;
    int qntVertices = 0;
    int qntArestas = 0;

    fscanf(file, "%d\n ", &qntVertices);
    fscanf(file, "%d\n", &qntArestas);
    Grafo g = constroiGrafo(qntVertices);

    for (i = 0; i < qntArestas; i++) {

        int v = 0, w = 0, peso = 0;
        fscanf(file, "%d %d %d\n", &v, &w, &peso);
        insereAresta(g, v, w, peso);
    }
    return g;
}

int procuraMenorDistancia(float* dist, int* visitado, int nv) {

    int i, menor = INT_MAX, primeiro = 1;

    for (i = 0; i < nv; i++) {
        if (dist[i] < menor && visitado[i] == 0) {
            if (primeiro) {
                menor = i;
                primeiro = 0;
            }
            else {
                if (dist[menor] > dist[i])
                    menor = i;
            }
        }
    }
    return menor;
}

void menorCaminho(Grafo g, int ini, int* ant, float* dist, int v2) {

    int i, cont = 0, NaoVisitado = 0, ind = 0, * visitado, vertice_processado = 0;

    cont = g->Ver;
    NaoVisitado = g->Ver + 1;

    visitado = (int*)malloc(NaoVisitado * sizeof(int));

    for (i = 0; i < NaoVisitado; i++) {

        ant[i] = -1;
        dist[i] = INT_MAX;
        visitado[i] = 0;
    }

    dist[ini] = 0;

    while (cont > 0) {

        vertice_processado = procuraMenorDistancia(dist, visitado, NaoVisitado);

        visitado[vertice_processado] = 1;

        cont--;

        int vizinho;

        for (vizinho = 0; vizinho < g->Ver + 1; vizinho++) {

            if (g->adjacencia[vertice_processado][vizinho] > 0) {

                ind = g->adjacencia[vertice_processado][vizinho] + dist[vertice_processado];

                if (ind < dist[vizinho]) {

                    ant[vizinho] = vertice_processado;
                    dist[vizinho] = ind;
                }
                ind = 0;
            }
        }
    }

    free(visitado);

}

void lerGrafo(Grafo g1, bool grafoCriado, int ver, int ver2, bool outputF) {

    if (grafoCriado) {
        if (ver2 == -1) {
            ver2 = g1->Ver + 1;

            int ant[g1->Ver + 1];
            float dist[g1->Ver + 1];

            menorCaminho(g1, ver, ant, dist, ver2);
            int i;

            for (i = 1; i < g1->Ver + 1; i++) {
                if (outputF)  fprintf(outputFile, "%d:%.0f  ", i, dist[i]);
                else printf("%d:%.0f  ", i, dist[i]);
            }
        }
        else {
            int ant[g1->Ver + 1];
            float dist[g1->Ver + 1];

            menorCaminho(g1, ver, ant, dist, ver2);
            int i;
            if (dist[ver2] <= 9999) {
                if (outputF) fprintf(outputFile, "%.0f \n", dist[ver2]);
                else printf("%.0f \n", dist[ver2]);
            }
            else {
                if (outputF) fprintf(outputFile, "Não existe caminho entre os vertices escolhidos");
                else printf("Não existe caminho entre os vertices escolhidos");
            }
        }
    }
    else {
        if (outputF) fprintf(outputFile, "Grafo nao iniciado\n");
        else printf("Grafo nao iniciado\n");
    }
}

int main(int argc, char* argv[]) {

    int parameter, initial = -1, last = -1;
    bool s = false, outputF = false;
    bool grafoCriado = false;
    Grafo g1;

    for (parameter = 0; parameter < argc; parameter++) {

        if (strcmp(argv[parameter], "-h") == 0) {
            printf("-h \t\t\t\t : mostra o help\n-o <arquivo> \t\t\t : redireciona a saida para o \"arquivo\"\n-f <arquivo> \t\t\t : indica o \"arquivo\" que contém o grafo de entrada\n-s \t\t\t\t : mostra a solução (em ordem crescente)\n-i \t\t\t\t : vértice inicial (dependendo do algoritmo)\n-l \t\t\t\t : vértice final (dependendo do algoritmo)\n\n");
            return 0;
        }
        else if (strcmp(argv[parameter], "-o") == 0) {
            outputFile = fopen(argv[parameter + 1], "w");
            outputF = true;
        }
        else if (strcmp(argv[parameter], "-f") == 0) {
            if (strcmp(argv[parameter + 1], "-s") == 0) {
                s = true;
                g1 = importarGrafo(argv[parameter + 2]);
                grafoCriado = true;
            }
            else {
                g1 = importarGrafo(argv[parameter + 1]);
                grafoCriado = true;
            }
        }
        else if (strcmp(argv[parameter], "-i") == 0) {
            initial = atoi(argv[parameter + 1]);
        }
        else if (strcmp(argv[parameter], "-l") == 0) {
            last = atoi(argv[parameter + 1]);
        }
    }

    lerGrafo(g1, grafoCriado, initial, last, outputF);

    return 0;
}

