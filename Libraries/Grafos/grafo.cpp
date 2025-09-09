#include "grafo.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <limits>
#include <unordered_map>
#include <algorithm> // std::reverse

void Grafo::agregarCiudad(const std::string& nombre) {
    if (adyacencia.find(nombre) == adyacencia.end())
        adyacencia[nombre] = {};
}

void Grafo::agregarRuta(const std::string& ciudad1, const std::string& ciudad2, float distancia) {
    agregarCiudad(ciudad1);
    agregarCiudad(ciudad2);

    adyacencia[ciudad1].push_back({ciudad2, distancia});
    adyacencia[ciudad2].push_back({ciudad1, distancia});
}

void Grafo::imprimirGrafo() const {
    for (const auto& par : adyacencia) {
        std::cout << "Ciudad: " << par.first << "\n";
        for (const auto& conexion : par.second)
            std::cout << "  -> " << conexion.first << " (" << conexion.second << " km)\n";
        std::cout << std::endl;
    }
}

bool Grafo::cargarDesdeArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo("Logs/" + nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << nombreArchivo << std::endl;
        return false;
    }

    std::string c1, c2;
    float distancia;
    while (archivo >> c1 >> c2 >> distancia) {
        agregarRuta(c1, c2, distancia);
    }
    archivo.close();
    return true;
}

// ------------------- GETTERS / SETTERS -------------------

std::vector<std::string> Grafo::getCiudades() const {
    std::vector<std::string> ciudades;
    for (const auto& par : adyacencia)
        ciudades.push_back(par.first);
    return ciudades;
}

std::vector<std::pair<std::string, float>> Grafo::getRutas(const std::string& ciudad) const {
    auto it = adyacencia.find(ciudad);
    if (it != adyacencia.end())
        return it->second;
    return {};
}

void Grafo::setRutas(const std::string& ciudad, const std::vector<std::pair<std::string, float>>& rutas) {
    adyacencia[ciudad] = rutas;
}

// ------------------- RUTA MÁS CORTA -------------------

std::vector<std::string> Grafo::rutaMasCorta(const std::string& origen, const std::string& destino) const {
    std::unordered_map<std::string, float> dist;
    std::unordered_map<std::string, std::string> prev;

    for (const auto& par : adyacencia)
        dist[par.first] = std::numeric_limits<float>::infinity();

    dist[origen] = 0;

    using P = std::pair<float, std::string>; // (distancia, ciudad)
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    pq.push({0, origen});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (u == destino) break;

        for (auto& [v, peso] : getRutas(u)) {
            float alt = d + peso;
            if (alt < dist[v]) {
                dist[v] = alt;
                prev[v] = u;
                pq.push({alt, v});
            }
        }
    }

    // Reconstruir ruta
    std::vector<std::string> ruta;
    std::string actual = destino;
    while (actual != origen) {
        ruta.push_back(actual);
        if (prev.find(actual) == prev.end())
            return {}; // no hay ruta
        actual = prev[actual];
    }
    ruta.push_back(origen);
    std::reverse(ruta.begin(), ruta.end());
    return ruta;
}