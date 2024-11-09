#include "Grafo.hpp"
#include <iostream>
#include <unordered_map>

Grafo::Grafo() {}

void Grafo::adicionaAresta(const std::string& inicio, const std::string& fim)
{
    listaAdj[inicio].push_back(fim);
}

void Grafo::imprimeAresta(const std::string& inicio, const std::string& fim)
{
    auto it = listaAdj.find(inicio);
    
    // Se a cidade não for encontrada
    if (it == listaAdj.end()) 
    {
        std::cout <<  inicio << " não encontrado." << std::endl;
        return;
    }
    else
    {
    //Percorrendo as adjacências do vértice inicial
        for (auto& adjacente : it->second) {
            if (adjacente == fim) {
                std::cout << inicio << " " << fim << std::endl;
                return;
            }
        }
    }

    std::cout << "Aresta (" << inicio << ", " << fim << ") não encontrada." << std::endl;
}

void Grafo::imprimeVertice(const std::string&vertice)
{
    auto it = listaAdj.find(vertice);
    
    // Se a cidade não for encontrada
    if (it == listaAdj.end()) 
    {
        return;
    }
    else
    {
    std::cout << vertice << std::endl;
    }
}

void Grafo::imprimeAdjacencia(const std::string&vertice)
{
    auto it = listaAdj.find(vertice);
    
    // Se a cidade não for encontrada
    if (it == listaAdj.end()) 
    {
        return;
    }

    // Se o vertice for encontrada, imprime as adjacências
    auto adjacencias = it->second; 

    if (adjacencias.empty()) 
    {
        std::cout << "Nenhuma adjacencia." << std::endl;
    } 
    else 
    {
        for (const auto& vizinho : adjacencias) 
        {
            std::cout << vizinho << " ";
        }
        std::cout << std::endl;
    }
}