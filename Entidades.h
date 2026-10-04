#pragma once
#include <iostream>
#include <string>

using namespace std;

// ==========================================
// 1. ENTIDAD: Usuario
// ==========================================
class Usuario {
private:
    int idUsuario;
    string nombre;
    string email;

public:
    Usuario() {
        idUsuario = 0;
        nombre = "";
        email = "";
    }

    Usuario(int id, string nom, string mail) {
        idUsuario = id;
        nombre = nom;
        email = mail;
    }

    int getIdUsuario() const { return idUsuario; }
    string getNombre() const { return nombre; }
    string getEmail() const { return email; }

    void setIdUsuario(int id) { idUsuario = id; }
    void setNombre(string nom) { nombre = nom; }
    void setEmail(string mail) { email = mail; }

    void mostrarInfo() const {
        cout << "[Usuario #" << idUsuario << "] "
             << nombre << " | Email: " << email << "\n";
    }
};


// ==========================================
// 2. ENTIDAD: Tablero
// ==========================================
class Tablero {
private:
    int idTablero;
    int idUsuario;
    string nombre;
    bool esPrivado;

public:
    Tablero() {
        idTablero = 0;
        idUsuario = 0;
        nombre = "";
        esPrivado = false;
    }

    Tablero(int id, int idUser, string nom, bool privado) {
        idTablero = id;
        idUsuario = idUser;
        nombre = nom;
        esPrivado = privado;
    }

    int getIdTablero() const { return idTablero; }
    int getIdUsuario() const { return idUsuario; }
    string getNombre() const { return nombre; }
    bool getEsPrivado() const { return esPrivado; }

    void setIdTablero(int id) { idTablero = id; }
    void setIdUsuario(int idUser) { idUsuario = idUser; }
    void setNombre(string nom) { nombre = nom; }
    void setEsPrivado(bool privado) { esPrivado = privado; }

    void mostrarInfo() const {
        cout << "[Tablero #" << idTablero << "] "
             << nombre << " (User ID: " << idUsuario << ") "
             << " | Visibilidad: " << (esPrivado ? "Privado" : "Publico") << "\n";
    }
};


// ==========================================
// 6. ENTIDAD: Pin
// ==========================================
class Pin {
private:
    int idPin;
    string titulo;
    string descripcion;
    int idTablero;
    int idCategoria;
    int popularidad;
    string fechaCreacion;

public:
    Pin() {
        idPin = 0;
        titulo = "";
        descripcion = "";
        idTablero = 0;
        idCategoria = 0;
        popularidad = 0;
        fechaCreacion = "";
    }

    Pin(int id, string tit, string desc, int idTab, int idCat, int pop, string fecha) {
        idPin = id;
        titulo = tit;
        descripcion = desc;
        idTablero = idTab;
        idCategoria = idCat;
        popularidad = pop;
        fechaCreacion = fecha;
    }

    int getIdPin() const { return idPin; }
    string getTitulo() const { return titulo; }
    string getDescripcion() const { return descripcion; }
    int getIdTablero() const { return idTablero; }
    int getIdCategoria() const { return idCategoria; }
    int getPopularidad() const { return popularidad; }
    string getFechaCreacion() const { return fechaCreacion; }

    void setIdPin(int id) { idPin = id; }
    void setTitulo(string tit) { titulo = tit; }
    void setDescripcion(string desc) { descripcion = desc; }
    void setIdTablero(int idTab) { idTablero = idTab; }
    void setIdCategoria(int idCat) { idCategoria = idCat; }
    void setPopularidad(int pop) { popularidad = pop; }
    void setFechaCreacion(string fecha) { fechaCreacion = fecha; }

    void mostrarInfo() const {
        cout << "[Pin #" << idPin << "] "
             << titulo << " | Popularidad: " << popularidad
             << " | Tablero ID: " << idTablero
             << " | Cat ID: " << idCategoria << "\n";
    }
};

