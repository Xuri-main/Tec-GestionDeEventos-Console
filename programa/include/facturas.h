/**
 * Archivo: facturas.h
 * Descripcion: Este archivo contiene las declaraciones de la gestion de facturas.
 * Autores: Ginger Rodríguez G.
 * Fecha: 28/03/2026
 */

#ifndef FACTURAS_H
#define FACTURAS_H

#include "estructuras.h"

// Memoria
// Inicializa la memoria para almacenar facturas.
void inicializarMemoriaFacturas(int capacidad_inicial);
// Libera toda la memoria utilizada por las facturas.
void liberarMemoriaFacturas();

// Getters
// Retorna la cantidad total de facturas registradas.
int getCantidadFacturas();
// Retorna el arreglo de facturas almacenadas.
Factura* getArregloFacturas();

// Acciones
// Agrega una nueva factura con toda la informacion de la compra.
void agregarFactura(const char *fecha_compra, const char *cedula, const char *nombre_cliente, const char *nombre_evento, const char *productora, const char *sitio_evento, const char *fecha_evento, int cantidad_detalles, DetalleFactura *detalles, float subtotal, float costo_servicio, float total);

// Menus

// Muestra en pantalla la lista de facturas registradas.
void gestionListaFacturas();

#endif // FACTURAS_H