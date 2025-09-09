#include "ArbolBPlus.h"
#include <algorithm>

NodoBPlus::NodoBPlus(bool hoja) : esHoja(hoja), siguiente(nullptr) {}

NodoBPlus::~NodoBPlus() {
    for (auto h : hijos)
        delete h;
}

ArbolBPlus::ArbolBPlus(int g) : raiz(nullptr), grado(g) {}
ArbolBPlus::~ArbolBPlus() { delete raiz; }

// Inserción simple sin splits (para simplificar el ejemplo)
void ArbolBPlus::insertar(const Ciudad& ciudad) {
    if (!raiz) {
        raiz = new NodoBPlus(true);
        raiz->claves.push_back(ciudad);
        return;
    }

    // Inserción en hoja (simplificada, sin split)
    NodoBPlus* nodo = raiz;
    while (!nodo->esHoja) {
        int i = 0;
        while (i < nodo->claves.size() && ciudad.nombre > nodo->claves[i].nombre)
            i++;
        nodo = nodo->hijos[i];
    }

    // Insertar en orden alfabético
    auto it = std::lower_bound(nodo->claves.begin(), nodo->claves.end(), ciudad,
                               [](const Ciudad& a, const Ciudad& b){ return a.nombre < b.nombre; });
    nodo->claves.insert(it, ciudad);
}

// Búsqueda por nombre
Ciudad* ArbolBPlus::buscar(const std::string& nombre) {
    NodoBPlus* nodo = raiz;
    while (nodo) {
        if (nodo->esHoja) {
            for (auto& c : nodo->claves)
                if (c.nombre == nombre)
                    return &c;
            return nullptr;
        } else {
            int i = 0;
            while (i < nodo->claves.size() && nombre > nodo->claves[i].nombre)
                i++;
            nodo = nodo->hijos[i];
        }
    }
    return nullptr;
}

// Impresión recursiva
void ArbolBPlus::imprimirArbol() const {
    imprimirNodo(raiz, 0);
}

void ArbolBPlus::imprimirNodo(NodoBPlus* nodo, int nivel) const {
    if (!nodo) return;

    std::cout << std::string(nivel * 4, ' ');
    for (const auto& c : nodo->claves)
        std::cout << c.nombre << "(" << c.poblacion << ") ";
    std::cout << std::endl;

    if (!nodo->esHoja)
        for (auto h : nodo->hijos)
            imprimirNodo(h, nivel + 1);
}