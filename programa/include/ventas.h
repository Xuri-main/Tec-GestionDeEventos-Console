/**
 * Archivo: ventas.h
 * Descripcion: Declaracion de funciones para la gestion de ventas y consultas.
 * Autores: Ginger Rodríguez G.
 * Fecha: 27/03/2026
 */

#ifndef VENTAS_H
#define VENTAS_H

#include "estructuras.h"
#include "eventos.h"

int compararFechas(const char *fecha_evento, const char *fecha_inicial);

// Menus
void consultaPorEvento();
void compraDeBoletos();

#endif // VENTAS_H