#include "Libraries/Grafos/grafo.h"
#include "Libraries/BPlus/ArbolBPlus.h"
#include "Libraries/Paquetes/GestorDePaquetes.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> // std::remove_if, etc.

int main() {
    Grafo g;
    ArbolBPlus arbol(3);
    GestorDePaquetes gestor;

    std::ifstream file;

    // 1️⃣ Cargar ciudades desde Nodes.txt
    file.open("Logs/Ciudades.txt");
    if (!file) { std::cerr << "Error al abrir Ciudades.txt\n"; return 1; }

    std::string ciudad;
    // Ignorar BOM UTF-8 si existe
    if (file.peek() == '\xEF') file.ignore(3);

    while (std::getline(file, ciudad)) {
        if (!ciudad.empty()) {
            // Limpiar espacios iniciales y finales
            ciudad.erase(0, ciudad.find_first_not_of(" \t\r\n"));
            ciudad.erase(ciudad.find_last_not_of(" \t\r\n") + 1);
            g.agregarCiudad(ciudad);
        }
    }
    file.close();

    // 2️⃣ Cargar rutas desde Rutas.txt
    file.open("Logs/Rutas.txt");
    if (!file) { std::cerr << "Error al abrir Rutas.txt\n"; return 1; }

    std::string ciudad1, ciudad2;
    float distancia;
    while (file >> ciudad1 >> ciudad2 >> distancia) {
        // Limpiar posibles espacios residuales
        ciudad1.erase(0, ciudad1.find_first_not_of(" \t\r\n"));
        ciudad1.erase(ciudad1.find_last_not_of(" \t\r\n") + 1);
        ciudad2.erase(0, ciudad2.find_first_not_of(" \t\r\n"));
        ciudad2.erase(ciudad2.find_last_not_of(" \t\r\n") + 1);
        g.agregarRuta(ciudad1, ciudad2, distancia);
    }
    file.close();

    // 3️⃣ Cargar paquetes desde GestorDePaquetes.txt
    file.open("Logs/GestorDePaquetes.txt");
    if (!file) { std::cerr << "Error al abrir GestorDePaquetes.txt\n"; return 1; }

    std::string destino;
    int prioridad;
    while (file >> destino >> prioridad) {
        gestor.agregarPaquete({destino, prioridad});
    }
    file.close();

    // 4️⃣ Cargar informacion de ciudades desde ArbolBPlus.txt
    file.open("Logs/ArbolBPlus.txt");
    if (!file) { std::cerr << "Error al abrir ArbolBPlus.txt\n"; return 1; }

    std::string nombreCiudad;
    int poblacion;
    while (file >> nombreCiudad >> poblacion) {
        arbol.insertar({nombreCiudad, poblacion});
    }
    file.close();

    // 5️⃣ Listar ciudades para elegir origen
    std::cout << "Ciudades disponibles:\n";
    for (const auto& c : g.getCiudades())
        std::cout << " - " << c << "\n";

    std::string ciudadOrigen;
    std::cout << "Seleccione la ciudad de origen: ";
    std::getline(std::cin >> std::ws, ciudadOrigen); // <<<< aquí se ignoran espacios iniciales

    // 6️⃣ Simulacion de entrega
    while (gestor.hayPaquetes()) {
        Paquete paquete = gestor.obtenerSiguiente();
        std::cout << "\nEntregando paquete a " << paquete.destino 
                  << " (Prioridad: " << paquete.prioridad << ")\n";

        // Encontrar ruta más corta
        auto ruta = g.rutaMasCorta(ciudadOrigen, paquete.destino);
        std::cout << "Ruta desde " << ciudadOrigen << " hasta " << paquete.destino << ": ";
        for (size_t i = 0; i < ruta.size(); ++i) {
            std::cout << ruta[i];
            if (i != ruta.size() - 1) std::cout << " -> ";
        }
        std::cout << "\n";

        // Mostrar info ciudad
        Ciudad* info = arbol.buscar(paquete.destino);
        if (info)
            std::cout << "Informacion de " << info->nombre 
                      << ": poblacion = " << info->poblacion << "\n";
        else
            std::cout << "No se encontro informacion de la ciudad.\n";
    }

    return 0;
}