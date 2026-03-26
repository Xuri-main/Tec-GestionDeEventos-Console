/**
 * Archivo: archivos.h
 * Descripcion: Declaraciones para la gestion de lectura y escritura de archivos .txt.
 * Autores: Emilio Funes R.
 * Fecha de creación: 25/03/2026
 */

#ifndef ARCHIVOS_H
#define ARCHIVOS_H

// Rutas
#define RUTA_USUARIOS "../data/usuarios.txt"
#define RUTA_SITIOS "../data/sitios.txt"
#define RUTA_EVENTOS "../data/eventos.txt"

void cargarTodosLosDatos();
void guardarTodosLosDatos();
int obtenerCredencialesAdmin(char *usuario, char *clave);

void cargarSitios();
void guardarSitios();
int cargarLoteSitiosDesdeRuta(const char *ruta);

#endif // ARCHIVOS_H