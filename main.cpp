#include <iostream>
#include <limits>
#include "LList.h"
#include "city.h"
#include "cityDB.h"
#include "arrayList.h"

void showMenu(){
    std::cout << "\n ==== CITY DATABASE MENU ====\n";
    std::cout << "1. Add a city\n";
    std::cout << "2. Load cities from file\n";
    std::cout << "3. Search by name\n";
    std::cout << "4. Delete by name\n";
    std::cout << "5. Search by coordinates\n";
    std::cout << "6. View all cities\n";
    std::cout << "7. Inspect current element\n";
    std::cout << "8. Clear database\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose an option: ";
}

int main() {
    LList<City> linkedList;
    AList<City> arrayList(1000); //Max capacity
    int choice;

    do{
        showMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch(choice) {
            case 1: {
                std::string name;
                float x, y;
                std::cout << "City name: ";
                std::getline(std::cin, name);
                std::cout << "X coordinate: ";
                std::cin >> x;
                std::cout << "Y coordinate: ";
                std::cin >> y;
                std::cin.ignore();

                City newCity{name, x, y};      //For array-based list

                logOperation("Insert (Array List)", [&]() {
                    arrayList.append(newCity);
                });

                logOperation("Insert city (Linked List)", [&](){
                    linkedList.append({name, x, y});
                });
                std::cout << name << " was added to the database.\n";
                break;
            }
            case 2: {
                std::string filename;
                std::cout << "Enter filename (e.g., cities.txt): ";
                std::getline(std::cin, filename);

                logOperation("Load from file (Array List)", [&]() {
                    loadCitiesFromFile(filename, arrayList);
                });

                logOperation("Load cities from file (Linked List)", [&](){
                    loadCitiesFromFile(filename, linkedList);
                });
                break;
            }
            case 3: {
                std::string name;
                std::cout << "Enter name to search: ";
                std::getline(std::cin, name);

                logOperation("Search by name (Array List)", [&]() {
                    City* found = searchByName(arrayList, name);
                    if (found) {
                        std::cout << "Found (AL): " << *found << "\n";
                        delete found;
                    } else {
                        std::cout << "City not found (AL).\n";
                    }
                });

                logOperation("Search by name (Linked List)", [&]() {
                    City* found = searchByName(linkedList, name);
                    if(found) {
                        std::cout << "Found: " << *found << '\n';
                        delete found;
                    } else {
                        std::cout << "City not found.\n";
                    }
                 });
                break;
            }
            case 4: {
                std::string name;
                std::cout << "Enter name to delete: ";
                std::getline(std::cin, name);

                logOperation("Delete by name (Array List)", [&]() {
                    if (deleteByName(arrayList, name))
                        std::cout << "Deleted (AL).\n";
                    else
                        std::cout << "Not found (AL).\n";
                });

                logOperation("Delete by name (Linked List)", [&](){
                    if(deleteByName(linkedList,name))
                        std::cout << name << " was deleted from the database.\n";
                    else
                        std::cout << "City not found.\n";
                });
                break;
            }
            case 5: {
                float x, y;
                std::cout << "Enter X coordinate: ";
                std::cin >> x;
                std::cout << "Enter Y coordinate: ";
                std::cin >> y;
                std::cin.ignore();

                logOperation("Search by coordinates (Array List)", [&]() {
                    City* found = searchByCoordinates(arrayList, x, y);
                    if (found) {
                        std::cout << "Found (AL): " << *found << "\n";
                        delete found;
                    } else {
                        std::cout << "Not found (AL).\n";
                    }
                });

                logOperation("Search by coordinates (Linked List)", [&](){
                    City* found = searchByCoordinates(linkedList, x, y);
                        if(found) {
                        std::cout << "Found: " << *found << '\n';
                        delete found;
                      } else {
                    std::cout << "City not found.\n";
                }
                });
                break;
            }
            case 6: {
                std::cout << "\nAll cities in the database:\n";

                std::cout << "\n--- Cities in Array List ---\n";
                logOperation("Print (Array List)", [&]() {
                    arrayList.print();
                });

                std::cout << "\n--- Cities in Linked List ---\n";
                logOperation("Print all cities in the database (Linked List)", [&](){
                    linkedList.print();
                });
                break;
            }

            case 7: {
                std::cout << "\n--- Current Element Menu ---\n";
                std::cout << "a. Show current element\n";
                std::cout << "b. Move to next element\n";
                std::cout << "c. Move to previous element\n";
                std::cout << "d. Move to last element\n";
                std::cout << "e. Show current position\n";
                std::cout << "f. Back to main menu\n";

                char sub;
                std::cin >> sub;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                switch (sub) {
                    case 'a':
                        logOperation("Get current (Array List)", [&]() {
                            try {
                                std::cout << "Array List: " << arrayList.getValue() << "\n";
                            } catch (...) {
                                std::cout << "Array List: No current element.\n";
                            }
                        });
                        logOperation("Get current (Linked List)", [&]() {
                            try {
                                std::cout << "Linked List: " << linkedList.getValue() << "\n";
                            } catch (...) {
                                std::cout << "Linked List: No current element.\n";
                            }
                        });
                        break;

                    case 'b':
                        logOperation("Next (Array List)", [&]() {
                            arrayList.next();
                            std::cout << "Array List: " << arrayList.getValue() << "\n";
                        });
                        logOperation("Next (Linked List)", [&]() {
                            linkedList.next();
                            std::cout << "Linked List: " << linkedList.getValue() << "\n";
                        });
                        break;

                    case 'c':
                        logOperation("Previous (Array List)", [&]() {
                            arrayList.prev();
                            std::cout << "Array List: " << arrayList.getValue() << "\n";
                        });
                        logOperation("Previous (Linked List)", [&]() {
                            linkedList.prev();
                            std::cout << "Linked List: " << linkedList.getValue() << "\n";
                        });
                        break;

                    case 'd':
                        logOperation("Move to end (Array List)", [&]() {
                            if (arrayList.length() == 0) {
                                std::cout << "Array List: Empty.\n";
                                  return;
                                }
                            arrayList.moveToEnd();
                            arrayList.prev(); //Step back to the last valid element
                            std::cout << "Array List: " << arrayList.getValue() << "\n";
                        });
                        logOperation("Move to end (Linked List)", [&]() {
                            if (linkedList.length() == 0) {
                                std::cout << "Linked List: Empty.\n";
                                return;
                            }
                            linkedList.moveToEnd();
                            linkedList.prev(); //Step back to the last valid element
                            std::cout << "Linked List: " << linkedList.getValue() << "\n";
                        });
                        break;

                    case 'e':
                        logOperation("Show current position (Array List)", [&]() {
                            std::cout << "Array List position: " << arrayList.currPos() << "\n";
                        });

                        logOperation("Show current position (Linked List)", [&]() {
                            std::cout << "Linked List position: " << linkedList.currPos() << "\n";
                        });
                        break;

                    default:
                        std::cout << "Returning to main menu...\n";
                }
                break;
            }
            case 8: { 
                logOperation("Clear (Array List)", [&]() {
                    arrayList.clear();
                });
                logOperation("Clear (Linked List)", [&]() {
                    linkedList.clear();
                });
                std::cout << "All cities cleared from both databases.\n";
                break;
            }

            case 0: 
                std::cout << "See you next time!\n";
                break;
                
            default:
                std::cout << "Invalid option. Try again.\n\n";
            }
        }while(choice != 0);

    return 0;
}