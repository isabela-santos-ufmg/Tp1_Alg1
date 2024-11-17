#ifndef PATRULHAMENTO_HPP
#define PATRULHAMENTO_HPP

#include <vector>
#include <string>
#include <unordered_map>
#include <stack>
#include "Grafo.hpp" // Assumindo que você tem um arquivo Grafo.hpp com a definição do grafo

// Função que verifica se a componente tem um ciclo Euleriano
bool cicloEuleriano(const Grafo& g, const std::vector<std::string>& componente, const std::string& cidadeCapital);

// Função que encontra a rota de patrulhamento em uma componente
std::vector<std::string> encontrarRotaEuleriana(const Grafo& g, const std::vector<std::string>& componente, const std::string& cidadeCapital);

// Função principal que encontra os patrulhamentos para todas as componentes
void calcularPatrulhamentos(const Grafo& g, const std::vector<std::vector<std::string>>& componentes, const std::string& cidadeCapital, const std::vector<std::string>& batalhoes);

#endif // PATRULHAMENTOS_HPP