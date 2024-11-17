#include "Bfs.hpp"
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <climits>
#include <limits>
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

    // std::cout << "Bfs(" << inicio << ")" << std::endl;
    
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
                    /*
                    std::cout << "Vizinho " << vizinho << " adicionado, distancia: " << distancia[vizinho] 
                            << ", altura: " << altura[vizinho] << std::endl;
                    std::cout << "Altura máxima: " << maxAltura << std::endl;
                    std::cout << "Total de estradas passadas: " << estradasTotal << std::endl;
                    std::cout << "Vértices alcançados: " << verticesAlcancados << std::endl;
                    */
                }
            }
        }
    }

    // Verifica se o BFS alcançou todos os vértices do grafo
    if (verticesAlcancados == g.getVertices()) {
        //std::cout << inicio << " alcançou todos os vértices" << std::endl;
        return {estradasTotal, maxAltura};
    } else {
        // Retorna valores altos se não alcançou todos os vértices
        return {DBL_MAX, DBL_MAX};
    }
}

void bfs(const Grafo& g, const std::string& cidadeInicial, 
         std::unordered_map<std::string, double>& distancias, 
         std::unordered_map<std::string, std::string>& predecessores) {
    // Inicializa a fila para o BFS
    std::queue<std::string> fila;
    fila.push(cidadeInicial);
    distancias[cidadeInicial] = 0;

    // Inicializa o map de predecessores
    predecessores[cidadeInicial] = "";

    while (!fila.empty()) {
        std::string atual = fila.front();
        fila.pop();

        const auto& listaAdj = g.getListaAdj();
        if (listaAdj.find(atual) != listaAdj.end()) {
            const auto& adjacentes = listaAdj.at(atual);
            for (const std::string& vizinho : adjacentes) {
                if (distancias.find(vizinho) == distancias.end()) {  // Se o vizinho não foi visitado
                    distancias[vizinho] = distancias[atual] + 1;
                    predecessores[vizinho] = atual;
                    fila.push(vizinho);
                }
            }
        }
    }
}

std::pair<double, double> calcularDistanciaEntreVertices(const Grafo& g, const std::string& origem, const std::string& destino) {
    std::unordered_map<std::string, double> distancias;
    std::unordered_map<std::string, std::string> predecessores;

    // Realiza a BFS a partir do vértice de origem
    bfs(g, origem, distancias, predecessores);

    // Verifica se o destino foi alcançado
    if (distancias.find(destino) != distancias.end()) {
        return {distancias[destino], distancias[destino]};  // Retorna a distância até o destino
    } else {
        // Retorna valores altos se o destino não é alcançável
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

// Função auxiliar para encontrar o índice da componente que contém a capital
double indiceComponenteCapital(const std::vector<std::vector<std::string>>& componentes, const std::string& capital) {
    for (double i = 0; i < componentes.size(); ++i) {
        for (const auto& vertice : componentes[i]) {
            if (vertice == capital) {
                return i; // Retorna o índice da componente que contém a capital
            }
        }
    }
    return -1; // Retorna -1 se a capital não for encontrada em nenhuma componente
}

// Função para encontrar os batalhões mais próximos da capital
std::vector<std::string> batalhoes(const Grafo& g, const std::string& capital,
                                   const std::vector<std::vector<std::string>>& componentes) {
    std::vector<std::string> batalhoesProximos;

    // Inicializa `distancias` e `predecessores` para armazenar os dados da BFS
    std::unordered_map<std::string, double> distancias;
    std::unordered_map<std::string, std::string> predecessores;

    // Encontra o índice da componente que contém a capital
    double indiceCapital = indiceComponenteCapital(componentes, capital);
    if (indiceCapital == -1) {
        std::cerr << "Erro: Capital não encontrada em nenhuma das componentes." << std::endl;
        return {};
    } else {
        // std::cout << "Capital encontrada na componente " << indiceCapital << std::endl;
    }

    // Executa a BFS a partir da capital para preencher `distancias`
    bfs(g, capital, distancias, predecessores);

    // Itera sobre as componentes, ignorando a que contém a capital
    for (size_t i = 0; i < componentes.size(); ++i) {
        if (i == indiceCapital) continue; // Ignora a componente da capital

        // Para cada componente desconectada, buscamos o vértice mais próximo
        double menorDistancia = std::numeric_limits<double>::max();
        std::string batalhaoMaisProximo;

        for (const std::string& vertice : componentes[i]) {
            // Verifique se o vértice existe nas distâncias antes de acessar
            if (distancias.find(vertice) == distancias.end()) {
                std::cerr << "Erro: Vértice " << vertice << " não encontrado nas distâncias." << std::endl;
                continue;
            }

            double distancia = distancias[vertice];
            if (distancia < menorDistancia) {
                menorDistancia = distancia;
                batalhaoMaisProximo = vertice;
            }
        }

        if (!batalhaoMaisProximo.empty()) {
            batalhoesProximos.push_back(batalhaoMaisProximo);
        }
    }

    return batalhoesProximos;
}
