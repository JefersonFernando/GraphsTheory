#include <iostream>
#include <fstream>
#include <limits.h>
#include <queue>
#include <string.h>

using namespace std;

int V;

bool bfs(int rGraph[100][100], int s, int t, int parent[]){
    bool visited[100];

    memset(visited, 0, sizeof(visited));

    std::queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while(!q.empty()){
        int i = q.front();

        q.pop();

        for(int j = 0; j < V; j++){
            if(visited[j] == false && rGraph[i][j]){
                if(j == t){
                    parent[j] = i;
                    return true;
                }

                q.push(j);
                parent[j] = i;
                visited[j] = true;  
            }
        }
    }

    return false;
}

int fordFulkerson(int graph[100][100], int s, int t){
    int i, j;

    int rGraph[100][100];

    for(i = 0; i < V; i++){
        for(j = 0; j < V; j++){
            rGraph[i][j] = graph[i][j];
        }
    } 

    int parent[100];

    int max_flow = 0;

    while(bfs(rGraph, s, t, parent)){
        int path_flow = INT_MAX;

        for(i = t; i != s; i = parent[i]){
            j = parent[i];
            path_flow = std::min(path_flow, rGraph[j][i]);
        }

        for(i = t; i != s; i = parent[i]){
            j = parent[i];
            rGraph[j][i] -= path_flow;
            rGraph[i][j] += path_flow;
        }

        max_flow += path_flow;

    }

    return max_flow;


}

void help(){
    cout << "Algoritmo de Ford-Fulkerson.\n";
    cout << "-h : mostra o help.\n";
    cout << "-o <arquivo> : redireciona a saida para o ‘‘arquivo’’\n";
    cout << "-f <arquivo> : indica o ‘‘arquivo’’ que contém o grafo de entrada\n";
    cout << "-s : mostra a solução (em ordem crescente)\n";
    cout << "-i : vértice inicial (dependendo do algoritmo)\n";
    cout << "-l : vértice final (dependendo do algoritmo)\n";
}

int main(int argc, char *argv[]){

    bool show = false;
    int initial = 0, final = 0;
    char *input, *output;
    fstream fr, fw;
    int n, nedges = 0;
    int graph[100][100];
    int edge1, edge2, size;

    memset(graph, 0, sizeof(graph));

    argv++;
    argc--;

    while(argc > 0){
        if(!strcmp(argv[0],"-h")){
            help();
            argv++;
            argc--;
        }else if(!strcmp(argv[0], "-o")){
            argv++;
            argc--;
            output = argv[0];
            argv++;
            argc--;
        }else if(!strcmp(argv[0], "-f")){
            argv++;
            argc--;
            input = argv[0];
            argv++;
            argc--;
        }else if(!strcmp(argv[0], "-s")){
            show = true;
            argv++;
            argc--;
        }else if(!strcmp(argv[0], "-i")){
            argv++;
            argc--;
            initial = atoi(argv[0]);
            argv++;
            argc--;
        }else if(!strcmp(argv[0], "-l")){
            argv++;
            argc--;
            final = atoi(argv[0]);
            argv++;
            argc--;
        }
    }

    fr.open(input, ios::in);
    fw.open(output, ios::out);

    fr >> V;

    fr >> nedges;

    for(int i = 0; i < nedges; i++){
        fr >> edge1;
        fr >> edge2;
        fr >> size;
        graph[edge1 -1 ][edge2 - 1] = size;
        graph[edge2 - 1][edge1 - 1] = size;
    }

    int result = fordFulkerson(graph, initial - 1 , final - 1);
    if(show){
        cout << result;
    }

    fw << result;

    return 0;
}