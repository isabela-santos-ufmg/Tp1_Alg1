#include "Bfs.hpp"
#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <climits>
#include <cfloat>

std::pair<double, double> bfs(const Grafo& g, const std::string& inicio) {
    std::unordered_map<std::string, double> distancia;
    std::unordered_map<std::string, double> altura;
    std::unordered_map<std::string, bool> visitado;
    std::queue<std::string> q;

    // Inicializa todos os vértices como "não visitados"
    for (const auto& pair : g.getListaAdj()) {
        visitado[pair.first] = false;
        distancia[pair.first] = 0;
        altura[pair.first] = 0;
    }

    std::cout << "Bfs(" << inicio << ")" << std::endl;
    
    // Coloca o vértice inicial na fila
    q.push(inicio);
    distancia[inicio] = 0;
    altura[inicio] = 0;
    visitado[inicio] = true;

    int maxAltura = 0;
    int estradasTotal = 0;
    int verticesAlcancados = 1; // Começa contando o vértice inicial

    // Inicia o BFS
    while (!q.empty()) {
        std::string atual = q.front();
        q.pop();

        auto it = g.getListaAdj().find(atual);
        if (it != g.getListaAdj().end()) {
            // Processa cada vizinho do vértice atual
            for (const std::string& vizinho : g.getListaAdj().find(atual)->second) {
                // Se o vizinho ainda não foi visitado
                if (!visitado[vizinho]) {
                    visitado[vizinho] = true;  // Marca o vizinho como visitado
                    distancia[vizinho] = distancia[atual] + 1;
                    altura[vizinho] = altura[atual] + 1;
                    maxAltura = std::max(static_cast<double>(maxAltura), altura[vizinho]);
                    estradasTotal += 1;
                    q.push(vizinho);
                    verticesAlcancados++;  // Conta o vértice alcançado
                    
                    // Log para depuração
                    std::cout << "Vizinho " << vizinho << " adicionado, distancia: " << distancia[vizinho] 
                            << ", altura: " << altura[vizinho] << std::endl;
                    std::cout << "Altura máxima: " << maxAltura << std::endl;
                    std::cout << "Total de estradas passadas: " << estradasTotal << std::endl;
                    std::cout << "Vértices alcançados: " << verticesAlcancados << std::endl;
                }
            }
        }
    }

    // Verifica se o BFS alcançou todos os vértices do grafo
    if (verticesAlcancados == g.getVertices()) {
        std::cout << inicio << " alcançou todos os vértices" << std::endl;
        return {estradasTotal, maxAltura};
    } else {
        // Retorna valores altos se não alcançou todos os vértices
        return {DBL_MAX, DBL_MAX};
    }
}

std::string capital(const Grafo& g)
{
    std::string capital = "";
    double menorEstradaTotal = DBL_MAX;
    double menorAltura = DBL_MAX;

    for (const auto& pair : g.getListaAdj()) {
        const std::string& vertice = pair.first;

        // Chama o BFS e imprime os vértices alcançados
        auto [estradasTotal, maxAltura] = bfs(g, vertice);

        // Verifica se o vértice conseguiu alcançar todos os outros
        if (estradasTotal != DBL_MAX) {
            // Se esse vértice for a melhor escolha para ser a capital
            if (estradasTotal < menorEstradaTotal || (estradasTotal == menorEstradaTotal && maxAltura < menorAltura)) {
                capital = vertice;
                menorEstradaTotal = estradasTotal;
                menorAltura = maxAltura;
            }
        }
    }

    return capital;
}
