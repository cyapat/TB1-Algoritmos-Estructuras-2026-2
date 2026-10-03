#pragma once
#ifndef LISTA_SIMPLE_H
#define LISTA_SIMPLE_H

#include <iostream>
#include <functional>
#include "Nodo.h"

using namespace std;

template <typename T>
class ListaSimple {
private:
    NodoSimple<T>* cabeza;
    int cantidad;

public:
    ListaSimple() {
        cabeza = nullptr;
        cantidad = 0;
    }

    ~ListaSimple() {
        limpiar();
    }

    int getCantidad() const {
        return cantidad;
    }

    bool esVacia() const {
        return cabeza == nullptr;
    }

    // Insertar al final de la lista
    void insertarFinal(T dato) {
        NodoSimple<T>* nuevo = new NodoSimple<T>(dato);
        if (esVacia()) {
            cabeza = nuevo;
        }
        else {
            NodoSimple<T>* aux = cabeza;
            while (aux->getSiguiente() != nullptr) {
                aux = aux->getSiguiente();
            }
            aux->setSiguiente(nuevo);
        }
        cantidad++;
    }

    // Recorrer e imprimir los elementos mediante un callback/lambda
    void recorrer(function<void(T)> accion) const {
        NodoSimple<T>* aux = cabeza;
        while (aux != nullptr) {
            accion(aux->getDato());
            aux = aux->getSiguiente();
        }
    }

    // Buscar un elemento segun un criterio
    T* buscar(function<bool(T)> criterio) const {
        NodoSimple<T>* aux = cabeza;
        while (aux != nullptr) {
            if (criterio(aux->getDato())) {
                return new T(aux->getDato());
            }
            aux = aux->getSiguiente();
        }
        return nullptr;
    }

    // =================================================================
    // 3 MÉTODOS NUEVOS EXIGIDOS POR LA RÚBRICA (PERSONA 1)
    // =================================================================

    // Método Nuevo 1: Contar elementos que cumplen un criterio (Uso con Lambdas)
    int contarSi(function<bool(T)> criterio) const {
        int contador = 0;
        NodoSimple<T>* aux = cabeza;
        while (aux != nullptr) {
            if (criterio(aux->getDato())) {
                contador++;
            }
            aux = aux->getSiguiente();
        }
        return contador;
    }

    // Método Nuevo 2: Eliminar un nodo en memoria según un criterio especificado
    bool eliminarSi(function<bool(T)> criterio) {
        if (esVacia()) return false;

        NodoSimple<T>* actual = cabeza;
        NodoSimple<T>* anterior = nullptr;

        while (actual != nullptr) {
            if (criterio(actual->getDato())) {
                if (anterior == nullptr) {
                    cabeza = actual->getSiguiente();
                } else {
                    anterior->setSiguiente(actual->getSiguiente());
                }
                delete actual;
                cantidad--;
                return true;
            }
            anterior = actual;
            actual = actual->getSiguiente();
        }
        return false;
    }

    // Método Nuevo 3: Invertir completamente el orden de los nodos en la lista
    void invertir() {
        NodoSimple<T>* anterior = nullptr;
        NodoSimple<T>* actual = cabeza;
        NodoSimple<T>* siguiente = nullptr;

        while (actual != nullptr) {
            siguiente = actual->getSiguiente();
            actual->setSiguiente(anterior);
            anterior = actual;
            actual = siguiente;
        }
        cabeza = anterior;
    }

    // Vaciar lista y liberar memoria dinamica
    void limpiar() {
        while (cabeza != nullptr) {
            NodoSimple<T>* aux = cabeza;
            cabeza = cabeza->getSiguiente();
            delete aux;
        }
        cantidad = 0;
    }
};

#endif // LISTA_SIMPLE_H
