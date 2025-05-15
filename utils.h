#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <chrono>

void Assert(bool val, std::string s);
extern int defaultSize;

template <typename F>
void logOperation(const std::string& label, F&& fn) {
    auto start = std::chrono::high_resolution_clock::now();

    fn();            //Run the operation

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << label << " completed successfully in " << duration.count() << "µs\n";
}

#endif