#include "Patrulhas.hpp"
#include <unordered_map>
#include <unordered_set>
#include <stack>

Patrulhas::Patrulhas(const Grafo& grafo, const std::vector<std::vector<std::string>>& componentes)
    : grafo(grafo), componentes(componentes) {}

bool Patrulhas::verificarCicloEuleriano(const std::vector<std::string>& componente) {
    std::unordered_map<std::string, int> inDegree, outDegree;
    
    // Calcula o grau de entrada e saída de cada vértice
    for (const auto& vertice : componente) {
        for (const auto& vizinho : grafo.getListaAdj().at(vertice)) {
            outDegree[vertice]++;
            inDegree[vizinho]++;
        }
    }

    // Verifica a condição de Euler: grau de entrada deve ser igual ao grau de saída
    for (const auto& vertice : componente) {
        if (inDegree[vertice] != outDegree[vertice]) {
            return false;
        }
    }
    return true;
}

void Patrulhas::encontrarCicloEuleriano(const std::string& start, std::vector<std::string>& ciclo, 
                                             std::unordered_map<std::string, std::vector<std::string>>& adjacencias) {
    std::stack<std::string> caminho;
    caminho.push(start);

    while (!caminho.empty()) {
        std::string v = caminho.top();
        if (!adjacencias[v].empty()) {
            caminho.push(adjacencias[v].back());  // Escolhe uma aresta não percorrida
            adjacencias[v].pop_back();  // Remove a aresta
        } else {
            ciclo.push_back(v);
            caminho.pop();
        }
    }
}

std::vector<std::vector<std::string>> Patrulhas::calcularPatrulhamento() {
    std::vector<std::vector<std::string>> rotas;

    for (const auto& componente : componentes) {
        if (componente.size() > 1 && verificarCicloEuleriano(componente)) {
            // Cria um mapa de adjacência para a componente
            std::unordered_map<std::string, std::vector<std::string>> adjacencias;
            for (const auto& vertice : componente) {
                for (const auto& vizinho : grafo.getListaAdj().at(vertice)) {
                    adjacencias[vertice].push_back(vizinho);
                }
            }

            // Encontra o ciclo Euleriano a partir do primeiro vértice
            std::vector<std::string> ciclo;
            encontrarCicloEuleriano(componente[0], ciclo, adjacencias);
            rotas.push_back(ciclo);
        }
    }

    return rotas;
}
