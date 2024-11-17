#ifndef PATRULHAS_HPP
#define PATRULHAS_HPP

#include "Grafo.hpp"
#include <vector>
#include <string>

class Patrulhas {
public:
    Patrulhas(const Grafo& grafo, const std::vector<std::vector<std::string>>& componentes);
    std::vector<std::vector<std::string>> calcularPatrulhamento();

private:
    bool verificarCicloEuleriano(const std::vector<std::string>& componente);
    void encontrarCicloEuleriano(const std::string& start, std::vector<std::string>& ciclo, 
                                 std::unordered_map<std::string, std::vector<std::string>>& adjacencias);

    const Grafo& grafo;
    const std::vector<std::vector<std::string>>& componentes;
};

#endif
