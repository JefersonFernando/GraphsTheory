all: fulkerson dijkstra kruskal prim

fulkerson: ./fulkerson/fulkerson.cpp
    g++ ./fulkerson/fulkerson.cpp -o fulkerson

dijkstra: ./Dijkstra/Dijkstra.c
    gcc ./Dijkstra/Dijkstra.c -o Dijkstra
    
kruskal: ./Kruskal/Kruskal.c
    gcc ./Kruskal/Kruskal.c -o Kruskal
    
prim: ./Prim/Prim.c
    gcc ./Prim/Prim.c -o Prim
    
run: fulkerson dijkstra kruskal prim
    fulkerson.exe -f -s ./fulkerson/in.txt -o ./fulkerson/out.txt -i 1
    Dijkstra.exe -f ./Dijkstra/in.txt -o ./Dijkstra/out.txt -i 1
    Kruskal.exe -f ./Kruskal/in.txt -o ./Kruskal/out.txt -i 1
    Prim.exe -f ./Prim/in.txt -o ./Prim/out.txt -i 1