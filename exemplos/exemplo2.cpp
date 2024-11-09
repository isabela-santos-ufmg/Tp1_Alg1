#include "Grafo.hpp"
#include "Bfs.hpp"

#include <iostream>

int main() {
    Grafo meuGrafo(5, 6);

    // Adicionando arestas entre cidades
    meuGrafo.adicionaAresta("L", "R");
    meuGrafo.adicionaAresta("R", "Y");
    meuGrafo.adicionaAresta("Y", "L");
    meuGrafo.adicionaAresta("Y", "B");
    meuGrafo.adicionaAresta("B", "U");
    meuGrafo.adicionaAresta("U", "Y");

    meuGrafo.imprimeGrafo();
    
    // como é const e adicionar aresta nao é, nao é possivel adicionar arestas no grafo reverso
    //invertido.adicionaAresta("inicio", "fim");

    std::string cidadeCapital = capital(meuGrafo);
    std::cout << "A capital é: " << cidadeCapital << std::endl;

    return 0;
}