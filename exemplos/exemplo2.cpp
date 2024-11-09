#include "Grafo.hpp"
#include "Bfs.hpp"

#include <iostream>

int main() {
    Grafo meuGrafo(6, 5);

    // Adicionando arestas entre cidades
    meuGrafo.adicionaAresta("V", "O");
    meuGrafo.adicionaAresta("O", "IS");
    meuGrafo.adicionaAresta("IT", "B");
    meuGrafo.adicionaAresta("B", "Y");
    meuGrafo.adicionaAresta("V", "IT");

    meuGrafo.imprimeGrafo();
    
    // como é const e adicionar aresta nao é, nao é possivel adicionar arestas no grafo reverso
    //invertido.adicionaAresta("inicio", "fim");

    std::string cidadeCapital = capital(meuGrafo);
    std::cout << "A capital é: " << cidadeCapital << std::endl;

    return 0;
}