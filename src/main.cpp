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
    
    for (int i = 0; i < estradas; i++)
    {
        if (std::getline(arq, linha))
        {
            std::istringstream stream(linha);
            stream >> inicio >> fim;
            meuGrafo.adicionaAresta(inicio, fim);
        }
    }

    meuGrafo.imprimeGrafo();
    
    // Define a capital usando a função BFS
    std::string cidadeCapital = capital(meuGrafo);
    std::cout << "A capital é: " << cidadeCapital << std::endl;

    // Obtém as componentes fortemente conectadas usando Kosaraju
    auto componentes = kosaraju(meuGrafo);
    
    // Exibe as componentes fortemente conectadas
    std::cout << "Componentes fortemente conectadas:" << std::endl;
    for (size_t i = 0; i < componentes.size(); ++i) {
        std::cout << "Componente " << i + 1 << ": ";
        for (const std::string& vertice : componentes[i]) {
            std::cout << vertice << " ";
        }
        std::cout << std::endl;
    }

    // Calcula e exibe o número de batalhões necessários
    int numeroBatalhoes = componentes.size() - 1;
    std::cout << "Número de batalhões necessários: " << numeroBatalhoes << std::endl;

    // Verifica e exibe os batalhões escolhidos para cada componente que não contém a capital
    std::cout << "Escolha dos batalhões:" << std::endl;
    for (size_t i = 0; i < componentes.size(); ++i) {
        bool capitalNaComponente = false;

        // Verifica manualmente se a capital está presente na componente
        for (const std::string& vertice : componentes[i]) {
            if (vertice == cidadeCapital) {
                capitalNaComponente = true;
                break;
            }
        }

        // Se a capital não está nesta componente, então encontramos um vértice para ser o batalhão
        if (!capitalNaComponente) {
            std::string batalhaoEscolhido = batalhao(meuGrafo, cidadeCapital, componentes);
            std::cout << "Componente " << i + 1 << ": Batalhão designado na cidade " << batalhaoEscolhido << std::endl;
        }
    }

    arq.close();
    return 0;
}
