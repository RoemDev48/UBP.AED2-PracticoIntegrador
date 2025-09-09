#include "Libraries/BPlus/ArbolBPlus.h"
#include <iostream>
#include <string>

int main() {
    ArbolBPlus arbol(3);  // grado mínimo 3
    int opcion;

    do {
        std::cout << "\n==== Arbol B+ de Ciudades ====\n";
        std::cout << "1. Insertar ciudad\n";
        std::cout << "2. Buscar ciudad\n";
        std::cout << "3. Imprimir arbol\n";
        std::cout << "0. Salir\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch(opcion) {
            case 1: {
                std::string nombre;
                int poblacion;
                std::cin.ignore(); 
                std::cout << "Nombre de la ciudad: ";
                std::getline(std::cin, nombre); 
                std::cout << "Poblacion: ";
                std::cin >> poblacion;
                arbol.insertar({nombre, poblacion});
                std::cout << "Ciudad insertada.\n";
                break;
        }
            case 2: {
                std::string nombre;
                std::cin.ignore();  // limpia el buffer previo
                std::cout << "Ingrese nombre de la ciudad a buscar: ";
                std::getline(std::cin, nombre);  // lee toda la línea incluyendo espacios

                Ciudad* c = arbol.buscar(nombre);
                if (c)
                    std::cout << "Ciudad encontrada: " << c->nombre
                            << ", Poblacion: " << c->poblacion << std::endl;
                else
                    std::cout << "Ciudad " << nombre << " no encontrada.\n";
                break;
            }
            case 3:
                std::cout << "Contenido del arbol:\n";
                arbol.imprimirArbol();
                break;
            case 0:
                std::cout << "Saliendo...\n";
                break;
            default:
                std::cout << "Opcion invalida.\n";
        }

    } while(opcion != 0);

    return 0;
}