/**
 * Archivo: eventos.h
 * Descripcion: Declaracion de funciones para la gestion de eventos.
 * Autores: Emilio Funes R.
 * Fecha: 26/03/2026
 */

#ifndef EVENTOS_H
#define EVENTOS_H

#include "estructuras.h"
#include "sitios.h"

// Memoria
void inicializarMemoriaEventos(int capacidad_inicial);
void liberarMemoriaEventos();

// Getters
int getCantidadEventos();
Evento* getArregloEventos();

// Agregar
Evento* agregarEvento(const char *nombre, const char *productora, const char *fecha, Sitio *sitio_base);

// Menus y Visualizacion
void gestionEventos();
void estadoEventos();

#endif // EVENTOS_H
