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
void inicializarMemoriaFacturas(int capacidad_inicial);
void liberarMemoriaFacturas();

// Getters
int getCantidadFacturas();
Factura* getArregloFacturas();

// Acciones
void agregarFactura(const char *fecha_compra, const char *cedula, const char *nombre_cliente, const char *nombre_evento, const char *productora, const char *sitio_evento, const char *fecha_evento, int cantidad_detalles, DetalleFactura *detalles, float subtotal, float costo_servicio, float total);

// Menus
void gestionListaFacturas();

#endif // FACTURAS_H