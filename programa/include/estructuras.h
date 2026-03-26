/**
 * Archivo: estructuras.h
 * Descripcion: Este archivo contiene las definiciones de las estructuras de datos utilizadas en 
 *              el programa de gestión de eventos.
 * Autores: Emilio Funes R. & Ginger Rodríguez G.
 * Fecha de creación: 20/03/2026
 */

#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

// Asiento
typedef struct {
    char *identificador;    // "V1", "V2"
    int vendido;            // 0 = Disponible, 1 = Vendido
} Asiento;

// Sector
typedef struct {
    char *nombre;           // "VIP", "General"
    char inicial;           // 'V', 'G'
    int cantidad_espacios;  
    float precio; 
    float recaudado;        
    Asiento *asientos;
} Sector;

// Sitio de Eventos
typedef struct {
    char *nombre;
    char *ubicacion;    
    char *sitio_web;
    int cantidad_sectores;
    Sector *sectores;
} Sitio;

// Evento
typedef struct {
    char *nombre;
    char *productora;
    char *fecha;
    Sitio *sitio_base;
    int cantidad_sectores_evento;
    Sector *sectores_evento;
} Evento;

// Factura
typedef struct {
    int id_factura;
    char *fecha_compra;
    char *cedula_cliente;
    char *nombre_cliente;
    char *nombre_evento;
    float subtotal;
    float costo_servicio;
    float total;
} Factura;

#endif // ESTRUCTURAS_H