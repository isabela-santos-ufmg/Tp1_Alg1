#include "Grafo.hpp"
#include "Bfs.hpp"
#include "Kosaraju.hpp"
#include "Patrulhamento.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <sys/stat.h>
#include <dirent.h>

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

    // Identificando a cidade capital
    std::string cidadeCapital = capital(meuGrafo);

    // Chama o algoritmo de Kosaraju para encontrar as componentes fortemente conectadas
    std::vector<std::vector<std::string>> componentes = kosaraju(meuGrafo);

    // Calcula os batalhões mais próximos da capital
    std::vector<std::string> batalhoesSecundarios = batalhoes(meuGrafo, cidadeCapital, componentes);

    // Escreve os resultados no arquivo
    std::cout << cidadeCapital << std::endl;
    std::cout << componentes.size() - 1 << std::endl;  // Exclui a capital
    for (const auto& b : batalhoesSecundarios) 
    {
        std::cout << b << std::endl;
    }
    
    // Exibe as componentes fortemente conectadas
    
    /*
    std::cout << "Componentes fortemente conectadas retornadas pelo Kosaraju:" << std::endl;
    for (size_t i = 0; i < componentes.size(); ++i) {
        std::cout << "Componente " << i << " (Tamanho: " << componentes[i].size() << "): ";
        for (const auto& vertice : componentes[i]) {
            std::cout << vertice << " ";
        }
        std::cout << std::endl;
    }
    */

    
    calcularPatrulhamentos(meuGrafo, componentes, cidadeCapital, batalhoesSecundarios);

    // Fecha os arquivos
    arq.close();
    return 0;
}
