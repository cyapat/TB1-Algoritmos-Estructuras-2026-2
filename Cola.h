#pragma once
#ifndef COLA_H
#define COLA_H

#include <iostream>
#include <functional>
#include "Nodo.h"

using namespace std;

template <typename T>
class Cola {
private:
    NodoSimple<T>* frente;
    NodoSimple<T>* final;
    int cantidad;

public:
    Cola() {
        frente = nullptr;
        final = nullptr;
        cantidad = 0;
    }

    ~Cola() {
        limpiar();
    }

    bool esVacia() const {
        return frente == nullptr;
    }

    int getCantidad() const {
        return cantidad;
    }

    // Operacion principal de la cola: insertar al final
    void encolar(T dato) {
        NodoSimple<T>* nuevo = new NodoSimple<T>(dato);

        if (esVacia()) {
            frente = nuevo;
            final = nuevo;
        }
        else {
            final->setSiguiente(nuevo);
            final = nuevo;
        }

        cantidad++;
    }

    // Operacion principal de la cola: retirar el primero
    bool desencolar(T& dato) {
        if (esVacia()) {
            return false;
        }

        NodoSimple<T>* eliminado = frente;
        dato = frente->getDato();
        frente = frente->getSiguiente();

        if (frente == nullptr) {
            final = nullptr;
        }

        delete eliminado;
        cantidad--;
        return true;
    }

    // Consultar el primer elemento sin eliminarlo
    bool verFrente(T& dato) const {
        if (esVacia()) {
            return false;
        }

        dato = frente->getDato();
        return true;
    }

    // Metodo nuevo 1: recorrer la cola aplicando una lambda
    void recorrer(function<void(T)> accion) const {
        NodoSimple<T>* actual = frente;

        while (actual != nullptr) {
            accion(actual->getDato());
            actual = actual->getSiguiente();
        }
    }

    // Metodo nuevo 2: contar elementos que cumplen un criterio
    int contarSi(function<bool(T)> criterio) const {
        int contador = 0;
        NodoSimple<T>* actual = frente;

        while (actual != nullptr) {
            if (criterio(actual->getDato())) {
                contador++;
            }
            actual = actual->getSiguiente();
        }

        return contador;
    }

    // Metodo nuevo 3: calcular promedio de un valor numerico del objeto
    float promedio(function<float(T)> selector) const {
        if (esVacia()) {
            return 0.0f;
        }

        float suma = 0.0f;
        NodoSimple<T>* actual = frente;

        while (actual != nullptr) {
            suma = suma + selector(actual->getDato());
            actual = actual->getSiguiente();
        }

        return suma / cantidad;
    }

    // Metodo adicional: comprobar si existe un elemento segun un criterio
    bool existe(function<bool(T)> criterio) const {
        NodoSimple<T>* actual = frente;

        while (actual != nullptr) {
            if (criterio(actual->getDato())) {
                return true;
            }
            actual = actual->getSiguiente();
        }

        return false;
    }

    void limpiar() {
        NodoSimple<T>* actual = frente;

        while (actual != nullptr) {
            NodoSimple<T>* temp = actual;
            actual = actual->getSiguiente();
            delete temp;
        }

        frente = nullptr;
        final = nullptr;
        cantidad = 0;
    }
};

#endif // COLA_H
