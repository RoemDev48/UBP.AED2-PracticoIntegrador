#pragma once
#include <iostream>
#include <vector>
#include <string>

struct Ciudad {
    std::string nombre;
    int poblacion;

    Ciudad() : nombre(""), poblacion(0) {}
    Ciudad(const std::string& n, int p) : nombre(n), poblacion(p) {}
};

class NodoBPlus {
public:
    bool esHoja;
    std::vector<Ciudad> claves;         // Claves dentro del nodo
    std::vector<NodoBPlus*> hijos;      // Punteros a hijos
    NodoBPlus* siguiente;               // Para hojas: puntero al siguiente nodo hoja

    NodoBPlus(bool hoja);
    ~NodoBPlus();
};

class ArbolBPlus {
private:
    NodoBPlus* raiz;
    int grado;  // Máximo número de claves por nodo

public:
    ArbolBPlus(int g = 3); // grado mínimo 3
    ~ArbolBPlus();

    void insertar(const Ciudad& ciudad);
    Ciudad* buscar(const std::string& nombre);
    void imprimirArbol() const;

private:
    void imprimirNodo(NodoBPlus* nodo, int nivel) const;
};