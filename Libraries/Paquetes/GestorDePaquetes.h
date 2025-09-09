#pragma once
#include "Paquete.h"
#include <queue>
#include <stdexcept>

class GestorDePaquetes {
private:
    std::priority_queue<Paquete> paquetes;

public:
    GestorDePaquetes();
    ~GestorDePaquetes();

    void agregarPaquete(const Paquete& p);
    bool hayPaquetes() const;
    Paquete obtenerSiguiente();
};
