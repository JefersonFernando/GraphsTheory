fulkerson: ./fulkerson/fulkerson.cpp
    gpp ./fulkerson/fulkerson.cpp -o fulkerson

run: fulkerson
    fulkerson.exe -f ./fulkerson/in.txt -o ./fulkerson/out.txt -i 1 -f 6 -s 