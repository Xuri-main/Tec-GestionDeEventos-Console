/**
 * Archivo: estructuras.h
 * Descripcion: Este archivo contiene las definiciones de las estructuras de datos utilizadas en el programa de gestión de eventos.
 * Autores: Emilio Funes R. & Ginger Rodríguez G.
 * Fecha de creación: 20/03/2026
 */

#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

// Asiento
typedef struct {
    char identificador[10]; // "V1", "V2" (Inicial del sector)
    int vendido;            // 0 = Disponible, 1 = Vendido
} Asiento;

// Sector
typedef struct {
    char nombre[50];        // "VIP", "General"
    char inicial;           // 'V', 'G'
    int cantidad_espacios;  
    float precio; 
    float recaudado;        // Total de dinero recaudado por sector
    Asiento *asientos;      // Puntero, Arreglo dinámico
} Sector;

// Sitio de Eventos
typedef struct {
    char nombre[50];
    char ubicacion[100];
    char sitio_web[100];
    int cantidad_sectores;
    Sector *sectores;       // Puntero, Arreglo dinámico
} Sitio;

// 4. Estructura para el Evento
typedef struct {
    char nombre[100];
    char productora[100];
    char fecha[20];         // Formato DD/MM/AAAA
    Sitio *sitio_base;      // Puntero al sitio donde se realizará
    int cantidad_sectores_evento;
    Sector *sectores_evento; // Arreglo dinámico de sectores exclusivo para este evento
} Evento;

// Factura
typedef struct {
    int id_factura;
    char fecha_compra[20];
    char cedula_cliente[20];
    char nombre_cliente[100];
    char nombre_evento[100];
    float subtotal;
    float costo_servicio;   // 5% del subtotal
    float total;
} Factura;

#endif // ESTRUCTURAS_H