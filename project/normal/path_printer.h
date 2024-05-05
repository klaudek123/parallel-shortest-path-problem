#ifndef PATH_PRINTER_H
#define PATH_PRINTER_H

#include <string>
#include <vector>

class PathPrinter {
public:
    static void PrintMinPath(const std::string& srcCity, const std::string& desCity, int distance);
    static void PrintMinPath(const std::string& srcCity, const std::string& desCity, const std::vector<int>& pathArray, int desNode);
private:
    static void PrintUnknownPath(const std::string& srcCity, const std::string& desCity);
};



#endif //PATH_PRINTER_H
