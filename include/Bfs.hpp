#ifndef BFS_HPP
#define BFS_HPP

#include "Grafo.hpp"
#include <string>

std::pair<double, double> bfs(const Grafo& g, const std::string& inicio);
std::string capital(const Grafo& g);

#endif