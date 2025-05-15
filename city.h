#ifndef CITY_H
#define CITY_H

#include <string> 
#include <iostream>

struct City {
    std::string name;
    float x, y;

    bool operator == (const City& other) const { 
        return name == other.name && x == other.x && y == other.y;
    }
};

inline std::ostream& operator<<(std::ostream& os, const City& city) {
    os << city.name << " (" << city.x << ", " << city.y << ")";
    return os;
};

#endif