// ==========================================
// 7. ENTIDAD: Categoria
// ==========================================
class Categoria {
private:
    int idCategoria;
    string nombre;
    string descripcion;
    int cantidadPines;

public:
    Categoria() {
        idCategoria = 0;
        nombre = "";
        descripcion = "";
        cantidadPines = 0;
    }

    Categoria(int id, string nom, string desc, int cantidad) {
        idCategoria = id;
        nombre = nom;
        descripcion = desc;
        cantidadPines = cantidad;
    }

    int getIdCategoria() const { return idCategoria; }
    string getNombre() const { return nombre; }
    string getDescripcion() const { return descripcion; }
    int getCantidadPines() const { return cantidadPines; }

    void setIdCategoria(int id) { idCategoria = id; }
    void setNombre(string nom) { nombre = nom; }
    void setDescripcion(string desc) { descripcion = desc; }
    void setCantidadPines(int cantidad) { cantidadPines = cantidad; }

    void mostrarInfo() const {
        cout << "[Categoria #" << idCategoria << "] "
            << nombre << " - " << descripcion
            << " | Pines: " << cantidadPines << "\n";
    }
};

// ==========================================
// 11. ENTIDAD: Recomendacion
// ==========================================
class Recomendacion {
private:
    int idRecomendacion;
    int idUsuario;
    int idPin;
    float puntuacion;

public:
    Recomendacion() {
        idRecomendacion = 0;
        idUsuario = 0;
        idPin = 0;
        puntuacion = 0.0f;
    }

    Recomendacion(int id, int idUser, int idP, float punt) {
        idRecomendacion = id;
        idUsuario = idUser;
        idPin = idP;
        puntuacion = punt;
    }

    int getIdRecomendacion() const { return idRecomendacion; }
    int getIdUsuario() const { return idUsuario; }
    int getIdPin() const { return idPin; }
    float getPuntuacion() const { return puntuacion; }

    void setIdRecomendacion(int id) { idRecomendacion = id; }
    void setIdUsuario(int idUser) { idUsuario = idUser; }
    void setIdPin(int idP) { idPin = idP; }
    void setPuntuacion(float punt) { puntuacion = punt; }

    void mostrarInfo() const {
        cout << "[Recomendacion #" << idRecomendacion << "] "
             << "Usuario: " << idUsuario
             << " | Pin: " << idPin
             << " | Score: " << puntuacion << "\n";
    }
};


// ==========================================
// 12. ENTIDAD: HistorialBusqueda
// ==========================================
class HistorialBusqueda {
private:
    int idHistorial;
    int idUsuario;
    string terminoBuscado;
    string fecha;

public:
    HistorialBusqueda() {
        idHistorial = 0;
        idUsuario = 0;
        terminoBuscado = "";
        fecha = "";
    }

    HistorialBusqueda(int id, int idUser, string termino, string fec) {
        idHistorial = id;
        idUsuario = idUser;
        terminoBuscado = termino;
        fecha = fec;
    }

    int getIdHistorial() const { return idHistorial; }
    int getIdUsuario() const { return idUsuario; }
    string getTerminoBuscado() const { return terminoBuscado; }
    string getFecha() const { return fecha; }

    void setIdHistorial(int id) { idHistorial = id; }
    void setIdUsuario(int idUser) { idUsuario = idUser; }
    void setTerminoBuscado(string termino) { terminoBuscado = termino; }
    void setFecha(string fec) { fecha = fec; }

    void mostrarInfo() const {
        cout << "[Historial #" << idHistorial << "] "
             << "Usuario ID: " << idUsuario
             << " | Busqueda: " << terminoBuscado
             << " | Fecha: " << fecha << "\n";
    }
};


// ==========================================
// 13. ENTIDAD: PreferenciaUsuario
// ==========================================
class PreferenciaUsuario {
private:
    int idPreferencia;
    int idUsuario;
    int idCategoria;
    int nivelInteres;

public:
    PreferenciaUsuario() {
        idPreferencia = 0;
        idUsuario = 0;
        idCategoria = 0;
        nivelInteres = 0;
    }

