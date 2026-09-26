#ifndef ENTIDADES_H
#define ENTIDADES_H

#include <iostream>
#include <string>

using namespace std;

// ==========================================
// 1. ENTIDAD: Categoria
// ==========================================
class Categoria {
private:
    int idCategoria;
    string nombre;
    string descripcion;

public:
    // Constructores
    Categoria() {
        idCategoria = 0;
        nombre = "";
        descripcion = "";
    }

    Categoria(int id, string nom, string desc) {
        idCategoria = id;
        nombre = nom;
        descripcion = desc;
    }

    // Getters
    int getIdCategoria() const {
        return idCategoria;
    }

    string getNombre() const {
        return nombre;
    }

    string getDescripcion() const {
        return descripcion;
    }

    // Setters
    void setIdCategoria(int id) {
        idCategoria = id;
    }

    void setNombre(string nom) {
        nombre = nom;
    }

    void setDescripcion(string desc) {
        descripcion = desc;
    }

    // Mostrar informacion
    void mostrarInfo() const {
        cout << "[Cat. #" << idCategoria << "] " << nombre << " - " << descripcion << "\n";
    }
};

// ==========================================
// 2. ENTIDAD: Pin
// ==========================================
class Pin {
private:
    int idPin;
    string titulo;
    string urlImagen;
    string descripcion;
    int popularidad;
    int idCategoria;

public:
    // Constructores
    Pin() {
        idPin = 0;
        titulo = "";
        urlImagen = "";
        descripcion = "";
        popularidad = 0;
        idCategoria = 0;
    }

    Pin(int id, string tit, string url, string desc, int pop, int idCat) {
        idPin = id;
        titulo = tit;
        urlImagen = url;
        descripcion = desc;
        popularidad = pop;
        idCategoria = idCat;
    }

    // Getters
    int getIdPin() const {
        return idPin;
    }

    string getTitulo() const {
        return titulo;
    }

    string getUrlImagen() const {
        return urlImagen;
    }

    string getDescripcion() const {
        return descripcion;
    }

    int getPopularidad() const {
        return popularidad;
    }

    int getIdCategoria() const {
        return idCategoria;
    }

    // Setters
    void setIdPin(int id) {
        idPin = id;
    }

    void setTitulo(string tit) {
        titulo = tit;
    }

    void setUrlImagen(string url) {
        urlImagen = url;
    }

    void setDescripcion(string desc) {
        descripcion = desc;
    }

    void setPopularidad(int pop) {
        popularidad = pop;
    }

    void setIdCategoria(int idCat) {
        idCategoria = idCat;
    }

    // Mostrar informacion
    void mostrarInfo() const {
        cout << "  - Pin #" << idPin << ": " << titulo
            << " | Popularidad: " << popularidad
            << " | Cat: " << idCategoria << "\n";
    }
};

// ==========================================
// 3. ENTIDAD: Tablero
// ==========================================
class Tablero {
private:
    int idTablero;
    string nombre;
    bool esPrivado;
    int idUsuarioPropietario;

public:
    // Constructores
    Tablero() {
        idTablero = 0;
        nombre = "";
        esPrivado = false;
        idUsuarioPropietario = 0;
    }

    Tablero(int id, string nom, bool privado, int idUsuario) {
        idTablero = id;
        nombre = nom;
        esPrivado = privado;
        idUsuarioPropietario = idUsuario;
    }

    // Getters
    int getIdTablero() const {
        return idTablero;
    }

    string getNombre() const {
        return nombre;
    }

    bool getEsPrivado() const {
        return esPrivado;
    }

    int getIdUsuarioPropietario() const {
        return idUsuarioPropietario;
    }

    // Setters
    void setIdTablero(int id) {
        idTablero = id;
    }

    void setNombre(string nom) {
        nombre = nom;
    }

    void setEsPrivado(bool privado) {
        esPrivado = privado;
    }

    void setIdUsuarioPropietario(int idUsuario) {
        idUsuarioPropietario = idUsuario;
    }

    // Mostrar informacion
    void mostrarInfo() const {
        cout << "[Tablero #" << idTablero << "] " << nombre
            << " (Propietario ID: " << idUsuarioPropietario << ")"
            << (esPrivado ? " [Privado]" : " [Publico]") << "\n";
    }
};

// ==========================================
// 4. ENTIDAD: Usuario
// ==========================================
class Usuario {
private:
    int idUsuario;
    string username;
    string email;
    string biografia;

public:
    // Constructores
    Usuario() {
        idUsuario = 0;
        username = "";
        email = "";
        biografia = "";
    }

    Usuario(int id, string user, string mail, string bio) {
        idUsuario = id;
        username = user;
        email = mail;
        biografia = bio;
    }

    // Getters
    int getIdUsuario() const {
        return idUsuario;
    }

    string getUsername() const {
        return username;
    }

    string getEmail() const {
        return email;
    }

    string getBiografia() const {
        return biografia;
    }

    // Setters
    void setIdUsuario(int id) {
        idUsuario = id;
    }

    void setUsername(string user) {
        username = user;
    }

    void setEmail(string mail) {
        email = mail;
    }

    void setBiografia(string bio) {
        biografia = bio;
    }

    // Mostrar informacion
    void mostrarInfo() const {
        cout << "Usuario #" << idUsuario << " (@" << username << ") - " << email << "\n"
            << "Bio: " << biografia << "\n";
    }
};

// ==========================================
// 5. ENTIDAD: Recomendacion
// ==========================================
class Recomendacion {
private:
    int idRecomendacion;
    int idUsuarioDestino;
    Pin pinRecomendado;
    string razon;

public:
    // Constructores
    Recomendacion() {
        idRecomendacion = 0;
        idUsuarioDestino = 0;
        razon = "";
    }

    Recomendacion(int id, int idUsuario, Pin pin, string r) {
        idRecomendacion = id;
        idUsuarioDestino = idUsuario;
        pinRecomendado = pin;
        razon = r;
    }

    // Getters
    int getIdRecomendacion() const {
        return idRecomendacion;
    }

    int getIdUsuarioDestino() const {
        return idUsuarioDestino;
    }

    Pin getPinRecomendado() const {
        return pinRecomendado;
    }

    string getRazon() const {
        return razon;
    }

    // Setters
    void setIdRecomendacion(int id) {
        idRecomendacion = id;
    }

    void setIdUsuarioDestino(int idUsuario) {
        idUsuarioDestino = idUsuario;
    }

    void setPinRecomendado(Pin pin) {
        pinRecomendado = pin;
    }

    void setRazon(string r) {
        razon = r;
    }

    // Mostrar informacion
    void mostrarInfo() const {
        cout << "Recomendacion #" << idRecomendacion << " para Usuario #" << idUsuarioDestino << "\n";
        cout << "Razon: " << razon << "\n";
        pinRecomendado.mostrarInfo();
    }
};

#endif // ENTIDADES_H