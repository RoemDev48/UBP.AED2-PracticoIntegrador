#include "Node.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>

class City : public Node
{
public:
    City(const std::string& name = "Desconocida") : name(name) {}

    std::string getName() const { return name; }
    void setName(const std::string& n) { name = n; }

private:
    std::string name;
};

int main(int argc, char** argv)
{
    std::map<std::string, City*> cities; // <-- ahora punteros

    if (argc != 2)
    {
        std::cerr << "Número de argumentos inválido (recibidos: "
                  << argc << ", esperados: 2).\n";
        std::getchar();
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file)
    {
        std::cerr << "No se pudo abrir el archivo '" << argv[1] << "'.\n";
        std::getchar();
        return 1;
    }

    std::string city1, city2;
    float distance;

    while (file >> city1 >> city2 >> distance)
    {
        if (cities.find(city1) == cities.end())
            cities[city1] = new City(city1);
        if (cities.find(city2) == cities.end())
            cities[city2] = new City(city2);

        cities[city1]->addChild(cities[city2], distance);
        cities[city2]->addChild(cities[city1], distance);
    }

    for (const auto& pair : cities)
    {
        std::cout << "Ciudad: " << pair.first << "\n";
        for (const auto& child : pair.second->getChildren())
        {
            City* c = static_cast<City*>(child.first);
            std::cout << "  -> " << c->getName() << " (" << child.second << " km)\n";
        }
        std::cout << std::endl;
    }

    // Liberar memoria
    for (auto& pair : cities)
        delete pair.second;

    return 0;
}
