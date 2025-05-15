#ifndef CITYDB_H
#define  CITYDB_H

#include "LList.h"
#include "city.h"

template <typename ListType>
City* searchByName(ListType& list, const std::string& target);

template <typename ListType>
bool deleteByName(ListType& list, const std::string& target);

template <typename ListType>
City* searchByCoordinates(ListType& list, float x, float y);

template <typename ListType>
bool loadCitiesFromFile(const std::string& filename, ListType& list);

#endif