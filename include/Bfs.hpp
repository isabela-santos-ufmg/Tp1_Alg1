#ifndef BFS_HPP
#define BFS_HPP

#include "Grafo.hpp"
#include <string>
#include <unordered_set>

// Armazena pares número de estradas e altura máxima da bfs de cada ponto daquele vértice de inicio
std::pair<double, double> bfs(const Grafo& g, const std::string& inicio);
// Roda BFS para todos os pontos e compara o de menor número de estradas e de altura mínima que passa em todos os vértices
std::string capital(const Grafo& g);
void bfs(const Grafo& g, const std::string& cidadeInicial, 
         std::unordered_map<std::string, double>& distancias, 
         std::unordered_map<std::string, std::string>& predecessores);
std::pair<double, double> calcularDistanciaEntreVertices(const Grafo& g, const std::string& origem, const std::string& destino);
double indiceComponenteCapital(const std::vector<std::vector<std::string>>& componentes, const std::string& capital);
std::vector<std::string> batalhoes(const Grafo& g, const std::string& cidadeCapital, 
                                   const std::vector<std::vector<std::string>>& componentes);
#endif