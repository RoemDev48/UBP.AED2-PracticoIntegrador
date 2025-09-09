#pragma once
#include <string>

struct Paquete {
    std::string destino;
    int prioridad;

    Paquete(const std::string& d = "", int p = 0) : destino(d), prioridad(p) {}

    bool operator<(const Paquete& other) const {
        return prioridad < other.prioridad; // mayor prioridad primero
    }
};