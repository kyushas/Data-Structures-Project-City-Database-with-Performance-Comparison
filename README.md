# Cities-Database---Data-Structure-Analysis
Composite experiment developed for my Computer Science degree (Data Structures &amp; Algorithms course).
This project implements a city database using both a Singly Linked List and an Array-based List, allowing operations such as insertion, deletion, searching, and file loading. It then compares the efficiency and behavior of both data structures through real-time performance measurements.

> **Note:** The data structure implementations (and the "assert" function) are based on _Data Structures and Algorithm Analysis in C++ (3rd Edition)_ by Clifford A. Shaffer, with minor modifications for improved efficiency (e.g., replacing `NULL` with `nullptr`, and other modern C++ best practices).
>
> ## Features
- Custom singly linked list implementation (no STL containers)
- Freelist support for memory-efficient node reuse
- Interactive menu system (terminal-based)
- Load cities from file (supports names with spaces and quotes, check the formatting in the example files (european_capitals.txt & american_capitals.txt))
- Search and delete by city name or coordinates
- Real-time operation timing comparison with microsecond precision (using the chrono library)

## Handling "Last Element" Access

In this project, both the singly linked list and array list include an option to view the **last element** in the database. However, each structure handles the "end" position differently, so some extra care is needed:

### Array-Based List
Calling `moveToEnd()` in the array list sets the internal cursor **past the last valid element**, which makes directly calling `getValue()` invalid and will trigger an assertion failure, therefore exiting the program.

To solve this:
- After `moveToEnd()`, we manually call `prev()` to step back to the actual last element.
- Then we safely use `getValue()` to retrieve it.

```cpp
logOperation("Move to end (Array List)", [&]() {
                            if (arrayList.length() == 0) {
                                std::cout << "Array List: Empty.\n";
                                  return;
                                }
                            arrayList.moveToEnd();
                            arrayList.prev(); //Step back to the last valid element
                            std::cout << "Array List: " << arrayList.getValue() << "\n";
                        });
```

### Linked List
In the linked list implementation `moveToEnd()` moves the `curr` pointer directly to the last element, so `getValue()` is safe to be called immediately (unless the list is empty). To avoid errors, the code also checks if the list is empty and if it is, it skips the operation and print an error message instead. 

```cpp
logOperation("Move to end (Linked List)", [&]() {
    if (linkedList.length() == 0) {
        std::cout << "Linked List: Empty.\n";
        return;
    }
    linkedList.moveToEnd();
    linkedList.prev(); //Step back to the last valid element
    std::cout << "Linked List: " << linkedList.getValue() << "\n";
});
```
