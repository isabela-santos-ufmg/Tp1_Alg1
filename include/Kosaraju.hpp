#ifndef KOSARAJU_HPP
#define KOSARAJU_HPP

#include "Grafo.hpp"
#include <unordered_map>
#include <vector>
#include <stack>
#include <iostream>

// Função DFS para calcular os tempos de descoberta e finalização
void dfs(const Grafo& g, const std::string& vertice, 
         std::unordered_map<std::string, bool>& visitado, 
         std::unordered_map<std::string, int>& tempoDescoberta, 
         std::unordered_map<std::string, int>& tempoFinalizacao, 
         std::stack<std::string>& ordemFinalizacao, int& tempoAtual);

void dfsReverso(const Grafo& g, const std::string& vertice, 
                std::unordered_map<std::string, bool>& visitado, 
                std::vector<std::string>& componente);

// Função para rodar o algoritmo de Kosaraju
std::vector<std::vector<std::string>> kosaraju(const Grafo& g);
Grafo criarGrafoDeComponentes(const Grafo& g, const std::vector<std::vector<std::string>>& componentes);
#endif
