#ifndef GRAFO_HPP
#define GRAFO_HPP
#include <vector>
#include <unordered_map>
#include <string>

class Grafo{
    public:
        Grafo(double vertices, double arestas);
        double getVertices() const;
        double getArestas() const;
        Grafo grafoReverso() const;
        void adicionaAresta(const std::string& inicio, const std::string& fim);
        void imprimeAresta(const std::string& inicio, const std::string& fim) const;
        void imprimeVertice(const std::string&vertice) const;
        void imprimeAdjacencia(const std::string&vertice) const;
        const std::unordered_map<std::string, std::vector<std::string>>& getListaAdj() const;
        void imprimeGrafo() const;

    private:
        std::unordered_map<std::string, std::vector<std::string>> listaAdj;
        double vertices;  
        double arestas;  
};

#endif