#include "Grafo.hpp"
#include "Bfs.hpp"

#include <iostream>

int main() {
    Grafo meuGrafo(6, 8);

    // Adicionando arestas entre cidades
    meuGrafo.adicionaAresta("R", "V");
    meuGrafo.adicionaAresta("R", "K");
    meuGrafo.adicionaAresta("K", "T");
    meuGrafo.adicionaAresta("T", "K");
    meuGrafo.adicionaAresta("V", "B");
    meuGrafo.adicionaAresta("B", "V");
    meuGrafo.adicionaAresta("V", "M");
    meuGrafo.adicionaAresta("M", "V");

    meuGrafo.imprimeAdjacencia("R");
    meuGrafo.imprimeAdjacencia("V");
    meuGrafo.imprimeAdjacencia("M");
    meuGrafo.imprimeAdjacencia("B");
    meuGrafo.imprimeAdjacencia("T");
    meuGrafo.imprimeAdjacencia("K");

    meuGrafo.imprimeGrafo();
    
    // como é const e adicionar aresta nao é, nao é possivel adicionar arestas no grafo reverso
    //invertido.adicionaAresta("inicio", "fim");

    std::string cidadeCapital = capital(meuGrafo);
    std::cout << "A capital é: " << cidadeCapital << std::endl;

    return 0;
}