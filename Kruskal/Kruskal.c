#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <locale.h>
#include <limits.h>
#define vertice int
FILE *outputFile;

struct grafo{

    int Ver;
    int *VerX;
    int *VerY;
    int Ar;
    int **adjacencia;
    int **arestas;

};

// Definindo o tipo Grafo.

typedef struct grafo *Grafo;

// Alocação de matriz, as variaveis r e c determinam a quantidade de linhas e colunas enquanto a val é o valor de cada posição.

static int **Matriz(int r, int c, int val){

    int **matriz = malloc(r * sizeof(int *));

    for(vertice i = 0; i < r; ++i){
        matriz[i] = malloc(c * sizeof(int));
    }
    for(vertice i = 0; i < r; ++i){
        for(vertice j = 0; j < r; ++j)
            matriz[i][j] = val;
    }
    return matriz;
}

// Inicialização de um grafo com 0 arrestas e v para quantidade de vertices.

Grafo constroiGrafo(int v){

    Grafo G = malloc(sizeof *G);
    G->Ver = v;
    G->VerX = malloc(v*sizeof(int *));
    G->VerY = malloc(v*sizeof(int *));
    G->Ar = 0;
    G->adjacencia = Matriz(v+1,v+1,0);
    G->arestas = Matriz(v+1,v+1,0);

    return G;

}

// //Função pra debug, mostra a matriz de adjacencia.

void exibeMatriz(Grafo g){
    for(vertice v = 1; v < g->Ver+1; ++v){
        for(vertice w = 1; w < g->Ver+1; ++w)
            printf("%d  ", g->adjacencia[v][w]);
            //printf("GRAU-> %d", g->adjacencia[v][w]->grau);
        printf("\n");
    }
    printf("\n");
}

//Função pra debug, mostra a matriz de posição.

void exibeMatriz2(Grafo g){
    for(vertice v = 1; v < g->Ver+1; ++v){
        for(vertice w = 1; w < g->Ver+1; ++w)
            printf("%d  ", g->arestas[v][w]);
            //printf("GRAU-> %d", g->adjacencia[v][w]->grau);
        printf("\n");
    }
    printf("\n");
}

// Insere uma aresta com peso passado por parametro entre os vertices v-w no grafo caso essa aresta nao exista.

void insereAresta(Grafo g, vertice v, vertice w, int peso){

    if(g->adjacencia[v][w] == 0 && v != w){
        g->adjacencia[v][w] = peso;
        g->adjacencia[w][v] = peso;
        g->arestas[v][w] = 1;
        g->arestas[w][v] = 1;
        g->Ar++;
    }
}

//Função pra debug, mostra os adjacentes a cada vértice

void imprimeAjacenteLinha(Grafo g){

    for(vertice v = 1; v < g->Ver+1; ++v){
        printf("\nAdjacentes de %2d: ", v);
        for(vertice w = 0; w < g->Ver; ++w){
            if(g->adjacencia[v][w] != 0 && w != v){
                printf("%2d, ", w);
            }
        }
    }
}

//Cria uma copia da matriz com pesos para a matriz de posição

int criaCopia(Grafo g){

    for(vertice i = 0; i< g->Ver+1; i++){
        for(vertice j = 0; j< g->Ver+1; j++){
            g->arestas[i][j] = g->adjacencia[i][j];
        }
    }

}

//Retorna o indice de onde tem aresta

int retornaIndiceComAresta(Grafo g, int i){

    for(vertice j = 0; j < g->Ver; j++){
        if(g->arestas[i][j] != 0 && j != i){
            g->arestas[i][j] = 0;
            return j;
        }
    }
}

// Retorna o grau do vértice

int grauVer(Grafo g, vertice ver){

    int grau = 0;

        for(vertice w = 1; w < g->Ver+1; ++w){
            if(g->adjacencia[ver][w] != 0 && ver != w){
                //printf("Primeiro adjacente de %d sera: %2d, peso: %d\n", ver, w, g->adjacencia[ver][w]);
                grau++;
            }
    }
    return grau;
}

// Importa o grafo de um arquivo de texto.

