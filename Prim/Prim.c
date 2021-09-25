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
        for(vertice w = 0; w < g->Ver+1; ++w){
            if(g->adjacencia[v][w] != 0 && w != v){
                printf("%2d, ", w);
            }
        }
    }
}

//Cria uma copia da matriz com pesos para a matriz de posição

int criaCopia(Grafo g){

    for(vertice i = 1; i< g->Ver+1; i++){
        for(vertice j = 0; j< g->Ver+1; j++){
            g->arestas[i][j] = g->adjacencia[i][j];
        }
    }
}

//Retorna o indice de onde tem aresta

int retornaIndiceComAresta(Grafo g, int i){

    for(vertice j = 0; j < g->Ver+1; j++){
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
/*int pesoKruskal(int i, int j){
    int peso = 0;



    return peso;
}*/
void algPrim(Grafo g1, int orig, int *pai){

    int i,j,grau, dest, primeiro, NV = g1->Ver+1;
    int menorPeso = 0;

    for(i=1; i<NV; i++){
        pai[i] = -1;//sem pai
    }

    pai[1] = 0;

    while(1){
        primeiro = 1; // Verifica se é o primeiro vertice, caso encontre duas arestas com o mesmo peso.
        for(i=1; i<NV; i++){ //Percorre todos os vértices do grafo
            grau = grauVer(g1, i);
            if(pai[i] != -1){ // Procura um vértice que já foi visitado
                for(j=0; j<grau; j++){ //Percorre todos os vizinhos do vértice.

                    int indice = retornaIndiceComAresta(g1,i);//retorna o indice da aresta
                    //printf("\ni->%d j->%d", i,j);
                    if(pai[indice] == -1){ //Verifica se foi visitado

                        //printf("\n%d <-vertice %d <-indice\n", i,indice);
                        if(primeiro){// Procura a aresta de menor custo.
                            menorPeso = g1->adjacencia[i][indice];
                            orig = i;
                            dest = indice;
                            primeiro = 0;
                            //printf("primeiro");
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
        pai[dest] = orig;

        criaCopia(g1);//Refaz a matriz de referência
    }
}

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
  algPrim(g1, 0, pai);

    for(i=2; i<g1->Ver+1; i++){
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
