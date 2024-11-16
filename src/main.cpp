#include "Grafo.hpp"
#include "Bfs.hpp"
#include "Kosaraju.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main(int argc, char* argv[]) 
{
    int cidades, estradas;
    std::string inicio, fim;

    if (argc != 2) 
    {
        std::cerr << "Está faltando o argv[1] <nome_do_arquivo>" << std::endl;
        return 1;
    }
    
    std::ifstream arq;
    arq.open(argv[1]);

    if (!arq.is_open()) 
    {
        std::cerr << "Erro ao abrir o arquivo: " << argv[1] << std::endl;
        return 1;
    }

    std::string linha;
    if (std::getline(arq, linha))
    {
        std::istringstream stream(linha);
        stream >> cidades >> estradas;
    }
    
    Grafo meuGrafo(cidades, estradas);
    
    for (int i = 0; i < estradas; i++)  // Corrigido para 'int'
    {
        if (std::getline(arq, linha))
        {
            std::istringstream stream(linha);
            stream >> inicio >> fim;
            meuGrafo.adicionaAresta(inicio, fim);
        }
    }

    meuGrafo.imprimeGrafo();
    
    // Identificando a cidade capital
    std::string cidadeCapital = capital(meuGrafo);
    std::cout << "A capital é: " << cidadeCapital << std::endl;

    // Chama o algoritmo de Kosaraju para encontrar as componentes fortemente conectadas
    std::vector<std::vector<std::string>> componentes = kosaraju(meuGrafo);
    
    // Exibe as componentes fortemente conectadas
    std::cout << "Componentes fortemente conectadas retornadas pelo Kosaraju:" << std::endl;
    for (size_t i = 0; i < componentes.size(); ++i) {
        std::cout << "Componente " << i << " (Tamanho: " << componentes[i].size() << "): ";
        for (const auto& vertice : componentes[i]) {
            std::cout << vertice << " ";
        }
        std::cout << std::endl;
    }
    


    // Calcula os batalhões mais próximos da capital
    std::vector<std::string> batalhoesProximos = batalhoes(meuGrafo, cidadeCapital, componentes);
    
    // Exibe o número de batalhões e suas localizações
    std::cout << "Número de batalhões: " << componentes.size() - 1 << std::endl;  // Exclui a capital
    std::cout << "Batalhões mais próximos da capital:" << std::endl;
    for (const auto& b : batalhoesProximos) {
        std::cout << "Batalhão em: " << b << std::endl;
    }

    arq.close();
    return 0;
}