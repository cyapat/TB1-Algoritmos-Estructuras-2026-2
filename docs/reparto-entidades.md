# Reparto inicial de entidades - Pinterest

Este reparto sale del documento de entidades enviado para el sistema tipo Pinterest. La idea es que cada integrante avance 5 entidades y luego se integren en una sola aplicacion de consola.

## Persona 1 - Usuarios y tableros

1. Usuario
   - idUsuario: int
   - nombre: string
   - username: string
   - correo: string
   - fechaRegistro: string

2. Tablero
   - idTablero: int
   - nombre: string
   - idUsuario: int
   - descripcion: string
   - esPublico: bool
   - cantidadPines: int
   - fechaCreacion: string

3. Perfil
   - idPerfil: int
   - idUsuario: int
   - biografia: string
   - fotoPerfil: string
   - cantidadSeguidores: int

4. Seguidor
   - idSeguidor: int
   - idUsuarioQueSigue: int
   - idUsuarioSeguido: int
   - fechaInicio: string

5. Notificacion
   - idNotificacion: int
   - idUsuario: int
   - mensaje: string
   - leida: bool
   - fecha: string

## Persona 2 - Pines y categoria

6. Pin
   - idPin: int
   - titulo: string
   - descripcion: string
   - idTablero: int
   - idCategoria: int
   - popularidad: int
   - fechaCreacion: string

7. Categoria
   - idCategoria: int
   - nombre: string
   - descripcion: string
   - cantidadPines: int

8. Etiqueta
   - idEtiqueta: int
   - nombre: string
   - idPin: int

9. Comentario
   - idComentario: int
   - idPin: int
   - idUsuario: int
   - texto: string
   - fecha: string

10. Interaccion
    - idInteraccion: int
    - idPin: int
    - idUsuario: int
    - tipo: string
    - fecha: string

## Persona 3 - Recomendaciones

11. Recomendacion
    - idRecomendacion: int
    - idPinRecomendado: int
    - idUsuarioDestino: int
    - motivo: string
    - vista: bool
    - prioridad: int

12. HistorialBusqueda
    - idHistorial: int
    - idUsuario: int
    - terminoBuscado: string
    - fecha: string

13. PreferenciaUsuario
    - idPreferencia: int
    - idUsuario: int
   - idCategoria: int
    - nivelInteres: int

14. TendenciaDiaria
    - idTendencia: int
    - idCategoria: string
    - totalInteracciones: int
    - fecha: string

15. SimilitudPin
    - idSimilitud: int
    - idPinA: int
    - idPinB: int
    - porcentajeSimilitud: float

## Integracion minima esperada

- Tableros: lista simple.
- Categorias: lista doble.
- Recomendaciones: cola.
- Popularidad: MergeSort aplicado a pines o tendencias.
- Similitud: metodo recursivo sobre pines, etiquetas o categorias.
- Persistencia: archivos en la carpeta `data/`.
