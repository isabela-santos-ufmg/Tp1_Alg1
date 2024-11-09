#ifndef GRAFO_HPP
#define GRAFO_HPP
#include <vector>
#include <unordered_map>
#include <string>
// usado lista de adjacência de vector de vector para fácil acesso de vértices/arestas

class Grafo{
    public:
        Grafo();
        void adicionaAresta(const std::string& inicio, const std::string& fim);
        void imprimeAresta(const std::string& inicio, const std::string& fim);
        void imprimeVertice(const std::string&vertice);
        void imprimeAdjacencia(const std::string&vertice);
    private:
        std::unordered_map<std::string, std::vector<std::string>> listaAdj;
};


#endif