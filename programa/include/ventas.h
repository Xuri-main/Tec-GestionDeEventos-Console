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

/*Compara dos fechas y retorna 1 si la del evento es igual o posterior*/
int compararFechas(const char *fecha_evento, const char *fecha_inicial);

// Menus
/*Permite consultar eventos a partir de una fecha ingresada*/
void consultaPorEvento();
/*Permite realizar la compra de boletos para eventos futuros*/
void compraDeBoletos();

#endif // VENTAS_H