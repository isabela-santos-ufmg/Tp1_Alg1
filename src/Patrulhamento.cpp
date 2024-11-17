#include "Patrulhamento.hpp"
#include <iostream>
#include <unordered_map>
#include <stack>

// Função que verifica se a componente tem um ciclo Euleriano
bool cicloEuleriano(const Grafo& g, const std::vector<std::string>& componente, const std::string& cidadeCapital) {
    std::unordered_map<std::string, int> entradas, saídas;
    
    // Calcula entradas e saídas
    for (const auto& vertice : componente) {
        auto it = g.getListaAdj().find(vertice);
        if (it != g.getListaAdj().end()) {
            for (const auto& vizinho : it->second) {
                saídas[vertice]++;
                entradas[vizinho]++;
            }
        }
    }

    // Verifica se todos os vértices têm a mesma quantidade de entradas e saídas
    for (const auto& vertice : componente) {
        if (entradas[vertice] != saídas[vertice]) {
            return false;
        }
    }
    
    return true;
}

// Função para substituir std::find, procurando um valor em um vetor
bool encontrarValorNoVetor(const std::vector<std::string>& vetor, const std::string& valor) {
    for (const auto& item : vetor) {
        if (item == valor) {
            return true;
        }
    }
    return false;
}

// Função que encontra a rota de patrulhamento em uma componente
std::vector<std::string> encontrarRotaEuleriana(const Grafo& g, const std::vector<std::string>& componente, const std::string& pontoDePartida) {
    std::unordered_map<std::string, std::vector<std::string>> grafoLocal;
    
    // Copia as arestas do grafo original para o grafo local
    for (const auto& vertice : componente) {
        auto it = g.getListaAdj().find(vertice);
        if (it != g.getListaAdj().end()) {
            grafoLocal[vertice] = it->second;
        }
    }

    std::vector<std::string> rota;
    std::stack<std::string> pilha;

    pilha.push(pontoDePartida);

    // Realiza a busca para encontrar o ciclo Euleriano, ou patrulhamento
    while (!pilha.empty()) {
        std::string v = pilha.top();

        // Se ainda há arestas para explorar, empilha o próximo vértice
        if (!grafoLocal[v].empty()) {
            pilha.push(grafoLocal[v].back());
            grafoLocal[v].pop_back();  // Remove a última aresta explorada
        } else {
            rota.push_back(v);
            pilha.pop();
        }
    }

    // Revertendo a ordem da rota manualmente (substituindo std::reverse)
    std::vector<std::string> rotaRevertida;
    for (int i = rota.size() - 1; i >= 0; --i) {
        rotaRevertida.push_back(rota[i]);
    }

    return rotaRevertida;
}

// Função principal que encontra os patrulhamentos para todas as componentes
void calcularPatrulhamentos(const Grafo& g, const std::vector<std::vector<std::string>>& componentes, const std::string& cidadeCapital, const std::vector<std::string>& batalhoes) {
    // Itera sobre cada componente para encontrar os patrulhamentos possíveis
    for (const auto& componente : componentes) {
        if (componente.size() > 1) { // Ignora componentes com apenas um vértice
            // Verifica se a componente contém a capital
            bool temCapital = encontrarValorNoVetor(componente, cidadeCapital);

            // Determina o ponto de partida (capital ou batalhão secundário)
            std::string pontoDePartida = cidadeCapital;

            if (!temCapital) {
                // Caso a capital não esteja na componente, o patrulhamento deve começar de um batalhão secundário
                for (const auto& batalhao : batalhoes) {
                    // Verifica se algum batalhão da lista de batalhões está na componente
                    for (const auto& b : componente) {
                        if (batalhao == b) {
                            pontoDePartida = b;
                            break;
                        }
                    }
                    if (pontoDePartida != cidadeCapital) break; // Se encontrar o batalhão, quebra o laço
                }
            }

            std::cout << "Componente com patrulhamento possível: ";
            for (const auto& vertice : componente) {
                std::cout << vertice << " ";
            }
            std::cout << std::endl;

            // Encontra a rota Euleriana para a componente
            std::vector<std::string> rota = encontrarRotaEuleriana(g, componente, pontoDePartida);
            
            std::cout << "Rota de patrulhamento: ";
            for (const auto& v : rota) {
                std::cout << v << " ";
            }
            std::cout << std::endl;
        }
    }
}
