#include "path_printer.h"

#include <iostream>

// void PathPrinter::PrintMinPath(const std::string& srcCity, const std::string& desCity, int distance) {
//     if (distance == 100000) {
//         PrintUnknownPath(srcCity, desCity);
//     } else {
//         std::cout << "\nThe minimum distance between " << srcCity << " and " << desCity << " is " << distance << std::endl;
//     }
// }

void PathPrinter::PrintMinPath(const std::string& srcCity, const std::string& desCity, const std::vector<int>& pathArray, int desNode) {
    // std::cout << std::endl << "The minimum distance between " << srcCity << " and " << desCity << " is " << pathArray[desNode] << std::endl;
    for (int i = 0; i < pathArray.size(); ++i) {
        if (pathArray[i] == 100000) {
            std::cout << "Unknown ";
        } else {
            std::cout << pathArray[i] << " ";
        }
    }
    std::cout << std::endl;
}

void PathPrinter::PrintUnknownPath(const std::string& srcCity, const std::string& desCity) {
    std::cout << "\nThe minimum distance between " << srcCity << " and " << desCity << " is unknown" << std::endl;
}
