#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <limits>
#include <cstdlib>

class Utils {
public:
    static void limpiarPantalla() {
#ifdef _WIN32
        // Visual Studio / Windows: limpia realmente la consola.
        system("cls");
#else
        // Alternativa para terminales compatibles con ANSI.
        std::cout << "\033[2J\033[H";
#endif
    }

    static void limpiarEntrada() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    static void pausar() {
#ifdef _WIN32
        // No depende del buffer de cin, por eso la pantalla queda visible
        // hasta que el usuario presiona una tecla.
        std::cout << "\n";
        system("pause");
#else
        std::cout << "\nPresiona Enter para continuar...";
        std::cin.clear();
        if (std::cin.rdbuf()->in_avail() > 0) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.get();
#endif
    }
};

#endif // UTILS_H
