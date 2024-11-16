#include "Kosaraju.hpp"
#include "Bfs.hpp"

#include <cfloat>

void dfs(const Grafo& g, const std::string& vertice, 
         std::unordered_map<std::string, bool>& visitado, 
         std::unordered_map<std::string, int>& tempoDescoberta, 
         std::unordered_map<std::string, int>& tempoFinalizacao, 
         std::stack<std::string>& ordemFinalizacao, int& tempoAtual) {
    visitado[vertice] = true;
    tempoDescoberta[vertice] = tempoAtual++;
    
    // Verifica se o vértice existe no mapa antes de acessar seus vizinhos
    auto it = g.getListaAdj().find(vertice);
    if (it != g.getListaAdj().end()) {
        for (const std::string& vizinho : it->second) {
            if (!visitado[vizinho]) {
                dfs(g, vizinho, visitado, tempoDescoberta, tempoFinalizacao, ordemFinalizacao, tempoAtual);
            }
        }
    }
    
    // Após visitar todos os vizinhos, registra o tempo de finalização
    tempoFinalizacao[vertice] = tempoAtual++;
    ordemFinalizacao.push(vertice); // Adiciona o vértice na pilha de finalização
}

void dfsReverso(const Grafo& g, const std::string& vertice, 
                std::unordered_map<std::string, bool>& visitado, 
                std::vector<std::string>& componente) {
    visitado[vertice] = true;
    componente.push_back(vertice);

    // Verifica se o vértice existe no mapa antes de acessar seus vizinhos
    auto it = g.getListaAdj().find(vertice);
    if (it != g.getListaAdj().end()) {
        for (const std::string& vizinho : it->second) {
            if (!visitado[vizinho]) {
                dfsReverso(g, vizinho, visitado, componente);
            }
        }
    }
}

std::vector<std::vector<std::string>> kosaraju(const Grafo& g) {
    std::unordered_map<std::string, bool> visitado;
    std::unordered_map<std::string, int> tempoDescoberta;
    std::unordered_map<std::string, int> tempoFinalizacao;
    std::stack<std::string> ordemFinalizacao;
    int tempoAtual = 0;

    // Passo 1: Realiza a DFS no grafo original para obter a ordem de finalização
    for (const auto& vertice : g.getListaAdj()) {
        if (!visitado[vertice.first]) {
            dfs(g, vertice.first, visitado, tempoDescoberta, tempoFinalizacao, ordemFinalizacao, tempoAtual);
        }
    }

    // Passo 2: Cria o grafo reverso
    Grafo grafoReverso = g.grafoReverso();

    // Passo 3: Realiza a DFS no grafo reverso usando a ordem de finalização
    // obtida na primeira DFS
    std::vector<std::vector<std::string>> componentes;
    visitado.clear();
    
    while (!ordemFinalizacao.empty()) {
        std::string vertice = ordemFinalizacao.top();
        ordemFinalizacao.pop();

        if (!visitado[vertice]) {
            std::vector<std::string> componente;
            dfsReverso(grafoReverso, vertice, visitado, componente);
            componentes.push_back(componente);
        }
    }


    // Já temos as componentes, agora precisamos ver quais cidades de cada componente
    // está conectada na componente da capital 

    return componentes;
}

Grafo criarGrafoDeComponentes(const Grafo& g, const std::vector<std::vector<std::string>>& componentes) {
    // Criando um novo grafo de componentes, onde cada componente é um vértice
    Grafo grafoComponentes(componentes.size(), 0); // Passando o número de componentes como o número de vértices
    
    std::unordered_map<std::string, int> indiceComponente;

    // Passo 1: Mapeando os vértices para seus respectivos componentes
    for (double i = 0; i < componentes.size(); ++i) {
        for (const std::string& vertice : componentes[i]) {
            indiceComponente[vertice] = i;  // Associando cada vértice ao seu componente
        }
    }
    // Passo 2: Criando as arestas entre os componentes
    // Para isso, verificamos as arestas no grafo original
    for (const auto& par : g.getListaAdj()) {
        const std::string& vertice = par.first;
        double componenteOrigem = indiceComponente[vertice];

        for (const std::string& vizinho : par.second) {
            double componenteDestino = indiceComponente[vizinho];
            // Se o componente origem e o destino forem diferentes, adicionamos a aresta entre os componentes
            if (componenteOrigem != componenteDestino) {
                grafoComponentes.adicionaAresta(std::to_string(componenteOrigem), std::to_string(componenteDestino));
            }
        }
    }

    return grafoComponentes;
}

/*std::vector<std::string> batalhoes(const Grafo& g, const std::string& capital, const std::vector<std::vector<std::string>>& componentes) {
    std::vector<std::string> batalhoes;
    
    // Passo 1: Criar o grafo de componentes
    Grafo grafoComponentes = criarGrafoDeComponentes(g, componentes);

    // Passo 2: Para cada componente, verificar se a capital está presente ou escolher um batalhão
    for (const auto& componente : componentes) {
        bool encontrouCapital = false;
        for (const auto& vertice : componente) {
            if (vertice == capital) {
                encontrouCapital = true;
                break;
            }
        }

        // Se a capital não está na componente, encontramos o batalhão
        if (!encontrouCapital) {
            // Utilizamos BFS para encontrar o batalhão com a menor distância da capital
            double menorDistancia = DBL_MAX;
            std::string batalhao;

            for (const auto& vertice : componente) {
                auto [distancia, altura] = bfs(g, vertice);  // BFS a partir de cada vértice da componente
                if (distancia < menorDistancia) {
                    menorDistancia = distancia;
                    batalhao = vertice;
                }
            }

            batalhoes.push_back(batalhao);
        }
    }

    return batalhoes;
}*/