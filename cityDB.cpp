#include "city.h"
#include <fstream>
#include <sstream>
#include <iostream>

template <typename ListType>
City* searchByName(ListType& list, const std::string& target) {
    list.moveToStart();
    for (int i = 0; i < list.length(); ++i) {
        City current = list.getValue();
        if (current.name == target) {
            return new City(current);
        }
        list.next();
    }
    return nullptr;
}

template <typename ListType>
bool deleteByName(ListType& list, const std::string& target) {
    list.moveToStart();
    for (int i = 0; i < list.length(); ++i) {
        if (list.getValue().name == target) {
            list.remove();
            return true;
        }
        list.next();
    }
    return false;
}

template <typename ListType>
City* searchByCoordinates(ListType& list, float x, float y) {
    list.moveToStart();
    for (int i = 0; i < list.length(); ++i) {
        City current = list.getValue();
        if (current.x == x && current.y == y) {
            return new City(current);
        }
        list.next();
    }
    return nullptr;
}

template <typename ListType>
bool loadCitiesFromFile(const std::string& filename, ListType& list) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Failed to open file: " << filename << "\n";
        return false;
    }

    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string name;
        float x, y;

        if (line[0] == '"') {
            size_t end = line.find('"', 1);
            if (end == std::string::npos) continue;
            name = line.substr(1, end - 1);
            iss.seekg(end + 1);
        } else {
            iss >> name;
        }

        iss >> x >> y;
        if (!iss.fail()) {
            list.append({name, x, y});
        }
    }

    std::cout << "Cities loaded from file.\n";
    return true;
}

//Explicit instantiations for linker
#include "LList.h"
#include "arrayList.h"

template City* searchByName(LList<City>&, const std::string&);
template City* searchByName(AList<City>&, const std::string&);
template bool deleteByName(LList<City>&, const std::string&);
template bool deleteByName(AList<City>&, const std::string&);
template City* searchByCoordinates(LList<City>&, float, float);
template City* searchByCoordinates(AList<City>&, float, float);
template bool loadCitiesFromFile(const std::string&, LList<City>&);
template bool loadCitiesFromFile(const std::string&, AList<City>&);
