#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <limits>

class Utils {
public:
    static void limpiarPantalla() {
        std::cout << "\033[2J\033[H";
    }

    static void limpiarEntrada() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    static void pausar() {
        std::cout << "\nPresiona Enter para continuar...";
        limpiarEntrada();
    }
};

#endif // UTILS_H