    PreferenciaUsuario(int id, int idUser, int idCat, int nivel) {
        idPreferencia = id;
        idUsuario = idUser;
        idCategoria = idCat;
        nivelInteres = nivel;
    }

    int getIdPreferencia() const { return idPreferencia; }
    int getIdUsuario() const { return idUsuario; }
    int getIdCategoria() const { return idCategoria; }
    int getNivelInteres() const { return nivelInteres; }

    void setIdPreferencia(int id) { idPreferencia = id; }
    void setIdUsuario(int idUser) { idUsuario = idUser; }
    void setIdCategoria(int idCat) { idCategoria = idCat; }
    void setNivelInteres(int nivel) { nivelInteres = nivel; }

    void mostrarInfo() const {
        cout << "[Preferencia #" << idPreferencia << "] "
             << "Usuario ID: " << idUsuario
             << " | Categoria ID: " << idCategoria
             << " | Nivel de interes: " << nivelInteres << "/10\n";
    }
};


// ==========================================
// 14. ENTIDAD: TendenciaDiaria
// ==========================================
class TendenciaDiaria {
private:
    int idTendencia;
    int idCategoria;
    int totalInteracciones;
    string fecha;

public:
    TendenciaDiaria() {
        idTendencia = 0;
        idCategoria = 0;
        totalInteracciones = 0;
        fecha = "";
    }

    TendenciaDiaria(int id, int idCat, int total, string fec) {
        idTendencia = id;
        idCategoria = idCat;
        totalInteracciones = total;
        fecha = fec;
    }

    int getIdTendencia() const { return idTendencia; }
    int getIdCategoria() const { return idCategoria; }
    int getTotalInteracciones() const { return totalInteracciones; }
    string getFecha() const { return fecha; }

    void setIdTendencia(int id) { idTendencia = id; }
    void setIdCategoria(int idCat) { idCategoria = idCat; }
    void setTotalInteracciones(int total) { totalInteracciones = total; }
    void setFecha(string fec) { fecha = fec; }

    void mostrarInfo() const {
        cout << "[Tendencia #" << idTendencia << "] "
             << "Categoria ID: " << idCategoria
             << " | Interacciones: " << totalInteracciones
             << " | Fecha: " << fecha << "\n";
    }
};


// ==========================================
// 15. ENTIDAD: SimilitudPin
// ==========================================
class SimilitudPin {
private:
    int idSimilitud;
    int idPinA;
    int idPinB;
    float porcentajeSimilitud;

public:
    SimilitudPin() {
        idSimilitud = 0;
        idPinA = 0;
        idPinB = 0;
        porcentajeSimilitud = 0.0f;
    }

    SimilitudPin(int id, int pinA, int pinB, float porcentaje) {
        idSimilitud = id;
        idPinA = pinA;
        idPinB = pinB;
        porcentajeSimilitud = porcentaje;
    }

    int getIdSimilitud() const { return idSimilitud; }
    int getIdPinA() const { return idPinA; }
    int getIdPinB() const { return idPinB; }
    float getPorcentajeSimilitud() const { return porcentajeSimilitud; }

    void setIdSimilitud(int id) { idSimilitud = id; }
    void setIdPinA(int pinA) { idPinA = pinA; }
    void setIdPinB(int pinB) { idPinB = pinB; }
    void setPorcentajeSimilitud(float porcentaje) { porcentajeSimilitud = porcentaje; }

    void mostrarInfo() const {
        cout << "[Similitud #" << idSimilitud << "] "
             << "Pin A: " << idPinA
             << " | Pin B: " << idPinB
             << " | Similitud: " << porcentajeSimilitud << "%\n";
    }
};

// ==========================================
// 8. ENTIDAD: Etiqueta
// ==========================================
class Etiqueta {
private:
    int idEtiqueta;
    string nombre;
    int idPin;

public:
    Etiqueta() {
        idEtiqueta = 0;
        nombre = "";
        idPin = 0;
    }

