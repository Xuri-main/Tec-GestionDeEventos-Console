/**
 * Archivo: sitios.h
 * Descripcion: Declaracion de funciones para la gestion de sitios de eventos.
 * Autores: Jareck Levell C.
 * Fecha de creación: 26/03/2026
 */

#ifndef SITIOS_H
#define SITIOS_H

#include "estructuras.h"

void gestionSitioEventos();

void inicializarMemoriaSitios(int capacidad_inicial);
int registrarSitioEnMemoria(const char *nombre, const char *ubicacion, const char *web, int cant_sectores);
int obtenerCantidadSitios();
Sitio* obtenerArregloSitios();

void liberarMemoriaSitios();

#endif // SITIOS_H