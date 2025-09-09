#include "GestorDePaquetes.h"

GestorDePaquetes::GestorDePaquetes() {}
GestorDePaquetes::~GestorDePaquetes() {}

void GestorDePaquetes::agregarPaquete(const Paquete& p) {
    paquetes.push(p);
}

bool GestorDePaquetes::hayPaquetes() const {
    return !paquetes.empty();
}

Paquete GestorDePaquetes::obtenerSiguiente() {
    if (paquetes.empty())
        throw std::runtime_error("No hay paquetes disponibles");
    Paquete p = paquetes.top();
    paquetes.pop();
    return p;
}
