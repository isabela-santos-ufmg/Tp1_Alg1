#include "Grafo.hpp"

int main() {
    Grafo meuGrafo;

    // Adicionando arestas entre cidades
    meuGrafo.adicionaAresta("Paris", "Londres");
    meuGrafo.adicionaAresta("Paris", "Roma");
    meuGrafo.adicionaAresta("Londres", "Berlim");

    // Imprimindo um vértice específico
    meuGrafo.imprimeVertice("Paris");  // Vértice existente
    meuGrafo.imprimeVertice("NovaYork");  // Vértice não existente

    // Imprimindo uma aresta específica
    meuGrafo.imprimeAresta("Paris", "Roma");  // Aresta existente
    meuGrafo.imprimeAresta("Paris", "Berlim");  // Aresta não existente
    meuGrafo.imprimeAdjacencia("Paris");
    meuGrafo.imprimeAdjacencia("Berlim");

    return 0;
}