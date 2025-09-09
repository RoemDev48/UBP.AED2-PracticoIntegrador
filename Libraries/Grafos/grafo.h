#pragma once
#include <string>
#include <vector>
#include <map>

class Grafo {
private:
    // Lista de adyacencia: ciudad -> vector de pares (ciudad vecina, distancia)
    std::map<std::string, std::vector<std::pair<std::string, float>>> adyacencia;

public:
    Grafo() {}

    // Métodos existentes
    void agregarCiudad(const std::string& nombre);
    void agregarRuta(const std::string& ciudad1, const std::string& ciudad2, float distancia);
    void imprimirGrafo() const;

    // Cargar desde archivo
    bool cargarDesdeArchivo(const std::string& nombreArchivo);

    // --- NUEVOS SETTERS / GETTERS ---
    
    // Obtener todas las ciudades
    std::vector<std::string> getCiudades() const;

    // Obtener las rutas de una ciudad
    std::vector<std::pair<std::string, float>> getRutas(const std::string& ciudad) const;

    // Modificar o reemplazar rutas de una ciudad
    void setRutas(const std::string& ciudad, const std::vector<std::pair<std::string, float>>& rutas);

    // Calcular ruta más corta usando Dijkstra
    std::vector<std::string> rutaMasCorta(const std::string& origen, const std::string& destino) const;
};