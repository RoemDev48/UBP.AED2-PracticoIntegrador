#include <iostream>
#include "Libraries/Grafos/grafo.h"

int main()
{
    Grafo g;

    if (g.cargarDesdeArchivo("Nodes.txt"))
    {
        std::cout << "Grafo cargado correctamente.\n";
        g.imprimirGrafo();
    }
    else
    {
        std::cerr << "Error al cargar el grafo.\n";
    }

    return 0;
}