    Etiqueta(int id, string nom, int idP) {
        idEtiqueta = id;
        nombre = nom;
        idPin = idP;
    }

    int getIdEtiqueta() const { return idEtiqueta; }
    string getNombre() const { return nombre; }
    int getIdPin() const { return idPin; }

    void setIdEtiqueta(int id) { idEtiqueta = id; }
    void setNombre(string nom) { nombre = nom; }
    void setIdPin(int idP) { idPin = idP; }

    void mostrarInfo() const {
        cout << "[Etiqueta #" << idEtiqueta << "] "
             << nombre
             << " | Pin ID: " << idPin << "\n";
    }
};


// ==========================================
// 9. ENTIDAD: Comentario
// ==========================================
class Comentario {
private:
    int idComentario;
    int idPin;
    int idUsuario;
    string texto;
    string fecha;

public:
    Comentario() {
        idComentario = 0;
        idPin = 0;
        idUsuario = 0;
        texto = "";
        fecha = "";
    }

    Comentario(int id, int idP, int idUser, string txt, string fec) {
        idComentario = id;
        idPin = idP;
        idUsuario = idUser;
        texto = txt;
        fecha = fec;
    }

    int getIdComentario() const { return idComentario; }
    int getIdPin() const { return idPin; }
    int getIdUsuario() const { return idUsuario; }
    string getTexto() const { return texto; }
    string getFecha() const { return fecha; }

    void setIdComentario(int id) { idComentario = id; }
    void setIdPin(int idP) { idPin = idP; }
    void setIdUsuario(int idUser) { idUsuario = idUser; }
    void setTexto(string txt) { texto = txt; }
    void setFecha(string fec) { fecha = fec; }

    void mostrarInfo() const {
        cout << "[Comentario #" << idComentario << "] "
             << "Pin ID: " << idPin
             << " | Usuario ID: " << idUsuario
             << " | Texto: " << texto
             << " | Fecha: " << fecha << "\n";
    }
};


// ==========================================
// 10. ENTIDAD: Interaccion
// ==========================================
class Interaccion {
private:
    int idInteraccion;
    int idPin;
    int idUsuario;
    string tipo;
    string fecha;

public:
    Interaccion() {
        idInteraccion = 0;
        idPin = 0;
        idUsuario = 0;
        tipo = "";
        fecha = "";
    }

    Interaccion(int id, int idP, int idUser, string tip, string fec) {
        idInteraccion = id;
        idPin = idP;
        idUsuario = idUser;
        tipo = tip;
        fecha = fec;
    }

    int getIdInteraccion() const { return idInteraccion; }
    int getIdPin() const { return idPin; }
    int getIdUsuario() const { return idUsuario; }
    string getTipo() const { return tipo; }
    string getFecha() const { return fecha; }

    void setIdInteraccion(int id) { idInteraccion = id; }
    void setIdPin(int idP) { idPin = idP; }
    void setIdUsuario(int idUser) { idUsuario = idUser; }
    void setTipo(string tip) { tipo = tip; }
    void setFecha(string fec) { fecha = fec; }

    void mostrarInfo() const {
        cout << "[Interaccion #" << idInteraccion << "] "
             << "Pin ID: " << idPin
             << " | Usuario ID: " << idUsuario
             << " | Tipo: " << tipo
             << " | Fecha: " << fecha << "\n";
    }
};

// ==========================================
// 3. ENTIDAD: Perfil (Persona 1)
// ==========================================
class Perfil {
private:
    int idPerfil;
    int idUsuario;
    string biografia;
    string fotoPerfil;
    int cantidadSeguidores;

public:
    Perfil() {
        idPerfil = 0;
        idUsuario = 0;
        biografia = "";
        fotoPerfil = "";
        cantidadSeguidores = 0;
    }

    Perfil(int id, int idUser, string bio, string foto, int seguidores) {
        idPerfil = id;
        idUsuario = idUser;
        biografia = bio;
        fotoPerfil = foto;
        cantidadSeguidores = seguidores;
    }

