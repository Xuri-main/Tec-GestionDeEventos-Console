/**
 * Archivo: sitios.h
 * Descripcion: Declaracion de funciones para la gestion de sitios de eventos.
 * Autores: Jareck Levell C.
 * Fecha de creación: 26/03/2026
 */

#ifndef SITIOS_H
#define SITIOS_H

#include "estructuras.h"

// Memoria
void inicializarMemoriaSitios(int capacidad_inicial);
void liberarMemoriaSitios();

// Getters y Busqueda
int getCantidadSitios();
Sitio* getArregloSitios();
int existeSitio(const char *nombre);
Sitio* obtenerSitioPorNombre(const char *nombre);

// Agregar y Modificar
int agregarSitio(const char *nombre, const char *ubicacion, const char *web, int cant_sectores);
int agregarSectorASitio(int indiceSitio, const char *nombreSector, char inicial, int cantidad);
char* crearIdentificadorAsiento(char inicial, int numero);
void resetearSectores(int indiceSitio);

// Menus y Visualizacion
void gestionSitioEventos();
void mostrarSitios();
void gestionEspaciosEventos();
void mostrarSectoresDeSitio(int indiceSitio);

#endif // SITIOS_H