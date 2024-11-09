#include "Grafo.hpp"
#include "Bfs.hpp"

#include <iostream>

int main() {
    double vertices = 0;
    double arestas = 0;
    std::string inicio = "";
    std::string fim = "";
    
    std::cin >> vertices >> arestas;
    Grafo meuGrafo(vertices, arestas);

    // Adicionando arestas entre cidades
    for(double i = 0; i < arestas; i++)
    {
        std::cin >> inicio >> fim;
        meuGrafo.adicionaAresta(inicio, fim);
    }

    meuGrafo.imprimeGrafo();

    std::string cidadeCapital = capital(meuGrafo);
    std::cout << "A capital é: " << cidadeCapital << std::endl;

    return 0;
}