Grafo importarGrafo(char *path){

    FILE *file;

    file = fopen(path, "r");
    int i;
    int qntVertices = 0;
    int qntArestas = 0;

    fscanf(file, "%d\n ", &qntVertices);
    fscanf(file, "%d\n", &qntArestas);
    Grafo g = constroiGrafo(qntVertices);

    for(i = 0; i < qntArestas; i++){

        int v = 0, w = 0, peso = 0;
        fscanf(file, "%d %d %d\n", &v, &w, &peso);
        insereAresta(g, v, w, peso);
    }

    return g;
}

void algKruskal(Grafo g1, int orig, int *pai){

    int i,j,grau, dest, primeiro, NV = g1->Ver+1;
    int menorPeso = 0;

    int *arv = (int*) malloc(NV * sizeof(int));//vetor aux

    for(i=1; i<NV; i++){
        arv[i] = i;
        pai[i] = -1;//sem pai
    }

    while(1){
        primeiro = 1;
        for(i=1; i<NV; i++){
            grau = grauVer(g1, i);
            for(j=0; j<grau; j++){

                int indice = retornaIndiceComAresta(g1,i);
                //printf("\ni->%d j->%d", i,j);
                if(arv[i] != arv[indice]){

                    if(indice >= i){
                            //printf("\n%d <-vertice %d <-indice\n", i,indice);
                        if(primeiro){

                            menorPeso = g1->adjacencia[i][indice];
                            orig = i;
                            dest = indice;
                            primeiro = 0;
                            //printf("\n%d <-menorPeso %d <-Orig %d <-Dest\n", menorPeso,orig,dest);

                        }else{
                            if(menorPeso > g1->adjacencia[i][indice]){
                                menorPeso = g1->adjacencia[i][indice];
                                orig = i;
                                dest = indice;
                                //printf("\n%d <-menorPeso %d <-Orig %d <-Dest\n", menorPeso,orig,dest);
                            }
                        }
                    }
                }
            }
        }
        //printf("\nMenor peso da rodada -> %d terminou  orig(vertice) ->%d dest(indice) ->%d", menorPeso, orig, dest);

        if(primeiro == 1) break;
        if(pai[orig] == -1) pai[orig] = dest;
        else pai[dest] = orig;

        for(i=0; i<NV; i++){
            if(arv[i] == arv[dest])
                arv[i] = arv[orig];
        }
        criaCopia(g1);
    }
    free(arv);
}
/*int main(){

    setlocale(LC_ALL, "portuguese");

    int condicao = 0, escolha = 0;
    bool grafoCriado = false;
    Grafo g1;

    g1 = importarGrafo("in.txt");
    //system("pause");
    grafoCriado = true;

    //exibeMatriz(g1); //Debug
    //exibeMatriz2(g1); //Debug
    //imprimeAjacenteLinha(g1); //Debug

    int i, pai[g1->Ver];
    algKruskal(g1,0,pai);

    printf("Aqui estão de forma não ordenada os vértices que se ligam e foram a árvore geradora minima");
    for(i=1; i<g1->Ver+1; i++){

        printf("\n(%d, %d)", pai[i],i);
    }

}*/
char output_file[500] = "";

int main(int argc, char *argv[]) {

  int parameter, initial = -1;
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
      if (strcmp(argv[parameter+1], "-s") == 0) {
        s = true;
        g1 = importarGrafo(argv[parameter+2]);
      grafoCriado = true;
      } else {
        g1 = importarGrafo(argv[parameter+1]);
      grafoCriado = true;
      }
    }
    else if (strcmp(argv[parameter], "-i") == 0){
      initial = atoi(argv[parameter + 1]);
    }
  }
  int i, somador=0, pai[g1->Ver];
  algKruskal(g1,0,pai);

    for(i=1; i<g1->Ver; i++){
        if(s == true){
            if (outputF) fprintf(outputFile,"(%d, %d)  ", pai[i],i);
            else printf("(%d, %d)  ", pai[i],i);
        }
        somador += g1->adjacencia[pai[i]][i];
    }
    if(s ==  false){
        if (outputF) fprintf(outputFile,"%d", somador);
        else  printf("%d", somador);
    }

  return 0;
}