    int getIdPerfil() const { return idPerfil; }
    int getIdUsuario() const { return idUsuario; }
    string getBiografia() const { return biografia; }
    string getFotoPerfil() const { return fotoPerfil; }
    int getCantidadSeguidores() const { return cantidadSeguidores; }

    void setIdPerfil(int id) { idPerfil = id; }
    void setIdUsuario(int idUser) { idUsuario = idUser; }
    void setBiografia(string bio) { biografia = bio; }
    void setFotoPerfil(string foto) { fotoPerfil = foto; }
    void setCantidadSeguidores(int seguidores) { cantidadSeguidores = seguidores; }

    void mostrarInfo() const {
        cout << "[Perfil #" << idPerfil << "] "
             << "Usuario ID: " << idUsuario
             << " | Seguidores: " << cantidadSeguidores
             << " | Bio: " << biografia << "\n";
    }
};

// ==========================================
// 4. ENTIDAD: Seguidor (Persona 1)
// ==========================================
class Seguidor {
private:
    int idSeguidor;
    int idUsuarioQueSigue;
    int idUsuarioSeguido;
    string fechaInicio;

public:
    Seguidor() {
        idSeguidor = 0;
        idUsuarioQueSigue = 0;
        idUsuarioSeguido = 0;
        fechaInicio = "";
    }

    Seguidor(int id, int usuarioQueSigue, int usuarioSeguido, string fecha) {
        idSeguidor = id;
        idUsuarioQueSigue = usuarioQueSigue;
        idUsuarioSeguido = usuarioSeguido;
        fechaInicio = fecha;
    }

    int getIdSeguidor() const { return idSeguidor; }
    int getIdUsuarioQueSigue() const { return idUsuarioQueSigue; }
    int getIdUsuarioSeguido() const { return idUsuarioSeguido; }
    string getFechaInicio() const { return fechaInicio; }

    void setIdSeguidor(int id) { idSeguidor = id; }
    void setIdUsuarioQueSigue(int idUsuario) { idUsuarioQueSigue = idUsuario; }
    void setIdUsuarioSeguido(int idUsuario) { idUsuarioSeguido = idUsuario; }
    void setFechaInicio(string fecha) { fechaInicio = fecha; }

    void mostrarInfo() const {
        cout << "[Seguidor #" << idSeguidor << "] "
             << "Usuario " << idUsuarioQueSigue
             << " sigue a Usuario " << idUsuarioSeguido
             << " | Desde: " << fechaInicio << "\n";
    }
};

// ==========================================
// 5. ENTIDAD: Notificacion (Persona 1)
// ==========================================
class Notificacion {
private:
    int idNotificacion;
    int idUsuario;
    string mensaje;
    bool leida;
    string fecha;

public:
    Notificacion() {
        idNotificacion = 0;
        idUsuario = 0;
        mensaje = "";
        leida = false;
        fecha = "";
    }

    Notificacion(int id, int idUser, string msg, bool estaLeida, string fec) {
        idNotificacion = id;
        idUsuario = idUser;
        mensaje = msg;
        leida = estaLeida;
        fecha = fec;
    }

    int getIdNotificacion() const { return idNotificacion; }
    int getIdUsuario() const { return idUsuario; }
    string getMensaje() const { return mensaje; }
    bool getLeida() const { return leida; }
    string getFecha() const { return fecha; }

    void setIdNotificacion(int id) { idNotificacion = id; }
    void setIdUsuario(int idUser) { idUsuario = idUser; }
    void setMensaje(string msg) { mensaje = msg; }
    void setLeida(bool estaLeida) { leida = estaLeida; }
    void setFecha(string fec) { fecha = fec; }

    void mostrarInfo() const {
        cout << "[Notificacion #" << idNotificacion << "] "
             << "Usuario ID: " << idUsuario
             << " | " << mensaje
             << " | Estado: " << (leida ? "Leida" : "Pendiente")
             << " | Fecha: " << fecha << "\n";
    }
};
